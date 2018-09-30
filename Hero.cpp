#include "Hero.h"
#include "World.h"
Hero::Hero() {}

//Setter

void Hero::set_Name(std::string input) {
	 Name = input;
}
void Hero::set_Job(std::string input) {
	 Job = input;
}
void Hero::set_Health(int input) {
	currentHealth = input;
}
void Hero::set_Mana(int input) {
	Mana = input;
}
void Hero::add_Experience(int added_Xp) {
	 Experience = get_Experience() + added_Xp;
}
void Hero::add_Gold(int added_Gold) {
	Gold = get_Gold() + added_Gold;
	if (Gold < 0) Gold = 0;
}
void Hero::add_Health(int bonus_Health) {
	Health = get_Health() + bonus_Health;
}
void Hero::add_Mana(int Bonus_Mana) {
	Mana = get_Mana() + Bonus_Mana;
}
int Hero::set_Position(int y, int x) {
	Colorize Format;
	if (x > 0 && x < 40 && y > 0 && y < 10) {
		Y = y;
		X = x;
	}
	else { 
		Format.WorldPaint(4, "You cannot go that direction. \n"); 
		return 0;
	}
}
          

//Getter

std::vector<int> Hero::get_Position() {
	std::vector<int> Position;
	Position.push_back(Y);
	Position.push_back(X);
	return Position;
}
std::vector<int> Hero::get_NextMove(int y, int x) {
	std::vector<int> NextMove;
	NextMove.push_back(y);
	NextMove.push_back(x);
	return NextMove;
}
int Hero::get_cHealth() {
	return currentHealth;
}
int Hero::get_NextLvl() {
	return Experience_Required;
}
int Hero::get_Health() {
	return Health;
}
int Hero::get_Mana() {
	return Mana;
}
int Hero::get_Level() {
	return Level;
}
int Hero::get_Experience() {
	return Experience;
}
int Hero::get_Gold() {
	return Gold;
}
std::string Hero::get_Name() {
	return Name;
}
std::string Hero::get_Job() {
	return Job;
}

//Functions
bool Hero::levelup_Player() {
	if (Experience >= Experience_Required) {
		Experience_Required += 130;
		Experience = 0;
		Level++;
		Health += 10;
		return true;
	}
	else {
		return false;
	}
}
void Hero::Move(std::string command) {
	std::map<std::string, std::pair<int, int>> Move_Cmd
	{
		{ "n",{ 0,Y+1 } },
		{ "e",{ X+1,0 } },
		{ "s",{ 0,Y-1 } },
		{ "w",{ X-1,0 } },
		{ "look",{ 1,1 } },
	};
}
void Hero::Heal() {
	Colorize Format;
	Format.WorldPaint(14, "\n A warm glow surrounds you, you feel better already!\n");
	if (Mana >= 10)
	{
		int heal = 1 + rand() % 35;
		Mana -= 10;
		currentHealth += heal;
	}
	else {
		Format.WorldPaint(12, "\n Insufficient mana. \n");
	}

}

//class H:Hero {
//private:
//	//string name, job;
//	//int exp;
//	//vector<string> inventory[4];
//	//Ordinate Player_Position;
//
//public:
//	//{Get:Set Name
//	void Hero::setName(string input) { name = input; }
//	string Hero::getName() { return name; }
//	//{Get:Set Job
//	void Hero::setJob(string input) { job = input; }
//	string Hero::getJob() { return job; }
//	//{Get:Set Exp
//	void Hero::setExp(int input) { exp = input; }
//	int Hero::getExp() { return exp; }
//	//{Get:Set Exp
//	void Hero::setOrdinate(int X, int Y) { Player_Position.x = X; Player_Position.y = Y; }
//	Ordinate Hero::getOrdinate() { return Player_Position; }
//};

//		//			//monsterName = "wolf";
//		//			//string MName = monsterName;
//		//			//monsterName = Format.Lower(monsterName);
//		//			//int HP = Player.get_Health(), MP = Player.get_Mana(), CHP = Player.get_cHealth();
//		//			//int MHP = Game_State.get_MonsterCache()[0].get_MaxHealth();
//		//			//int MType = Game_State.get_MonsterCache()[0].get_Type();
//		//			//

//		//			//if (monsterName == command_2) {
//		//			//	Format.Paint(7, "\n You attack the ", command_2);
//		//			//	Sleep(2000);
//		//				//Fight.Setup(1, 1, 1, 1, 1, MName);

//		//				//Battle();
//		//				//if () {
//		///*					Player.set_Health(Fight.Recover()[0]);
//		//					Player.set_Mana(Fight.Recover()[1]);
//		//					int xp = Fight.Recover()[2] * 10 + (rand() % ((Fight.Recover()[2] * 10) + 1) + 1);
//		//					int gold = Fight.Recover()[2] + (rand() % ((Fight.Recover()[2] * 5) + 1) + 1);
//		//					Player.add_Experience(xp);
//		//					Player.add_Gold(gold);
//		//					cout << "\n You gained " << gold << " gold, and " << xp << " experience for your efforts!\n";
//		//					if (Player.levelup_Player())
//		//						Format.WorldPaint(14, "\n You've gained a level! You are now level: "); cout << Player.get_Level();*/
//		//				//}
//		//				//else {
//		//				//	Sleep(1000);
//		//				//	Format.Pseudo_Clear(3);
//		//				//	cin.clear();
//		//				//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
//		//				//	Format.WorldPaint(12, "\nYOU DIED\n");
//		//				//	getchar();
//		//				//	Death();
//		//				//}
//		//			}
//		//			else { 
//		//				cout << "You do not see that monster here.";
//		//				return; 
//		//			}
//#include "Hero.h"
//#include "Painter.h"
//#include "World.h"
//#include "Monster.h"
//#include <map>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <map>
//#include <algorithm>
//#include <iomanip>
//#include <limits>
//#include <iterator>
//#include <sstream>
//#include <cctype>
//#include <Windows.h>
//HANDLE  hConsole;
//hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//FlushConsoleInputBuffer(hConsole);
//SetConsoleTextAttribute(hConsole, Color);
//std::cout << color_me << extra;
//SetConsoleTextAttribute(hConsole, 15);
