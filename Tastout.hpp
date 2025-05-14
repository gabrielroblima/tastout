#ifndef TASTOUT_HPP 
#define TASTOUT_HPP

#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <vector>
#include <cstring>

#define TASTOUT_VERSION "v0.0.1"

//-------DEBUG-------
#define DEBUG 1
#define DEBUG_MSG(msg) \
    std::cout << "\033[34m" << msg << "\033[0m" << std::endl;

template<typename Ttarget, typename Tammo>
class Tastout
{
public:
	
	/**
	 * \param [in] isTattooInHead defines if tattoing is in head (true) or in tail (false)
	 **/
	
	Tastout(const bool & isTattooInHead) : magicNumber_("TAsTout"), isTattooInHead_(isTattooInHead), className_("--------------------Class::Tastout--------------------")
	{
		//! Creates a reversed copy of magic number
		magicNumber_ = magicNumber_ + TASTOUT_VERSION;
		reverseMagicNumber_ = magicNumber_;
		reverse(reverseMagicNumber_.begin(), reverseMagicNumber_.end());
		
	}
	
	//! Magic number is based on version, so user can get magic number by this function
	const std::string & getMagicNumber(){return magicNumber_;};
	
	/**
	 * \param targetData 
	 * \param sizeOfTargetData
	 * \param ammoData
	 * \param sizeOfAmmoData
	 **/
	const bool write(Ttarget* targetData, const size_t & sizeOfTargetData, const Tammo* ammoData, const size_t & sizeOfAmmoData, const bool & isBigEndian)
	{	
		#if DEBUG
			DEBUG_MSG(className_)	
		#endif
		
		//We are going to send all data in form of text i.e. ascii
		tastoutStream_ << magicNumber_;
		tastoutStream_ << 'T';
		tastoutStream_ << std::hex << std::setfill('0') << std::setw(2) << 8*sizeof(Tammo);
		if(isBigEndian) tastoutStream_ << 'B'; else tastoutStream_ << 'b';
		tastoutStream_ << std::hex << std::setfill('0') << std::setw(2) << sizeOfAmmoData << 'i'; 
		//For this moment the type integer was used but after it'll be possible to choose dataType
		
		//Add ammo data to tastoutStream in hex
		for(size_t i = 0; i < sizeOfAmmoData; i++)
		{
			tastoutStream_ << std::hex << std::setfill('0') << std::setw(2*sizeof(Tammo)) << static_cast<unsigned long long int>(ammoData[i]);
		}
		
		#if DEBUG
			DEBUG_MSG(tastoutStream_.str())	
		#endif
		
		//Verify if target data is capable of storing all ammo data
		size_t neededTargetDataSize = 8*tastoutStream_.str().size();
		
		#if DEBUG
			DEBUG_MSG("Required data size: " + std::to_string(neededTargetDataSize))
		#endif
		
		if(sizeOfTargetData < neededTargetDataSize) return false;
		
		//!														|>Represents 1 Tammo |>Represents 1 Tammo
		//! To write 1 Tammo in n Ttarget we need a bitset with 8b*sizeof(Ttarget)B * 8b*sizeof(Tammo)B bits
		std::bitset<8*sizeof(Ttarget)> destination;
		
		//! Creates 1 bitset of 8b*sizeof(Tammo)B bits
		std::bitset<8> source;
		
		//! Tattoo string bytes into targetSource
		for(size_t i = 0; i < neededTargetDataSize; i+= 8)
		{
			source ^= source;
			source |= tastoutStream_.str()[i/8];
			for(size_t j = 0; j < 8; j++)
			{
				destination ^= destination; // Garants destination is clear
				destination |= targetData[i+j]; // Copy target to destination
				destination[0] = source[7-j]; // Sets last significant bit of current destination to source[j]
				targetData[i+j] = destination.to_ulong();
			}
		} 
		
		return true;
	}

private:
	
	std::string magicNumber_;
	std::string reverseMagicNumber_;
	const bool isTattooInHead_;
	std::stringstream tastoutStream_;
	std::string className_;
	
};
#endif
