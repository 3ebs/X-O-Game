#include "Game.h"



Game::Game(){}

void Game::setSize(int size)
{
	intSize = size;
}
int Game::getSize()
{
	return intSize;
}

void Game::playGame()
{
	undoFlag = false;
	saveFlag = false;
	for (int i = 0; i < 12; i++)
	{
		counter[i] = "";
	}
	string command;
	string mode;
	string yousef;
	string size;
	string character;
kkk:	command = cwin.get_string("Enter 'new' for New Game , 'load' for Loading the Last Game: ");
	if (command == "load")
	{
		savedGame.open("last saved game.txt");
		if (savedGame.is_open())
		{
			string x;
			savedGame >> x;
			if (x == "")
			{
				Message mm(Point(-19, 18), "There is NO previous game to be loaded OR file is corrupted!!");
				cwin << mm;
				Sleep(3000);
				cwin.clear();
				goto kkk;
			}
		}
		savedGame.close();
		loadBGD();
		goto exit;
	}
	else if (command == "new")
	{
kk:		mode = cwin.get_string("Enter 'p' for Player VS Player mode , 'c' for Player VS Computer mode: ");
		if (mode == "p") managePlayers(1);
		else if (mode == "c") managePlayers(0);
		else
		{
			Message mm(Point(-19, 18), "INVALID command!!");
			cwin << mm;
			Sleep(3000);
			cwin.clear();
			goto kk;
		}
	}
	else
	{
		Message mm(Point(-19, 18), "INVALID command!!");
		cwin << mm;
		Sleep(3000);
		cwin.clear();
		goto kkk;
	}
	
kok:	size = cwin.get_string("Choose Size of Board: 3x3 , 4x4 , 5x5: ");
	if (size == "3x3") setSize(3);
	else if (size == "4x4") setSize(4);
	else if (size == "5x5") setSize(5);
	else 
	{
		Message mm(Point(-19, 18), "INVALID size!!");
		cwin << mm;
		Sleep(3000);
		cwin.clear();
		goto kok;
	}
	fillBoardFlags();
	checkIfempty = true;
	if (getSize() == 3)
	{
		winningStacks = new list<string>[8];
	}
	else if (getSize() == 4)
	{
		winningStacks = new list<string>[10];
	}
	else if (getSize() == 5)
	{
		winningStacks = new list<string>[12];
	}
kiki:	yousef = p1.getName() + ", choose X/O: ";
	character = cwin.get_string(yousef);
	if (character != "X" && character != "O")
	{
		Message mm(Point(-19, 18), "INVALID character!!");
		cwin << mm;
		Sleep(3000);
		cwin.clear();
		goto kiki;
	}
	p1.setChar(character);
	if (p1.getChar() == "X") p2.setChar("O");
	else if (p1.getChar() == "O") p2.setChar("X");
	stacking(getSize(), computerFlag);
	drawBoard();
	StartGame();
exit:
	last_decision();
}
void Game::managePlayers(bool x)
{
	player.open("players.txt");
	if (player.is_open())
	{
		string input;
		int score;
		player >> numberOfPlayers;
		for (int i = 0; i < numberOfPlayers; i++)
		{
			player >> input;
			player >> score;
			players[input] = score;
		}
	}
	string checkPlayer; 
	string name;
	map <string, int> ::iterator findPlayer;
L:	checkPlayer = cwin.get_string("Enter 'e' for Existing Player1, 'n' for New Player1: ");
	if (checkPlayer != "e" && checkPlayer != "n")
	{
		Message mm(Point(-19, 18), "INVALID command!!");
		cwin << mm;
		Sleep(3000);
		cwin.clear();
		goto L;
	}
lk:	name = cwin.get_string("Enter Your Nickname: ");
	if (name.length() > 8) 
	{
		Message mm(Point(-19, 18), "Nickname is too long!!");
		cwin << mm;
		Sleep(3000);
		cwin.clear();
		goto lk;
	}
	if (checkPlayer == "e")
	{
		if (players.count(name) == 0)
		{
			Message mm(Point(-19, 18), "Nickname does not EXIST!!!");
			cwin << mm;
			Sleep(3000);
			cwin.clear();
			goto L;
		}
	}
	else if (checkPlayer == "n")
	{
		if (players.count(name) != 0)
		{
			Message mm(Point(-19, 18), "Nickname already EXISTS!!!");
			cwin << mm;
			Sleep(3000);
			cwin.clear();
			goto L;
		}
		players[name] = 0; // addition to map
		numberOfPlayers++;
	}
	p1.setName(name);
	p1.setScore(players[name]);
	playerFlag = false;

	if (x)
	{
L1:		checkPlayer = cwin.get_string("Enter 'e' for Existing Player2, 'n' for New Player2: ");
llk:		name = cwin.get_string("Enter Your Nickname: ");
		if (name.length() > 8)
		{
			Message mm(Point(-19, 18), "Nickname is too long!!");
			cwin << mm;
			Sleep(3000);
			cwin.clear();
			goto llk;
		}
		if (checkPlayer == "e")
		{
			if (players.count(name) == 0)
			{
				Message mm(Point(-19, 18), "Nickname does not EXIST!!!");
				cwin << mm;
				Sleep(3000);
				cwin.clear();
				goto L1;
			}
		}
		else if (checkPlayer == "n")
		{
			if (players.count(name) != 0)
			{
				Message mm(Point(-19, 18), "Nickname already EXISTS!!!");
				cwin << mm;
				Sleep(3000);
				cwin.clear();
				goto L1;
			}
			players[name] = 0; // addition to map
			numberOfPlayers++;
		}
		p2.setName(name);
		p2.setScore(players[name]);
		computerFlag = false;
	}
	else
	{
		p2.setName("Computer");
		mode();
		computerFlag = true;
	}
	player.close();
}
void Game::mode()
{
	string choice;
yuu:	choice = cwin.get_string("For Easy Mode enter 'easy', For Hard Mode enter 'hard':");
	if (choice == "easy") level = 1;
	else if (choice == "hard") level = 2;
	else
	{
		Message mm(Point(-19, 18), "INVALID command!!");
		cwin << mm;
		Sleep(3000);
		cwin.clear();
		goto yuu;
	}
}
void Game::saveBGD()
{
	savedGame.open("last saved game.txt", ios::out | ios::trunc);
	savedGame.clear();
	if (savedGame.is_open())
	{
		vector<string> v;
		v = undo.top();
		savedGame << getSize() << endl;
		savedGame << numberOfPlayers << endl;
		savedGame << p1.getChar() << " " << p2.getChar() << endl;
		savedGame << p1.getName() << " " << p2.getName() << endl;
		/*string ay = computerFlag ? "computer" : "player";
		savedGame << ay << endl;*/
		if (computerFlag) savedGame << to_string(level) << " " << "!" << endl;
		else savedGame << "!" << endl;
		for (vector<string>::iterator i = v.begin(); i != v.end(); i++)
		{
			savedGame << *i << " ";
		}
		savedGame << endl;
		savedGame << "!" << endl;
		string x;
		stack<string> tmp;
		while (!turns.empty())
		{
			x = turns.top();
			tmp.push(x);
			turns.pop();
		}
		while (!tmp.empty())
		{
			x = tmp.top();
			savedGame << x << endl;
			tmp.pop();
		}
		savedGame << "!";
	}
	savedGame.close();
	exit(0);
}
void Game::drawBoard()
{
	int size = getSize();
	if (size == 3)
	{
		Line l1(Point(-7.5, 7.5), Point(7.5, 7.5));Line l2(Point(7.5, 7.5), Point(7.5, -7.5));
		Line l3(Point(7.5, -7.5), Point(-7.5, -7.5));Line l4(Point(-7.5, -7.5), Point(-7.5, 7.5));
		Line l5(Point(-2.5, 7.5), Point(-2.5, -7.5));Line l6(Point(2.5, 7.5), Point(2.5, -7.5));
		Line l7(Point(-7.5, 2.5), Point(7.5, 2.5));Line l8(Point(-7.5, -2.5), Point(7.5, -2.5));
		cwin << l1 << l2 << l3 << l4 << l5 << l6 << l7 << l8;
	}
	else if (size == 4)
	{
		Line l1(Point(-8, 8), Point(8, 8)); Line l2(Point(8, 8), Point(8, -8));
		Line l3(Point(8, -8), Point(-8, -8)); Line l4(Point(-8, -8), Point(-8, 8));
		Line l5(Point(-4, 8), Point(-4, -8)); Line l6(Point(0, 8), Point(0, -8));
		Line l7(Point(4, 8), Point(4, -8)); Line l8(Point(-8, 4), Point(8, 4));
		Line l9(Point(-8, 0), Point(8, 0)); Line l10(Point(-8, -4), Point(8, -4));
		cwin << l1 << l2 << l3 << l4 << l5 << l6 << l7 << l8 << l9 << l10;
	}
	else if (size == 5)
	{
		Line l1(Point(-7.5, 7.5), Point(7.5, 7.5)); Line l2(Point(7.5, 7.5), Point(7.5, -7.5));
		Line l3(Point(7.5, -7.5), Point(-7.5, -7.5)); Line l4(Point(-7.5, -7.5), Point(-7.5, 7.5));
		Line l5(Point(4.5, 7.5), Point(4.5, -7.5)); Line l6(Point(1.5, 7.5), Point(1.5, -7.5));
		Line l7(Point(-1.5, 7.5), Point(-1.5, -7.5)); Line l8(Point(-4.5, 7.5), Point(-4.5, -7.5));
		Line l9(Point(-7.5, 4.5), Point(7.5, 4.5)); Line l10(Point(-7.5, 1.5), Point(7.5, 1.5));
		Line l11(Point(-7.5,-1.5), Point(7.5,-1.5)); Line l12(Point(-7.5,-4.5), Point(7.5,-4.5));
		cwin << l1 << l2 << l3 << l4 << l5 << l6 << l7 << l8 <<l9 << l10 << l11 <<l12;
	}
	Line l555(Point(19, -19), Point(14, -19)); Line L666(Point(19, -19), Point(19, -16)); Line L777(Point(19, -16), Point(14, -16));
	Line l666(Point(14, -19), Point(14, -16));
	Message MM(Point(14.35, -17), "SAVE&EXIT");
	cwin << MM << L666 << L777 << l666 << l555;
	if (computerFlag)
	{
		Line l55(Point(-19, -19), Point(-14, -19)); Line L66(Point(-19, -19), Point(-19, -16)); Line L77(Point(-19, -16), Point(-14, -16));
		Line l66(Point(-14, -19), Point(-14, -16));
		Message M(Point(-18, -17), "UNDO");
		cwin << l55 << L66 << L77 << l66 << M ;
	}
	int s = players[p1.getName()];
	string p = p1.getName() + ": " + to_string(s);
	Message mo(Point(-19, 17), p);
	cwin << mo;
	if (!computerFlag)
	{
		int ss = players[p2.getName()];
		string po = p2.getName() + ": " + to_string(ss);
		Message moo(Point(-19, 13), po);
		cwin << moo;
	}
}

