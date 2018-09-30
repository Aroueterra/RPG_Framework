#include "World.h"
#include "Painter.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

WorldMap::WorldMap() {}

Room::Room(string title, string description, int n) {
	Title = title;
	Description = description;
	Code = n;
}
Room::Room() {}
GameState::GameState() {}
//Room::Room(string title, string description, int code);

void WorldMap::Reveal(int player_y, int player_x) {
	Colorize Format;
	int Tile;
	if (replacedCounter>0)
	{
		for (int y = 0, x = 0; y < 10;)
		{
			if (Map[y][x] == 20)
				Map[y][x] = replaced_Tile;
			x++;
			if (x == 40 && y != 10) {
				y++;
				cout << endl;
				x = 0;
			}
		}
	}
	else {
		replacedCounter++;
	}
	replaced_Tile = Map[player_y][player_x];
	Map[player_y][player_x] = 20;
	//Format.Pseudo_Clear(5);
	Format.WorldPaint(9, "[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~(");	Format.WorldPaint(14, "  EBERON  "); 	Format.WorldPaint(9, ")~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
	for (int y = 0, x = 0; y < 10;)
	{
		cout << " ";
		switch (Map[y][x]) {
		case 1:
			Format.WorldPaint(15, "^");
			break;
		case 2:
			Format.WorldPaint(2, "*");
			break;
		case 3:
			Format.WorldPaint(2, "*"); 
			break;
		case 4:
			Format.WorldPaint(10, "*");
			break;
		case 5:
			Format.WorldPaint(3, "~");
			break;
		case 6:
			Format.WorldPaint(14, "#");
			break;
		case 7:
			Format.WorldPaint(13, "I");
			break;
		case 8:
			Format.WorldPaint(14, "O");
			break;
		case 9:
			Format.WorldPaint(14, "=");
			break;
		case 10:
			Format.WorldPaint(6, ".");
			break;
		case 11:
			Format.WorldPaint(13, "=");
			break;
		case 12:
			Format.WorldPaint(9, "~");
			break;
		case 13:
			Format.WorldPaint(6, "=");
			break;
		case 14:
			Format.WorldPaint(8, "I");
			break;
		case 15:
			Format.WorldPaint(0, "=");
			break;
		case 20:
			Format.WorldPaint(13, "@");
			break;
		}
		x++;
		if (x == 40 && y != 10) {
			y++;
			cout << endl;
			x = 0;
		}
	}
	Format.WorldPaint(9, "[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~(");	Format.WorldPaint(15, " WEST MAP "); 	Format.WorldPaint(9, ")~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
}
int WorldMap::get_Map_Tile(int y, int x) {
	return Map[y][x];
}

string forest_Description = "\nThis forest has seen better days, you reckon.\nYou are surrounded on each side by rows of tall evergreen trees.\nOut of the corner of your eye, you can spot animals darting through the shadows.\nIt would be best if you did not have to stay any longer.\n";
string grass_Description = "\nThe tall grass blocks your vision and your feet sink deep into mud.\nDespite the uneven footing, you can make your way across. Several insects inhabit this marsh.\n";
string road_Description = "\nThe royal road to New Estera is frequented by merchants and travellers alike.\nYour journey will take you away from the comforts of this castle.\nYou should be able to avoid any monster encounters if you stick to the road.\n";
string sand_Description = "\nLow sand and gravel make easy travel. Small creatures tend to hide themselves \nunder the pockets of sand here, best avoid resting anytime soon.\nYou quicken your stride.\n";
string bridge_Description = "\nA thin mist smoothes over the rickety wooden bridge.\nThe river beneath roars furiously, and constantly licks against the railing.\nYou try not to fall through the cracks.\n";
string farm_Description = "\nThis plot of land has been struck by a serious case of drought.]nWhat was once full of greenery and life is now a barren waste.\nPerhaps this was the doing of evil, not nature?\n";
string door_Description = "\nYou stand before a massive oaken door. \nYou can hear feet shuffling inside, enter?\n";

Room Forest("|Rain Forest", forest_Description, 4);
Room Grass("|Suspicious Grass", grass_Description, 3);
Room Road("|Royal Road", road_Description, 6);
Room Sand("|Sandy Shore", sand_Description, 10);
Room Bridge("|Old Bridge", bridge_Description, 9);
Room Door("|Massive Door", door_Description, 8);
Room Farm("|Farmlands", farm_Description, 8);

void Room::get_Info(int tile) {
	Colorize Format;
	switch (tile) {
	case 2:
	case 4:
		Format.WorldPaint(14, Forest.get_Title());
		Format.WorldPaint(1, "---------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Forest.get_Description());
		break;
	case 3:
		Format.WorldPaint(14, Grass.get_Title());
		Format.WorldPaint(1, "---------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Grass.get_Description());
		break;
	case 6:
		Format.WorldPaint(14, Road.get_Title());
		Format.WorldPaint(1, "---------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Road.get_Description());
		break;
	case 8:
		Format.WorldPaint(14, Door.get_Title());
		Format.WorldPaint(1, "---------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Door.get_Description());
		break;
	case 9:
		Format.WorldPaint(14, Bridge.get_Title());
		Format.WorldPaint(1, "--------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Bridge.get_Description());
		break;
	case 10:
		Format.WorldPaint(14, Sand.get_Title());
		Format.WorldPaint(1, "--------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Sand.get_Description());
		break;
	case 13:
		Format.WorldPaint(14, Farm.get_Title());
		Format.WorldPaint(1, "--------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Farm.get_Description());
		break;
	}
}

string Room::get_Title() {
	return Title;
}
int Room::get_Code() {
	return Code;
}
string Room::get_Description() {
	return Description;
}


vector<Monster> GameState::get_MonsterCache() {
	if (!MonsterCache.empty()) {
		vector<Monster> list = MonsterCache;
		return list;
	}
	else 
		vector<Monster> list;
}

void GameState::list_Monster(Monster monster) {
	MonsterListing.clear();
	MonsterListing.push_back(monster.get_Name());
}
void GameState::kill_MonsterCache() {
	Monster monster;
}
void GameState::fill_MonsterCache(Monster monster) {
	MonsterCache.push_back(monster);
}
void GameState::empty_MonsterCache() {
	MonsterCache.clear();
}
