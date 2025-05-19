#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "Tastout.hpp"
#include "../CImg/CImg.h"

#define VERSION "v0.0.1"

typedef uint16_t dataType;
typedef uint16_t CImg_t;

#define MAX_SIZE 65535

int main(int argc, char** argv)
{
	//command arguments, i.e. CLI option
	cimg_usage(("Creates a graph, tattoos growing time, decay time, min and max values into this CImg Graph. The data is untattooed and info is displayed.\n" \
			   "It uses different GNU libraries (see --info option)\n\n" \
	           "usage: ./tastout -h -I\n" \
			   "       ./tastout -n 16348 -g 8192 -l 2000 \n" \
			   "\n version: "+std::string(VERSION)+"\n compilation date:" \
    ).c_str());//cimg_usage
    
		const int samples = cimg_option("-n", 8192, "Number of points in graph");
		const dataType growTime = cimg_option("-g", samples/2, "Number of points of growing");
		const dataType decayTime = cimg_option("-d", samples-growTime, "Number of points of growing");
		const dataType maxValue = cimg_option("-M", 65535, "Max value of exponential");
		const dataType minValue = cimg_option("-m", 0, "Minimal value of exponential");
		const bool show = cimg_option("-s", true, "Enables and disables display");
    
	///standard options
	const bool show_h = cimg_option("-h",    false,NULL);//-h hidden option
    bool show_help=		cimg_option("--help",show_h,"help (or -h option)");show_help=show_h|show_help; //same --help or -h option
	bool show_info= 	cimg_option("-I",false,NULL);//-I hidden option
	if( cimg_option("--info",show_info,"show compilation options (or -I option)") ) {show_info=true;cimg_library::cimg::info();}//same --info or -I option
	bool show_version=cimg_option("-v",false,NULL);//-v hidden option
	if( cimg_option("--version",show_version,"show version (or -v option)") ) {show_version=true;std::cout<<VERSION<<std::endl;return 0;}//same --version or -v option
	if(show_help) {/*print_help(std::cerr);*/return EXIT_SUCCESS;}
	//}CLI option
	
	//! Creates a Cimg object to save a physicalCurve, that's why it has only one dimension
	cimg_library::CImg<CImg_t> physicalCurve(samples, 1, 1, 1, 0);
	
	srand(time(NULL));
	//! Fills physicalCurve with a peak curve. It grows until growTime and decays until the end of physicalCurve elements
	cimg_forX(physicalCurve, x)
	{
		if(x < growTime)
		{
			physicalCurve(x) = minValue + static_cast<CImg_t>(maxValue * exp(x-growTime));
		}else
		{
			physicalCurve(x) = minValue + static_cast<CImg_t>(maxValue * exp(growTime-x));
		}
	}

	//! Data to be tattooed in graph
	dataType physicalInfo[] = {growTime, decayTime, maxValue, minValue};
	
	Tastout<CImg_t, dataType> tastout;
	
	cimg_library::CImg<CImg_t> rawPhysicalCurve(samples, 1, 1, 1, 0);
	rawPhysicalCurve = physicalCurve;
	
	if(tastout.write(physicalCurve.data(), physicalCurve.size(), physicalInfo, 4) != TASTOUT::SUCCESS) return EXIT_FAILURE;
	
	#if cimg_display
	if(show)
	{	
		//! CImg display to show curves before and after tattoo
		cimg_library::CImgDisplay physicalCurveBefore(640, 480, "Physical curve before tattoo");
		cimg_library::CImgDisplay physicalCurveAfter(640, 480, "Physical curve after tattoo");

		//! Draws curves into cimgDisplay
		rawPhysicalCurve.display_graph(physicalCurveBefore);
		physicalCurve.display_graph(physicalCurveAfter);
		while (!physicalCurveBefore.is_closed() && !physicalCurveAfter.is_closed() && !physicalCurveBefore.is_keyESC() && !physicalCurveAfter.is_keyESC() && !physicalCurveBefore.is_keyQ() && !physicalCurveAfter.is_keyQ())
		{
			physicalCurveBefore.wait(10);
			physicalCurveAfter.wait(10);
		}
	}else
	{
		std::cout << "Non tattooed data" << std::endl;
		rawPhysicalCurve.print();
		std::cout << "Tattooed data" << std::endl;
		physicalCurve.print();
	}
	#endif
	
	size_t sizeOfReceivedData = 0;
	if(tastout.read(physicalCurve.data(), physicalCurve.size(), sizeOfReceivedData) != TASTOUT::SUCCESS) return EXIT_FAILURE;
	
	const dataType* receivedData = tastout.getRead();
	
	for(int i = 0; i < sizeOfReceivedData; i++)
	{
		std::cout << "Received info = " << receivedData[i] << std::endl;
	}
	
	return EXIT_SUCCESS;
}