void Game::stacking(int size, bool f)
{
	if (size == 3 && !f)
	{
		turns.push("X");
		for (int i = 0; i < 4; i++)
		{
			turns.push("O"); turns.push("X");
		}
	}
	else if (size == 3 && f)
	{
		turns.push(p1.getChar());
		for (int i = 0; i < 4; i++)
		{
			turns.push(p2.getChar()); turns.push(p1.getChar());
		}
	}
	else if (size == 4 && !f)
	{
		for (int i = 0; i < 8; i++)
		{
			turns.push("O"); turns.push("X");
		}
	}
	else if (size == 4 && f)
	{
		for (int i = 0; i < 8; i++)
		{
			turns.push(p2.getChar()); turns.push(p1.getChar());
		}
	}
	else if (size == 5 && !f)
	{
		turns.push("X");
		for (int i = 0; i < 12; i++)
		{
			turns.push("O"); turns.push("X");
		}
	}
	else if (size == 5 && f)
	{
		turns.push(p1.getChar());
		for (int i = 0; i < 12; i++)
		{
			turns.push(p2.getChar()); turns.push(p1.getChar());
		}
	}
}

void Game::StartGame()
{
	
WH:	while (!player1win && !player2win && !endGameFlag && !undoFlag && !saveFlag)
	{
		turn();
		searchForwinner();
	}
	if (undoFlag)
	{
		undoBGD();
		turns.push(p2.getChar());
		turns.push(p1.getChar());
		undoFlag = false;
		goto WH; 
	}
	else if (saveFlag) saveBGD();
	if (player1win)
	{
		Sleep(1000);
		cwin.clear();
		winning_style();
		string p = p1.getName() + " wins!";
		Message m(Point(-2, 0), p);
		cwin << m;
		if (computerFlag && level ==1) players[p1.getName()] += 10;
		else if (computerFlag && level == 2) players[p1.getName()] += 20;
		else players[p1.getName()] += 10;
		p = "Your score is " + to_string(players[p1.getName()]);
		Message mm(Point(-2, -1), p);
		cwin << mm;
		
	}
	else if (player2win)
	{
		Sleep(1000);
		cwin.clear();
		winning_style();
		string p = p2.getName() + " wins!";
		Message m(Point(-2, 0), p);
		cwin << m;
		if (!computerFlag)
		{
			players[p2.getName()] += 10;
			p = "Your score is " + to_string(players[p2.getName()]);
			Message mm(Point(-2, -1), p);
			cwin << mm;
		}
	}
	else if (endGameFlag)
	{
		Sleep(1000);
		cwin.clear();
		winning_style();
		Message m(Point(-2, 0), "Game Over!!");
		cwin << m;
	}
	storeAccounts();
}
void Game::turn()
{
	Point position;
	string insideStack;
	string whichTurn;
	insideStack = turns.top();
M:	if (p1.getChar() == insideStack)
{
		Message mn(Point(-19, 9), p1.getName() + "'s turn to play with " + p1.getChar());
		cwin << mn;
		position = p1.play(getSize(), p1.getChar(), playerFlag, level, counter, computerFlag);
		if (position.get_x() == -19 && position.get_y() == -19) undoFlag = true;
		if (position.get_x() == 19 && position.get_y() == 19) saveFlag = true;
		fillWinningStacks(position, p1.getChar());
}
	else
	{
		Message mnn(Point(-19, 9), p2.getName() + "'s turn to play with " + p2.getChar());
		cwin << mnn;
		if (computerFlag) Sleep(100);
		position = p2.play(getSize(), p2.getChar(), computerFlag, level, counter, 0);
		if (position.get_x() == 19 && position.get_y() == 19) saveFlag = true;
		fillWinningStacks(position, p2.getChar());
	}
	if (checkIfempty || undoFlag)
	{
		draw(insideStack, getSize(), position);
		if (!undoFlag)
			fillingUndo(insideStack, position);
		if (checkIfempty && !saveFlag)
			turns.pop();

	}
	else goto M;
	undoMoshBGD();
}
void Game::undoMoshBGD()
{
	
	cwin.clear(); 
	drawBoard(); 
	eraseWinningStacks();
	vector<string>tmp;
	fillBoardFlags();
	if (!undo.empty())
	{
		tmp = undo.top();
		vector <string>::iterator lef;
		string tmpo; int tmpx; int tmpy;
		for (lef = tmp.begin(); lef != tmp.end(); lef += 3)
		{
			tmpo = *lef;
			lef++; tmpx = atoi((*lef).c_str());
			lef++; tmpy = atoi((*lef).c_str());
			draw(tmpo, getSize(), Point(tmpx, tmpy));
			fillWinningStacks(Point(tmpx, tmpy), tmpo);
			lef--; lef--;
		}
	}
}
void Game::undoBGD()
{
	cwin.clear();
	drawBoard(); 
	eraseWinningStacks();
	vector<string>tmp;
	fillBoardFlags();
	if (undo.size() == 1) undo.pop();
	else if (undo.size() > 1)
	{
		undo.pop(); undo.pop();
	}
	if (!undo.empty())
	{
		tmp = undo.top();
		vector <string>::iterator lef;
		string tmpo; int tmpx; int tmpy;
		for (lef = tmp.begin(); lef != tmp.end(); lef += 3)
		{
			tmpo = *lef;
			lef++; tmpx = atoi((*lef).c_str());
			lef++; tmpy = atoi((*lef).c_str());
			draw(tmpo, getSize(), Point(tmpx, tmpy));
			fillWinningStacks(Point(tmpx, tmpy), tmpo);
			lef--; lef--;

		}
	}
}
void Game::loadBGD()
{
	player.open("players.txt");
	if (player.is_open())
	{
		string input;
		int score;
		player >> numberOfPlayers;
		for (int i = 0; i < numberOfPlayers; i++)
		{
			player >> input;
			player >> score;
			players[input] = score;
		}
	}
	player.close();
	savedGame.open("last saved game.txt");
	if (savedGame.is_open())
	{
		fillBoardFlags();
		string x;
		string o;
		string u;
		int s;
		vector<string> v;
		savedGame >> s;
		setSize(s);
		//drawBoard();
		checkIfempty = true;
		if (getSize() == 3)
		{
			winningStacks = new list<string>[8];
		}
		else if (getSize() == 4)
		{
			winningStacks = new list<string>[10];
		}
		else if (getSize() == 5)
		{
			winningStacks = new list<string>[12];
		}
		savedGame >> s;
		numberOfPlayers = s;
		savedGame >> x >> o;
		p1.setChar(x);
		p2.setChar(o);
		savedGame >> x >> o;
		p1.setName(x);
		p2.setName(o);
		//savedGame >> x;
		computerFlag = (o == "Computer") ? true : false;
		savedGame >> x;
		if (x != "!")
		{
			level = atoi(x.c_str());
			savedGame >> x;
		}

		while (1)
		{
			savedGame >> x;
			if (x == "!") break;
			savedGame >> o >> u;
			v.push_back(x); v.push_back(o); v.push_back(u);
		}
		drawBoard();
		undo.push(v);
		vector<string> tmp = undo.top();
		vector <string>::iterator lef;
		string tmpo; int tmpx; int tmpy;
		for (lef = tmp.begin(); lef != tmp.end(); lef += 3)
		{
			tmpo = *lef;
			lef++; tmpx = atoi((*lef).c_str());
			lef++; tmpy = atoi((*lef).c_str());
			draw(tmpo, getSize(), Point(tmpx, tmpy));
			fillWinningStacks(Point(tmpx, tmpy), tmpo);
			lef--; lef--;
		}
		while (1)
		{
			savedGame >> x;
			if (x == "!") break;
			turns.push(x);
		}
	}
	savedGame.close();
	StartGame();
}
void Game::eraseWinningStacks()
{
	for (int i = 0; i < 12; i++)
	{
		counter[i] = "";
	}
	int length;
	if (getSize() == 3)length = 8;
	else if (getSize() == 4) length = 10;
	else if (getSize() == 5)length = 12;
	for (int i = 0; i < length; i++)
	{
		winningStacks[i].erase(winningStacks[i].begin(), winningStacks[i].end());

	}
}

