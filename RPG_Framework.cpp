// RPG_Framework.cpp : Defines the entry point for the console application.
#include "Hero.h"
#include "Painter.h"
#include "World.h"
#include "Monster.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <iterator>
#include <sstream>
#include <cctype>
#include <Windows.h>
#undef max;

using namespace std;

//Global Initialization
Hero Player;
WorldMap World;
Monster Enemy;
Room Cell;
GameState Game_State;
Combat Fight;

//Prototyping
int Choose_Job(int option);
void Receive_Command();
void Encounter(int tile);
bool Playing(true);

//Action Functions
#pragma region Action-Functions

vector<string> Split(string input) {
	stringstream ss(input);
	string output;
	vector<string> result;
	while (getline(ss, output, ' ')) {
		result.push_back(output);
	}
	return result;
}

void Aligned(string input, int width) {
	cout << left << setw(width) << input;
}

int Roll_Dice(int min, int max) {
	int roll;
	return roll = rand() % (max - min + 1) + min;
}

int CheckMove(int Move) {
	Colorize Format;
	switch (Move) {
	case 1:
		Format.WorldPaint(4, "The mountain looks difficult to climb, you choose to go elsewhere.\n");
		return 0;
		break;
	case 5:
	case 12:
		Format.WorldPaint(4, "There is a body of water blocking your path.\n");
		return 0;
		break;
	case 7:
	case 14:
		Format.WorldPaint(4, "The building walls block your path.\n");
		return 0;
		break;
	case 13:
		Format.WorldPaint(4, "You cannot enter this way.\n");
		return 0;
		break;
	}
	return 1;
}

void Attribute() {
	Colorize Format;
	string name = Player.get_Name();
	int hp = Player.get_cHealth(), mana = Player.get_Mana(), gold = Player.get_Gold();
	int nextlevel = Player.get_NextLvl() - Player.get_Experience();
	cout << "\n" << name; Format.WorldPaint(9, " <"); 
	if (hp < (Player.get_Health() / 2)) {
		cout << hp; Format.WorldPaint(12, "Hp ");
	}
	else {
		cout << hp; Format.WorldPaint(9, "Hp ");
	}
	cout << mana;  Format.WorldPaint(9, "Mana "); 
	cout << gold; Format.WorldPaint(9, "Gold "); 
	cout << nextlevel; Format.WorldPaint(9, "LVL> \n");
}

void Death() {
	Colorize Format;
	string s;
	Format.Pseudo_Clear(5);
	cout << "\n Your journey has reached its end. Though you did not become the hero in your vision, your deeds will forever be remembered.\n";
	Aligned(Player.get_Name(), 10);
	Aligned(Player.get_Job(), 40);
	Aligned(" you did not die in vain...", 50);
	Aligned("\n You reached level: ", 10);
	Aligned(s = to_string(Player.get_Level()), 40);
	Aligned(" well done!", 50);
	Aligned("\n You had ", 10);
	Aligned(s = to_string(Player.get_Gold()), 40);
	Aligned(" gold remaining.", 50);
	Aligned("\n MAY FATE ", 10);
	Aligned(" BRING YOU", 40);
	Aligned(" BACK", 50);
	system("pause");
	Playing = false;
}

void Help() {
	Colorize Format;
	Format.Pseudo_Clear(1);
	Aligned("\nCommand", 10);
	Aligned("Description", 40);
	Aligned("Syntax", 50);
	Aligned("\n kill", 10);
	Aligned("Initiates combat with target", 40);
	Aligned("[kill] [target]", 50);
	Aligned("\n Heal", 10);
	Aligned("Cast a healing spell on yourself (If you are a mage)", 40);
	Aligned("[heal]", 50);
	Aligned("\n look", 10);
	Aligned("Pulls a description of your location", 40);
	Aligned("[look]", 50);
	Aligned("\n say", 10);
	Aligned("Speak out loud ", 40);
	Aligned("[say] [sentence]", 50);
	Aligned("\n buy", 10);
	Aligned("Purchases an item if in a shop location ", 40);
	Aligned("[buy] [1-10]", 50);
	Aligned("\n north", 10);
	Aligned("Go north ", 40);
	Aligned("[north] || [n]", 50);
	Aligned("\n east", 10);
	Aligned("Go east ", 40);
	Aligned("[east] [e]", 50);
	Aligned("\n west", 10);
	Aligned("Go west ", 40);
	Aligned("[west] [w]", 50);
	Aligned("\n south", 10);
	Aligned("Go south ", 40);
	Aligned("[south] [s] \n", 50);
}
#pragma endregion

