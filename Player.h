#include <string>
#include <stack>
#include <map>
#include"ccc_win.h"
#include <fstream>
#include<vector>
#include <list>
#include <math.h>

using namespace std; 

class Player
{
private:
	string character;
	string nickname;
	unsigned int score;
	int offsetx[5]; int offsety[5]; int offsetxy1; int offsetxy2[2];
public:
	Player();
	string getName();
	void setName(string s);
	string getChar();
	void setChar(string c);
	unsigned int getScore();
	void setScore(unsigned int i);
	//string X(int x);
	//string O(int x);
	Point play(int size, string x ,bool y,int level,string ar[], bool com); 
	void undo();
	string GenChar(int n);
	string GenOpChar(int n);
	void compPlay(int &x, int&y, int i, int size);
};