#include "Room.h"

using namespace std;

Room::Room()
{
	Setup();
};

Room::Room(string name, string desc, string item)
{
	Setup(name, desc, item);
};

//funzione che determina i valori di setup di una stanza
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

//setup dei pointers per il riconoscimento delle stanze e la loro locazione
void Room::SetNeighbors(Room* ptrNorth, Room* ptrSouth, Room* ptrWest, Room* ptrEast)
{
	ptrNeighborNorth = ptrNorth;
	ptrNeighborSouth = ptrSouth;
	ptrNeighborEast = ptrEast;
	ptrNeighborWest = ptrWest;
};

//funzione che printa le stanze nelle quali puoi muoverti dalla tua current 
void Room::OutputNeighbors()
{
	cout << "You can go: ";

	if (ptrNeighborNorth != nullptr) { cout << "(N)North"; }
	if (ptrNeighborSouth != nullptr) { cout << "(S)South"; }
	if (ptrNeighborEast != nullptr) { cout << "(E)East"; }
	if (ptrNeighborWest != nullptr) { cout << "(W)West"; }

	cout << endl;
};


//funzione che printa nome e descrizione della stanza
void Room::OutputRoomName()
{
	cout << Name << endl;
	cout << Description << endl;
	cout << endl;
}

//funzione che printa stanze vicine e eventuale item presente 
void Room::OutputRoomData()
{

	cout << Item << endl;
	OutputNeighbors();
	cout << endl;
}

/*
funzione che restituisce true se una stanza è adiacente a quella current
*/
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