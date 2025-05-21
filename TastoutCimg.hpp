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
	
	/**
	 * \param [inout] targetData CImg object to receive tattooing
	 * \param [in] ammoData CImg objet with data to be tattooed
	 **/
	TASTOUT write(cimg_library::CImg<Ttarget> & targetData, cimg_library::CImg<Tammo> & ammoData)
	{
		return Tastout<Ttarget, Tammo>::write(targetData.data(), targetData.size(), ammoData.data(), ammoData.size());
	}
	
	/**
	 * \param [in] tattooedData CImg object with tattooed data
	 * \param [out] receivedData CImg objet with received data
	 **/
	TASTOUT read(cimg_library::CImg<Ttarget> & tattooedData, cimg_library::CImg<Tammo> & receivedData)
	{
		std::vector<Tammo> receivedVector;
		if(Tastout<Ttarget, Tammo>::read(tattooedData.data(), tattooedData.size(), receivedVector) != TASTOUT::SUCCESS) return TASTOUT::READ_FAILLURE;
		
		receivedData.assign(receivedVector.data(), receivedVector.size());
		
		return TASTOUT::SUCCESS;
	}	
};


#endif
