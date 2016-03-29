//====================================================================================================
// Filename:	Fresher.cpp
// Created by:	Jack Ng
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Fresher.h"
#include "Caller.h"

#include<iostream>
#include <windows.h>
#include <time.h>


using namespace std;

//====================================================================================================
// Class Definitions
//====================================================================================================

//Setting all Fresher available in the begining
Fresher::Fresher()
	: mAvailable(true)
	, mID(-1)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

Fresher::~Fresher()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------
bool Fresher::RecieveCall(Caller& caller)
{
	mCallerInfo.push_back(caller.GetID()+1);
	//cout << "Fresher " << GetID()+1 << " has answered your call: "<< caller.GetID()+1 << endl;
	//Simple Dice Roll
	srand(time(NULL));
	int y = rand() % 6;
	//Sleep 2 second so we could read message
	Sleep(2000);
	if (y >= 3)
	{
		//cout << "Fresher " << GetID() + 1 << " has fixed your problem: " << caller.GetID()+1 << endl;
		caller.SetStatus(CallerStatus::LevelSolved);	//Set problem is solved
		Sleep(2000);
		mAvailable = true;
		return true;
	}
	else
	{
		//cout << "Fresher " << GetID() + 1 << " can't fix your problem: " << caller.GetID()+1 << endl;
		//Can not fix problem and change caller status to level two 
		caller.SetStatus(CallerStatus::LevelTwo);
		Sleep(2000);
		mAvailable = true;
		return false;
	}
}

//----------------------------------------------------------------------------------------------------
