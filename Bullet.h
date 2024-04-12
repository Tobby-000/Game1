//×Óµ¯Àà
#pragma once
using namespace std;
class Bullet {
private:
	int y;
	int x;
	int x0;
	int y0;

public:
	bool isshoot = 1;
	Bullet(int x, int y);
	void set(int x, int y);
	bool print(int x1, int y1);
	bool move();
	bool emove();
	int getx();
	int gety();
	void shoot();
};