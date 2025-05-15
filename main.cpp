#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Tastout.hpp"

#define VERSION "v0.0.1"

typedef uint8_t Tammo;
typedef uint8_t Ttarget;

#define AMMO_SIZE 10
#define TARGET_SIZE 320

int main(int argc, char** argv)
{
	//! Instance of Tastout class with tastout in head
	Tastout<Ttarget, Tammo> tastout(true);
	
	Ttarget target[TARGET_SIZE]; // Target data => It will be tattooed
	for(size_t i = 0; i < TARGET_SIZE; i++){target[i] = rand() & 0xFF;} // fills target random with values between 0 and 255;
	
	
	Tammo ammo[AMMO_SIZE]; //Ammo data =>	It's the tattoo of target
	for(size_t i = 0; i < AMMO_SIZE; i++)
	{
		ammo[i] = rand() & 0xFF;
		std::cout << std::dec << i << ' ';
		std::cout << "0x" << std::hex << std::setfill('0') << std::setw(sizeof(Tammo)*2) << static_cast<unsigned long long>(ammo[i]) << ' ';
		std::cout << "0d" << std::dec << std::setw(log10((1ULL << (8*sizeof(Tammo))) - 1) + 1) << static_cast<unsigned long long>(ammo[i]) << std::endl;
	} // fills ammo with random values between 0 and 255 and show values in hex and dec;
	
	
	
	if(not tastout.write(target, TARGET_SIZE, ammo, AMMO_SIZE, true)) return EXIT_FAILURE;	
	
	Tammo* received;
	size_t received_size;
	
	tastout.read(target, TARGET_SIZE, received, received_size);
	for(size_t i = 0; i < received_size; i++)
	{
		std::cout << std::dec << i << ' ';
		std::cout << "0x" << std::hex << std::setfill('0') << std::setw(sizeof(Tammo)*2) << static_cast<unsigned long long>(received[i]) << ' ';
		std::cout << "0d" << std::dec << std::setw(log10((1ULL << (8*sizeof(Tammo))) - 1) + 1) << static_cast<unsigned long long>(received[i]) << std::endl;
	} // Output received values from tattoo;
	
	return EXIT_SUCCESS;
}
