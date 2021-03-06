#include "Program.h";

using namespace std;

//setup stanze e inizializzazione del programma
Program::Program()
{
	m_ptrCurrentRoom = nullptr;
	n_done = false;
	SetupRooms();
}

//funzione di Run del programma entro il quale vengono gestiti input e azioni
void Program::Run()
{
	//print di comandi e introduzione alla storia
	cout << story << endl;
	cout << "" << endl;
	ShowCommands();
	cout << "" << endl;
	string currentStatus = "";
	//mentre il programma � in funzione
	while (!n_done)
	{
		m_ptrCurrentRoom->OutputRoomName();
		currentStatus = HandleUserInput();


		cout << "\t" << currentStatus << endl;

		//lose condition
		if (m_ptrCurrentRoom->Name == "Livingroom" && parentsDistracted == false) 
		{
			cout << "Your parents caught you!" << endl;
			n_done = true;
 		}

	}
	//termine programma
	if (n_done) {
		cout << "THE END" << endl;
	}


}

//funzione che printa la lista dei comandi disponibili
void Program::ShowCommands() 
{

	cout << "command list : " << endl;
	cout << "(N)North - to go north" << endl;
	cout << "(S)South - to go south" << endl;
	cout << "(E)East - to go east" << endl;
	cout << "(W)West - to go west" << endl;
	cout << "BAG - to inspect your inventory" << endl;
	cout << "LOOK - to inspect the room you find yourself in" << endl;
	cout << "PICK - to collect any useful object in the room" << endl;
	cout << "USE + (ITEM NAME) - to use your items" << endl;
	cout << "INTERACT - to interact with the room" << endl;
	cout << "COMMANDS - to show command keys" << endl;
}

//setup di tutte le room: nome, descrizione, item, interactions e localizzazione delle stanze
void Program::SetupRooms()
{
	//create room with name and description
	int startingRoom = CreateRoom("Bedroom", "This is your bedroom", "Nothing usefull here");
	int room1 = CreateRoom("Hallway", "1st floor - Hallway", "Nothing usefull here");
	int room2 = CreateRoom("Jenny's bedroom", "This is your sister's bedroom, you shouldn't be here...", "Nothing usefull here");
	int room3 = CreateRoom("Entrance hall", "This is the entrance hall, the door is locked. Watch out for your parents in the livingroom (S)South!", "Nothing usefull here");
	int gunRoom = CreateRoom("Kitchen", "You are in the kitchen, there is a bottle of wine.", "Bottle of wine");
	int monsterRoom = CreateRoom("Livingroom", "Your parents are watching TV on the couch, be careful!", "Nothing usefull here");
	int keyRoom = CreateRoom("Shelf", "The car's keys must be here somewhere...", "key");
	int room7 = CreateRoom("Garage's stairs", "You are walking down the stairs...", "Nothing usefull here");
	int exitRoom = CreateRoom("Garage", "Use the key and escape!", "Nothing usefull here");



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

//funzione che va a generare tutte le stanze e ad inserirle in un vector
int Program::CreateRoom(string name, string description, string item)
{
	int index = m_rooms.size();
	Room* room = new Room;
	room->Setup(name, description, item);
	m_rooms.push_back(room);

	return (index);
};

//funzione di utilizzo per gli items
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

//funzione di check per la win condition
void Program::CheckWin() 
{
	for (int i = 0; i < Bag.size(); i++)
	{
		if (Bag[i] == "Bottle of wine") 
		{
			WineFound = true;
		}
		
	}
}

//funzione che gestisce gli input e aggiorna il current status del giocatore
string Program::HandleUserInput()
{
	string currentStatus = "";
	string userInput;
	cout << "Now what?" << endl;
	cout << ">" << endl;
	getline(cin, userInput);
	cout.flush();
	system("cls");
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
			CheckWin();
			if (WineFound == true) 
			{
				currentStatus = "Congratulations! You successfully escaped, now you can reach the party!";
				n_done = true;
			}
			else 
			{
				currentStatus = "You must find some wine first";
			}
			
		}
		else
		{
			currentStatus = "You must find the key to escape...";
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
	else if (userInput == "INTERACT") {

	if (m_ptrCurrentRoom->Name == "Kitchen")
	{
		currentStatus = "You opened the gas valve.";
		cout << "The alarm started" << endl;
		cout << "Your parents are distracted, go find the key!" << endl;
		parentsDistracted = true;
		m_rooms[5]->Description = "Parents are distracted";
	}
	else 
	{
		currentStatus = "Nothing interactable here...";
	}
}
	else if (userInput == "COMMANDS") 
{
ShowCommands();
}
	else {
		currentStatus = "Unknown command...";
	}

	return currentStatus;
}