void Game::fillingUndo(string chara , Point pos)
{
	vector<string> v;
	if (undo.empty())
	{
		v.push_back(chara); v.push_back(to_string(pos.get_x())); v.push_back(to_string(pos.get_y()));
		undo.push(v);
	}
	else
	{
		v = undo.top();
		v.push_back(chara); v.push_back(to_string(pos.get_x())); v.push_back(to_string(pos.get_y()));
		undo.push(v);
	}
}

void Game::fillWinningStacks(Point p, string ch)
{
	if (getSize() == 3)
	{
		
		if (p.get_x() == 0 && p.get_y() == 0 && busyPosition[0][0]) //box1
		{
			row1_3x3.push_back(ch); col1_3x3.push_back(ch); diag1_3x3.push_back(ch); busyPosition[0][0] = false; checkIfempty = true; 
			counter[0] += ch; counter[5] += ch; counter[10] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == 0 && busyPosition[0][1])// box2
		{
			row1_3x3.push_back(ch); col2_3x3.push_back(ch); busyPosition[0][1] = false; checkIfempty = true;
			counter[0] += ch; counter[6] += ch; 
		}
		else if (p.get_x() == 2 && p.get_y() == 0 && busyPosition[0][2]) //box3
		{
			row1_3x3.push_back(ch); col3_3x3.push_back(ch); diag2_3x3.push_back(ch); busyPosition[0][2] = false; checkIfempty = true; 
			counter[0] += ch; counter[7] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 0 && p.get_y() == -1 && busyPosition[1][0])//box4
		{
			row2_3x3.push_back(ch); col1_3x3.push_back(ch); busyPosition[1][0] = false; checkIfempty = true;
			counter[1] += ch; counter[5] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == -1 && busyPosition[1][1])//box5
		{
			row2_3x3.push_back(ch); col2_3x3.push_back(ch); diag1_3x3.push_back(ch); diag2_3x3.push_back(ch); busyPosition[1][1] = false; checkIfempty = true; 
			counter[1] += ch; counter[6] += ch; counter[10] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == -1 && busyPosition[1][2])//box6
		{
			row2_3x3.push_back(ch); col3_3x3.push_back(ch); busyPosition[1][2] = false; checkIfempty = true;
			counter[1] += ch; counter[7] += ch; 
		}
		else if (p.get_x() == 0 && p.get_y() == -2 && busyPosition[2][0])//box7
		{
			row3_3x3.push_back(ch); col1_3x3.push_back(ch); diag2_3x3.push_back(ch); busyPosition[2][0] = false; checkIfempty = true; 
			counter[2] += ch; counter[5] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == -2 && busyPosition[2][1])//box8
		{
			row3_3x3.push_back(ch); col2_3x3.push_back(ch); busyPosition[2][1] = false; checkIfempty = true; 
			counter[2] += ch; counter[6] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == -2 && busyPosition[2][2])//box9
		{
			row3_3x3.push_back(ch); col3_3x3.push_back(ch); diag1_3x3.push_back(ch); busyPosition[2][2] = false; checkIfempty = true;
			counter[2] += ch; counter[7] += ch; counter[10] += ch;
		}
		else if (p.get_x() == 19 && p.get_y() == 19) checkIfempty = true;
		else checkIfempty = false;


	}
	else if (getSize() == 4)
	{
		if (p.get_x() == 0 && p.get_y() == 0 && busyPosition[0][0]) //box1
		{
			row1_4x4.push_back(ch); col1_4x4.push_back(ch); diag1_4x4.push_back(ch); busyPosition[0][0] = false; checkIfempty = true;
			counter[0] += ch; counter[5] += ch; counter[10] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == 0 && busyPosition[0][1])// box2
		{
			row1_4x4.push_back(ch); col2_4x4.push_back(ch); busyPosition[0][1] = false; checkIfempty = true;
			counter[0] += ch; counter[6] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == 0 && busyPosition[0][2]) //box3
		{
			row1_4x4.push_back(ch); col3_4x4.push_back(ch); busyPosition[0][2] = false; checkIfempty = true;
			counter[0] += ch; counter[7] += ch;
		}
		else if (p.get_x() == 3 && p.get_y() == 0 && busyPosition[0][3]) //box4
		{
			row1_4x4.push_back(ch); col4_4x4.push_back(ch); diag2_4x4.push_back(ch); busyPosition[0][3] = false; checkIfempty = true;
			counter[0] += ch; counter[8] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 0 && p.get_y() == -1 && busyPosition[1][0])//box5
		{
			row2_4x4.push_back(ch); col1_4x4.push_back(ch); busyPosition[1][0] = false; checkIfempty = true;
			counter[1] += ch; counter[5] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == -1 && busyPosition[1][1])//box6
		{
			row2_4x4.push_back(ch); col2_4x4.push_back(ch); diag1_4x4.push_back(ch); busyPosition[1][1] = false; checkIfempty = true;
			counter[1] += ch; counter[6] += ch; counter[10] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == -1 && busyPosition[1][2])//box7
		{
			row2_4x4.push_back(ch); col3_4x4.push_back(ch); diag2_4x4.push_back(ch); busyPosition[1][2] = false; checkIfempty = true;
			counter[1] += ch; counter[7] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 3 && p.get_y() == -1 && busyPosition[1][3])//box8
		{
			row2_4x4.push_back(ch); col4_4x4.push_back(ch); busyPosition[1][3] = false; checkIfempty = true;
			counter[1] += ch; counter[8] += ch;
		}
		else if (p.get_x() == 0 && p.get_y() == -2 && busyPosition[2][0])//box9
		{
			row3_4x4.push_back(ch); col1_4x4.push_back(ch); busyPosition[2][0] = false; checkIfempty = true;
			counter[2] += ch; counter[5] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == -2 && busyPosition[2][1])//box10
		{
			row3_4x4.push_back(ch); col2_4x4.push_back(ch); diag2_4x4.push_back(ch); busyPosition[2][1] = false; checkIfempty = true;
			counter[2] += ch; counter[6] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == -2 && busyPosition[2][2])//box11
		{
			row3_4x4.push_back(ch); col3_4x4.push_back(ch); diag1_4x4.push_back(ch); busyPosition[2][2] = false; checkIfempty = true;
			counter[2] += ch; counter[7] += ch; counter[10] += ch;
		}
		else if (p.get_x() == 3 && p.get_y() == -2 && busyPosition[2][3]) //box12
		{
			row3_4x4.push_back(ch); col4_4x4.push_back(ch); busyPosition[2][3] = false; checkIfempty = true;
			counter[2] += ch; counter[8] += ch;
		}
		else if (p.get_x() == 0 && p.get_y() == -3 && busyPosition[3][0]) //box13
		{
			row4_4x4.push_back(ch); col1_4x4.push_back(ch); diag2_4x4.push_back(ch); busyPosition[3][0] = false; checkIfempty = true;
			counter[3] += ch; counter[5] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == -3 && busyPosition[3][1]) //box14
		{
			row4_4x4.push_back(ch); col2_4x4.push_back(ch); busyPosition[3][1] = false; checkIfempty = true;
			counter[3] += ch; counter[6] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == -3 && busyPosition[3][2]) //box15
		{
			row4_4x4.push_back(ch); col3_4x4.push_back(ch); busyPosition[3][2] = false; checkIfempty = true;
			counter[3] += ch; counter[7] += ch;
		}
		else if (p.get_x() == 3 && p.get_y() == -3 && busyPosition[3][3]) //box16
		{
			row4_4x4.push_back(ch); col4_4x4.push_back(ch); diag1_4x4.push_back(ch); busyPosition[3][3] = false; checkIfempty = true;
			counter[3] += ch; counter[8] += ch; counter[10] += ch;
		}
		else if (p.get_x() == 19 && p.get_y() == 19) checkIfempty = true;
		else checkIfempty = false;
	}
	else if (getSize() == 5)
	{
		if (p.get_x() == 0 && p.get_y() == 0 && busyPosition[0][0]) //box1
		{
			row1_5x5.push_back(ch); col1_5x5.push_back(ch); diag1_5x5.push_back(ch); busyPosition[0][0] = false; checkIfempty = true;
			counter[0] += ch; counter[5] += ch; counter[10] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == 0 && busyPosition[0][1])// box2
		{
			row1_5x5.push_back(ch); col2_5x5.push_back(ch); busyPosition[0][1] = false; checkIfempty = true;
			counter[0] += ch; counter[6] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == 0 && busyPosition[0][2]) //box3
		{
			row1_5x5.push_back(ch); col3_5x5.push_back(ch); busyPosition[0][2] = false; checkIfempty = true;
			counter[0] += ch; counter[7] += ch;
		}
		else if (p.get_x() == 3 && p.get_y() == 0 && busyPosition[0][3]) //box4
		{
			row1_5x5.push_back(ch); col4_5x5.push_back(ch); busyPosition[0][3] = false; checkIfempty = true;
			counter[0] += ch; counter[8] += ch;
		}
		else if (p.get_x() == 4 && p.get_y() == 0 && busyPosition[0][4]) //box5
		{
			row1_5x5.push_back(ch); col5_5x5.push_back(ch); diag2_5x5.push_back(ch); busyPosition[0][4] = false; checkIfempty = true;
			counter[0] += ch; counter[9] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 0 && p.get_y() == -1 && busyPosition[1][0])//box6
		{
			row2_5x5.push_back(ch); col1_5x5.push_back(ch); busyPosition[1][0] = false; checkIfempty = true;
			counter[1] += ch; counter[5] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == -1 && busyPosition[1][1])//box7
		{
			row2_5x5.push_back(ch); col2_5x5.push_back(ch); diag1_5x5.push_back(ch); busyPosition[1][1] = false; checkIfempty = true;
			counter[1] += ch; counter[6] += ch; counter[10] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == -1 && busyPosition[1][2])//box8
		{
			row2_5x5.push_back(ch); col3_5x5.push_back(ch); busyPosition[1][2] = false; checkIfempty = true;
			counter[1] += ch; counter[7] += ch;
		}
		else if (p.get_x() == 3 && p.get_y() == -1 && busyPosition[1][3]) //box9
		{
			row2_5x5.push_back(ch); col4_5x5.push_back(ch); diag2_5x5.push_back(ch); busyPosition[1][3] = false; checkIfempty = true;
			counter[1] += ch; counter[8] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 4 && p.get_y() == -1 && busyPosition[1][4]) //box10
		{
			row2_5x5.push_back(ch); col5_5x5.push_back(ch); busyPosition[1][4] = false; checkIfempty = true;
			counter[1] += ch; counter[9] += ch;
		}
		else if (p.get_x() == 0 && p.get_y() == -2 && busyPosition[2][0])//box11
		{
			row3_5x5.push_back(ch); col1_5x5.push_back(ch); busyPosition[2][0] = false; checkIfempty = true;
			counter[2] += ch; counter[5] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == -2 && busyPosition[2][1])//box12
		{
			row3_5x5.push_back(ch); col2_5x5.push_back(ch); busyPosition[2][1] = false; checkIfempty = true;
			counter[2] += ch; counter[6] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == -2 && busyPosition[2][2])//box13
		{
			row3_5x5.push_back(ch); col3_5x5.push_back(ch); diag1_5x5.push_back(ch); diag2_5x5.push_back(ch); busyPosition[2][2] = false; checkIfempty = true;
			counter[2] += ch; counter[7] += ch; counter[10] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 3 && p.get_y() == -2 && busyPosition[2][3]) //box14
		{
			row3_5x5.push_back(ch); col4_5x5.push_back(ch); busyPosition[2][3] = false; checkIfempty = true;
			counter[2] += ch; counter[8] += ch;
		}
		else if (p.get_x() == 4 && p.get_y() == -2 && busyPosition[2][4]) //box15
		{
			row3_5x5.push_back(ch); col5_5x5.push_back(ch); busyPosition[2][4] = false; checkIfempty = true;
			counter[2] += ch; counter[9] += ch;
		}
		else if (p.get_x() == 0 && p.get_y() == -3 && busyPosition[3][0]) //box16
		{
			row4_5x5.push_back(ch); col1_5x5.push_back(ch); busyPosition[3][0] = false; checkIfempty = true;
			counter[3] += ch; counter[5] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == -3 && busyPosition[3][1]) //box17
		{
			row4_5x5.push_back(ch); col2_5x5.push_back(ch); diag2_5x5.push_back(ch); busyPosition[3][1] = false; checkIfempty = true;
			counter[3] += ch; counter[6] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == -3 && busyPosition[3][2]) //box18
		{
			row4_5x5.push_back(ch); col3_5x5.push_back(ch); busyPosition[3][2] = false; checkIfempty = true;
			counter[3] += ch; counter[7] += ch;
		}
		else if (p.get_x() == 3 && p.get_y() == -3 && busyPosition[3][3]) //box19
		{
			row4_5x5.push_back(ch); col4_5x5.push_back(ch); diag1_5x5.push_back(ch); busyPosition[3][3] = false; checkIfempty = true;
			counter[3] += ch; counter[8] += ch;
		}
		else if (p.get_x() == 4 && p.get_y() == -3 && busyPosition[3][4]) //box20
		{
			row4_5x5.push_back(ch); col5_5x5.push_back(ch); busyPosition[3][4] = false; checkIfempty = true;
			counter[3] += ch; counter[9] += ch;
		}
		else if (p.get_x() == 0 && p.get_y() == -4 && busyPosition[4][0]) //box21
		{
			row5_5x5.push_back(ch); col1_5x5.push_back(ch); diag2_5x5.push_back(ch); busyPosition[4][0] = false; checkIfempty = true;
			counter[4] += ch; counter[5] += ch; counter[11] += ch;
		}
		else if (p.get_x() == 1 && p.get_y() == -4 && busyPosition[4][1]) //box22
		{
			row5_5x5.push_back(ch); col2_5x5.push_back(ch); busyPosition[4][1] = false; checkIfempty = true;
			counter[4] += ch; counter[6] += ch;
		}
		else if (p.get_x() == 2 && p.get_y() == -4 && busyPosition[4][2]) //box23
		{
			row5_5x5.push_back(ch); col3_5x5.push_back(ch); busyPosition[4][2] = false; checkIfempty = true;
			counter[4] += ch; counter[7] += ch;
		}
		else if (p.get_x() == 3 && p.get_y() == -4 && busyPosition[4][3]) //box24
		{
			row5_5x5.push_back(ch); col4_5x5.push_back(ch); busyPosition[4][3] = false; checkIfempty = true;
			counter[4] += ch; counter[8] += ch;
		}
		else if (p.get_x() == 4 && p.get_y() == -4 && busyPosition[4][4]) //box25
		{
			row5_5x5.push_back(ch); col5_5x5.push_back(ch); diag1_5x5.push_back(ch); busyPosition[4][4] = false; checkIfempty = true;
			counter[4] += ch; counter[9] += ch; counter[10] += ch;
		}
		else if (p.get_x() == 19 && p.get_y() == 19) checkIfempty = true;
		else checkIfempty = false;
	}
}

