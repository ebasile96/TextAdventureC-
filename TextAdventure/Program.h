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
		string HandleUserInput();
		int CreateRoom(string name, string description);
		Room* m_ptrCurrentRoom;
		vector<Room*> m_rooms;
		bool n_done;

};

Program::Program() 
{
	m_ptrCurrentRoom = nullptr;
	n_done = false;
	SetupRooms();
}

void Program::Run() 
{

	string currentStatus = "";
	while (!n_done)
	{
		m_ptrCurrentRoom->OutputRoomInfo();

		currentStatus = HandleUserInput();
		

		cout << "\t" << currentStatus << endl;
		cout << endl << "Press Enter to Continue..." << endl;
	} 

}

void Program::SetupRooms() 
{
	//create room with name and description
	int startingRoom = CreateRoom("Room0", "asdasd");
	int room1 = CreateRoom("Room1", "asdasd");
	int room2 = CreateRoom("Room2", "asdasd");
	int room3 = CreateRoom("Room3", "asdasd");
	int gunRoom = CreateRoom("Room4", "asdasd");
	int monsterRoom = CreateRoom("Room5", "asdasd");
	int keyRoom = CreateRoom("Room6", "asdasd");
	int room7 = CreateRoom("Room7", "asdasd");
	int exitRoom = CreateRoom("Room8", "asdasd");



	//setup neighbors
	m_rooms[startingRoom]->SetNeighbors(nullptr, m_rooms[1], nullptr, nullptr);
	m_rooms[room1]->SetNeighbors(m_rooms[startingRoom], m_rooms[3], m_rooms[2], nullptr);
	m_rooms[room2]->SetNeighbors(nullptr, nullptr, nullptr, m_rooms[1]);
	m_rooms[room3]->SetNeighbors(m_rooms[1], m_rooms[monsterRoom], nullptr, m_rooms[gunRoom]);
	m_rooms[gunRoom]->SetNeighbors(nullptr, nullptr, m_rooms[3], nullptr);
	m_rooms[monsterRoom]->SetNeighbors(m_rooms[3], m_rooms[keyRoom], nullptr, nullptr);
	m_rooms[keyRoom]->SetNeighbors(m_rooms[monsterRoom], nullptr, nullptr, m_rooms[7]);
	m_rooms[room7]->SetNeighbors(nullptr, m_rooms[exitRoom], m_rooms[keyRoom], nullptr);
	m_rooms[exitRoom]->SetNeighbors(m_rooms[7], nullptr, nullptr, nullptr);

	m_ptrCurrentRoom = m_rooms[startingRoom]; 

}

int Program::CreateRoom(string name, string description) 
{
	int index = m_rooms.size();
	Room* room = new Room;
	room->Setup(name, description);
	m_rooms.push_back(room);

	return (index);
};

string Program::HandleUserInput() 
{
	string currentStatus = "";
	string userInput;
	cout << "Now what?" << endl;
	cout << ">" << endl;
	getline(cin, userInput);

	if (userInput == "N")
	{
		if (m_ptrCurrentRoom->CanGo(NORTH))
		{
			currentStatus = "You went North";
			m_ptrCurrentRoom = m_ptrCurrentRoom->ptrNeighborNorth;
		}
		else
		{
			currentStatus = "You can't go North!";
		}
	}
	else if (userInput == "S")
	{
		if (m_ptrCurrentRoom->CanGo(SOUTH))
		{
			currentStatus = "You went South";
			m_ptrCurrentRoom = m_ptrCurrentRoom->ptrNeighborSouth;
		}
		else
		{
			currentStatus = "You can't go South!";
		}
	}
	else if (userInput == "E")
	{
		if (m_ptrCurrentRoom->CanGo(EAST))
		{
			currentStatus = "You went East";
			m_ptrCurrentRoom = m_ptrCurrentRoom->ptrNeighborEast;
		}
		else
		{
			currentStatus = "You can't go East!";
		}
	}
	else if (userInput == "W")
	{
		if (m_ptrCurrentRoom->CanGo(WEST))
		{
			currentStatus = "You went West";
			m_ptrCurrentRoom = m_ptrCurrentRoom->ptrNeighborWest;
		}
		else
		{
			currentStatus = "You can't go West!";
		}
	}

	else {
		currentStatus = "Unknown command...";
	}

	return currentStatus;
}


#endif // !PROGRAM_H
