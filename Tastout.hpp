#ifndef TASTOUT_HPP
#define TASTOUT_HPP

#include <algorithm>
#include <string>

#define TASTOUT_VERSION "v0.0.1"

template<typename Ttarget, typename Tammo>
class Tastout
{
public:
	
	/**
	 * \param [in] isTattooInHead defines if tattoing is in head (true) or in tail (false)
	 **/
	
	Tastout(const bool & isTattooInHead) : magicNumber_("TAsTout"+TASTOUT_VERSION), isTattooInHead_(isTattooInHead)
	{
		//! Creates a reversed copy of magic number
		reverseMagicNumber_(magicNumber_);
		reverse(reverseMagicNumber_.begin(), reverseMagicNumber_.end());
		//! header size = magic number size + 1B (Text or Binary) + 2B (data size in ascii hexadecimal) + 1B (endianess) + 2B (number of spread data) + 1B (spread data Type) 
		tastoutHeaderSize_ = magicNumber_.size() + 7;
		
	}
	
	//! Magic number is based on version, so user can get magic number by this function
	const std::string & getMagicNumber(){return magicNumber_};
	
	/**
	 * \param targetData 
	 * \param sizeOfTargetData
	 * \param ammoData
	 * \param sizeOfAmmoData
	 **/
	const bool write(const Ttarget* targetData, const & size_t sizeOfTargetData, const Tammo* ammoData, const & size_t sizeOfAmmoData)
	{		
		
		
		
		
	}

private:
	
	const std::string magicNumber_;
	const std::string reverseMagicNumber_;
	const bool isTattooInHead_;
	size_t tastoutHeaderSize_;
	
}
#endif
