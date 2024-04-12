//Enemy class

#include"Enemy.h"

Enemy::Enemy(int max) {
	int b = max, a = 2;
	y = -1;
	x = rand() % (b - a + 1) + a;
}
int Enemy::getx() {
	return x;
}
int Enemy::gety() {
	return y;
}
bool Enemy::print(int y1, int x1) {
	if (live) {
		if ((x > x1 - 2 && x < x1 + 2) && y == y1 || (y1 == y || y1 - +1 == y) && x == x1)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
bool Enemy::move() {
	if (y > 22) {
		return 1;
	}
	else {
		y++;
		return 0;
	}
}
void Enemy::kill() {
	live = 0;
	return;
}