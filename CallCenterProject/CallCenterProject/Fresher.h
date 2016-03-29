#ifndef INCLUDED_FRESHER_H
#define INCLUDED_FRESHER_H

//====================================================================================================
// Filename:	Fresher.h
// Created by:	Jack Ng
// Description:	Class for a singler fresher employee.
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

class Fresher
{
public:

	Fresher();
	~Fresher();


	// Accessors
	bool IsAvailable() const					{ return mAvailable; }
	int GetID() const							{ return mID; }
	std::vector<int> GetCallerInfo()				{ return mCallerInfo; }


	//CPP
	bool RecieveCall(Caller& caller);

	// Mutators
	void SetAvailable(bool available)			{ mAvailable = available; }
	void SetID(int id)							{ mID = id; }


private:
	bool mAvailable;
	int mID;

	std::vector<int> mCallerInfo;
};















#endif	//#ifndef INCLUDED_FRESHER_H