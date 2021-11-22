#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "ExampleGame.h"

using namespace std;

int main() {
	cout << "Welcome to the Minesweeper!" << endl;
	cout << "Press ARROW KEYS to navigate through the field" << endl;
	cout << "Press the F key to flag current cell" << endl;
	cout << "Press the D key to unflag current cell" << endl;
	cout << "Press the SPACE BAR to open the cell" << endl;
	cout << "Have a nice game!)" << endl << endl;
	ExampleGame play;
	return 0;
}