//Story Progression
#pragma region Progression

int View_Job() {
	Colorize Format;
	int input;
	bool isValid;
	Format.Pseudo_Clear(2);
	Format.Paint(11, " Choose from the following Job Classes:", "\n");
	cout << "\tType [1] to view the Swordsman's abilities. \n\tType [2] to view the Warlock's abilities.\n";

	while (!(cin >> input) || input < 1 || input > 2) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Format.Paint(12, "Invalid input ignored; please enter a valid command.", "\n");
	}

	int choice = Choose_Job(input);
	if (choice == 0) View_Job();
	else return choice;
}

int Choose_Job(int option) {
	Colorize Format;
	string yesno;
	bool isValid = false;
	bool Valid = false;
	switch (option) {
	case 1:
		Format.Pseudo_Clear(1);
		Format.Paint(3, "\t[SWORDSMAN]", "\n");
		cout << "\t The swordsman is a powerful warrior skilled in melee combat;\n"
			 << "\t swordsmen do not rely on magic, but their experience in battle and the armor on their back.\n"
			 << "\t The swordsman gains increased innate health and physical damage. They also start with 20 gold to spend\n";
		Format.Paint(10, "\n\t Health +30, Attack + 1, Gold + 20", "\n");
		Format.Paint(14, "\nAccept this class? (y/n)\n", "");
		while ((!(cin >> yesno)) || yesno != "y" || yesno != "n") {
			yesno = Format.Lower(yesno);
			if (yesno == "y"||yesno == "n") break;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Format.Paint(12, "Invalid input ignored; please enter a valid command.", "\n");
		}
		if (yesno == "y") {
			Player.set_Job("Swordsman");
			Fight.Fighter++;
			return 1;
		}
		else if (yesno == "n") {
			return 0;
		}
		break;
	case 2:		
		Format.Pseudo_Clear(1);
		Format.Paint(3, "\t[WARLOCK]", "\n");
		cout << "\t The warlock is a mysterious practitioner of the dark arts;\n"
			 << "\t warlocks have low health and even lower attack damage output; they rely on spells to turn the tide of battle.\n"
			 << "\t The warlock gains increased mana. They also start with a spell to use.\n";
		Format.Paint(10, "\n\t Mana +50, +HEAL, Gold + 10", "\n");
		Format.Paint(14, "\nAccept this class? (y/n)\n", "");
		while ((!(cin >> yesno)) || yesno != "y" || yesno != "n") {
			yesno = Format.Lower(yesno);
			if (yesno == "y" || yesno == "n") break;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Format.Paint(12,"Invalid input ignored; please enter a valid command.","\n");
		}
		if (yesno == "y" || yesno == "Y") {
			Player.set_Job("Warlock");
			return 1;
		}
		else if (yesno == "n" || yesno == "N") {
			return 0;
		}
		break;
	}
}

void Introduction() {
	Colorize Format;
	string name;
	cout << " By what name shall we know thee? \n";
	getline(cin, name);
	Player.set_Name(name);
	Sleep(1000);
	View_Job();
	if (Player.get_Job() == "Swordsman") {
		Player.add_Health(30);
		Player.add_Gold(20);
	}
	else { 
		Player.add_Mana(50);
		Player.add_Gold(10);
	}
	Format.Pseudo_Clear(1);
	Format.Paint(14, " \tWelcome to Eberon, ", ""); cout << Player.get_Name();  
	Format.Paint(14, "!\n \tThe road ahead is long and tiresome, use this time to review your capabilities before starting upon this adventure!","\n\n\n\n\t");
    Format.Paint(15, Player.get_Name(), " "); Format.Paint(3, Player.get_Job(), "\n");
	Format.Paint(10, "\t\tHealth: ", ""); cout << Player.get_Health(); Format.Paint(10, "\tMana: ", ""); cout << Player.get_Mana();
	Format.Paint(10, "\t\tStarting Gold: ", "\t"); cout << Player.get_Gold();
	Sleep(4000);
	Format.Pseudo_Clear(3);
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	Format.Paint(14, "\t\t\t[You will start with these attributes. Enter any letter to proceed]", "\n");
	getchar();
}

