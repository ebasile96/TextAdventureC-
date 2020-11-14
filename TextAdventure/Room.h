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
	Room(string name, string desc, string item);
	void SetNeighbors(Room* ptrNorth, Room* ptrSouth, Room* ptrWest, Room* ptrEast);
	void Setup(string name = "", string description = "", string item ="");

	void OutputRoomName();
	void OutputNeighbors();
	void OutputRoomData();
	bool CanGo(Direction direction);

	string Name;
	string Description;
	string Item;
	Room* ptrNeighborNorth;
	Room* ptrNeighborSouth;
	Room* ptrNeighborWest;
	Room* ptrNeighborEast;
};

Room::Room() 
{
	Setup();
};
Room::Room(string name, string desc, string item) 
{
	Setup(name, desc, item);
};
void Room::Setup(string name, string description, string item) 
{
	this->Name = name;
	this->Description = description;
	this->Item = item;
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

void Room::OutputRoomName()
{
	cout << Name << endl;
	cout << Description << endl;
	cout << endl;
}

void Room::OutputRoomData() 
{

	cout << Item << endl;
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

