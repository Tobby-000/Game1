//引用
#include<iostream>
#include<Windows.h>
#include<vector>
#include<conio.h>
#include<ctime>
#include"player.h"
#include"Bullet.h"
#include"Enemy.h"

using namespace std;
//常数(简单模式数值)
const int SCREEN_WIDTH = 40;
const int SCREEN_HEIGHT = 25;
const int DELAY_TIME = 5;
const int PLAYER_LIFE_DEFAULT = 5;
const int BULLET_SPEED = 1;
const int ENEMY_BULLET_SPEED = 1;
const int BULLET_SHOOT_SPEED = 5;
const int ENEMY_BULLET_SHOOT_SPEED = 20;
const int FLASH_DURATION = 40;
const int BULLET_LIFESPAN = 100;
const int SCORE_PER_ENEMY = 1000;
const int GAME_TICK_LIMIT = 300000;
//全局变量
int ENEMY_SPAWN_INTERVAL = 40;
int ENEMY_SPEED = 5;
int life = PLAYER_LIFE_DEFAULT;
int score = 0;
int tick = 0;
int shootdelay = 0;
int delay = 0;
int modeselect = 0;
bool start = 0;
//函数声明
inline void gameRender(Player* player, vector<Bullet>& bullets, vector<Bullet>& Enemybullets, vector<Enemy>& enemies);
void Updater(Player* player, vector<Bullet>& bullets, vector<Bullet>& Enemybullets, vector<Enemy>& enemies);
void menuRender() ;
void restart() {
	life = PLAYER_LIFE_DEFAULT;
	score = 0;
	tick = 0;
	shootdelay = 0;
	delay = 0;
	modeselect = 0;
	start = 0;
}
//主函数定义
int main()
{
	while (true) {
		srand(static_cast<unsigned int>(time(nullptr)));
		Player* player = new Player(SCREEN_HEIGHT, SCREEN_WIDTH, FLASH_DURATION);
		vector<Bullet> bullets;
		vector<Enemy> enemies;
		vector<Bullet> enemyBullets;
		int begin = 0;
		int first = 0;
		int sum = 0;

		while (true)
		{
			if (start == 0) {
				Sleep(DELAY_TIME * 10);
				if (GetAsyncKeyState(VK_DOWN) & 0X8000) {
					modeselect++;
					if (modeselect == 3)
						modeselect = 0;
				}
				else if (GetAsyncKeyState(VK_UP) & 0X8000) {
					modeselect--;
					if (modeselect == -1)
						modeselect = 2;
				}
			}
			else {
				Sleep(DELAY_TIME);
				if (GetAsyncKeyState(VK_LEFT) & 0X8000)
					player->left();
				else if (GetAsyncKeyState(VK_RIGHT) & 0X8000)
					player->right();
				else if (GetAsyncKeyState(VK_UP) & 0X8000)
					player->up();
				else if (GetAsyncKeyState(VK_DOWN) & 0X8000)
					player->down();
			}
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

			if (start == 0) {
				if (GetAsyncKeyState(VK_RETURN) & 0X8000) {
					start = 1;
					if (modeselect == 1) {
						ENEMY_SPEED = 3;
						ENEMY_SPAWN_INTERVAL = 20;
						life = 3;
					}
					else if (modeselect == 2) {
						system("cls");
						cout << "Please input the Enemy speed(2-10):";
						cin >> ENEMY_SPEED;
						cout << "Please input the  Enemy spawn interval(10-100):";
						cin >> ENEMY_SPAWN_INTERVAL;
						cout << "Please input the Player life:";
						cin >> life;
						system("cls");
						if (ENEMY_SPEED < 2 || ENEMY_SPEED>10 || ENEMY_SPAWN_INTERVAL < 10 || ENEMY_SPAWN_INTERVAL>100 || life < 1) {
							cout << "Invalid input, please input again" << endl;
							Sleep(3000);
							system("cls");
							start = 0;
							continue;
						}
						if (life == 114514) {
							ENEMY_SPEED = 1;
							ENEMY_SPAWN_INTERVAL = 1;
							modeselect = 3;
						}
					}
				}
				menuRender();
			}
			else {
				Updater(player, bullets, enemyBullets, enemies);
				gameRender(player, bullets, enemyBullets, enemies);
				if (life == 0)
					break;
				else
					score++;
			}
		}
		system("cls");
		cout << "Game Over" << endl;
		cout << "Your Score is :  " << score << endl;
		Sleep(3000);
		cout << "Type ENTER to Restart this game" << endl;

		while (1) {
			if (GetAsyncKeyState(VK_RETURN) & 0X8000) {
				restart();
				break;
			}
		}
	}
}
//菜单渲染函数
void menuRender() {
		for (int i = 0; i < SCREEN_HEIGHT; i++) {
			for (int j = 0; j < SCREEN_WIDTH+30; j++) {
				if (i == SCREEN_HEIGHT / 4 && j == 4) {
					if (modeselect != 0) {
						cout << "  1.简单模式";
						for (int k = 0; k < SCREEN_WIDTH - 17; k++)
							cout << " ";
					}
					else {
						cout << "> 1.简单模式  <";
						for (int k = 0; k < SCREEN_WIDTH - 20; k++)
							cout << " ";
					}
					cout << "□";
					for (int k = 0; k < 29; k++)
						cout << " ";
					cout << "□";
					break;
				}
				else if (i == SCREEN_HEIGHT / 2 && j == 4) {
					if (modeselect != 1) {
						cout << "  2.困难模式";
						for (int k = 0; k < SCREEN_WIDTH - 17; k++)
							cout << " ";
					}
					else {
						cout << "> 2.困难模式  <";
						for (int k = 0; k < SCREEN_WIDTH - 20; k++)
							cout << " ";
					}
					cout << "□";
					for(int k=0;k<29;k++)
						cout << " ";
					cout << "□";
					break;
				}
				else if (i == SCREEN_HEIGHT / 4*3 && j == 4){
					if (modeselect != 2) {
						cout << "  3.自定义";
						for (int k = 0; k < SCREEN_WIDTH - 15; k++)
							cout << " ";
					}
					else {
						cout << "> 3.自定义    <";
						for (int k = 0; k < SCREEN_WIDTH - 20; k++)
							cout << " ";
					}
					cout << "□";
					for (int k = 0; k < 29; k++)
						cout << " ";
					cout << "□";
					break;
				}
				else if (i == 0 || i == SCREEN_HEIGHT - 1 || j == 0 || j == SCREEN_WIDTH - 1||j==SCREEN_WIDTH+29)
					cout << "□";
				else
					cout << " ";
			}
			cout << endl;
		}
}

