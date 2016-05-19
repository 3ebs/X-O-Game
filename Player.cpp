#include "Player.h"


Player::Player()
{
	offsetxy1 = 0;
	for (int i = 0; i < 5; i++)
	{
		offsetx[i] = 0;
		offsety[i] = 0;
	}
	for (int i = 0; i < 2; i++)
		offsetxy2[i] = 0;
}
string Player::getName()
{
	return nickname;
}
void Player::setName(string s)
{
	nickname = s;
}
string Player::getChar()
{
	return character;
}
void Player::setChar(string c)
{
	character = c;
}
unsigned int Player::getScore()
{
	return score;
}
void Player::setScore(unsigned int i)
{
	score = i;
}
Point Player::play(int size, string ch,bool y ,int level,string ar[], bool com)//determine el position 
{
	if (y == false)
	{
		Point clicked = cwin.get_mouse("");
		if (size == 3)
		{
			if (clicked.get_x() < -2.5 && clicked.get_x() > -7.5 && clicked.get_y() < 7.5 && clicked.get_y() > 2.5)//BOX1
			{
				Point center(0, 0); return center;
			}
			else if (clicked.get_x() < 2.5 && clicked.get_x() > -2.5 && clicked.get_y() < 7.5 && clicked.get_y() > 2.5)//BOX2
			{
				Point center(1, 0); return center;
			}
			else if (clicked.get_x() < 7.5 && clicked.get_x() > 2.5 && clicked.get_y() < 7.5 && clicked.get_y() > 2.5)//BOX3
			{
				Point center(2, 0); return center;
			}
			else if (clicked.get_x() < -2.5 && clicked.get_x() > -7.5 && clicked.get_y() < 2.5 && clicked.get_y() > -2.5)//BOX4
			{
				Point center(0, -1); return center;
			}
			else if (clicked.get_x() < 2.5 && clicked.get_x() > -2.5 && clicked.get_y() < 2.5 && clicked.get_y() > -2.5)//BOX5
			{
				Point center(1, -1); return center;
			}
			else if (clicked.get_x() < 7.5 && clicked.get_x() > 2.5 && clicked.get_y() < 2.5 && clicked.get_y() > -2.5)//BOX6
			{
				Point center(2, -1); return center;
			}
			else if (clicked.get_x() < -2.5 && clicked.get_x() > -7.5 && clicked.get_y() < -2.5 && clicked.get_y() > -7.5)//BOX7
			{
				Point center(0, -2); return center;
			}
			else if (clicked.get_x() < 2.5 && clicked.get_x() > -2.5 && clicked.get_y() < -2.5 && clicked.get_y() > -7.5)//BOX8
			{
				Point center(1, -2); return center;
			}
			else if (clicked.get_x() < 7.5 && clicked.get_x() > 2.5 && clicked.get_y() < -2.5 && clicked.get_y() > -7.5)//BOX9
			{
				Point center(2, -2); return center;
			}
			else if (clicked.get_x() < 19 && clicked.get_x() > 14 && clicked.get_y() < -16 && clicked.get_y() > -19)
			{
				Point center(19, 19); return center;
			}
		}
		else if (size == 4)
		{
			if (clicked.get_x() < -4 && clicked.get_x() > -8 && clicked.get_y() < 8 && clicked.get_y() > 4)//BOX1
			{
				Point center(0, 0); return center;
			}
			else if (clicked.get_x() < 0 && clicked.get_x() > -4 && clicked.get_y() < 8 && clicked.get_y() > 4)//BOX2
			{
				Point center(1, 0); return center;
			}
			else if (clicked.get_x() < 4 && clicked.get_x() > 0 && clicked.get_y() < 8 && clicked.get_y() > 4)//BOX3
			{
				Point center(2, 0); return center;
			}
			else if (clicked.get_x() < 8 && clicked.get_x() > 4 && clicked.get_y() < 8 && clicked.get_y() > 4)//BOX4
			{
				Point center(3, 0); return center;
			}
			else if (clicked.get_x() < -4 && clicked.get_x() > -8 && clicked.get_y() < 4 && clicked.get_y() > 0)//BOX5
			{
				Point center(0, -1); return center;
			}
			else if (clicked.get_x() < 0 && clicked.get_x() > -4 && clicked.get_y() < 4 && clicked.get_y() > 0)//BOX6
			{
				Point center(1, -1); return center;
			}
			else if (clicked.get_x() < 4 && clicked.get_x() > 0 && clicked.get_y() < 4 && clicked.get_y() > 0)//BOX7
			{
				Point center(2, -1); return center;
			}
			else if (clicked.get_x() < 8 && clicked.get_x() > 4 && clicked.get_y() < 4 && clicked.get_y() > 0)//BOX8
			{
				Point center(3, -1); return center;
			}
			else if (clicked.get_x() < -4 && clicked.get_x() > -8 && clicked.get_y() < 0 && clicked.get_y() > -4)//BOX9
			{
				Point center(0, -2); return center;
			}
			else if (clicked.get_x() < 0 && clicked.get_x() > -4 && clicked.get_y() < 0 && clicked.get_y() > -4)//BOX10
			{
				Point center(1, -2); return center;
			}
			else if (clicked.get_x() < 4 && clicked.get_x() > 0 && clicked.get_y() < 0 && clicked.get_y() > -4)//BOX11
			{
				Point center(2, -2); return center;
			}
			else if (clicked.get_x() < 8 && clicked.get_x() > 4 && clicked.get_y() < 0 && clicked.get_y() > -4)//BOX12
			{
				Point center(3, -2); return center;
			}
			else if (clicked.get_x() < -4 && clicked.get_x() > -8 && clicked.get_y() < -4 && clicked.get_y() > -8)//BOX13
			{
				Point center(0, -3); return center;
			}
			else if (clicked.get_x() < 0 && clicked.get_x() > -4 && clicked.get_y() < -4 && clicked.get_y() > -8)//BOX14
			{
				Point center(1, -3); return center;
			}
			else if (clicked.get_x() < 4 && clicked.get_x() > 0 && clicked.get_y() < -4 && clicked.get_y() > -8)//BOX15
			{
				Point center(2, -3); return center;
			}
			else if (clicked.get_x() < 8 && clicked.get_x() > 4 && clicked.get_y() < -4 && clicked.get_y() > -8)//BOX16
			{
				Point center(3, -3); return center;
			}
			else if (clicked.get_x() < 19 && clicked.get_x() > 14 && clicked.get_y() < -16 && clicked.get_y() > -19)
			{
				Point center(19, 19); return center;
			}
		}
		else if (size == 5)
		{
			if (clicked.get_x() > -7.5 && clicked.get_x() < -4.5 && clicked.get_y() > 4.5 && clicked.get_y() < 7.5)//BOX1
			{
				Point center(0, 0); return center;
			}
			else if (clicked.get_x() > -4.5 && clicked.get_x() < -1.5 && clicked.get_y() > 4.5 && clicked.get_y() < 7.5)//BOX2
			{
				Point center(1, 0); return center;
			}
			else if (clicked.get_x() > -1.5 && clicked.get_x() < 1.5 && clicked.get_y() > 4.5 && clicked.get_y() < 7.5)//BOX3
			{
				Point center(2, 0); return center;
			}
			else if (clicked.get_x() > 1.5 && clicked.get_x() < 4.5 && clicked.get_y() > 4.5 && clicked.get_y() < 7.5)//BOX4
			{
				Point center(3, 0); return center;
			}
			else if (clicked.get_x() > 4.5 && clicked.get_x() < 7.5 && clicked.get_y() > 4.5 && clicked.get_y() < 7.6)//BOX5
			{
				Point center(4, 0); return center;
			}
			else if (clicked.get_x() > -7.5 && clicked.get_x() < -4.5 && clicked.get_y() > 1.5 && clicked.get_y() < 4.5)//BOX6
			{
				Point center(0, -1); return center;
			}
			else if (clicked.get_x() > -4.5 && clicked.get_x() < -1.5 && clicked.get_y() > 1.5 && clicked.get_y() < 4.5)//BOX7
			{
				Point center(1, -1); return center;
			}
			else if (clicked.get_x() > -1.5 && clicked.get_x() < 1.5 && clicked.get_y() > 1.5 && clicked.get_y() < 4.5)//BOX8
			{
				Point center(2, -1); return center;
			}
			else if (clicked.get_x() > 1.5 && clicked.get_x() < 4.5 && clicked.get_y() > 1.5 && clicked.get_y() < 4.5)//BOX9
			{
				Point center(3, -1); return center;
			}
			else if (clicked.get_x() > 4.5 && clicked.get_x() < 7.5 && clicked.get_y() > 1.5 && clicked.get_y() < 4.5)//BOX10
			{
				Point center(4, -1); return center;
			}
			else if (clicked.get_x() > -7.5 && clicked.get_x() < -4.5 && clicked.get_y() > -1.5 && clicked.get_y() < 1.5)//BOX11
			{
				Point center(0, -2); return center;
			}
			else if (clicked.get_x() > -4.5 && clicked.get_x() < -1.5 && clicked.get_y() > -1.5 && clicked.get_y() < 1.5)//BOX12
			{
				Point center(1, -2); return center;
			}
			else if (clicked.get_x() > -1.5 && clicked.get_x() < 1.5 && clicked.get_y() > -1.5 && clicked.get_y() < 1.5)//BOX13
			{
				Point center(2, -2); return center;
			}
			else if (clicked.get_x() > 1.5 && clicked.get_x() < 4.5 && clicked.get_y() > -1.5 && clicked.get_y() < 1.5)//BOX14
			{
				Point center(3, -2); return center;
			}
			else if (clicked.get_x() > 4.5 && clicked.get_x() < 7.5 && clicked.get_y() > -1.5 && clicked.get_y() < 1.5)//BOX15
			{
				Point center(4, -2); return center;
			}
			else if (clicked.get_x() > -7.5 && clicked.get_x() < -4.5 && clicked.get_y() > -4.5 && clicked.get_y() < -1.5)//BOX16
			{
				Point center(0, -3); return center;
			}
			else if (clicked.get_x() > -4.5 && clicked.get_x() < -1.5 && clicked.get_y() > -4.5 && clicked.get_y() < -1.5)//BOX17
			{
				Point center(1, -3); return center;
			}
			else if (clicked.get_x() > -1.5 && clicked.get_x() < 1.5 && clicked.get_y() > -4.5 && clicked.get_y() < -1.5)//BOX18
			{
				Point center(2, -3); return center;
			}
			else if (clicked.get_x() > 1.5 && clicked.get_x() < 4.5 && clicked.get_y() > -4.5 && clicked.get_y() < -1.5)//BOX19
			{
				Point center(3, -3); return center;
			}
			else if (clicked.get_x() > 4.5 && clicked.get_x() < 7.5 && clicked.get_y() > -4.5 && clicked.get_y() < -1.5)//BOX20
			{
				Point center(4, -3); return center;
			}
			else if (clicked.get_x() > -7.5 && clicked.get_x() < -4.5 && clicked.get_y() > -7.5 && clicked.get_y() < -4.5)//BOX21
			{
				Point center(0, -4); return center;
			}
			else if (clicked.get_x() > -4.5 && clicked.get_x() < -1.5 && clicked.get_y() > -7.5 && clicked.get_y() < -4.5)//BOX22
			{
				Point center(1, -4); return center;
			}
			else if (clicked.get_x() > -1.5 && clicked.get_x() < 1.5 && clicked.get_y() > -7.5 && clicked.get_y() < -4.5)//BOX23
			{
				Point center(2, -4); return center;
			}
			else if (clicked.get_x() > 1.5 && clicked.get_x() < 4.5 && clicked.get_y() > -7.5 && clicked.get_y() < -4.5)//BOX24
			{
				Point center(3, -4); return center;
			}
			else if (clicked.get_x() > 4.5 && clicked.get_x() < 7.5 && clicked.get_y() > -7.5 && clicked.get_y() < -4.5)//BOX25
			{
				Point center(4, -4); return center;
			}
			else if (clicked.get_x() < 19 && clicked.get_x() > 14 && clicked.get_y() < -16 && clicked.get_y() > -19)
			{
				Point center(19, 19); return center;
			}
		}
		if (com)
		{
			if (clicked.get_x() > -19 && clicked.get_x() < -14 && clicked.get_y() < -16 && clicked.get_y() > -19)
			{
				Point center(-19, -19); return center;
			}
		}
	}
	else if (y == true && level == 1)//EASYYYYY MODDDDDDDEEEEEEEE
	{
		int o = rand() % size;
		int u = rand() % size;
		Point center(o, -u); return center;

	}
	else if (y == true && level == 2)//HAAAAAAAARRRRRRRRDDDDDDDDDD MOOOODEEEEEEEEEE
	{
		int o = 0; int u = 0;
		for (int i = 0; i < 12; i++)//bnlf 3l counter
		{
			if (ar[i] == GenChar(size -1))
			{
				compPlay(o, u, i, size);
				Point center(o, -u); return center;
			}
			else if (ar[i] == GenOpChar(size - 1))
			{
				compPlay(o, u, i, size);
				Point center(o, -u); return center;
			}
		}
		o = rand() % size;
		u = rand() % size;
		Point center(o, -u); return center;
	}
	return Point(111, 111); //big error 
}

