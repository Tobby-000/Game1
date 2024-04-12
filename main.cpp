#include<iostream>
#include<Windows.h>
#include<vector>
#include<conio.h>
#include<ctime>
#include"player.h"
#include"Bullet.h"
#include"Enemy.h"

using namespace std;
const int SCREEN_WIDTH = 30;
const int SCREEN_HEIGHT = 25;
const int PLAYER_LIFE_DEFAULT = 5;
const int BULLET_SPEED = 1;
const int ENEMY_SPEED = 1;
const int FLASH_DURATION = 40;
const int BULLET_LIFESPAN = 100;
const int ENEMY_SPAWN_INTERVAL = 40;
const int SCORE_PER_ENEMY = 1000;
const int GAME_TICK_LIMIT = 300000;

int life = 5;
int score = 0;
int tick = 0;
int shootdelay = 0;
int delay = 0;

void gameRender(Player* player, vector<Bullet>& bullets, vector<Bullet>& Enemybullets, vector<Enemy>& enemies);
void Updater(Player* player, vector<Bullet>& bullets, vector<Bullet>& Enemybullets, vector<Enemy>& enemies);

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	Player* player = new Player(SCREEN_HEIGHT, SCREEN_WIDTH);
	vector<Bullet> bullets;
	vector<Enemy> enemies;
	vector<Bullet> enemyBullets;
	int begin = 0;
	int first = 0;
	int sum = 0;

	while (true)
	{
		Sleep(10);
		if (GetAsyncKeyState(VK_LEFT) & 0X8000)
			player->left();
		else if (GetAsyncKeyState(VK_RIGHT) & 0X8000)
			player->right();
		else if (GetAsyncKeyState(VK_UP) & 0X8000)
			player->up();
		else if (GetAsyncKeyState(VK_DOWN) & 0X8000)
			player->down();

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		Updater(player, bullets, enemyBullets, enemies);
		gameRender(player, bullets, enemyBullets, enemies);
		if (life == 0)
			break;
		else
			score++;
	}
	system("cls");
	cout << "Game Over" << endl;
	cout << "Your Score is :  " << score << endl;
	Sleep(3000);
	cout << "Type any key to end this game" << endl;
	while (1) {
		if (_kbhit() != 0)
			break;
	}
}

void gameRender(Player* player,vector<Bullet>& bullets,vector<Bullet>& Enemybullets,vector<Enemy>& enemies) {
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			bool am = 0;
			bool en = 0;
			bool enam = 0;
			for (int k = 0; k < bullets.size(); k++) {
				am = bullets[k].print(i, j);
				if (am)
					break;
			}
			for (int k = 0; k < enemies.size(); k++) {
				en = enemies[k].print(i, j);
				if (en)
					break;
			}
			for (int k = 0; k < Enemybullets.size(); k++) {
				enam = Enemybullets[k].print(i, j);
				if (enam)
					break;
			}
			if (i == 0 || i == 24 || j == 0 || j == 29)
				cout << "□";
			else if (player->print(i, j))
				cout << player->s;
			else if (am)
				cout << "▲";
			else if (en || enam)
				cout << "▼";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << "Score: " << score << "          Life:  " << life << endl;
	cout << "Programmed by Tobby_000";
}

void Updater(Player* player, vector<Bullet>& bullets, vector<Bullet>& enemyBullets, vector<Enemy>& enemies) {
	for (int m = 0; m < enemies.size(); m++) {
		for (int n = 0; n < bullets.size(); n++) {
			if (enemies[m].live && bullets[n].isshoot && enemies[m].print(bullets[n].getx(), bullets[n].gety())) {
				enemies[m].kill();
				bullets[n].shoot();
				score += 1000;
			}
		}
	}
	for (int n = 0; n < enemyBullets.size(); n++) {
		if (player->getflash())
			if (enemyBullets[n].isshoot && player->print(enemyBullets[n].getx(), enemyBullets[n].gety())) {
				enemyBullets[n].shoot();
				score += 1000;
				life--;
				player->Flash();
			}
	}
	tick++;
	player->flashing();
	if (shootdelay == 0 && GetAsyncKeyState(VK_SPACE) & 0X8000) {
		Bullet temp(player->gety(), player->getx());
		bullets.push_back(temp);
		shootdelay = 10;
	}
	else if (shootdelay != 0)
		shootdelay--;
	if (tick % 40 == 0) {
		for (;;) {
			bool gen = 1;
			Enemy tem(27);
			for (int i = 0; i < enemies.size(); i++) {
				if (tem.getx() >= enemies[i].getx() - 1 && tem.getx() <= enemies[i].getx() + 1)
					gen = 0;
			}
			if (gen) {
				enemies.push_back(tem);
				break;
			}
		}
	}
	if (tick % 10 == 0) {
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].live) {
				Bullet temp(enemies[i].gety(), enemies[i].getx());
				enemyBullets.push_back(temp);
			}
		}
	}
	if (tick == 300000)
		tick = 0;
	for (int k = 0; k < bullets.size(); k++) {
		if (bullets[k].move()) {
			bullets.erase(bullets.begin());
		}
	}
	for (int k = 0; k < enemyBullets.size(); k++) {
		if (enemyBullets[k].emove()) {
			enemyBullets.erase(enemyBullets.begin());
		}
	}
	for (int k = 0; k < enemies.size(); k++) {
		if (tick % 5 == 0) {
			if (enemies[k].move())
				enemies.erase(enemies.begin());
		}
		if (player->getflash() && enemies[k].live
			&& (enemies[k].print(player->gety(), player->getx()) || enemies[k].print(player->gety() - 1, player->getx())
				|| enemies[k].print(player->gety(), player->getx() + 1) || enemies[k].print(player->gety(), player->getx() - 1))) {
			life--;
			enemies[k].kill();
			player->Flash();
		}
		else
			delay--;
	}
}
