#pragma once	
#include <iostream>
using namespace std;
class Player {
private:
	int x;
	int y;
	int maxX;
	int maxY;
	int flash_timer= 0;
public:
	const string s = "¡ö";
	Player(int maxY, int maxX);
	bool print(int y1, int x1);
	void left();
	void right();
	int getx();
	int gety();
	void up();
	void down();
	void Flash();
	void flashing();
	bool getflash();
};