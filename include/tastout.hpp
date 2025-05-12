#ifndef TASTOUT_HPP
#define TASTOUT_HPP

#include <string>

//Should we work with different types to tatoo or we work with a string to be tatooed?
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
	 char write(const std::string & signal, const std::string & value, std::string & tatooedSignal)
	 {
		//! Verify if the signal can be tatooed
		if(signal.size() <=  value.size() + magicNumber_.size()) return 1;
		
		if(isTatooInHead_)
		{
			//! Tatoos the signal concatenating the magic number, the value and the most significatives digits of signal
			tatooedSignal = magicNumber_ + value + signal.substr(0, signal.size() - (value.size() + magicNumber_.size()) - 1);			
		}else
		{
		}
		
		return 0;
	 }
	 
	 char read(){}	 
 private:
 
	const std::string magicNumber_;
	const bool isTatooInHead_;
};



#endif
