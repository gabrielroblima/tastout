#include <iostream>
#include <vector>
#include "../tcp_zmq/Tcp.hpp"
#include "TastoutCimg.hpp"

int main(int argc, char** argv)
{
	
	//! \todo define use_cimg
	//! Command Line options
	const std::string data_port = cimg_option("--data", "5555", "data port for receiving a bunch of data");
	const std::string control_port = cimg_option("--control", "5556", "control port for receiving number of data or stop signal, e.g. 100 data blocks");
	const std::string info_port = cimg_option("--info", "5557", "info port for receiving data type and size, e.g. <float>[sx,sy,sz,sc]");
	const std::string address = cimg_option("-a", "localhost", "address of the receiving device, e.g. 10.10.4.123");

	//! Initialize receiver object
	CImgRecv<TData> recv(address, control_port, info_port, data_port);
	//! Initialize data object as a CImgList with at least 1 image.
	cimg_library::CImgList<TData> list(1);
	//! Initialize tastout instance
	TastoutCimg<TData, TData> tastout;
	unsigned iter;
	
	//! Cimg to store received data
	cimg_library::CImg<TData> tattoo;
	
	//! Initialize variable to store number of tattooed data in CImg
	size_t sizeOfReceivedData;
	
	while(true)
	{
		//! Control function to receive number of iterations or stop signal
		//! \todo move declaration "CImgTcp control" out of the loop
		std::cout << "Waiting for number of data to receive or stop signal." << std::endl;
		CImgTcp control = recv.control(iter); if(control == CImgTcp::receiveError) return EXIT_FAILURE;
		//! Check if a stop signal was received
		if(control == CImgTcp::stop) return EXIT_SUCCESS;
		std::cout << "Received " << iter << " iterations." << std::endl;
		
		//! Receives dimensions (and data type)
		//! \todo data type should be checked
		if(recv.info(list[0]) == CImgTcp::receiveError) return EXIT_FAILURE;
		//! Assign dimensions and iterations (number of images) to list
		list.assign(iter, list[0].width(), list[0].height(), list[0].depth(), list[0].spectrum());
		std::cout << "Dimensions assigned N = " << list.size() 
									 << " X = " << list[0].width() 
									 << " Y = " << list[0].height() 
									 << " Z = " << list[0].depth() 
									 << " C = " << list[0].spectrum() << std::endl;
		
									 
		//! Receive and store each image in list
		cimglist_for(list, i)
		{
			if(recv.data(list[i]) == CImgTcp::receiveError) return EXIT_FAILURE;
			
			if(tastout.read(list[i], tattoo) != TASTOUT::SUCCESS) return EXIT_FAILURE;

			std::cout<<"receive #"<<i<<"\r" ;
			std::cout << "Tattooed Max = " << static_cast<int>(tattoo[0]) << " Tattooed Min = " << static_cast<int>(tattoo[1]) << std::endl;
		}//data loop
        std::cout<<std::endl;

		//! Print received data
		list.print();
	}//infinite loop
	
	return EXIT_SUCCESS;
}//main
