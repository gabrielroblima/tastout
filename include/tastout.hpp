#ifndef TASTOUT_HPP
#define TASTOUT_HPP

#include <string>
#include <vector>
#include <iostream>
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
	  * \param [in] value values to be tattooed
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
				
		if(isTattooInHead_)
		{
			std::ostringstream tastoutStream;
			//! Tattoos the signal concatenating the magic number and information
			tastoutStream << magicNumber_ << "T08b" << std::hex << value.size() << "i";
			std::cout << tastoutStream.str() << std::endl;
			for(int i = 0; i < value.size(); i++)
			{
				tastoutStream << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(value[i]);
			}
			std::cout << std::hex << tastoutStream.str() << std::endl;
		}else
		{
			//~ //! Reverse magic number
			//~ std::string reverseMagicNumber(magicNumber_);
			//~ reverse(reverseMagicNumber.begin(),reverseMagicNumber.end());
			
			//~ //! Reverse value
			//~ std::string reverseValue(value);
			//~ reverse(reverseValue.begin(),reverseValue.end());
			
			//~ //! Tattoos the signal concatenating the most significatives digits of signal, the reversed value and and the reversed magic number
			//~ tattooedSignal = signal.substr(0, signal.size() - (value.size() + magicNumber_.size())) + reverseValue + reverseMagicNumber;
		}//isTattooInHead
		return 0;
	 }
	 
	 char read(const std::string & tattooedSignal, std::string & value)
	 {
		//~ std::string reverseMagicNumber(magicNumber_);
		//~ reverse(reverseMagicNumber.begin(), reverseMagicNumber.end());
	
		//~ if(tattooedSignal.find(magicNumber_) == 0)
		//~ {
			//~ value = tattooedSignal.substr(12, 8);
		//~ }else if(tattooedSignal.find(reverseMagicNumber))
		//~ {
			//~ value = tattooedSignal;
			//~ reverse(value.begin(), value.end());
			//~ value = tattooedSignal.substr(11, 8);
			//~ reverse(value.begin(), value.end());
		//~ }
		return 0;
	 }	 
 private:
 
	const std::string magicNumber_;
	const bool isTattooInHead_;
};



#endif