int Lore() {
	Colorize Format;
	Format.Pseudo_Clear(1);
	Format.Paint(14, " You are negotiating passage to the northern mountains with the gatekeeper of ", ""); Format.Paint(15, "New Estera", ""); Format.Paint(14, " when suddenly, the southern gates burst wide open. \n", 
		" A calvacade of armed men, likely the king's own guard, marches through and into the heart of the city.\n Everyone stares in awe, but you decide to take this opportunity to slip past.");
	Format.Paint(14, "\n\tMake your choice.\n", "");
	cout << "\tType [escape] to attempt to slip past unseen. \n\tor\n\tType [wait] to join the crowd in seeing the king's army trot past.\n";
	string choice;
	while ((!(cin >> choice)) || choice != "escape" || choice != "wait") {
		choice = Format.Lower(choice);
		if (choice == "escape" || choice == "wait") break;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Format.Paint(12, "Invalid input ignored; please enter a valid command.", "\n");
	}
	int roll = Roll_Dice(1, 6);
	if (choice == "escape") {
		Format.Paint(14, "\n You cannot wait, you quietly step back and towards the exit.", "\n");
		Sleep(4000);
		if (Player.get_Job() == "Swordsman") {
			roll += 1;
			cout << "\n Because of your sword training, you find it easier to move with agility. (+1 chance) \n";
		}
		if (roll > 4) {
			Format.Paint(10, " You rolled a ", ""); cout << roll; Format.Paint(10, ", a success.", "\n");
			Format.Paint(14, " You slip past the gatekeeper and into the outside fields without having to pay, score!\n","");
			Sleep(4000);
			Format.Pseudo_Clear(3);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Format.Paint(14, "\n\t[Enter any letter to proceed]", "\n");
			getchar();
		}
		else {
			Format.Paint(12, " You rolled a ", ""); cout << roll; Format.Paint(12, ", and failed to escape.", "\n");
			Format.Paint(14, " The gatekeeper catches you by the collar before you can leave and takes the gold you owe to pass.\n", " You notice that he may have taken a little more than he should have... \n");
			Format.Paint(12, " You lose 7 gold.", "\n");
			Player.add_Gold(-7);
			Sleep(4000);
			Format.Pseudo_Clear(3);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Format.Paint(14, "\n\t[Enter any letter to proceed]", "\n");
			getchar();
		}
	}
	if (choice == "wait") {
		Format.Paint(14, "\n You decide to wait for the parade to pass and then pay the toll fee.","\n");
		Sleep(4000);
		if (Player.get_Job() == "Warlock") {
			roll += 1;
			cout << "\n You converse with the gatekeeper while waiting and talk about magick. (+1 chance) \n";
		}
		if (roll > 4) {
			Format.Paint(10, " You rolled a ", ""); cout << roll; Format.Paint(10, ", a success.", "\n");
			Format.Paint(14, " The gatekeeper is amazed by your quest, he offers to give you some gold for the road.", "\n");
			Format.Paint(10, " You gain 4 gold.","\n");
			Player.add_Gold(4);
			Sleep(4000);
			Format.Pseudo_Clear(3);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Format.Paint(14, "\n\t[Enter any letter to proceed]", "\n");
			getchar();
		}
		else {
			Format.Paint(12, " You rolled a ", ""); cout << roll; Format.Paint(12, ", and failed to escape.", "\n");
			Format.Paint(14, " The parade finally made it out of view, now it is time to pay.", "\n");
			Format.Paint(12, " You lose 5 gold.", "\n");
			Player.add_Gold(-5);
			Sleep(4000);
			Format.Pseudo_Clear(3);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Format.Paint(14, "\n\t[Enter any letter to proceed]", "\n");
			getchar();
		}
	}
	Format.Pseudo_Clear(1);
	Format.Paint(14, "\n In the world of Eberon, you play the role of a miscreant adventurer as he works his way up through skill and valor to become a mighty hero.",
		"\n You are now entering a lawless land outside the city walls, you must fight to survive.");
	cout << "\n\n To control your adventurer, you must issue specific commands like [kill] or [get]. \n Type [help] now to get a list of things you can do OR; type [adventure] to begin the game!\n";
	while ((!(cin >> choice)) || choice != "help" || choice != "adventure") {
		choice = Format.Lower(choice);
		if (choice == "help" || choice == "adventure") break;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Format.Paint(12, "Invalid input ignored; please enter a valid command.", "\n");
	}
	if (choice == "help") {
		Help();
		cout << "\n\n\t Now, type [adventure] to begin the game!\n";
	}
	else if (choice == "adventure") {
		Sleep(2000);
		Format.Pseudo_Clear(3);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Format.Paint(14, "\t\t\t[Enter any letter to proceed]", "\n");
		getchar();
		return 1;
	}
	while ((!(cin >> choice)) || choice != "adventure") {
		choice = Format.Lower(choice);
		if (choice == "adventure") break;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Format.Paint(12, "Invalid input ignored; please enter a valid command.", "\n");
	}
	Sleep(2000);
	Format.Pseudo_Clear(3);
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	Format.Paint(14, "\t\t\t[Enter any letter to proceed]", "\n");
	getchar();
	return 1;
}

