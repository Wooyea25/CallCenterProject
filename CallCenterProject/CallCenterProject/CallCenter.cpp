//====================================================================================================
// Filename:	CallCenter.cpp
// Created by:	Jack Ng
// Date: 03/06/2016
// Changed on 03/13/2016
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CallCenter.h"
#include <iostream>
#include "Fresher.h"
#include "Caller.h"
#include <windows.h>


using namespace std;

//====================================================================================================
// Function Definitions
//====================================================================================================

//Private Function to make sure when screen is cleared it will not blink
void ClearScreen()
{
	COORD Position;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

//----------------------------------------------------------------------------------------------------


//====================================================================================================
// Class Definitions
//====================================================================================================

CallCenter::CallCenter()
	: mNumFresher(0)
	, mTL()
	, mPM()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CallCenter::~CallCenter()
{
	//Making sure mFreshers memory is deleted when it is destructed;
	EndOffice();
}

//----------------------------------------------------------------------------------------------------
//Fucntion where it assign all the callers
bool CallCenter::Assign(Caller& caller)
{
	Fresher* tempFPtr = mFreshers;
	switch (caller.GetStatus())
	{
		case CallerStatus::LevelSolved:
		{
			return true;
		}
		case CallerStatus::LevelOne:
		{
			//looping through each Fresher to see if they are available
			for (int i = 0; i < mNumFresher; i++)
			{
				if (tempFPtr->IsAvailable())
				{
					//Assign Fresher to Caller and Set Fresher to unavailable
					caller.SetAssign(i);
					tempFPtr->SetAvailable(false);
					return false;
				}
				tempFPtr++;
			}

			caller.SetAssign(-1);
			//Loop through all Fresher and they are all busy so set level to two
			caller.SetStatus(CallerStatus::LevelTwo);
		}
		case CallerStatus::LevelTwo:
		{
			//if TL is free
			if (mTL.IsAvailable())
			{
				//Assign TL to Caller and Set TL to unavailable
				caller.SetAssign(-1);		//-1 is TL	
				mTL.SetAvailable(false);
				return false;
			}
			else
			{
				caller.SetStatus(CallerStatus::LevelThree);
				caller.SetAssign(-3);
			}
			//TL is busy so set level to three
			
		}
		case CallerStatus::LevelThree:
		{
			//if PM is free and Set PM to unavailable
			if (mPM.IsAvailable())
			{
				caller.SetAssign(-2);		//-2 is PM
				mPM.SetAvailable(false);
				return false;
			}
			else
			{
				caller.SetAssign(-3);
			}
			break;
		}
		default:
		{
			//cout<<"error at Call->Assign Function->default" <<endl;
		}
	}
}

//----------------------------------------------------------------------------------------------------
//Fucntion where it start all the calls
void CallCenter::Call(Caller& caller)
{
	Fresher* tempFPtr = mFreshers;
	bool Solved = false;
	while (!Solved)
	{
		x.lock();
		Solved = Assign(caller);
		x.unlock();
		if (Solved)
		{
			break;
		}
		if (caller.GetAssign() == -1)
		{
			mTL.RecieveCall(caller);
		}
		else if (caller.GetAssign() == -2)
		{
			mPM.RecieveCall(caller);
		}
		else if (caller.GetAssign() >= 0 && caller.GetAssign() <= mNumFresher)
		{
			mFreshers[caller.GetAssign()].RecieveCall(caller);
		}
		else
		{
			//Everyone is either busy or PM and TL is with someone right now
			//cout << "Error->CallCenter->Call" << endl;
		}
	}	
}

//First attempt, perfectly working code, problem is the call is recieved cocurrently but the
//people in office is working linearly
/*void CallCenter::Call(Message& caller)
{
	//Copy pointer to local pointer
	Fresher* tempFPtr = mFreshers;

	x.lock();

	for (int i = 0; i < mNumFresher; i++)
	{
		//if any fresher is free RecieveCall is called,
		if (tempFPtr->IsAvailable())
		{
			tempFPtr->RecieveCall(caller);
			break;
		}
		tempFPtr++;
	}
	//TL will recieve call if no fresher is free
	if (caller.GetSolved() != true)
	{
		if (mTL.IsAvailable())
		{
			mTL.RecieveCall(caller);
		}
	}
	//PM will recieve call if no one is free
	while (caller.GetSolved() != true)
	{
		if (mTL.IsAvailable())
		{
			mPM.RecieveCall(caller);
		}
	}
	x.unlock();
}
*/
//----------------------------------------------------------------------------------------------------

//Creating all the Freshers at the start of Office Creation
void CallCenter::StartOffice(int fresherNum)
{
	mNumFresher = fresherNum;
	mFreshers = new Fresher[fresherNum];
	for (int i = 0; i < fresherNum; i++)
	{
		if (mFreshers[i].GetID() == -1)
		{
			mFreshers[i].SetID(i);
		}
	}
}

//----------------------------------------------------------------------------------------------------
//Render all calls on screen
void CallCenter::RenderOffice()
{

	ClearScreen();
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//Printing Freshers
	for (int i = 0; i < mNumFresher; i++)
	{
		SetConsoleTextAttribute(hOut, (mFreshers[i].IsAvailable() ? 2:14));
		cout << "Fresher: " << (mFreshers[i].GetID() + 1);
		vector<int>tempCallerInfo = mFreshers[i].GetCallerInfo();
		for (int j = 0; j < tempCallerInfo.size(); j++)
		{
			SetConsoleTextAttribute(hOut, 13);
			cout << " " << tempCallerInfo[j];
		}
		cout << endl;
	}
	//Printing TL
	SetConsoleTextAttribute(hOut, (mTL.IsAvailable()? 2 : 14));
	cout << "Tech Lead: " ;
	vector<int>tempTLCallerInfo = mTL.GetCallerInfo();
	for (int j = 0; j < tempTLCallerInfo.size(); j++)
	{
		SetConsoleTextAttribute(hOut, 13);
		cout << " " << tempTLCallerInfo[j];
	}
	cout << endl;
	//Printing PM
	SetConsoleTextAttribute(hOut, (mPM.IsAvailable() ? 2 : 14));
	cout << "Product Manager: ";
	vector<int>tempPMCallerInfo = mPM.GetCallerInfo();
	for (int j = 0; j < tempPMCallerInfo.size(); j++)
	{
		SetConsoleTextAttribute(hOut, 13);
		cout << " " << tempPMCallerInfo[j];
	}
	cout << endl;
	
	int i = 0;
	while (i < 5)
	{
		i++;
		cout << endl;
	}

}

//----------------------------------------------------------------------------------------------------


void CallCenter::EndOffice()
{
	delete[] mFreshers;
	mFreshers = nullptr;
}

//----------------------------------------------------------------------------------------------------


