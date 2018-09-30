#ifndef Hero_H
#define Hero_H	
#include "Painter.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
class Hero {
private:
	//Role
	std::string Name;
    std::string Job;
	int Gold = 0;
	//Logistics
	int Experience = 0;
	int Experience_Required = 100;
	int Level = 1;
	//Combat
	int Health = 100;
	int currentHealth = Health;
	int Mana = 50;
	//Location
	int X, Y;
public:
	Hero();
	void Move(std::string command);
	int set_Position(int y, int x);
	std::vector<int> get_Position();
	std::vector<int> get_NextMove(int y, int x);
	void set_Name(std::string input);
	void set_Job(std::string input);
	void set_Health(int input);
	void set_Mana(int input);

	void add_Health(int bonus_Health);
	void add_Mana(int bonus_Mana);
	void add_Experience(int added_Xp);
	void add_Gold(int added_Gold);
	bool levelup_Player();
	std::string get_Name();
	std::string get_Job();
	int get_NextLvl();
	int get_Health();
	int get_cHealth();
	int get_Mana();
	int get_Experience();
	int get_Gold();
	int get_Level();
	void Heal();
};

#endif

//Player.add_Experience(Player.get_Experience(), y);

//class Heros {
//private:
	//int exp;
	//vector<std::string> inventory[4];
	//Ordinate Player_Position;
//public:
	//Heros(int s);
	//int method(int Xp);
	////{Get:Set Name
	//void Hero::setName(string input) { name = input; }
	//string Hero::getName() { return name; }
	////{Get:Set Job
	//void Hero::setJob(string input) { job = input; }
	//string Hero::getJob() { return job; }
	////{Get:Set Exp
	//void Hero::setExp(int input) { exp = input; }
	//int Hero::getExp() { return exp; }
	////{Get:Set Exp
	//void Hero::setOrdinate(int X, int Y) { Player_Position.x = X; Player_Position.y = Y; }
	//Ordinate Hero::getOrdinate() { return Player_Position; }
//};

//#include "create_map.h"
//
//void Create_Map() {
//
//}
//
//class Coordinates {
//public:
//	//Get:Set Tile value
//	int get_Location() { return area_Loc; }
//	void set_Location(int Loc) { area_Loc = Loc; }
//	//Get:Set XY Coordinates of prev. cell
//	pair<int, int> getArea_XY() { return area_XY; }
//	void setArea_XY(pair<int, int> XY) { area_XY = XY; }
//	//Get:Set XY Coordinates of current cell
//	pair<int, int> getCurrent_XY() { return current_XY; }
//	void setCurrent_XY(pair<int, int> XY) { current_XY = XY; }
//private:
//	int area_Loc;
//	pair<int, int> area_XY;
//	pair<int, int> current_XY;
//};
