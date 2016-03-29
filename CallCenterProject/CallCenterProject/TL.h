#ifndef INCLUDED_TL_H
#define INCLUDED_TL_H

//====================================================================================================
// Filename:	TL.h
// Created by:	Jack Ng
// Description:	Class for a technical lead.
// Date: 03/05/2016
//====================================================================================================



//====================================================================================================
// Includes
//====================================================================================================
#include <vector>


//====================================================================================================
// Class Declarations
//====================================================================================================
class Caller;


class TL
{
public:
	TL();
	~TL();


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















#endif	//#ifndef INCLUDED_TL_H