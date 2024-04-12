//µ–»À¿‡
#pragma once
#include <cstdlib>
using namespace std;
class Enemy {
private:
	int x;
	int y;
public:
	bool live = 1;
	Enemy(int max);
	int getx();
	int gety();
	bool print(int y1, int x1);
	bool move();
	void kill();
};