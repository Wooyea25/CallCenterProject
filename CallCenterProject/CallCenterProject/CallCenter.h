#ifndef INCLUDED_CALLCENTER_H
#define INCLUDED_CALLCENTER_H

//====================================================================================================
// Filename:	CallCenter.h
// Created by:	Jack Ng
// Description:	Class for a Call Center.
// Date: 03/06/2016
// Changed on 03/13/2016
//====================================================================================================



//====================================================================================================
// Includes
//====================================================================================================
#include <vector>
#include "TL.h"
#include "PM.h"
#include <mutex>


//====================================================================================================
// Class Declarations
//====================================================================================================

class TL;
class PM;
class Fresher;
class Caller;



class CallCenter
{
public:
	CallCenter();
	~CallCenter();


	// Accessors
	int GetmNumFresher() const					{ return mNumFresher; }
	
	//CPP
	void Call(Caller& caller);			//Cocurrently call to different people in the call center

	void StartOffice(int fresherNum);
	void RenderOffice();
	void EndOffice();

	// Mutators
	void AddFresher(int num);


private:

	std::mutex x;
	int mNumFresher;

	Fresher* mFreshers;	
	TL mTL;
	PM mPM;
	

	bool Assign(Caller& caller);		//Function where it will internally assign all Calls
};















#endif	//#ifndef INCLUDED_CallCenter_H