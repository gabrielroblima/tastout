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

//!-------DEBUG-------
#define DEBUG 0
#define DEBUG_MSG(msg) \
    std::cout << "\033[34m [DEBUG]" << msg << "\033[0m" << std::endl;

enum class TASTOUT
{
	SUCCESS = 0,
	WRONG_SIZE,
	MAGIC_NUMBER_IDENTIFICATION_FAILURE, 
	WRONG_MAGIC_NUMBER_SIZE,
	INCOMPATIBLE_TYPE_SIZE	
};

template<typename Ttarget, typename Tammo>
class Tastout
{
public:
	
	//! Constructor
	Tastout() : magicNumber_("TAsTout"), className_("Class::Tastout")
	{
		//! Creates a magic number with version number
		magicNumber_ = magicNumber_ + TASTOUT_VERSION;		
	}
	
	//! Magic number is based on version, so user can get magic number by this function
	const std::string & getMagicNumber(){return magicNumber_;};
	
	/**
	 * \param targetData Pointer to data that will receive the tattoo 
	 * \param sizeOfTargetData Number of elements of data that will receive the tattoo
	 * \param ammoData Pointer to data that will be tattooed
	 * \param sizeOfAmmoData Number of elements to be tattooed
	 * \param isBigEndian Chooses between bigEndian and little endian
	 * 
	 * char output represents a uint8 value
	 **/
	const TASTOUT write(Ttarget* targetData, const size_t & sizeOfTargetData, const Tammo* ammoData, const size_t & sizeOfAmmoData)
	{	
		#if DEBUG
			DEBUG_MSG(className_)
			DEBUG_MSG("::write")	
		#endif
		
		//Clear stream content
		tastoutStream_.str("");
		//We are going to send all data in form of text i.e. ascii
		tastoutStream_ << magicNumber_;
		tastoutStream_ << 'T'; //! Type text
		tastoutStream_ << std::hex << std::setfill('0') << std::setw(2) << 8*sizeof(Tammo); //! Number of bits in tattooed data
		tastoutStream_ << 'b';
		tastoutStream_ << std::hex << std::setfill('0') << std::setw(2) << sizeOfAmmoData << 'i'; //! Number of elements to be tattooed
		//For this moment the type integer was used but after it'll be possible to choose dataType
		
		//!Add ammoData to tastoutStream in hex
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
		
		if(sizeOfTargetData < neededTargetDataSize)
		{
			std::cerr << "tastout::write => size of target data should at least " << neededTargetDataSize << std::endl;
			return TASTOUT::WRONG_SIZE;
		}

		//!														|>Represents 1 Tammo
		//! To write 1 Tammo in n Ttarget we need a bitset with 8b*sizeof(Ttarget)B bits 
		std::bitset<8*sizeof(Ttarget)> destination;
		
		//! Creates 1 bitset of 8b*sizeof(Tammo)B bits
		std::bitset<8> source;
		
		//! Tattoo string bytes into targetSource
		for(size_t i = 0; i < neededTargetDataSize; i+= 8)
		{
			source = tastoutStream_.str()[i/8];
			for(size_t j = 0; j < 8; j++)
			{
				destination = targetData[i+j]; // Copy target to destination
				destination[0] = source[7-j]; // Sets last significant bit of current destination to source[j]
				targetData[i+j] = destination.to_ulong();
			}
		}
		#if DEBUG
			DEBUG_MSG("Tastout finished!")
		#endif
		 
		return TASTOUT::SUCCESS;
	}//write
	