//string Player::X(int n)
//{
//	string x = "";
//	for (int i = 0; i < n; i++)
//	{
//		x += "X";
//	}
//	return x;
//}
//
//string Player::O(int n)
//{
//	string o = "";
//	for (int i = 0; i < n; i++)
//	{
//		o += "O";
//	}
//	return o;
//}

string Player::GenChar(int n)
{
	string gen = "";
	string ch = getChar(); 
	for (int i = 0; i < n; i++)
	{
		gen += ch;
	}
	return gen;
}

string Player::GenOpChar(int n)
{
	string gen = "";
	string ch;
	if (getChar() == "X") ch = "O";
	else if (getChar() == "O") ch = "X";
	for (int i = 0; i < n; i++)
	{
		gen += ch;
	}
	return gen;
}

void Player::compPlay(int &o, int &u, int i, int size)
{
	switch (i)
	{
	case 0://row1
		o = offsetx[0];
		u = 0;
		offsetx[0]++; break;
	case 1://row2
		o = offsetx[1];
		u = 1;
		offsetx[1]++; break;
	case 2://row3
		o = offsetx[2];
		u = 2;
		offsetx[2]++; break;
	case 3: //row4
		o = offsetx[3];
		u = 3;
		offsetx[3]++; break;
	case 4: //row5
		o = offsetx[4];
		u = 4;
		offsetx[4]++; break;
	case 5://col1
		o = 0;
		u = offsety[0];
		offsety[0]++; break;
	case 6://col2
		o = 1;
		u = offsety[1];
		offsety[1]++; break;
	case 7://col3
		o = 2;
		u = offsety[2];
		offsety[2]++; break;
	case 8: //col4
		o = 3;
		u = offsety[3];
		offsety[3]++; break;
	case 9://col5
		o = 4;
		u = offsety[4];
		offsety[4]++; break;
	case 10://diag1
		o = offsetxy1;
		u = offsetxy1;
		offsetxy1++; break;
	case 11://diag2
		o = offsetxy2[0] + size - 1;
		u = offsetxy2[1];
		offsetxy2[0]--;
		offsetxy2[1]++;
		break;
	}
}