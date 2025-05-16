#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Tastout.hpp"

#define VERSION "v0.0.1"

typedef uint8_t Tammo;
typedef uint8_t Ttarget;

#define AMMO_SIZE 10
#define TARGET_SIZE 321

int main(int argc, char** argv)
{
	
	/**
	 * This code is an example of Tastout. It firstly creates a table of random numbers to receive the tattoo and another one to be tattooed.
	 * The data to be tattooed is called ammo and is displayed to the user. The target receives the tattoo and a comparison between tattooed and untattooed data is shown.
	 * At the end, the recovered data read from target data is displayed, and a change comparison is made to guarantee that data changes were almost insignificant.
	 **/
	 
	srand (time(NULL));
	//! Instance of Tastout class with tastout in head
	Tastout<Ttarget, Tammo> tastout;
	
	
	//! Target data => It will receive the tattoo
	std::vector<Ttarget> target(TARGET_SIZE);
	for(size_t i = 0; i < TARGET_SIZE; i++){target[i] = rand() & 0xFF;} // fills target random with values between 0 and 255;
	
	std::vector<Ttarget> unchangedTarget = target; // Copy of target vector to display before and after
	
	//!Ammo data =>	It will be tattooed
	Tammo ammo[AMMO_SIZE]; 
	for(size_t i = 0; i < AMMO_SIZE; i++){ammo[i] = rand() & 0xFF;}
	
	//! Calls tastout write
	if(tastout.write(target.data(), TARGET_SIZE, ammo, AMMO_SIZE) != TASTOUT::SUCCESS) return EXIT_FAILURE;
	
	//! Display data block	
	std::cout << "These datas were tattooed into target data: " << std::endl << std::endl;
	
	for(size_t i = 0; i < AMMO_SIZE; i++)
	{
		std::cout << std::dec << i << ' ';
		std::cout << "0x" << std::hex << std::setfill('0') << std::setw(sizeof(Tammo)*2) << static_cast<unsigned long long>(ammo[i]) << ' ';
		std::cout << "0d" << std::dec << std::setw(log10((1ULL << (8*sizeof(Tammo))) - 1) + 1) << static_cast<unsigned long long>(ammo[i]) << std::endl;
	}
	
	std::bitset<8*sizeof(Ttarget)> outputByte;
	std::bitset<8> tattooedByte;
	std::cout << std::endl << std::endl << "----------------- Displaying Data -----------------" << std::endl;
	size_t startData = 8*(tastout.getMagicNumber().size()+7); // Position of first element tattooed
	
	//! Displays data before and after tattoo
	for(size_t i = startData; i < startData+AMMO_SIZE*8*sizeof(Tammo)*2; i+= 8)
	{
		std::cout << " Hex Target	Tattooed Target" << std::endl;
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
			}
		}		
	}
	
	//! Calculates and display maximal target change
	Ttarget max = 0, min = 0xFF;
	for(size_t i = 0; i < TARGET_SIZE; i++)
	{
		if(abs(target[i] - unchangedTarget[i]) > max) max = abs(target[i] - unchangedTarget[i]);
		if(abs(target[i] - unchangedTarget[i]) < min) min = abs(target[i] - unchangedTarget[i]);
	}
	
	std::cout << "Max change in target data was: " << std::to_string(max) << std::endl << "Min change in target data was: " << std::to_string(min) << std::endl << std::endl;
	
	//! Reception of data from tattooed data
	size_t received_size;
	if(tastout.read(target.data(), TARGET_SIZE, received_size) != TASTOUT::SUCCESS) return EXIT_FAILURE;
	const Tammo* received = tastout.getRead();
	
	std::cout << "These datas were read from tattooed target data: " << std::endl << std::endl;
	for(size_t i = 0; i < received_size; i++)
	{
		std::cout << std::dec << i << ' ';
		std::cout << "0x" << std::hex << std::setfill('0') << std::setw(sizeof(Tammo)*2) << static_cast<unsigned long long>(received[i]) << ' ';
		std::cout << "0d" << std::dec << std::setw(log10((1ULL << (8*sizeof(Tammo))) - 1) + 1) << static_cast<unsigned long long>(received[i]) << std::endl;
	}
	

	return EXIT_SUCCESS;
}
