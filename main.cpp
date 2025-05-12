#include <iostream>

#include "include/tastout.hpp"

int main (int argc, char** argv)
{
	Tastout tastout("TAsToutT08b4i", true);
	
	std::string signal("1632641282565121024204840968192");
	std::vector<unsigned char> value = {0x08, 0xAB, 0xCD, 0xEF};
	std::string tattooedSignal;
	
	if(tastout.write(signal, value, tattooedSignal) != 0) return EXIT_FAILURE;
	
	std::cout << " input: " << signal << std::endl
			  << "output: " << tattooedSignal << std::endl;
			  
	std::string untattooedSignal;
	std::string val;
	tastout.read(tattooedSignal, val);
			  
	//~ std::cout << val << std::endl;
	return EXIT_SUCCESS;
}
