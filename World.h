#ifndef  World_H
#define  World_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include "Monster.h"
using std::string;
using std::vector;

class WorldMap {
public:
	WorldMap();
	void Reveal(int player_y, int player_x);
	int get_Map_Tile(int y, int x);
private:
	int X, Y;
	int current_Tile;
	int replaced_Tile;
	int replacedCounter;
	int position; 
	int Map[10][40]{
		 { 1,1,7,12,12,12,10,7,11,11,11,11,11,11,11,11,7,10,10,10, 12,12,12,12,12,10,3,3,13,13, 13,1,1,1,1,1,14,15,15,15 },
		 { 7,8,7,10,5,5,10,7,7,8,7,7,7,7,7,7,7,4,4,10, 12,12,12,12,12,12,10,3,13,13, 13,13,13,1,1,1,14,15,15,15 },
		 { 3,3,1,10,5,10,1,1,1,6,6,6,6,3,3,2,4,4,4,10, 12,12,12,12,10,3,3,3,13,13, 13,13,13,13,1,1,14,15,15,15 },
		 { 3,3,10,5,5,10,1,1,6,4,3,3,6,3,3,2,4,4,4,10, 5,5,10,2,3,2,13,13,13,13, 13,13,13,13,13,13,14,15,15,15 },
		 { 1,10,9,9,9,6,6,6,6,4, 3,3,6,3,3,2,4,1,4,10, 5,5,10,2,3,2,13,13,13,13, 13,13,3,3,3,13,14,15,15,15 },
		 {10,10,5,5,5,6,4,4,4,4,2,2,6,6,6,2,2,4,1,10, 5,5,10,2,3,13,13,13,13,13, 13,13,13,3,13,13,14,15,15,15 },
		 { 5,5,5,6,6,6,4,1,1,4, 4,4,2,4,6,3,2,4,4,10, 5,5,5,10,10,3,13,13,13,13, 13,13,13,13,13,13,14,14,8,14 },
	     { 5,5,10,6,2,2,4,1,4, 4,4,4,4,3,3,3,6,6,6,9, 9,9,9,9,9,10,13,13,13,13, 13,13,13,13,13,13,13,13,13,1 },
		 { 12,10,2,6,2,2,4,1,1,4, 4,1,4,4,3,2,3,3,3,7, 5,5,12,12,10,10,10,13,13,13, 13,13,13,13,13,13,13,1,1,1 },
		 { 12,12,7,8,7,2,4,4,4,4, 4,4,1,4,4,4,3,3,7,7, 5,12,12,12,12,10,10,13,13,13, 13,13,13,13,13,1,1,1,1,1 }
	};
};// 1 - Mountain 2 - dGrass 3 - Suspicious Grass 4 - bGrass 5 - bWater 6 - Road 7 - Wall 8 - Enter 9 - Bridge 10 - Sand 11 - Interior 12 - Ocean 

class Room {
private:
	string Title, Description;
	int Code;
public:
	Room(string Title, string Description, int code);
	Room();
	void get_Info(int tile);
	int get_Code();
	string get_Title();
	string get_Description();
};

class GameState {
private:
	vector<Monster> MonsterCache;
	vector<string> MonsterListing;
public:
	GameState();
	void list_Monster(Monster monster);
	void kill_MonsterCache();
	void empty_MonsterCache();
	void fill_MonsterCache(Monster monster);
	vector<Monster> get_MonsterCache();
};
#endif // ! World_H
