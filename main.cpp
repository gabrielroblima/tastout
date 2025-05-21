#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "TastoutCimg.hpp"
#include "../CImg/CImg.h"

#define VERSION "v0.0.2"

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
	cimg_library::CImg<CImg_t> physicalCurve(samples);
	
	//! Defines a seed to rand function
	srand(time(NULL));
	
	//! Creates a vector to store received Data from tattoed data
	cimg_library::CImg<dataType> receivedData;
	
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
	cimg_library::CImg<dataType> physicalInfo(4);
	physicalInfo.fill(growTime, decayTime, maxValue, minValue);
	
	TastoutCimg<CImg_t, dataType> tastout;
	
	//! Initializes CImg to store curves
	cimg_library::CImg<CImg_t> gather(samples, 2);
	
	//! Stores the curve without tattoo
	gather.get_shared_row(0) = physicalCurve;
	cimg_library::CImg<CImg_t> difference = physicalCurve;
	
	//! Tattoos the curve
	if(tastout.writeCImg(physicalCurve, physicalInfo) != TASTOUT::SUCCESS) return EXIT_FAILURE;
	
	//! Stores the tattooed curve 
	gather.get_shared_row(1) =  physicalCurve;
	difference = physicalCurve - difference; 
	
	#if cimg_display
	if(show)
	{	
		//! Note: most of differences between before and after tattooing signals are going to be in the first elements of CImg
		gather.transpose().display_graph("Superposed before and after tattooing signals", 1, 1);
		difference.display_graph("Difference between before and after tattooing signals");
	}else
	{
		std::cout << "Non tattooed data" << std::endl;
		gather.get_shared_row(0).print();
		std::cout << "Tattooed data" << std::endl;
		gather.get_shared_row(1).print();
	}
	#endif
	
	if(tastout.readCImg(physicalCurve, receivedData) != TASTOUT::SUCCESS) return EXIT_FAILURE;

	receivedData.print();
	
	return EXIT_SUCCESS;
}
