#pragma once

#include <iostream>
#include <set>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <Windows.h>

using namespace std;

class Fields
{
public:
	char tField[12][12] = {};
	int trows = 12, tcols = 12, tmines = 25;
	char uField[12][12] = {};
	int urows = 12, ucols = 12;
	int user_row = 0;
	int user_col = 0;
	int count = 0;
	vector <pair<int, int>> FlagCoords;
	vector <pair<int, int>> BoxCoords;


	void GenField();
	void GenMines();
	int GenNeighbours(int rows, int cols);
	bool CheckIfInside(int row, int col);
	void FlagBox();
	void UnFlagBox();
	void FieldPrint();
	void OpenBox();
	bool EndGame();

};


class ExampleGame : public Fields
{
public:
	ExampleGame();
	void GameLoop();

protected:
	void track_key(const int key);
	void untrack_key(const int key);
private:
	virtual void on_button_press(const int button);
	void uppdateInput();
	set<int> m_PressedKeys;
	set<int> m_TrackedKeys;
};
