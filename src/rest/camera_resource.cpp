/*
 * camera_resource.cpp
 *
 *  Created on: 17 Jun 2017
 *      Author: gijs
 */

#include "camera_resource.h"
#include <iostream>
#include <fstream>
#include "../util/base64.h"
#include "rest.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "lifeline_handler.h"

using namespace cv;
using namespace std;

Camera *camera;

void get_camera_status_handler( const shared_ptr< Session > session)
{
	const string body = ::to_string(camera->status());
	session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

stringstream serialize(Mat input)
{
    // We will need to also serialize the width, height, type and size of the matrix
    int width = input.cols;
    int height = input.rows;
    int type = input.type();
    size_t size = input.total() * input.elemSize();

    // Initialize a stringstream and write the data
    stringstream ss;
    ss.write((char*)(&width), sizeof(int));
    ss.write((char*)(&height), sizeof(int));
    ss.write((char*)(&type), sizeof(int));
    ss.write((char*)(&size), sizeof(size_t));

    // Write the whole image data
    ss.write((char*)input.data, size);

    return ss;
}

void get_camera_snapshot_handler( const shared_ptr< Session > session)
{
	Mat snapshot = camera->takeSnapshot();
//	 stringstream serializedStream = serialize(snapshot);

	    // Base64 encode the stringstream
//	    string encoded;
//	    string stream = serializedStream.str();
//	 encoded = base64_encode(&stream, stream.length());
	imwrite("bla.jpg", snapshot);
//	snapshot = (snapshot.reshape(0,1)); // to make it continuous
//	int  imgSize = snapshot.total()*snapshot.elemSize();
//	const string body = string(reinterpret_cast<char*>(snapshot.data));
	ifstream stream("bla.jpg", ios::in | ios::binary);
	const string body = string( istreambuf_iterator< char >( stream ), istreambuf_iterator< char >( ) );
//	Size size = snapshot.size();

//	const string body = "";
//	  int total = size.width * size.height * snapshot.channels();
//	  std::cout << "Mat size = " << body << std::endl;

//	  std::vector<uchar> data(snapshot.ptr(), snapshot.ptr() + total);
//	  std::string body(data.begin(), data.end());
	const multimap< string, string > headers
	{
		{ "Content-Type", "image/jpeg" },
		{ "Content-Length", ::to_string( body.length() ) }
	};

	session->close( OK, body, headers );
}

void get_pic_test_handler( const shared_ptr< Session > session)
{
	const auto request = session->get_request( );
	const string filename = request->get_path_parameter( "filename" );

	cout << filename << endl;

	ifstream stream(filename, ios::in | ios::binary);
	if ( stream.is_open() )
	{
		const string body = string( istreambuf_iterator< char >( stream ), istreambuf_iterator< char >( ) );
		const multimap< string, string > headers
		{
			{ "Content-Type", "image/jpeg" },
			{ "Content-Length", ::to_string( body.length( ) ) }
		};
		stream.close();
		session->close( OK, body, headers );
	}
	else
	{
		session->close( NOT_FOUND );
	}
}

camera_resource::camera_resource(Camera *cam) {
	camera = cam;
	this->cameraGetStatusResource->set_path( "/camera/status" );
	this->cameraGetStatusResource->set_method_handler( "GET", get_camera_status_handler );
	this->cameraSnapshotResource->set_path( "/camera/snapshot" );
	this->cameraSnapshotResource->set_method_handler( "GET", get_camera_snapshot_handler );
	this->picTestResource->set_path( "/picTest" );
	this->picTestResource->set_method_handler( "GET", get_pic_test_handler );
}

list<shared_ptr<Resource>> camera_resource::getResources() {
	list<shared_ptr<Resource>> l = { this->cameraSnapshotResource, this->cameraGetStatusResource, this->picTestResource };
	return l;
}

