#include "Monster.h"
Monster::Monster() {}
Monster::Monster(std::string name, std::string description, int gold, int maxHealth, int type) {
	Name = name;
	Description = description;
	Gold = gold;
	MaxHealth = maxHealth;
	Type = type;
}
Combat::Combat() {}

//Init Combat stats;
void Combat::Setup(int p_hp, int p_cHealth, int p_mana, int m_health, int m_type , string name, int p_lvl) {
	P_hp = p_hp;  P_cHealth = p_cHealth;  P_mana = p_mana; M_health = m_health;  M_type = m_type; P_lvl = p_lvl;
	Name = name;
}
int Dice_Roll(int min, int max) {
	int roll;
	return roll = rand() % (max - min + 1) + min;
};

//Fetch warcry
std::map <int, string> pBattleCry{
	{ 0, "\n You reserve your stamina and defend.\n" },
	{ 1, "\n You jab the opponent with the hilt of your blade.\n" },
	{ 2, "\n You slice your opponent vertically.\n" },
	{ 3, "\n You feint back but lunge forward the next second.\n" },
	{ 4, "\n You seize your opponent's feet.\n" },
	{ 5, "\n You brush the opponent with the edge of your blade.\n" },
	{ 6, "\n You cut quickly and mercilessly.\n" },
	{ 7, "\n You advance and take the opponent from behind.\n" },
	{ 8, "\n You pierce the opponent through.\n" },
	{ 9, "\n You lunge forward full force.\n" },
	{ 10, "\n You assault your opponent with every ounce of your strength.\n" },
};
std::map <int, string> mBattleCry{
	{ 0, "\n Your opponent reserves their stamina and defends.\n" },
	{ 1, "\n Your opponent pokes at you.\n" },
	{ 2, "\n Your opponent slices your arm.\n" },
	{ 3, "\n Your opponent feints back but lunges forward the next second.\n" },
	{ 4, "\n Your opponent seizes your feet.\n" },
	{ 5, "\n Your opponent brushes hard against you.\n" },
	{ 6, "\n Your opponent cuts quickly and mercilessly.\n" },
	{ 7, "\n Your opponent advances and takes you from behind.\n" },
	{ 8, "\n Your opponent pierces you through.\n" },
	{ 9, "\n Your opponent lunges forward full force.\n" },
	{ 10, "\n Your opponent assaults you with every ounce of their strength.\n" },
};
string Combat::BattleCry(int stamina, int option) {
	string battlecry = "";

	if (option == 1)
	{
		return battlecry = pBattleCry.find(stamina)->second;
	}
	else
	{
		return battlecry = mBattleCry.find(stamina)->second;
	}
}

//Do battle
bool Combat::Battle() {
	Colorize Format;
	Format.Pseudo_Clear(2);
	int current_Stamina = 10;
	int enemy_Stamina = 10;
	int dealt_Damage;
	int round = 1;
	bool fighting = true;
	while (fighting == true) {
		cout << "\n\n\n\n\n [Round " << round << "]"; Format.WorldPaint(12, " You are in combat with: "); std::cout << Name << std::endl;
		cout << "\n Allot stamina to attack, or reserve stamina to defend. "; Format.WorldPaint(10, "Stamina: "); cout << current_Stamina << endl;
		int allot_Stamina;
		cout << "\n " << Name; Format.WorldPaint(4, " <"); cout << M_health; Format.WorldPaint(4, "Hp> \n");
		cout << "\n "; Format.WorldPaint(9, " <"); cout << P_cHealth; Format.WorldPaint(9, "Hp ");  cout << P_mana;  Format.WorldPaint(9, "Mana> \n");
		while (!(cin >> allot_Stamina) || allot_Stamina < 0 || allot_Stamina > 10 || allot_Stamina > current_Stamina) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			Format.Paint(12, "Invalid input ignored; please enter a number from zero to your current stamina level.", "\n");
		}
		if (allot_Stamina > current_Stamina) {
			Format.Paint(12, "Invalid input ignored; please enter a number from zero to your current stamina level.", "\n");
			allot_Stamina = 0;
			continue;
		}
		int roll = Dice_Roll(0, enemy_Stamina);
		if (enemy_Stamina == 0) { roll = 0; }
		//cout <<"\nRoll: "<< roll<<"\n";
		string p_battlecry = BattleCry(allot_Stamina, 1);
		string m_battlecry = BattleCry(roll, 2);
		cout << p_battlecry;
		Sleep(2500);
		cout << m_battlecry;
		Sleep(2500);
		//Draw
		if (allot_Stamina == roll && roll > 0)
		{
			cout << "\n Draw. Your attacks enter a deadlock and cancel each other out; no damage is dealt.\n";
		}
		//Both Defend
		else if (allot_Stamina == roll && roll == 0)
		{
			current_Stamina = 10;
			enemy_Stamina = 10;
			cout << "\n Draw. Neither of you attack, noone gets hurt.\n";
		}
		//Player wins
		else if (roll >= 1 && allot_Stamina > roll) {
			dealt_Damage = allot_Stamina - roll;
			if (dealt_Damage <= 4)
				dealt_Damage = 5 * ((P_lvl / 2) + 1);
			else 
				dealt_Damage = 5 * ((P_lvl / 2) + 1);
			if (Fighter > 0) dealt_Damage++;
			Damage(dealt_Damage, 1);
		}
		//Enemy wins
		else if (allot_Stamina >= 1 && roll > allot_Stamina) {
			dealt_Damage = roll - allot_Stamina;
			if (dealt_Damage < 4)
				dealt_Damage = 5;
			else
				dealt_Damage = 3;
			Damage(dealt_Damage, 2);
		}
		//Player blocks
		else if (allot_Stamina == 0 && roll >= 1) {
			Damage(1, 3);
			current_Stamina = 10;
		}
		//Enemy blocks
		else if (roll == 0 && allot_Stamina >= 1) {
			Damage(1, 4);
			enemy_Stamina = 10;
		}
		current_Stamina -= allot_Stamina;
		enemy_Stamina -= roll;
		round++;
		if (M_health <= 0) {
			return 1;
		}
		else if (P_cHealth <= 0) {
			return 0;
		}
	}

}
std::vector<int> Combat::Recover() {
	std::vector<int> recovery;
	recovery.push_back(P_cHealth);
	recovery.push_back(P_mana);
	recovery.push_back(M_type);
	return recovery;
};
void Combat::Damage(int damage, int option) {
	Colorize Format;
	if (option == 1) {
		M_health -= damage;
		Format.WorldPaint(7, "\n Your attack connects! Dealing "); cout << damage; Format.WorldPaint(7, " damage.\n");
	}
	else if (option == 2) {
		P_cHealth -= damage;
		Format.WorldPaint(4, "\n Your opponent's attack connects! Dealing "); cout << damage; Format.WorldPaint(4, " damage.\n");
	}
	else if (option == 3) {
		P_cHealth -= 1;
		Format.WorldPaint(7, "\n You block the opponent's attack, you only receive "); cout << damage; Format.WorldPaint(7, " damage.\n");
	}
	else if (option == 4) {
		M_health -= 1;
		Format.WorldPaint(4, "\n Your opponent blocks your attack. They receive ");  cout << damage; Format.WorldPaint(4, " damage.\n");
	}
}

