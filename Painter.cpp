#include "Painter.h"
using std::string;
using std::cout;
//Global base
Colorize::Colorize() {}

//Clears screen with endl
void Colorize::Pseudo_Clear(int option) {
	switch (option) {
	case 1:
		cout << string(80, '\n');
		break;
	case 2:
		cout << string(30, '\n');
		break;
	case 3:
		cout << string(10, '\n');
		break;
	case 4:
		cout << string(100, '\n');
		break;
	case 5:
		cout << string(12, '\n');
		break;
	}

}


void Colorize::Paint(int Color, std::string color_me, std::string extra) {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, Color);
	std::cout << color_me << extra;
	SetConsoleTextAttribute(hConsole, 15);
}
void Colorize::WorldPaint(int Color, std::string color_me) {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, Color);
	std::cout << color_me;
	SetConsoleTextAttribute(hConsole, 15);
}
std::string Colorize::Lower(std::string input) {
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}
