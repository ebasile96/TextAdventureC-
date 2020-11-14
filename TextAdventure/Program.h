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
		string HandleUserInput();
		int CreateRoom(string name, string description, string item);
		Room* m_ptrCurrentRoom;
		vector<Room*> m_rooms;
		bool n_done;
		vector<string> Bag{"Knife"};
		bool itemFound;
		string story = "Hi, you find yourself in your bedroom, try to escape from home to reach your friends at the party!";
	
};

Program::Program() 
{
	m_ptrCurrentRoom = nullptr;
	n_done = false;
	SetupRooms();
}

void Program::Run() 
{
	cout << story << endl;
	cout << "command list : " << endl;
	cout << "(N)North - to go north" << endl;
	cout << "(S)South - to go south" << endl;
	cout << "(E)East - to go east" << endl;
	cout << "(W)West - to go west" << endl;
	cout << "BAG - to inspect your inventory" << endl;
	cout << "LOOK - to inspect the room you find yourself in" << endl;
	cout << "PICK - to collect any useful object in the room" << endl;
	cout << "USE + (ITEM NAME) - to use your items" << endl;

	string currentStatus = "";
	while (!n_done)
	{
		m_ptrCurrentRoom->OutputRoomName();
		currentStatus = HandleUserInput();
		

		cout << "\t" << currentStatus << endl;
		
	} 

	if (n_done) {
		cout << "GAME OVER" << endl;
	}


}

void Program::SetupRooms() 
{
	//create room with name and description
	int startingRoom = CreateRoom("Bedroom", "This is your bedroom", "Nothing usefull here");
	int room1 = CreateRoom("Hallway", "1st floor - Hallway", "Nothing usefull here");
	int room2 = CreateRoom("Jenny's bedroom", "This is your sister's bedroom, you shouldn't be here...", "Nothing usefull here");
	int room3 = CreateRoom("Entrance hall", "This is the entrance hall, the door is locked.", "Nothing usefull here");
	int gunRoom = CreateRoom("Kitchen", "You are in the kitchen, there is a bottle of wine.", "Bottle of wine");
	int monsterRoom = CreateRoom("Livingroom", "Your parents are watching TV on the couch, be careful!", "Nothing usefull here");
	int keyRoom = CreateRoom("Shelf", "The car's keys must be here somewhere...", "key");
	int room7 = CreateRoom("Garage's stairs", "You are walking down the stairs...", "Nothing usefull here");
	int exitRoom = CreateRoom("Garage", "You can now escape and reach your friends at the party!", "Nothing usefull here");



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

int Program::CreateRoom(string name, string description, string item) 
{
	int index = m_rooms.size();
	Room* room = new Room;
	room->Setup(name, description, item);
	m_rooms.push_back(room);

	return (index);
};

void Program::Use(string _item) 
{
	//cerca l'item, se lo trovi usalo
	for (int i = 0; i < Bag.size(); i++)
	{
		if (Bag[i] == _item) 
		{
			itemFound = true;
			cout << "You used " + _item << endl;
		}
	}
	if (!itemFound) 
	{
		cout << _item + " not found." << endl;
	}
	
	

}

string Program::HandleUserInput() 
{
	string currentStatus = "";
	string userInput;
	cout << "Now what?" << endl;
	cout << ">" << endl;
	getline(cin, userInput);
	if (userInput == "LOOK") 
	{
		m_ptrCurrentRoom->OutputRoomData();
		
	}
	else if (m_ptrCurrentRoom->Item != "Nothing usefull here" && userInput == "PICK")
	{
		string _item = m_ptrCurrentRoom->Item;
		Bag.push_back(_item);
		cout << "You picked " + m_ptrCurrentRoom->Item << endl;
		cout << "You put " + m_ptrCurrentRoom->Item + " in your bag." << endl;
	}
	else if (userInput == "BAG") 
	{
		for (int i = 0; i < Bag.size(); i++) 
		{
			//currentStatus = Bag[i]; 
			cout << Bag[i] << endl;
		}
	}
	else if (userInput == "N")
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
	else if (userInput == "USE KNIFE") 
	{
		Use("Knife");
		if (m_ptrCurrentRoom->Name == "Livingroom" && itemFound == true) 
		{
			currentStatus = "You killed your family";
			n_done = true;
		}
		else 
		{
			currentStatus = "It can't be used here...";
		}
	}
	else if (userInput == "USE KEY") 
	{
		Use("key");
		if (m_ptrCurrentRoom->Name == "Garage" && itemFound == true) 
		{
			currentStatus = "Congratulations! You successfully escaped, now you can reach the party!";
			n_done = true;
		}
		else 
		{
			currentStatus = "It can't be used here...";
		}
	}
	else if (userInput == "USE BOTTLE OF WINE") 
	{
		Use("Bottle of wine");
		if (itemFound) 
		{
			currentStatus == "You got drunk!... Your parents spotted you and confined you to your room.";
			n_done = true;
		}
		else
		{
			currentStatus = "Search for some wine to bring to the party!";
		}
	}
	else {
		currentStatus = "Unknown command...";
	}

	return currentStatus;
}


#endif // !PROGRAM_H