//Getters
int Combat::getHealth(int option) {
	if (option == 1)
		return P_cHealth;
	else
		return M_cHealth;
}
string Combat::getName() {
		return Name;
}
int Combat::getType() {
	return M_type;
}



//Dense Woodlands
Monster Wolf("Wolf", " is here, stalking you from the shadows of the evergreens.", 20, 25, 2);
Monster Mosquito("Mosquito", " is here, looking for its next meal.", 10, 15, 1);
Monster Golem("Golem", " rests here, deactivated. Awaiting the day of its master's return.", 270, 270, 8);
//Woodlands
Monster Cat("Cat", " is here, affectionately rubbing against your feet.", 10, 15, 1);
Monster Pangolin("Pangolin", " is here, curled into a ball.", 30, 30, 3);
Monster Bear("Bear", " stalks, alert for any potential danger.", 70, 50, 5);
//Road
Monster Merchant("Merchant", " is here, peddling his wares to passersby.", 130, 100, 6);
Monster Villager("Villager", " is on his way to the city, backpack full of all sorts of things.", 80, 70, 2);
Monster Guard("Cityguard", " stands ready to serve and protect the citizens of New Estera.", 150, 300, 10);
//Sand
Monster Crab("Crabber", " is here, crawling on all fours.", 1, 15, 1);
Monster Rogue("Rogue", " is slinking into the shadows.", 200, 200, 1);
Monster Giant("Docchu", " is bathing in the river water, best steer clear of him.", 350, 400, 15);
//Farm
Monster Knight("DarkKnight", " patrols this area, he is armed to the teeth.", 400, 450, 17);
Monster Necro("Necromancer", " is communing with the dead.", 280, 170, 18);
Monster Dragon("Dragon", " is about to leap towards your position!", 1000, 500, 20);
std::vector<Monster>  ver;

Monster Monster::Monster_List(int key) {
	std::map<int, Monster> Monster_Map{
	{ 1, Wolf },
	{ 2, Mosquito },
	{ 3, Golem },
	{ 4, Cat },
	{ 5, Pangolin },
	{ 6, Bear },
	{ 7, Merchant },
	{ 8, Villager },
	{ 9, Guard }, 
	{ 10, Crab },
	{ 11, Rogue },
	{ 12, Giant },
	{ 13, Knight },
	{ 14, Necro },
	{ 15, Dragon }
	};
	return Monster_Map.find(key)->second;
}


#pragma region Getters

string Monster::get_Name() {
	return Name;
}
string Monster::get_Description() {
	return Description;
}
int Monster::get_Attack() {
	return Attack;
}
int Monster::get_Defense() {
	return Defense;
}
int Monster::get_Level() {
	return Level;
}
int Monster::get_Gold() {
	return Gold;
}
int Monster::get_Type() {
	return Type;
}
int Monster::get_MaxHealth() {
	return MaxHealth;
}
int Monster::get_Health() {
	return Health;
}
#pragma endregion