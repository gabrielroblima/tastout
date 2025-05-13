#include <iostream>

#include "include/tastout.hpp"

int main (int argc, char** argv)
{
	Tastout tastout("TAsTout", false);
	
	std::string signal("1632641282565121024204840968192");
	std::vector<unsigned char> input = {0x08, 0xAB, 0xCD, 0xEF, 0xB1};
	std::string tattooedSignal;
	
	if(tastout.write(signal, input, tattooedSignal) != 0) return EXIT_FAILURE;
	
	std::cout << " input: " << signal << std::endl
			  << "output: " << tattooedSignal << std::endl;
			  
	
	std::vector<unsigned char> output;
	tastout.read(tattooedSignal, output);
	
	std::cout << "Read values:" << std::endl;
	for(size_t i =0; i < output.size(); i++)
	{
		std::cout << i << ": " << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(output[i]) << std::endl;
	}
	
	return EXIT_SUCCESS;
}