map<string, int> Command_List{
	{ "north", 1 },
	{ "n", 1 },
	{ "east", 2 },
	{ "e", 2 },
	{ "south", 3 },
	{ "s", 3 },
	{ "west", 4 },
	{ "w", 4 },
	{ "look", 5 },
	{ "help", 6 },
	{ "heal", 7 },
	{ "get", 8 },
	{ "kill", 9 },
	{ "say", 10 }
};

void WorldView() {
	Colorize Format;
	cout << "\n\n\n\n\n";
	World.Reveal((Player.get_Position()[0]), (Player.get_Position()[1]));
	Format.Paint(14, "\n The world of Eberon lies before you...", "\n");
	cout << " The "; 	Format.Paint(13, "@", ""); cout << " symbol denotes your player position on the map. Try moving around!";
	Format.Paint(15, "\n You may now freely enter any valid command: ", "\n");
	int counter = 0;
	bool isValid = false;
	while (!(isValid)) { 
		Attribute();
		Receive_Command(); 
		counter++;
		if (counter == 1000) isValid = true;
	}
}
#pragma endregion

//Essential Commands
void Receive_Command() {
	Colorize Format;
	string command;
	vector<string> split_Command;
	while (!(getline(cin, command)) || Split(command).size() > 2) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Format.Paint(12, "Invalid input ignored; please enter a valid command.", "\n");
	}
	command = Format.Lower(command);
	string c;
	int counter = 0;
	for (char& c : command) {
		if (isspace(c)) {
			counter++;
		}
	}
	if (counter == 0)
	{
		int ordinate_x, ordinate_y, tile;
		map<string, int>::iterator itr = Command_List.find(command);
		int option;
		if (itr != Command_List.end()) {
			option = itr->second;//Command_List.find(command)->second;
		}
		else {
			cout << "\nNo such command detected\n";
			return;
		}
		if (option == 1) {
			ordinate_y = Player.get_Position()[0] - 1; ordinate_x = Player.get_Position()[1];
			tile = World.get_Map_Tile(ordinate_y, ordinate_x);
			if (CheckMove(tile) == 1) {
				if (Player.set_Position(ordinate_y, ordinate_x) != 0) {
					Format.Paint(8, "\n You leave to the north.", "\n");
					Sleep(1500);
					Game_State.empty_MonsterCache();
					Format.Pseudo_Clear(1);
					Format.Paint(8, "\n You arrive from the south.", "\n");
					World.Reveal(Player.get_Position()[0], Player.get_Position()[1]);
					//Game_State.empty_MonsterCache();
					Cell.get_Info(tile);
					Encounter(tile);
					Format.Pseudo_Clear(5);
				}
			}

		}
		else if (option == 2) {
			ordinate_y = Player.get_Position()[0]; ordinate_x = Player.get_Position()[1] + 1;
			tile = World.get_Map_Tile(ordinate_y, ordinate_x);
			if (CheckMove(tile) == 1) {
				if (Player.set_Position(ordinate_y, ordinate_x) != 0) {
					Format.Paint(8, "\n You leave to the east.", "\n");
					Sleep(1500);
					Game_State.empty_MonsterCache();
					Format.Pseudo_Clear(1);
					Format.Paint(8, "\n You arrive from the west.", "\n");
					World.Reveal(Player.get_Position()[0], Player.get_Position()[1]);
					Cell.get_Info(tile);
					Encounter(tile);
					Format.Pseudo_Clear(5);
				}
			}
		}
		else if (option == 3) {
			ordinate_y = Player.get_Position()[0] + 1; ordinate_x = Player.get_Position()[1];
			tile = World.get_Map_Tile(ordinate_y, ordinate_x);
			if (CheckMove(tile) == 1) {
				if (Player.set_Position(ordinate_y, ordinate_x) != 0)
				{
					Format.Paint(8, "\n You leave to the south.", "\n");
					Sleep(1500);
					Game_State.empty_MonsterCache();
					Format.Pseudo_Clear(1);
					Format.Paint(8, "\n You arrive from the north.", "\n");
					World.Reveal(Player.get_Position()[0], Player.get_Position()[1]);
					Cell.get_Info(tile);
					Encounter(tile);
					Format.Pseudo_Clear(5);
				}
			}
		}
		else if (option == 4) {
			ordinate_y = Player.get_Position()[0]; ordinate_x = Player.get_Position()[1] - 1;
			tile = World.get_Map_Tile(ordinate_y, ordinate_x);
			if (CheckMove(tile) == 1) {
				if (Player.set_Position(ordinate_y, ordinate_x) != 0)
				{
					Format.Paint(8, "\n You leave to the west.", "\n");
					Sleep(1500);
					Game_State.empty_MonsterCache();
					Format.Pseudo_Clear(1);
					Format.Paint(8, "\n You arrive from the east.", "\n");
					World.Reveal(Player.get_Position()[0], Player.get_Position()[1]);
					Cell.get_Info(tile);
					Encounter(tile);
					Format.Pseudo_Clear(5);
				}
			}
		}
		else if (option == 5) {
			Format.Paint(7, "\n You take a good look around.", "\n");
			Sleep(1500);
			Format.Pseudo_Clear(1);
			World.Reveal(Player.get_Position()[0], Player.get_Position()[1]);
		}
		else if (option == 6) {
			Format.Paint(7, "\n You pray to the gods for guidance.", "\n");
			Sleep(1500);
			Help();
		}
		else if (option == 7) {
			if (Player.get_Job() == "Warlock") {
				Format.Paint(11, "\n You pray to the gods for healing.", "\n");
				Sleep(1500);
				Player.Heal();
			} 
			else {
				Sleep(1500);
				Format.Paint(12, "\n This spell is only available to the warlock class", "\n");
			}
		}
	}
	else if (counter > 0 && counter < 2) {
		split_Command = Split(command);
		string command_1, command_2;
		command_1 = split_Command[0];
		command_2 = split_Command[1];
		int option;
		string monsterName;
		map<string, int>::iterator itr = Command_List.find(command_1);
		if (itr != Command_List.end()) {
			option = itr->second;
		}
		else {
			cout << "\nNo such command detected\n";
			return;
		}
		if (option == 8) {
			Format.Paint(7, "\n You get the item.", "\n");
			Sleep(1500);
		}
		else if (option == 9) {
			if (!Game_State.get_MonsterCache().empty()) {
				monsterName = Game_State.get_MonsterCache()[0].get_Name();
				monsterName = Format.Lower(monsterName);
				if (monsterName == command_2) {
					Format.Paint(7, "\n You attack the ", command_2);
					int HP = Player.get_Health(), MP = Player.get_Mana(), CHP = Player.get_cHealth();
					int MHP = Game_State.get_MonsterCache()[0].get_MaxHealth();
					int MType = Game_State.get_MonsterCache()[0].get_Type();
					int Plvl = Player.get_Level();
					Sleep(2000);
					Fight.Setup(HP, CHP, MP, MHP, MType, monsterName, Plvl);
					bool Result = Fight.Battle();
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (Result) {
						Player.set_Health(Fight.Recover()[0]);
						Player.set_Mana(Fight.Recover()[1]);
						int xp = Fight.Recover()[2] * 10 + (rand() % ((Fight.Recover()[2] * 10) + 1) + 1);
						int gold = Fight.Recover()[2] + (rand() % ((Fight.Recover()[2] * 5) + 1) + 1);
						Player.add_Experience(xp);
						Player.add_Gold(gold);
						Format.WorldPaint(12, "\n The "); cout << monsterName; Format.WorldPaint(12, " falls lifeless at your feet.\n");
						Format.WorldPaint(14, "\n You gained "); cout << gold; Format.WorldPaint(14, " gold, and "); cout << xp; Format.WorldPaint(14, " experience for your efforts!\n");
						if (Player.levelup_Player()) {
							Format.WorldPaint(14, "\n You've gained a level! You are now level: "); cout << Player.get_Level();
							Player.add_Health(25);
							Player.add_Mana(25);
							Player.set_Health(Player.get_Health());
						}
						else {
							cout << "\n You need " << Player.get_NextLvl() - Player.get_Experience() << " more experience to gain a level.\n";
						}
						Game_State.empty_MonsterCache();
					}
					else {
						Death();
					}
				}
				else {
					cout << "You do not see that monster here.";
					return;
				}
			}
		}
		else if (option == 10) {
			Sleep(1500);
			Format.Paint(11, "\n You say: ", ""); cout << "\"" << command_2 << "\"" << endl;
			if (Game_State.get_MonsterCache()[0].get_Name() == "Merchant" || Game_State.get_MonsterCache()[0].get_Name() == "Villager" || Game_State.get_MonsterCache()[0].get_Name() == "Cityguard") {
				Format.Paint(11, "\n A ", ""); cout << Game_State.get_MonsterCache()[0].get_Name(); Format.Paint(11, " responds:", ""); Format.Paint(11, " Good day to you stranger!", "\n");
			}
		}
	}
	else {
		Format.Paint(12, "Invalid compound input ignored; please enter a valid command.", "\n");
	}
}

