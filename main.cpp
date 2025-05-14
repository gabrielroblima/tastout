#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Tastout.hpp"

#define VERSION "v0.0.1"

typedef uint8_t Tammo;
typedef uint8_t Ttarget;


int main(int argc, char** argv)
{
	//! Instance of Tastout class with tastout in head
	Tastout<Tammo, Ttarget> tastout(true);
	
	Ttarget target[1000]; // Target data => It will be tattooed
	for(size_t i = 0; i < 1000; i++){target[i] = rand() & 0xFF;} // fills target random with values between 0 and 255;
	
	Tammo ammo[10]; //Ammo data =>	It's the tattoo of target
	for(size_t i = 0; i < 10; i++)
	{
		ammo[i] = rand() & 0xFF;
		std::cout << std::dec << i << ' ';
		std::cout << "0x" << std::hex << std::setfill('0') << std::setw(sizeof(Tammo)*2) << static_cast<unsigned long long>(ammo[i]) << ' ';
		std::cout << "0d" << std::dec << std::setw(log10((1ULL << (8*sizeof(Tammo))) - 1) + 1) << static_cast<unsigned long long>(ammo[i]) << std::endl;
	} // fills ammo with random values between 0 and 255 and show values in hex and dec;
	
	
	
	if(not tastout.write(target, 1000, ammo, 10, true));	
	
	return EXIT_SUCCESS;
}
