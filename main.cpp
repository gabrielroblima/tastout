#include <iostream>

#include "include/tastout.hpp"

int main (int argc, char** argv)
{
	//! Instance of tastout with "TAsTout" as magic number in the tail if false and in head if true 
	Tastout tastout(true);
	
	//! Input signal
	std::string signal("1632641282565121024204840968192");
	std::vector<unsigned char> input = {0x08, 0xAB, 0xCD};
	std::string tattooedSignal;
	
	//! Tattoo data into signal 
	if(tastout.write(signal, input, tattooedSignal) != 0) return EXIT_FAILURE;
	
	//! Outputs read values
	std::cout << "Write values:" << std::endl;
	for(size_t i =0; i < input.size(); i++)
	{
		std::cout << i << ": " << std::setfill(' ') << std::setw(3) << std::dec << static_cast<unsigned int>(input[i]) << " "; 
		std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(input[i]) << std::endl;
	}
	
	
	std::cout << " input signal: " << signal << std::endl
			  << "output signal: " << tattooedSignal << std::endl;
			  
	
	std::vector<unsigned char> output;
	//! Read tattooed data from signal
	tastout.read(tattooedSignal, output);
	
	//! Outputs read values
	std::cout << "Read values:" << std::endl;
	for(size_t i =0; i < output.size(); i++)
	{
		std::cout << i << ": " << std::setfill(' ') << std::setw(3) << std::dec << static_cast<unsigned int>(output[i]) << " "; 
		std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(output[i]) << std::endl;
	}
	
	return EXIT_SUCCESS;
}
