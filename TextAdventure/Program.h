#pragma once
#ifndef PROGRAM_H
#define PROGRAM_H
#include<iostream>
#include <vector>
#include <string>
#include "Room.h"

using namespace std;

class Program 
{
	public:
		void Run();
		Program();

	private:
		void SetupRooms();
		void Use(string _item);
		void CheckWin();
		void ShowCommands();
		string HandleUserInput();
		int CreateRoom(string name, string description, string item);
		Room* m_ptrCurrentRoom;
		vector<Room*> m_rooms;
		bool n_done;
		vector<string> Bag{"Knife"};
		bool itemFound;
		bool parentsDistracted = false;
		bool WineFound;
		string story = "Hi, you find yourself in your bedroom, try to escape from home to reach your friends at the party!";
	
};




#endif // !PROGRAM_H