void Game::draw(string ch, int size, Point center)
{
	Line l1, l2;
	Circle c;
	//double yy = 0;
	double sizeFactor;
	double x = center.get_x();
	double y = center.get_y();
	if (size == 3)
	{
		sizeFactor = 5;
		/*if (ch == "X")
		{
			for (double xx = -7; xx <= -3; xx += 0.00005)
			{
				yy = -xx;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
			for (double xx = -3; xx >= -7; xx -= 0.00005)
			{
				yy = xx + 10;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
		}
		else if (ch == "O")
		{
			for (double xx = -5 + 1.66666666666666; xx >= -5 - 1.66666666666666; xx -= 0.00005)
			{
				yy = sqrt(pow(1.66666666666666,2) - pow(xx+5, 2)) + 5;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
			for (double xx = -5 - 1.66666666666666; xx <= -5 + 1.66666666666666; xx += 0.00005)
			{
				yy = -sqrt(pow(1.66666666666666, 2) - pow(xx+5, 2)) + 5;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
		}*/
		l1 = Line(Point(-7, 7), Point(-3, 3));
		l2 = Line(Point(-3, 7), Point(-7, 3));
		c = Circle(Point(-5, 5), 1.666666666666667);
	}
	else if (size == 4)
	{
		sizeFactor = 4;
		/*if (ch == "X")
		{
			for (double xx = -7.5; xx <= -4.5; xx += 0.00005)
			{
				yy = -xx;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
			for (double xx = -4.5; xx >= -7.5; xx -= 0.00005)
			{
				yy = xx + 12;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
		}
		else if (ch == "O")
		{
			for (double xx = -6 + 1.333333333333333; xx >= -6 - 1.333333333333333; xx -= 0.00005)
			{
				yy = sqrt(pow(1.333333333333333, 2) - pow(xx + 6, 2)) + 6;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
			for (double xx = -6 - 1.333333333333333; xx <= -6 + 1.333333333333333; xx += 0.00005)
			{
				yy = -sqrt(pow(1.333333333333333, 2) - pow(xx + 6, 2)) + 6;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
		}*/
		l1 = Line(Point(-7.5, 7.5), Point(-4.5, 4.5));
		l2 = Line(Point(-4.5, 7.5), Point(-7.5, 4.5));
		c = Circle(Point(-6, 6), 1.333333333333333);
	}
	else if (size == 5)
	{
		sizeFactor = 3;
		/*if (ch == "X")
		{
			for (double xx = -7; xx <= -5; xx += 0.00005)
			{
				yy = -xx;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
			for (double xx = -5; xx >= -7; xx -= 0.00005)
			{
				yy = xx + 12;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
		}
		else if (ch == "O")
		{
			for (double xx = -6 + 1; xx >= -6 - 1; xx -= 0.00005)
			{
				yy = sqrt(pow(1, 2) - pow(xx + 6, 2)) + 6;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
			for (double xx = -6 - 1; xx <= -6 + 1; xx += 0.00005)
			{
				yy = -sqrt(pow(1, 2) - pow(xx + 6, 2)) + 6;
				Point p(xx, yy);
				p.move(sizeFactor * x, sizeFactor * y);
				cwin << p;
			}
		}*/
		l1 = Line(Point(-7, 7), Point(-5, 5));
		l2 = Line(Point(-5, 7), Point(-7, 5));
		c = Circle(Point(-6, 6), 1);
	}
	l1.move(sizeFactor * x, sizeFactor * y);
	l2.move(sizeFactor * x, sizeFactor * y);
	c.move(sizeFactor * x, sizeFactor * y);
	if (ch == "X") cwin << l1 << l2;
	else if (ch == "O") cwin << c;
}

