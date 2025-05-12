#ifndef TASTOUT_HPP
#define TASTOUT_HPP

#include <string>
#include <algorithm>

//Should we work with different types to tatoo or we work with a string to be tatooed?
//For the last bit change option, should we receive a string or a vector to work with?
//	  Will we send all the bytes and a header or the header will also be included as part of tatoo? 
class Tastout
{

public:
	
	//! Constructor
	/**
	 * \param [in] magicNumber magic number to include in tatooed signal
	 * \param [in] isTatooInHead define if tatoo is in head(true) or in tail(false)
	 **/
	 Tastout(const std::string & magicNumber, const bool & isTatooInHead = false) : magicNumber_(magicNumber), isTatooInHead_(isTatooInHead){}
	 
	 //! Write function tatoos the signal 
	 /**
	  * \param [in] signal input signal
	  * \param [in] value value to be tatooed
	  * \param [out] tatooedSignal tatooed signal
	  **/
	 char write(const std::string & signal, const std::string & value, std::string & tatooedSignal)
	 {
		//! Verify if the signal can be tatooed
		if(signal.size() <=  value.size() + magicNumber_.size()) return 1;
		
		if(isTatooInHead_)
		{
			//! Reverse signal to take tail
			std::string reverseSignal(signal);
			reverse(reverseSignal.begin(),reverseSignal.end());
			//! Tatoos the signal concatenating the magic number, the value and the most significatives digits of signal
			tatooedSignal = magicNumber_ + value + reverseSignal.substr(0, signal.size() - (value.size() + magicNumber_.size()));			
		}else
		{
			//! Reverse magic number
			std::string reverseMagicNumber(magicNumber_);
			reverse(reverseMagicNumber.begin(),reverseMagicNumber.end());
			
			//! Reverse value
			std::string reverseValue(value);
			reverse(reverseValue.begin(),reverseValue.end());
			
			//! Tatoos the signal concatenating the most significatives digits of signal, the reversed value and and the reversed magic number
			tatooedSignal = signal.substr(0, signal.size() - (value.size() + magicNumber_.size())) + reverseValue + reverseMagicNumber;
		}//isTatooInHead
		return 0;
	 }
	 
	 char read()
	 {
		
		
		return 0;
	 }	 
 private:
 
	const std::string magicNumber_;
	const bool isTatooInHead_;
};



#endif
