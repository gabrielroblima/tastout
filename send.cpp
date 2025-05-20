#include <iostream>
#include <cstdlib>
#include "../tcp_zmq/Tcp.hpp"
#include "Tastout.hpp"

#define VERSION "v0.0.1d"

int main(int argc, char** argv)
{
  //command arguments, i.e. CLI option
  cimg_usage(("Send a bunch of CImg data via TCP/IP or stop signal to the receiver.\n" \
  "The CImg data is tattooed (with bit by bit steganography)"\
  "It uses different GNU libraries (see --info option)\n\n" \
  "usage: ./send -h -I\n" \
  "       ./send -x 8192 -y 1 -z 1 -c 1 -a 193.48.111.60\n" \
  "\n version: "+std::string(VERSION)+"\n compilation date:" \
  ).c_str());//cimg_usage

	const unsigned int x = cimg_option("-x", 100, "data width");
	const unsigned int y = cimg_option("-y", 100, "data height");
	const unsigned int z = cimg_option("-z", 1, "data depth");
	const unsigned int c = cimg_option("-c", 1, "data spectrum");
	const bool stop = cimg_option("--stop", false, "stop option, i.e. request receiver to exit");
	const std::string data_port = cimg_option("--data", "5555", "data port");
	const std::string control_port = cimg_option("--control", "5556", "control port");
	const std::string info_port = cimg_option("--info", "5557", "info port");
	const std::string address = cimg_option("-a", "localhost", "address");
	const unsigned send_iterations = cimg_option("-n", 1, "number of data to send");

  ///standard options
  const bool show_h   =cimg_option("-h",    false,NULL);//-h hidden option
        bool show_help=cimg_option("--help",show_h,"help (or -h option)");show_help=show_h|show_help; //same --help or -h option
  bool show_info=cimg_option("-I",false,NULL);//-I hidden option
  if( cimg_option("--info",show_info,"show compilation options (or -I option)") ) {show_info=true;cimg_library::cimg::info();}//same --info or -I option
  bool show_version=cimg_option("-v",false,NULL);//-v hidden option
  if( cimg_option("--version",show_version,"show version (or -v option)") ) {show_version=true;std::cout<<VERSION<<std::endl;return 0;}//same --version or -v option
  if(show_help) {/*print_help(std::cerr);*/return 0;}
  //}CLI option

	//! Defines random seed
	std::srand(time(nullptr));
	
	//! Initializes sender object
	CImgSend<TData> send(address, control_port, info_port, data_port);

	//! Initializes tastout object
	Tastout<TData, TData> tastout;
	
	//! Initializes vector to be tattooed (we'll send only max and min values)
	TData tattoo[2]; 
	
	//! if requested by CLI option, send a stop signal and exit
	if(stop)
	{
		if(send.controlStop() == CImgTcp::sendError) return EXIT_FAILURE;
	}
	
	if(send_iterations < 1) return EXIT_FAILURE;
	
	//! Initializes CImgList
	cimg_library::CImgList<TData> list(send_iterations, x, y, z, c);
	
	//! Fill cimgList with images filled randomly
	cimglist_for(list, i)
	{
		list[i].rand(std::rand() & 0xF, std::rand() & 0xFF);
	}//data loop
	
	//! Output list to be send
	list.print();
	
	//! Send number of iterations
	if(send.control(send_iterations) == CImgTcp::sendError) return EXIT_FAILURE;
	//! Send CImg dimensions and type 
	if(send.info(list[0]) == CImgTcp::sendError) return EXIT_FAILURE;
	//! loop on datas
	cimglist_for(list, i)
	{	
		//! Saves list min and max value into data vector 
		tattoo[0] = list[i].max();
		tattoo[1] = list[i].min();
		
		//! Tattoos data into CImgList in position i 	
		if(tastout.write(list[i], list[i].size(), tattoo, 2) != TASTOUT::SUCCESS) return EXIT_FAILURE;
		
		//! Send tattooed data
		if(send.data(list[i]) == CImgTcp::sendError) return EXIT_FAILURE;
	}//data loop
	return EXIT_SUCCESS;
}//main
