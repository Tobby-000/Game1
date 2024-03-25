#include<iostream>
#include<Windows.h>
#include<vector>
using namespace std;
int score = 0;
class cl {
private:
	int x;
	int y;
    int maxX;
    int maxY;
public:
    const string s = "■";
	cl(int y,int x,int maxY,int maxX) {
		this->x = x;
		this->y = y;
        this->maxX = maxX;
        this->maxY = maxY;
	}
    bool print(int y1, int x1){
        if ((x1 > x - 2 && x1 < x + 2 )&&y1==y|| (y == y1 || y - 1 == y1)&&x==x1)
            return 1;
        else
            return 0;
    }
    void left() {
        if(x>2)
        x--;
        return;
    }
    void right() {
        if(x<maxX-3)
        x++;
        return;
    }
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
};
class ammo {
private:
    int y;
    int x;
    int x0;
    int y0;
    bool isshoot=0;
public:
    ammo(int x,int y) {
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
        return y1 == y && x1 == x&&isshoot;
    }
    bool move() {
        if (isshoot) {
            if (x <1) {
                return 1;
                isshoot = 0;
                y = y0;
                x = x0;
            }
            else {
                x--;
                return 0;
            }
        }
    }
    void shoot() {
        isshoot = 1;
        return;
    }
};
class enemy {
private:
    int x;
    int y;
public:
    enemy(){
        int b = 29, a = 1;
        y = 1;
        x = rand() % (b - a + 1) + a;
    }
    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
};
int main()
{
    cl* c = new cl(23,14,25,30);
    ammo shoot[10] = {
        ammo(0,0),
        ammo(0,0),
        ammo(0,0),
        ammo(0,0),
        ammo(0,0),
        ammo(0,0),
        ammo(0,0),
        ammo(0,0),
        ammo(0,0),
        ammo(0,0)
    };
    enemy ene[5] = {
        enemy(),
        enemy(),
        enemy(),
        enemy(),
        enemy()
    };
    int tick = 0;
    int begin = 0;
    int first = 0;
    int sum = 0;
    while (true)
    {
        Sleep(20);
        // 方向左键被按下了
        if (GetAsyncKeyState(VK_LEFT) & 0X8000)
        {
            c->left();
        }
        //方向右键被按下了 
        else if (GetAsyncKeyState(VK_RIGHT) & 0X8000)
        {
            c->right();
        }
        // 输出整个画面的for循环之前
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 30; j++)
            {
                bool am = 0;
                for (int k = 0; k < 10; k++) {
                    am = shoot[k].print(i, j);
                    if (am)
                        break;
                }
                if (i == 0 || i == 24 || j == 0 || j == 29)
                    cout << "□";
                else if (c->print(i,j)) {
                    cout << c->s;
                }
                else if (am) {
                    cout << "▲";
                }
                else
                    cout << " ";
            }

            cout << endl;
        }
        cout << "Score:  " << score << endl;
        tick++;
        if (tick % 5 == 0) {
            shoot[begin].shoot();
            shoot[begin].set(c->gety(), c->getx());
            if (begin < 9)
                begin++;
            else
                begin = 0;
        }
        if (tick == 300000) {
            tick = 0;
        }
        for (int k = 0; k < 10; k++) {
            if ((begin > first && k<begin && k>first) || (begin < first && (k > first || k < begin))) {
                if (shoot[k].move()) {
                    if (first < 9)
                        first++;
                    else
                        first = 0;
                }
            }
        }
    }


}


