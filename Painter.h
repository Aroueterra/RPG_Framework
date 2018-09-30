#ifndef Painter_H
#define Painter_H	
#include <Windows.h>
#include <iostream>
#include <string>
#include <algorithm>
class Colorize {
public:
	void Pseudo_Clear(int option);
	void Paint(int Color, std::string color_me, std::string extra);
	void WorldPaint(int Color, std::string color_me);
	std::string Lower(std::string input);
	Colorize();
};
//black=0,dark_blue=1,dGreen=2,dAqua=3,dRed=4,dYellow=6,dW=7,Gray=8,Blue=9,Green=10,11,Red=12,Purple=13
//L: 9-B 10-G 11-Aq 12-R 13-Prp 14-Y


#endif
