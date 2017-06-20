/*
 * websocket_handler.cpp
 *
 *  Created on: 17 Jun 2017
 *      Author: gijs
 */

#include "websocket_handler.h"
#include <map>
#include <iostream>
#include <chrono>
#include <string>
#include <cstring>
#include <memory>
#include <utility>
#include <cstdlib>
#include <restbed>
#include <system_error>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

using namespace std;
using namespace restbed;
using namespace std::chrono;

Car *car;
pthread_mutex_t checker_lock = PTHREAD_MUTEX_INITIALIZER;
shared_ptr< Service > service = nullptr;

map< string, shared_ptr< WebSocket > > sockets = { };

string base64_encode( const unsigned char* input, int length )
{
    BIO* bmem, *b64;
    BUF_MEM* bptr;

    b64 = BIO_new( BIO_f_base64( ) );
    bmem = BIO_new( BIO_s_mem( ) );
    b64 = BIO_push( b64, bmem );
    BIO_write( b64, input, length );
    ( void ) BIO_flush( b64 );
    BIO_get_mem_ptr( b64, &bptr );

    char* buff = ( char* )malloc( bptr->length );
    memcpy( buff, bptr->data, bptr->length - 1 );
    buff[ bptr->length - 1 ] = 0;

    BIO_free_all( b64 );

    return buff;
}

multimap< string, string > build_websocket_handshake_response_headers( const shared_ptr< const Request >& request )
{
    auto key = request->get_header( "Sec-WebSocket-Key" );
    key.append( "258EAFA5-E914-47DA-95CA-C5AB0DC85B11" );

    Byte hash[ SHA_DIGEST_LENGTH ];
    SHA1( reinterpret_cast< const unsigned char* >( key.data( ) ), key.length( ), hash );

    multimap< string, string > headers;
    headers.insert( make_pair( "Upgrade", "websocket" ) );
    headers.insert( make_pair( "Connection", "Upgrade" ) );
    headers.insert( make_pair( "Sec-WebSocket-Accept", base64_encode( hash, SHA_DIGEST_LENGTH ) ) );

    return headers;
}

void ping_handler( void )
{
    for ( auto entry : sockets )
    {
        auto key = entry.first;
        auto socket = entry.second;

        if ( socket->is_open( ) )
        {
            socket->send( WebSocketMessage::PING_FRAME );
        }
        else
        {
            socket->close( );
        }
    }
}

void close_handler( const shared_ptr< WebSocket > socket )
{
    if ( socket->is_open( ) )
    {
        auto response = make_shared< WebSocketMessage >( WebSocketMessage::CONNECTION_CLOSE_FRAME, Bytes( { 10, 00 } ) );
        socket->send( response );
    }

    const auto key = socket->get_key( );
    sockets.erase( key );

    fprintf( stderr, "Closed connection to %s.\n", key.data( ) );
}

void error_handler( const shared_ptr< WebSocket > socket, const error_code error )
{
    const auto key = socket->get_key( );
    fprintf( stderr, "WebSocket Errored '%s' for %s.\n", error.message( ).data( ), key.data( ) );
}

void message_handler( const shared_ptr< WebSocket > source, const shared_ptr< WebSocketMessage > message )
{
    const auto opcode = message->get_opcode( );

    if ( opcode == WebSocketMessage::PING_FRAME )
    {
        auto response = make_shared< WebSocketMessage >( WebSocketMessage::PONG_FRAME, message->get_data( ) );
        source->send( response );
    }
    else if ( opcode == WebSocketMessage::PONG_FRAME )
    {
        //Ignore PONG_FRAME.
        //
        //Every time the ping_handler is scheduled to run, it fires off a PING_FRAME to each
        //WebSocket. The client, if behaving correctly, will respond with a PONG_FRAME.
        //
        //On each occasion the underlying TCP socket sees any packet data transfer, whether
        //a PING, PONG, TEXT, or BINARY... frame. It will automatically reset the timeout counter
        //leaving the connection active; see also Settings::set_connection_timeout.
        return;
    }
    else if ( opcode == WebSocketMessage::CONNECTION_CLOSE_FRAME )
    {
        source->close( );
    }
    else if ( opcode == WebSocketMessage::BINARY_FRAME )
    {
        //We don't support binary data.
        auto response = make_shared< WebSocketMessage >( WebSocketMessage::CONNECTION_CLOSE_FRAME, Bytes( { 10, 03 } ) );
        source->send( response );
    }
    else if ( opcode == WebSocketMessage::TEXT_FRAME )
    {
        auto response = make_shared< WebSocketMessage >( *message );
        response->set_mask( 0 );

        for ( auto socket : sockets )
        {
            auto destination = socket.second;
            destination->send( response );
        }

        const auto key = source->get_key( );
        const auto data = String::format( "Received message '%.*s' from %s\n", message->get_data( ).size( ), message->get_data( ).data( ), key.data( ) );
        fprintf( stderr, "%s", data.data( ) );
    }
}

void get_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    const auto connection_header = request->get_header( "connection", String::lowercase );

    if ( connection_header.find( "upgrade" ) not_eq string::npos )
    {
        if ( request->get_header( "upgrade", String::lowercase ) == "websocket" )
        {
            const auto headers = build_websocket_handshake_response_headers( request );

            session->upgrade( SWITCHING_PROTOCOLS, headers, [ ]( const shared_ptr< WebSocket > socket )
            {
                if ( socket->is_open( ) )
                {
                    socket->set_close_handler( close_handler );
                    socket->set_error_handler( error_handler );
                    socket->set_message_handler( message_handler );

                    socket->send( "Welcome to Corvusoft Chat!", [ ]( const shared_ptr< WebSocket > socket )
                    {
                        const auto key = socket->get_key( );
                        sockets.insert( make_pair( key, socket ) );
                        car->setEnabled(1);

                        fprintf( stderr, "Sent welcome message to %s.\n", key.data( ) );
                    } );
                }
                else
                {
                    fprintf( stderr, "WebSocket Negotiation Failed: Client closed connection.\n" );
                }
            } );

            return;
        }
    }

    session->close( BAD_REQUEST );
}

void* connectionChecker(void* params) {
	Car *car = (Car*) params;
	while(1) {
		if (pthread_mutex_lock(&checker_lock) != 0) {
			cout << "Sockethandler: Could not get a lock on the queue" << endl;
		}
		if (car->getEnabled() != 0 && sockets.size() == 0) {
			cout << "No connections car stopped" << endl;
			car->setEnabled(0);
		}
		if (pthread_mutex_unlock(&checker_lock) != 0) {
			cout << "Sockethandler: Could not unlock the queue" << endl;
		}
	}
	return NULL;
}

websocket_handler::websocket_handler(Car *carP) {
	car = carP;
	this->resource = make_shared< Resource >( );
	this->resource->set_path( "/chat" );
	this->resource->set_method_handler( "GET", get_method_handler );
	pthread_t checker;
	pthread_create(&checker, NULL, connectionChecker, car);

}

shared_ptr<Resource> websocket_handler::getResource() {
	return this->resource;
}