//Encounters
void Encounter(int tile) {
	Colorize Format;
	int roll;
	switch (tile) {
	case 3:
	case 4:
		roll = Roll_Dice(1, 3);
		Format.WorldPaint(10, "  A "); cout << Enemy.Monster_List(roll).get_Name(); Format.WorldPaint(10, Enemy.Monster_List(roll).get_Description()); cout << endl;
		Game_State.fill_MonsterCache(Enemy.Monster_List(roll));
		break;
	case 2:
		roll = Roll_Dice(1, 6);
		if (roll < 4) break;
		Format.WorldPaint(10, "  A "); cout << Enemy.Monster_List(roll).get_Name(); Format.WorldPaint(10, Enemy.Monster_List(roll).get_Description()); cout << endl;
		Game_State.fill_MonsterCache(Enemy.Monster_List(roll));
		break;
	case 6:
	case 9:
		roll = Roll_Dice(4, 9);
		if (roll < 7) break;
		Format.WorldPaint(10, "  A "); cout << Enemy.Monster_List(roll).get_Name(); Format.WorldPaint(10, Enemy.Monster_List(roll).get_Description()); cout << endl;
		Game_State.fill_MonsterCache(Enemy.Monster_List(roll));
		//cout << "Lister:  " << Game_State.get_List()[0].get_Name();
		break;
	case 10:
		roll = Roll_Dice(5, 12);
		if (roll < 10) break;
		Format.WorldPaint(10, "  A "); cout << Enemy.Monster_List(roll).get_Name(); Format.WorldPaint(10, Enemy.Monster_List(roll).get_Description()); cout << endl;
		Game_State.fill_MonsterCache(Enemy.Monster_List(roll));
		//cout << "Lister:  " << Game_State.get_List()[0].get_Name();
		break;
	case 13:
		roll = Roll_Dice(6, 15);
		if (roll < 13) break;
		Format.WorldPaint(10, "  A "); cout << Enemy.Monster_List(roll).get_Name(); Format.WorldPaint(10, Enemy.Monster_List(roll).get_Description()); cout << endl;
		Game_State.fill_MonsterCache(Enemy.Monster_List(roll));
		//cout << "Lister:  " << Game_State.get_List()[0].get_Name();
		break;
	}
}

void Title_Sequence() {
	Colorize Format;
	cout << "\n  >RPG Framework ";
	cout << "\n   Developed by: August Bryan N. Florese ";
	cout << "\n   1 - CSSE \n";
	Sleep(3500);
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//getchar();
	Format.Pseudo_Clear(1);
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Main Function
int main() {
	Player.set_Position(8, 3);
	srand(time(0));
	while (Playing) {
		Title_Sequence();
		Introduction();
		getchar();
		Lore();
		WorldView();
		cout << endl;
		system("pause");
		Playing = false;
	}
	return 0;
}

