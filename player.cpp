
//Player class

#include"player.h"

Player::Player(int maxY, int maxX) {
	this->x = maxX/2;
	this->y = maxY-2;
	this->maxX = maxX;
	this->maxY = maxY;
}
bool Player::print(int y1, int x1) {
	if (flash_timer % 2 == 0) {
		if ((x1 > x - 2 && x1 < x + 2) && y1 == y || (y == y1 || y - 1 == y1) && x == x1)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
void Player::left() {
	if (x > 2)
		x--;
	return;
}
void Player::right() {
	if (x < maxX - 3)
		x++;
	return;
}
int Player::getx() {
	return x;
}
int Player::gety() {
	return y;
}
void Player::up() {
	if (y >= 3)
		y--;
	return;
}
void Player::down() {
	if (y <= maxY - 3)
		y++;
	return;
}
void Player::Flash() {
	flash_timer = 40;
	return;
}
void Player::flashing() {
	if (flash_timer > 0)
		flash_timer--;
	return;
}
bool Player::getflash() {
	if (flash_timer != 0)
		return 0;
	else
		return 1;
}