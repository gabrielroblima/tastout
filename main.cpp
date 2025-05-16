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
	
	//! Target data => It will receive the tattoo
	std::vector<Ttarget> target(TARGET_SIZE);
	for(size_t i = 0; i < TARGET_SIZE; i++){target[i] = rand() & 0xFF;} // fills target random with values between 0 and 255;
	
	std::vector<Ttarget> unchangedTarget = target; // Copy of target vector to display before and after
	
	//!Ammo data =>	It will be tattooed
	Tammo ammo[AMMO_SIZE]; 
	for(size_t i = 0; i < AMMO_SIZE; i++){ammo[i] = rand() & 0xFF;}
	
	//! Calls tastout write
	if(not tastout.write(target.data(), TARGET_SIZE, ammo, AMMO_SIZE, true)) return EXIT_FAILURE;
	
	//! Display data block	
	std::cout << "This data was tattooed into target data: " << std::endl;
	
	for(size_t i = 0; i < AMMO_SIZE; i++)
	{
		std::cout << std::dec << i << ' ';
		std::cout << "0x" << std::hex << std::setfill('0') << std::setw(sizeof(Tammo)*2) << static_cast<unsigned long long>(ammo[i]) << ' ';
		std::cout << "0d" << std::dec << std::setw(log10((1ULL << (8*sizeof(Tammo))) - 1) + 1) << static_cast<unsigned long long>(ammo[i]) << std::endl;
	}
	
	std::cout << "------------------------------------------------" << std::endl << std::endl;
	
	std::bitset<8*sizeof(Ttarget)> outputByte;
	std::bitset<8> tattooedByte;
	std::cout << "--------------- Displaying Data ---------------" << std::endl;
	size_t startData = 8*(tastout.getMagicNumber().size()+7); // Position of first element tattooed
	std::cout << " Hex Target	Tattooed Target" << std::endl;
	
	//! Displays data before and after tattoo
	for(size_t i = startData; i < startData+AMMO_SIZE*8*sizeof(Tammo)*2; i+= 8)
	{
		for(size_t j = 0; j < 8; j++)
		{
			std::cout << "0x" << std::hex << std::setfill('0') << std::setw(2*sizeof(Ttarget)) << static_cast<unsigned long long>(unchangedTarget[i+j]) << ' ';
			outputByte = unchangedTarget[i+j];
			std::cout << "0b" << outputByte << ' ';
			outputByte = target[i+j];
			tattooedByte[7-j] = outputByte[0];
			std::cout << "0b" << outputByte << std::endl;
			
			if(j == 7)
			{
				std::cout << "---------------------------------------------------" << std::endl 
						  << "Tattooed byte:  0b" << tattooedByte <<  " ASCII: " << static_cast<char>(tattooedByte.to_ulong()) << std::endl << std::endl;
				std::cout << " Hex Target	Tattooed Target" << std::endl;
			}
		}		
	}
	
	//! Reception of data from tattooed data
	size_t received_size;
	tastout.read(target.data(), TARGET_SIZE, received_size);
	Tammo* received;
	received = tastout.getRead();
	
	for(size_t i = 0; i < received_size; i++)
	{
		std::cout << std::dec << i << ' ';
		std::cout << "0x" << std::hex << std::setfill('0') << std::setw(sizeof(Tammo)*2) << static_cast<unsigned long long>(received[i]) << ' ';
		std::cout << "0d" << std::dec << std::setw(log10((1ULL << (8*sizeof(Tammo))) - 1) + 1) << static_cast<unsigned long long>(received[i]) << std::endl;
	}

	return EXIT_SUCCESS;
}
