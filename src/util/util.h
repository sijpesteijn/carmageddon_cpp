/*
 * util.h
 *
 *  Created on: 22 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_UTIL_UTIL_H_
#define SRC_UTIL_UTIL_H_

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

using namespace restbed;
using namespace std;

string base64_encode( const unsigned char* input, int length );
multimap< string, string > build_websocket_handshake_response_headers( const shared_ptr< const Request >& request );
void close_handler( const shared_ptr< WebSocket > socket );



#endif /* SRC_UTIL_UTIL_H_ */
