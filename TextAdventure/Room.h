#pragma once
#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string>
using namespace std;

enum Direction {NORTH = 0, SOUTH = 1, EAST = 2, WEST = 3};

struct Room
{
	Room();
	Room(string name, string desc);
	void SetNeighbors(Room* ptrNorth, Room* ptrSouth, Room* ptrWest, Room* ptrEast);
	void Setup(string name = "", string description = "");

	void OutputRoomInfo();
	void OutputNeighbors();
	bool CanGo(Direction direction);

	string Name;
	string Description;
	Room* ptrNeighborNorth;
	Room* ptrNeighborSouth;
	Room* ptrNeighborWest;
	Room* ptrNeighborEast;
};

Room::Room() 
{
	Setup();
};
Room::Room(string name, string desc) 
{
	Setup(name, desc);
};
void Room::Setup(string name, string description) 
{
	this->Name = name;
	this->Description = description;
	ptrNeighborNorth = nullptr;
	ptrNeighborSouth = nullptr;
	ptrNeighborEast = nullptr;
	ptrNeighborWest = nullptr;
};
void Room::SetNeighbors(Room* ptrNorth, Room* ptrSouth, Room* ptrWest, Room* ptrEast) 
{
	ptrNeighborNorth = ptrNorth;
	ptrNeighborSouth = ptrSouth;
	ptrNeighborEast = ptrEast;
	ptrNeighborWest = ptrWest;
};

void Room::OutputNeighbors() 
{
	cout << "You can go: ";

	if (ptrNeighborNorth != nullptr) { cout << "(N)North"; }
	if (ptrNeighborSouth != nullptr) { cout << "(S)South"; }
	if (ptrNeighborEast != nullptr) { cout << "(E)East"; }
	if (ptrNeighborWest != nullptr) { cout << "(W)West"; }

	cout << endl;
};

void Room::OutputRoomInfo()
{
	cout << Name << endl << Description << endl;
	OutputNeighbors();
	cout << endl;
}

bool Room::CanGo(Direction direction) 
{
	if (direction == NORTH && ptrNeighborNorth != nullptr) 
	{
		return true;
	}
	else if (direction == SOUTH && ptrNeighborSouth != nullptr)
	{
		return true;
	}
	else if (direction == EAST && ptrNeighborEast != nullptr)
	{
		return true;
	}
	else if (direction == WEST && ptrNeighborWest != nullptr)
	{
		return true;
	}

	return false;
}

#endif // !ROOM_H