void Game::searchForwinner()
{
	int size = getSize();
	int length;
	int count = 0;
	string found;
	if (size == 3) length = 8;
	else if (size == 4) length = 10;
	else if (size == 5) length = 12;
	list<string>::iterator character;
	for (int i = 0; i < length; i++)
	{
		if (!winningStacks[i].empty())
		{
			found = winningStacks[i].front();
			for (character = ++(winningStacks[i].begin()); character != winningStacks[i].end(); character++)
			{
				if (*character == found) count++;
			}
			if (count == size - 1)
			{
				if (p1.getChar() == found) player1win = true;
				else if (p2.getChar() == found) player2win = true;
				return;
			}
			count = 0;
		}
	}
	for (int i = 0; i < length; i++)
	{
		if (winningStacks[i].size() == size) 
			count++;
	}
	if (count == length) endGameFlag = true;
}
void Game::fillBoardFlags()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			busyPosition[i][j] = true;
		}
	}
}
void Game::storeAccounts()
{
	player.open("players.txt", ios::out | ios::trunc);
	if (player.is_open())
	{
		player << numberOfPlayers << endl;
		for (map<string, int>::iterator i = players.begin(); i != players.end(); i++)
		{
			player << i->first << " ";
			player << i->second << endl;
		}
	}
	player.close();
}

void Game::winning_style()
{
	double x, y;
	for (x = 8; x >= -8; x -= 0.002)
	{
		y = sqrt(64 - pow(x, 2));
		Message m(Point(x, y), "====");
		cwin << m;
	}
	for (x = -8; x <= 8; x += 0.002)
	{
		y = -sqrt(64 - pow(x, 2));
		Message m(Point(x, y), "====");
		cwin << m;
	}
}

void Game::last_decision()
{
	Line l555(Point(19, -19), Point(14, -19)); Line L666(Point(19, -19), Point(19, -16)); Line L777(Point(19, -16), Point(14, -16));
	Line l666(Point(14, -19), Point(14, -16));
	Message MM(Point(15.6, -17), "EXIT");
	cwin << MM << L666 << L777 << l666 << l555;
	Point clicka = cwin.get_mouse("");
	if (clicka.get_x() < 19 && clicka.get_x() > 14 && clicka.get_y() < -16 && clicka.get_y() > -19)
	{
		exit(0);
	}
}