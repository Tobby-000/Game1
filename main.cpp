#include<iostream>
#include<Windows.h>
#include<vector>
#include <conio.h>
using namespace std;
int life = 5;
int score = 0;
class cl {
private:
    int x;
    int y;
    int maxX;
    int maxY;
    int Flash = 0;
public:
    const string s = "■";
    cl(int y, int x, int maxY, int maxX) {
        this->x = x;
        this->y = y;
        this->maxX = maxX;
        this->maxY = maxY;
    }
    bool print(int y1, int x1) {
        if (Flash % 2 == 0) {
            if ((x1 > x - 2 && x1 < x + 2) && y1 == y || (y == y1 || y - 1 == y1) && x == x1)
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    void left() {
        if (x > 2)
            x--;
        return;
    }
    void right() {
        if (x < maxX - 3)
            x++;
        return;
    }
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
    void up() {
        if (y >= 3)
            y--;
        return;
    }
    void down() {
        if (y <= maxY - 3)
            y++;
        return;
    }
    void flash() {
        Flash = 40;
        return;
    }
    void flashing() {
        if (Flash > 0)
            Flash--;
        return;
    }
};
class ammo {
private:
    int y;
    int x;
    int x0;
    int y0;

public:
    bool isshoot = 1;
    ammo(int x, int y) {
        this->x = x;
        this->y = y;
        x0 = x;
        y0 = y;
    }
    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }
    bool print(int x1, int y1) {
        if (isshoot)
            return y1 == y && x1 == x;
        else
            return 0;
    }
    bool move() {
        if (x < -1) {
            return 1;
        }
        else {
            x--;
            return 0;
        }
    }
    bool emove() {
        if (x > 30) {
            return 1;
        }
        else {
            x++;
            return 0;
        }
    }
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }

    void shoot() {
        isshoot = 0;
        return;
    }
};
class enemy {
private:
    int x;
    int y;
public:
    bool live = 1;
    enemy(int max) {
        int b = max, a = 2;
        y = -1;
        x = rand() % (b - a + 1) + a;
    }
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
    bool print(int y1, int x1) {
        if (live) {
            if ((x > x1 - 2 && x < x1 + 2) && y == y1 || (y1 == y || y1 - +1 == y) && x == x1)
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    bool move() {
        if (y > 22) {
            return 1;
        }
        else {
            y++;
            return 0;
        }
    }
    void kill() {
        live = 0;
        return;
    }
};
int main()
{
    cl* c = new cl(23, 14, 25, 30);
    vector<ammo> shoot;
    vector<enemy> ene;
    vector<ammo> enesh;
    int tick = 0;
    int begin = 0;
    int first = 0;
    int sum = 0;
    int delay = 0;
    int shootdelay = 0;
    while (true)
    {
        Sleep(10);
        if (GetAsyncKeyState(VK_LEFT) & 0X8000)
        {
            c->left();
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0X8000)
        {
            c->right();
        }
        else if (GetAsyncKeyState(VK_UP) & 0X8000)
        {
            c->up();
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0X8000)
        {
            c->down();
        }
        for (int m = 0; m < ene.size(); m++) {
            for (int n = 0; n < shoot.size(); n++) {
                if (ene[m].live && shoot[n].isshoot && ene[m].print(shoot[n].getx(), shoot[n].gety())) {
                    ene[m].kill();
                    shoot[n].shoot();
                    score += 1000;
                }
            }
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 30; j++)
            {
                bool am = 0;
                bool en = 0;
                bool enam = 0;
                for (int k = 0; k < shoot.size(); k++) {
                    am = shoot[k].print(i, j);
                    if (am)
                        break;
                }
                for (int k = 0; k < ene.size(); k++) {
                    en = ene[k].print(i, j);
                    if (en)
                        break;
                }
                for (int k = 0; k < enesh.size(); k++) {
                    enam = enesh[k].print(i, j);
                    if (enam)
                        break;
                }
                if (i == 0 || i == 24 || j == 0 || j == 29)
                    cout << "□";
                else if (c->print(i, j)) {
                    cout << c->s;
                }
                else if (am) {
                    cout << "▲";
                }
                else if (en||enam) {
                    cout << "▼";
                }
                else
                    cout << " ";
            }
            cout << endl;
        }
        cout << "Score: " << score << "          Life:  " << life << endl;
        cout << "Programmed by Tobby_000";
        tick++;
        c->flashing();
        if (shootdelay == 0 && GetAsyncKeyState(VK_SPACE) & 0X8000) {
            ammo temp(c->gety(), c->getx());
            shoot.push_back(temp);
            shootdelay = 10;
        }
        else if (shootdelay != 0)
            shootdelay--;
        if (tick % 40 == 0) {
            enemy tem(27);
            ene.push_back(tem);
        }
        if (tick % 10 == 0) {
            for (int i = 0; i < ene.size(); i++) {
                ammo temp(ene[i].gety(), ene[i].getx());
                enesh.push_back(temp);
            }
        }
        if (tick == 300000) {
            tick = 0;
        }
        for (int k = 0; k < shoot.size(); k++) {
            if (shoot[k].move()) {
                shoot.erase(shoot.begin());
            }
        }
        for (int k = 0; k < enesh.size(); k++) {
            if (enesh[k].emove()) {
                enesh.erase(enesh.begin());
            }
        }
        for (int k = 0; k < ene.size(); k++) {
            if (tick % 5 == 0) {
                if (ene[k].move()) {
                    ene.erase(ene.begin());
                }
            }
            if (delay == 0) {
                if (ene[k].live && ene[k].print(c->gety(), c->getx())) {
                    life--;
                    delay = 40;
                    ene[k].kill();
                    c->flash();
                }
            }
            else
                delay--;
        }

        if (life == 0)
            break;
        else
            score++;
    }
    system("cls");
    cout << "Game Over" << endl;
    cout << "Your Score is :  " << score << endl;
    cout << "Type any key to end this game" << endl;
    while (1) {
        if (_kbhit())
            break;
    }
}
