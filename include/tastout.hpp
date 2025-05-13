#ifndef TASTOUT_HPP
#define TASTOUT_HPP

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <cstdlib>

//Should we work with different types to tattoo or we work with a string to be tattooed?
//For the last bit change option, should we receive a string or a vector to work with?
//	  Will we send all the bytes and a header or the header will also be included as part of tattoo? 
class Tastout
{

public:
	
	//! Constructor
	/**
	 * \param [in] magicNumber magic number to include in tattooed signal
	 * \param [in] isTattooInHead define if tattoo is in head(true) or in tail(false)
	 **/
	 Tastout(const std::string & magicNumber, const bool & isTattooInHead = false) : magicNumber_(magicNumber), isTattooInHead_(isTattooInHead){}
	 
	 //! Write function tattoos the signal output type char should be considered as int8
	 /**
	  * \param [in] signal input signal
	  * \param [in] value vector of values to be tattooed
	  * \param [out] tattooedSignal tattooed signal
	  **/
	 char write(const std::string & signal, const std::vector<unsigned char> & value, std::string & tattooedSignal)
	 {
		//! Verify if the signal can be tattooed
		if(signal.size() <=  value.size()*2 + magicNumber_.size()) return 1;
		//! Verify if value has less than 16 items
		if(value.size() > 0xF) return 1;
		
		//! Stream to send number of values
		//! T08 + b|B + (0~F) + i		
		std::ostringstream tastoutStream;
		
		//! Tattoo the signal concatenating the magic number and values
		tastoutStream << magicNumber_ << "T08b" << std::hex << value.size() << "i";
		for(int i = 0; i < value.size(); i++){tastoutStream << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(value[i]);}		

		if(isTattooInHead_)
		{			
			//! Concatenate the first digits of signal with tattoo
			tattooedSignal = tastoutStream.str() + signal.substr(0, signal.size() - tastoutStream.str().size());
		}else
		{
			//! Reverse the magic number and data
			std::string tastoutString(tastoutStream.str());
			reverse(tastoutString.begin(), tastoutString.end());
			
			//! Concatenate reversed tattoo with the first digits of signal 
			tattooedSignal = signal.substr(0, signal.size() - tastoutStream.str().size()) + tastoutString;
		}//isTattooInHead
		return 0;
	 }
	 
	 //! Read function get data tattooed into string type char should be considered as int8
	 /**
	  * \param [in] tattooedSignal input signal
	  * \param [in] values vector of values tattooed
	  **/
	 char read(std::string & tattooedSignal, std::vector<unsigned char> & values)
	 {
		std::string reverseMagicNumber(magicNumber_);
		reverse(reverseMagicNumber.begin(), reverseMagicNumber.end());
	
		//! Verify if the magic number is in head or tail 
		bool wasTattooFound = false;
		if(tattooedSignal.find(magicNumber_) == 0)
		{
			wasTattooFound = true;			
		}else if(tattooedSignal.find(reverseMagicNumber) != tattooedSignal.npos)
		{
			wasTattooFound = true;
			//! Reverse tattoo if the magic number is reversed
			reverse(tattooedSignal.begin(), tattooedSignal.end());
		}
		
		if(not wasTattooFound) return 1;
		
		//! Verify size of values and allocates memory if necessary
		size_t neededSizeOfValues = std::stoi(tattooedSignal.substr(11,1), nullptr, 16);
		if(values.size() < neededSizeOfValues)
		{
			values.reserve(neededSizeOfValues);
			values.resize(neededSizeOfValues);
		}
		
		unsigned int byte;
		std::stringstream stringStream;
		for(size_t i = 0; i < neededSizeOfValues; i++)
		{
			//! Copy byte to stream. The offset "13" represents the number of chars before the first value
			stringStream << std::hex << tattooedSignal.substr(2*i + 13, 2);
			stringStream >> byte;
			//! Copy byte to vector at position i
			memcpy(&values[i], &byte, 1);
			stringStream.clear();
		}
		
		return 0;
	 }	 
 private:
 
	const std::string magicNumber_;
	const bool isTattooInHead_;
};



#endif
