#include <memory>
#include <cstdlib>
#include <restbed>
#include <iostream>
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "src/domain/car.h"

using namespace std;
using namespace restbed;
using namespace cv;

int edgeThresh = 1;
int edgeThreshScharr=1;
VideoCapture cap(0); // open the video camera no. 0

void post_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    int content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
        session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
    } );
}

void get_method_handler( const shared_ptr< Session > session )
{
	auto then = std::chrono::system_clock::now();
//	bool bSuccess = cap.read(frame); // read a new frame from video
	Mat frame = imread("pic.jpeg", CV_LOAD_IMAGE_UNCHANGED);

	auto now = std::chrono::system_clock::now();
	  auto dur = now - then;
	  typedef std::chrono::duration<float> float_seconds;
	  auto secs = std::chrono::duration_cast<float_seconds>(dur);
	  std::cout << secs.count() << '\n';
	  cv::Size size = frame.size();

	    int total = size.width * size.height * frame.channels();

    const auto request = session->get_request( );

    std::vector<uchar> data(frame.ptr(), frame.ptr() + total);
    std::string body(data.begin(), data.end());
    const multimap< string, string > headers
                {
                    { "Content-Type", "image/jpeg" },
                    { "Content-Length", ::to_string( body.length( ) ) }
                };

                session->close( OK, body, headers );
}

std::string getOsName()
{
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __unix || __unix__
    return "Unix";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #else
    return "Other";
    #endif
}

int main( const int, const char** )
{
	Car car;
	cout << car.status() << endl;
	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	cout << getOsName() << endl;

	auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "POST", post_method_handler );
    resource->set_method_handler( "GET", get_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}
