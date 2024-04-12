//Bullet class

#include "Bullet.h"

Bullet::Bullet(int x, int y) {
	this->x = x;
	this->y = y;
	x0 = x;
	y0 = y;
}
void Bullet::set(int x, int y) {
	this->x = x;
	this->y = y;
}
bool Bullet::print(int x1, int y1) {
	if (isshoot)
		return y1 == y && x1 == x;
	else
		return 0;
}
bool Bullet::move() {
	if (x < -1) {
		return 1;
		y = y0;
		x = x0;
	}
	else {
		x--;
		return 0;
	}
}
bool Bullet::emove() {
	if (x > 30) {
		return 1;
	}
	else {
		x++;
		return 0;
	}
}
int Bullet::getx() {
	return x;
}
int Bullet::gety() {
	return y;
}

void Bullet::shoot() {
	isshoot = 0;
	return;
}