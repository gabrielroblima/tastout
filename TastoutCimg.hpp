#ifndef TASTOUT_CIMG_HPP
#define TASTOUT_CIMG_HPP

#include "Tastout.hpp"
#include "../CImg/CImg.h"

#define TASTOUT_CIMG_VERSION "v0.0.1"

/**
 * Class Tastout to work directly with CImg objects;
 **/
template<typename Ttarget, typename Tammo>
class TastoutCimg : public Tastout<Ttarget, Tammo>
{

public:

	//! TastoutCimg constructor calls Tastout constructor
	TastoutCimg() : Tastout<Ttarget, Tammo>(){}
	
	
	TASTOUT writeCImg(cimg_library::CImg<Ttarget> & targetData, cimg_library::CImg<Tammo> & ammoData)
	{
		return this->write(targetData.data(), targetData.size(), ammoData.data(), ammoData.size());
	}
	
	TASTOUT readCImg(cimg_library::CImg<Ttarget> & tattooedData, cimg_library::CImg<Tammo> & receivedData)
	{
		std::vector<Tammo> receivedVector;
		if(this->read(tattooedData.data(), tattooedData.size(), receivedVector) != TASTOUT::SUCCESS) return TASTOUT::READ_FAILLURE;
		
		receivedData.assign(receivedVector.size());
		
		memcpy(receivedData.data(), receivedVector.data(), receivedVector.size()*sizeof(Tammo));
		
		return TASTOUT::SUCCESS;
	}

	
};


#endif
