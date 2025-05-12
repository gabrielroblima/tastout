#ifndef TASTOUT_HPP
#define TASTOUT_HPP

#include <string>
#include <algorithm>

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
	 
	 //! Write function tattoos the signal 
	 /**
	  * \param [in] signal input signal
	  * \param [in] value value to be tattooed
	  * \param [out] tattooedSignal tattooed signal
	  **/
	 char write(const std::string & signal, const std::string & value, std::string & tattooedSignal)
	 {
		//! Verify if the signal can be tattooed
		if(signal.size() <=  value.size() + magicNumber_.size()) return 1;
		
		if(isTattooInHead_)
		{
			//! Reverse signal to take tail
			std::string reverseSignal(signal);
			reverse(reverseSignal.begin(),reverseSignal.end());
			//! Tattoos the signal concatenating the magic number, the value and the most significatives digits of signal
			tattooedSignal = magicNumber_ + value + reverseSignal.substr(0, signal.size() - (value.size() + magicNumber_.size()));			
		}else
		{
			//! Reverse magic number
			std::string reverseMagicNumber(magicNumber_);
			reverse(reverseMagicNumber.begin(),reverseMagicNumber.end());
			
			//! Reverse value
			std::string reverseValue(value);
			reverse(reverseValue.begin(),reverseValue.end());
			
			//! Tattoos the signal concatenating the most significatives digits of signal, the reversed value and and the reversed magic number
			tattooedSignal = signal.substr(0, signal.size() - (value.size() + magicNumber_.size())) + reverseValue + reverseMagicNumber;
		}//isTattooInHead
		return 0;
	 }
	 
	 char read(const std::string & tattooedSignal, std::string & untattooedSignal, std::string & value)
	 {
		std::string reverseMagicNumber(magicNumber_);
		reverse(reverseMagicNumber.begin(), reverseMagicNumber.end());
	
		if(tattooedSignal.find(magicNumber_) == 0)
		{
			std::cout << "Type: " << tattooedSignal.substr(7,2) << std::endl;
		}
		
		return 0;
	 }	 
 private:
 
	const std::string magicNumber_;
	const bool isTattooInHead_;
};



#endif
