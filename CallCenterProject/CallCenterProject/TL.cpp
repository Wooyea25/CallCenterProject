//====================================================================================================
// Filename:	TL.cpp
// Created by:	Jack Ng
// Date: 03/05/2016
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "TL.h"
#include "Caller.h"

#include<iostream>
#include <windows.h>
#include <time.h>

using namespace std;

//====================================================================================================
// Class Definitions
//====================================================================================================

TL::TL()
	: mAvailable(true)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

TL::~TL()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

bool TL::RecieveCall(Caller& caller)
{
	mCallerInfo.push_back(caller.GetID()+1);
	//cout << "TL has answered your caller " << caller.GetID() + 1 << endl;
	//Simple Dice Roll
	srand(time(NULL));
	int y = rand() % 6;
	//Sleep 2 second so we could read message
	Sleep(2000);
	//if its true set message flag to -1 and problem is fixed
	if (y >= 2)
	{
		//cout << "TL has fixed your problem" << endl;
		caller.SetStatus(CallerStatus::LevelSolved);
		Sleep(2000);
		mAvailable = true;
		return true;
	}
	//else set flag level to 1 and return false
	else
	{
		//cout << "TL can't fix caller " << caller.GetID()+1 << "'s problem" <<  endl;
		Sleep(2000);
		caller.SetStatus(CallerStatus::LevelThree);
		mAvailable = true;
		return false;
	}
}

//----------------------------------------------------------------------------------------------------
