#ifndef TASTOUT_CIMG_HPP
#define TASTOUT_CIMG_HPP

#include "Tastout.hpp"
#include "../CImg/CImg.h"

/**
 * Class Tastout to work directly with CImg objects;
 **/
template<typename Ttarget, typename Tammo>
class TastoutCimg : public Tastout<Ttarget, Tammo>
{

public:

	//! TastoutCimg constructor calls Tastout constructor
	TastoutCimg() : Tastout<Ttarget, Tammo>(){}
	
	TASTOUT write(cimg_library::CImg<Ttarget> & targetData, cimg_library::CImg<Tammo> & ammoData)
	{
		return write(targetData.data(), targetData.size(), ammoData.data(), ammoData.size());
	}
	
	TASTOUT read(cimg_library::CImg<Ttarget> & tattooedData, cimg_library::CImg<Tammo> & receivedData)
	{
		std::vector<Tammo> receivedVector;
		if(read(tattooedData.data(), tattooedData.size(), receivedVector) != TASTOUT::SUCCESS) return TASTOUT::READ_FAILLURE;
		
		receivedData.assign(receivedVector.size());
		
		memcpy(receivedData.data(), receivedVector.data(), receivedVector.size()*sizeof(Tammo));
		
		return TASTOUT::SUCCESS;
	}	
	

};


#endif
