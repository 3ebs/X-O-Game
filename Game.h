#include "Player.h"

using namespace std;

#define row1_3x3	winningStacks[0]
#define row2_3x3	winningStacks[1]
#define row3_3x3	winningStacks[2]
#define col1_3x3	winningStacks[3]
#define col2_3x3	winningStacks[4]
#define col3_3x3	winningStacks[5]
#define diag1_3x3	winningStacks[6]
#define diag2_3x3	winningStacks[7]
#define row1_4x4	winningStacks[0]
#define row2_4x4	winningStacks[1]
#define row3_4x4	winningStacks[2]
#define row4_4x4	winningStacks[3]
#define col1_4x4	winningStacks[4]
#define col2_4x4	winningStacks[5]
#define col3_4x4	winningStacks[6]
#define col4_4x4	winningStacks[7]
#define diag1_4x4	winningStacks[8]
#define diag2_4x4	winningStacks[9]
#define row1_5x5	winningStacks[0]
#define row2_5x5	winningStacks[1]
#define row3_5x5	winningStacks[2]
#define row4_5x5	winningStacks[3]
#define row5_5x5	winningStacks[4]
#define col1_5x5	winningStacks[5]
#define col2_5x5	winningStacks[6]
#define col3_5x5	winningStacks[7]
#define col4_5x5	winningStacks[8]
#define col5_5x5	winningStacks[9]
#define diag1_5x5	winningStacks[10]
#define diag2_5x5	winningStacks[11]

class Game 
{
private: 
	int intSize;
	Player p1;
	Player p2;
	bool undoFlag;
	bool saveFlag;
	bool endGameFlag;
	bool player1win;
	bool player2win;
	int numberOfPlayers;
	list<string> * winningStacks; 
	string counter[12];
	stack <vector<string>> undo;
	stack <string> turns;
	map <string, int> players;
	bool busyPosition[5][5];
	bool checkIfempty;
	bool playerFlag;
	bool computerFlag;
	int level;
	fstream player;
	fstream savedGame;
	void setSize(int size);
	int getSize();
	void storeAccounts();
	void undoMoshBGD();
	void fillBoardFlags();
	void draw(string ch, int size, Point center);
	void mode();
	void winning_style();
	void StartGame();
	void last_decision();
	void loadBGD();
	void managePlayers(bool x);
	void drawBoard();
	void turn();
	void fillWinningStacks(Point p, string x);
	void stacking(int size, bool x);
	void searchForwinner();
	void fillingUndo(string chara, Point pos);
	void undoBGD();
	void saveBGD();
	void eraseWinningStacks();
	
public: 
	Game();
	void playGame();
};