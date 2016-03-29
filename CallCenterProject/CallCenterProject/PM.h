#ifndef INCLUDED_PM_H
#define INCLUDED_PM_H

//====================================================================================================
// Filename:	PM.h
// Created by:	Jack Ng
// Description:	Class for a Product Manager.
// Date: 03/06/2016
//====================================================================================================



//====================================================================================================
// Includes
//====================================================================================================
#include <vector>

//====================================================================================================
// Class Declarations
//====================================================================================================

class Caller;

class PM
{
public:
	PM();
	~PM();


	// Accessors
	bool IsAvailable() const					{ return mAvailable; }
	std::vector<int> GetCallerInfo()				{ return mCallerInfo; }
	//CPP
	bool RecieveCall(Caller& caller);

	// Mutators
	void SetAvailable(bool available)			{ mAvailable = available; }


private:
	bool mAvailable;

	std::vector<int>mCallerInfo;
};















#endif	//#ifndef INCLUDED_PM_H