	/**
	 * \param tattooedData Pointer to data that received the tattoo 
	 * \param sizeOfTargetData Number of elements of tattooedData
	 * \param receivedData Pointer to received data "vector"
	 * \param sizeOfAmmoData Number of received elements
	 **/
	TASTOUT read(Ttarget* tattooedData, const size_t & sizeOfTattooedData, size_t & sizeOfReceivedData)
	{
		#if DEBUG
			DEBUG_MSG(className_)
			DEBUG_MSG("::read")	
		#endif
		
		if(sizeOfTattooedData < 8*magicNumber_.size())
		{
			std::cerr << "tastout::read => Tattooed Dada size should be greater then " << 8*magicNumber_.size() << std::endl;
			return TASTOUT::WRONG_MAGIC_NUMBER_SIZE; // Data size is not compatible
		}
		//! Allocates 2 bitsets, one to read a tattooed data and another to register a byte.
		std::bitset<8*sizeof(Ttarget)> readTattooed;
		std::bitset<8> byte;
		
		std::string informationRead("");
		
		//! Try to indentify magic number in head we add 7 do the magic number size to read the bytes of information
		for(size_t i = 0; i < 8*(magicNumber_.size()+7); i+= 8)
		{
			for(size_t j = 0; j < 8; j++)
			{
				readTattooed = tattooedData[i+j];
				byte[7-j] = readTattooed[0];
			}
			informationRead = informationRead + static_cast<char>(byte.to_ulong());	
		}
		
		//! Verify if magic number is present
		if(informationRead.substr(0, magicNumber_.size()) != magicNumber_)
		{
			std::cerr << "tastout::read => Failed to identify Magic Number" << std::endl; 
			return TASTOUT::MAGIC_NUMBER_IDENTIFICATION_FAILURE;// failed to identify magic number
		}
		
		//! Gets information about number of bits and number of elements received
		size_t receivedNumberOfBits = std::stoi(informationRead.substr(magicNumber_.size()+1,2), nullptr, 16);
		sizeOfReceivedData = std::stoi(informationRead.substr(magicNumber_.size()+4,2), nullptr, 16);
		
		if(8*sizeof(Tammo) != receivedNumberOfBits)
		{
			std::cerr << "tastout::read => Incompatible type sizes" << std::endl; 
			return TASTOUT::INCOMPATIBLE_TYPE_SIZE; //incorrect size for integers;
		}
		
		
		//! Allocates memory to store received data.
		receivedDataVector.reserve(sizeOfReceivedData);
		receivedDataVector.resize(sizeOfReceivedData); 
		
		#if DEBUG
			DEBUG_MSG("Received number of bits:")
			DEBUG_MSG(receivedNumberOfBits)
			DEBUG_MSG("Elements of received data:")
			DEBUG_MSG(sizeOfReceivedData)
			DEBUG_MSG("Received tastout header:")
			DEBUG_MSG(informationRead);
		#endif
		
		//! Continues to Read data 
		std::string dataString("");
		for(size_t i = 8*(magicNumber_.size()+7); i < 160 + 8*(receivedNumberOfBits/4)*sizeOfReceivedData; i+= 8)
		{
			byte ^= byte;
			for(size_t j = 0; j < 8; j++)
			{
				readTattooed = tattooedData[i+j];
				byte[7-j] = readTattooed[0];
				
			}
			dataString = dataString + static_cast<char>(byte.to_ulong());	
		}
		
		//! Converts all received data from string int values
		for(size_t i = 0; i < dataString.size(); i+=receivedNumberOfBits/4)
		{
			receivedDataVector[i/(receivedNumberOfBits/4)] = std::stoi(dataString.substr(i,receivedNumberOfBits/4), nullptr, 16);
			#if DEBUG
				DEBUG_MSG("Received data: ")
				std::stringstream ss;
				ss << std::to_string(receivedDataVector[i/(receivedNumberOfBits/4)]);
				DEBUG_MSG(ss.str())
			#endif
		}		
		return TASTOUT::SUCCESS;
	}
	
	//! Returns pointer to receivedDataVector
	const Tammo* getRead()
	{
		return receivedDataVector.data();
	}

private:
	
	std::string magicNumber_; //! MagicNumber => Includes Tastout version
	std::stringstream tastoutStream_; //! Stream to be tattooed
	std::string className_; //! Debug Info
	std::vector<Tammo> receivedDataVector; //! Vector to store read data after execution of read method 
	
};
#endif
