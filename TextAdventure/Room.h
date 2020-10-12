#pragma once
#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string>
using namespace std;

struct Room
{
	Room();
	Room(string name, string desc);
	void SetNeighbors(Room* ptrNorth, Room* ptrSouth, Room* ptrWest, Room* ptrEast);
	void Setup(string name = "", string description = "");

	void OutputRoomInfo();
	void OutputNeighbors();

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
	else if (ptrNeighborSouth != nullptr) { cout << "(S)South"; }
	else if (ptrNeighborEast != nullptr) { cout << "(E)East"; }
	else if (ptrNeighborWest != nullptr) { cout << "(W)West"; }

	cout << endl;
};

void Room::OutputRoomInfo()
{
	cout << Name << endl << Description << endl;
	OutputNeighbors();
	cout << endl;
}


#endif // !ROOM_H

