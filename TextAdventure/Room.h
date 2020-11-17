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



#endif // !ROOM_H