//游戏渲染函数
inline void gameRender(Player* player,vector<Bullet>& bullets,vector<Bullet>& Enemybullets,vector<Enemy>& enemies) {
	int render = 0;
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH+30; j++)
		{
			bool isBullet = 0;
			bool isEnemy= 0;
			bool isEnemyBullet = 0;
			for (int k = 0; k < bullets.size(); k++) {
				isBullet = bullets[k].print(i, j);
				if (isBullet)
					break;
			}
			for (int k = 0; k < enemies.size(); k++) {
				isEnemy = enemies[k].print(i, j);
				if (isEnemy)
					break;
			}
			for (int k = 0; k < Enemybullets.size(); k++) {
				isEnemyBullet = Enemybullets[k].print(i, j);
				if (isEnemyBullet)
					break;
			}
			if (render != 0) {
				render--;
				continue;
			}
			if (i == 0 || i == SCREEN_HEIGHT-1 || j == 0 || j == SCREEN_WIDTH-1||j==SCREEN_WIDTH+29)
				cout << "□";
			else if (i == SCREEN_HEIGHT / 4 && j == SCREEN_WIDTH + 6) {
				render = 9 + log10(life);
				cout << "LIFE  :  "<<life;
			}
			else if (i == SCREEN_HEIGHT / 4 * 2&& j == SCREEN_WIDTH + 6) {
				render = 9 + log10(score);
				cout << "SCORE :  " << score;
			}
			else if (i == SCREEN_HEIGHT / 4 * 3 && j == SCREEN_WIDTH + 6) {
				cout<<  "MODE  :";
				if (modeselect == 0)
					cout << "  EZ(easy)";
				else if (modeselect == 1)
					cout << "  Hard    ";
				else if (modeselect == 2)
					cout << "  Custom  ";
				else
					cout << "  114514  ";
				render = 16;
			}
			else if (player->print(i, j))
				cout << player->s;
			else if (isBullet)
				cout << "▲";
			else if (isEnemy)
				cout << "▼";
			else if(isEnemyBullet)
				cout << "┋";
			else
				cout << " ";
		}
		cout << endl;
	}
	/*
	* 宽度显示用代码
	for (int i = 0,j=0; i < SCREEN_WIDTH; i++) {
		if(j>9){
			j = 0;
		}
		cout << j;
		j++;
	}
	cout << endl;
	*/
	cout << "Score: " << score << endl<<"Life:  " << life << endl;
	cout << "Programmed by Tobby_000"<<endl<<"MODE:";
	if(modeselect==0)
		cout << "  EZ(easy)";
	else if(modeselect==1)
		cout << "  Hard    ";
	else if(modeselect==2)
		cout << "  Custom  ";
	else
		cout<<  "  114514  ";
}
//更新函数
void Updater(Player* player, vector<Bullet>& bullets, vector<Bullet>& enemyBullets, vector<Enemy>& enemies) {
	if (tick == GAME_TICK_LIMIT)
		tick = 0;
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
				score += SCORE_PER_ENEMY;
				life--;
				player->Flash();
			}
	}
	tick++;
	player->flashing();
	if (shootdelay == 0 && GetAsyncKeyState(VK_SPACE) & 0X8000) {
		Bullet temp(player->gety(), player->getx());
		bullets.push_back(temp);
		shootdelay = BULLET_SHOOT_SPEED;
	}
	else if (shootdelay != 0)
		shootdelay--;
	if (tick % ENEMY_SPAWN_INTERVAL == 0) {
		for (;;) {
			bool gen = 1;
			Enemy tem(SCREEN_WIDTH-3);
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
	if (tick % ENEMY_BULLET_SHOOT_SPEED == 0) {
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].live) {
				Bullet temp(enemies[i].gety(), enemies[i].getx());
				enemyBullets.push_back(temp);
			}
		}
	}
	if (tick % BULLET_SPEED == 0) {
		for (int k = 0; k < bullets.size(); k++) {
			if (bullets[k].move()) {
				bullets.erase(bullets.begin());
			}
		}
	}
	for (int k = 0; k < enemyBullets.size(); k++) {
		if (enemyBullets[k].emove()) {
			enemyBullets.erase(enemyBullets.begin());
		}
	}
	for (int k = 0; k < enemies.size(); k++) {
		if (tick % ENEMY_SPEED == 0) {
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