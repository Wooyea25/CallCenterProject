#ifndef INCLUDED_CALLER_H
#define INCLUDED_CALLER_H

//====================================================================================================
// Filename:	Caller.h
// Created by:	Jack Ng
// Description:	Class for a Caller.
// Date: 03/12/2016
//====================================================================================================


//====================================================================================================
// Includes
//====================================================================================================


//====================================================================================================
// Enum Declarations
//====================================================================================================
enum CallerStatus
{
	LevelSolved,	//Caller Solved
	LevelOne,		//Fresher level - 1
	LevelTwo,		//TL level - 2 
	LevelThree		//PM level - 3
};


//====================================================================================================
// Class Declarations
//====================================================================================================

class Caller
{
public:
	Caller();
	~Caller();


	// Accessors
	int GetID() const								{ return mID; }
	CallerStatus GetStatus() const					{ return mStatus; }
	int GetAssign() const							{ return mAssigned; }



	// Mutators
	void SetID(int id)								{ mID = id; }
	void SetStatus(CallerStatus s)					{ mStatus = s; }
	void SetAssign(int a)							{ mAssigned = a; }


private:
	int mID;
	CallerStatus mStatus;	//level of urgence
	
	int mAssigned;	//Currently assigned to which officer
};















#endif	//#ifndef INCLUDED_Caller_H