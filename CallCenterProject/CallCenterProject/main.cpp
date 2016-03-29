
#include <iostream>
#include <windows.h>
#include "CallCenter.h"
#include "Caller.h"
#include <thread> 
#include <vector>


using namespace std;


//A function wrapper so i could pass in a function with a class
void rf(CallCenter* CC, Caller& m)
{
	CC->Call(m);
}
//Cocurrent Render function
void rf2(CallCenter* CC)
{
	while (true)
	{
		CC->RenderOffice();
	}

}

int main()
{
	int choice = 0;
	int numOfFreshers = 0;
	do
	{
		//Menu option and clear options
		system("cls");
		cout << "Please select from the following options:\n1. Start Office\n2. Close Office\n";
		cin.sync(); // clear the input buffer
		cin >> choice;
		switch (choice)
		{
			case 1:
			{
				//grabing Freshers value
				int numOfCallers = 0;
				cout << "Input Number of Freshers" << endl;
				cin >> numOfFreshers;
				//grabing Caller value
				cout << "Input Number of Caller" << endl;
				cin >> numOfCallers;
				//With all the info now start the call center
				CallCenter CC1;
	
				CC1.StartOffice(numOfFreshers);
				system("CLS");
				//Creating messages threads
				std::vector<std::thread>t;
				Caller* m = new Caller[numOfCallers];
				//Passing in every message in threads into the office class function
				for (int i = 0; i < numOfCallers; i++)
				{
					m[i].SetID(i);
					t.push_back(thread(rf, &CC1, m[i]));
				}
				t.push_back(thread(rf2, &CC1));

				int choice2 = 0;

				while (choice2 != 2)
				{
					for (int i = 0; i < numOfCallers; i++)
					{
						if (t[i].joinable())
						{
							t[i].join();
							//cout << i << " has been solved" << endl;
						}
					}
				}
				break;
			}
			case 2:
			{
				cout << "Program will not exit" << endl;	
				break;
			}
			default:
			{
				cout << "Output Error" << endl;
				Sleep(2000);
				break;
			}
		}
		//Clearing cin for each menu options
		if (cin.fail())
		{
			cin.clear();
			cin.get();
			continue;
		}
	} while (choice != 2);
	return 0;
}