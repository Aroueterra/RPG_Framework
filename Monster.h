#ifndef Monster_H
#define Monster_H
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>
#include <iostream>
#include "Painter.h"
#undef max;

using std::string;
using std::cout; using std::endl; using std::cin;

class Monster {
private:
	int Health, Attack, Defense, Gold, Level, MaxHealth;
	int Type;
	string Name, Description;
public:
	void set_Name(std::string input);
	void set_Description(std::string input);
	string get_Name();
	string get_Description();
	int get_Attack();
	int get_Defense();
	int get_Gold();
	int get_Level();
	int get_Type();
	int get_MaxHealth();
	int get_Health();
	Monster(std::string Name, std::string Description, int Gold, int MaxHealth, int Type);
	Monster Monster_List(int key);
	Monster();
};

class Combat {
private:
	int P_hp; int P_cHealth; int P_mana; int P_def; int M_health; int M_cHealth; int M_type; int M_defense; int P_lvl;
	string Name;
public:
	int Fighter;
	void Setup(int p_hp, int p_cHealth, int p_mana, int m_health, int m_type, string name, int P_lvl);
	Combat();
	bool Battle();
	string BattleCry(int stamina, int option);
	void Damage(int damage, int option);
	int getHealth(int option);
	string getName();
	int getType();
	std::vector<int> Recover();
};

#endif

