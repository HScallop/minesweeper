#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

enum gamestate{noresult, win, lose};
void display(vector<vector<int> >&, vector<vector<int> >&);
gamestate step(vector<vector<int> >&, vector<vector<int> >&, int, int);
void init(vector<vector<int> >&, vector<vector<int> >&, int);


int main() {
	
	int n = 0;
	int mine = 0;
	int row = 0;
	int column = 0;
	int blank = 0;
	gamestate state = noresult;


	do {
		//let the user enter board length
		cout << "Please enter the mineboard length.\n";
		cin >> n;
		//make sure the board length entered is resonable, if not let he enter again
		if (n <= 1) {
			cout << "The length is unvalid please enter again.\n";
		}
	} while (n <= 1);


	do {
		//let the user enter mine numbers
		cout << "Please enter mine numbers.\n";
		cin >> mine;
		//make sure the mine number entered is resonable, if not, let he enter again
		if (mine >= n*n || mine < 1) {
			cout << "The mine number is unvalid please enter again.\n";
		}
	} while (mine >= n*n || mine < 1);

	vector<vector<int> > board(n + 2, vector<int>(n + 2));
	vector<vector<int> > record(n + 2, vector<int>(n + 2));
	
	init(board, record, mine);


	while (state == noresult) {

		//display
		display(board, record);



		//tell the user to take your step
		do {
			cout << "Please take your step.\n";
			cout << "Please enter row.\n";
			cin >> row;
			cout << "Please enter column.\n";
			cin >> column;
			if (row > board.size() - 2 || row<1 || column>board.size() - 2 || column < 1) {
				cout << "Unvalid move, please take another step.";
			}
			//check if the step is valid
		} while (row > board.size() - 2 || row<1 || column>board.size() - 2 || column < 1);


		state = step(board, record, row, column);
		
		//check if the winning condition holds
		blank = 0;
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board.size(); j++) {
				if (record[i][j] == 0 && board[i][j] != -1) {
					blank++;
				}
			}
		}

		if (blank == 0) {
			state = win;
		}


	}


	//show the result
	if (state == win) {
		cout << "You win!\n";
	}
	else {
		cout << "You lose :(\n";
	}


	//show the entire board with every information
	cout << "The inside view of the game board:\n";
	cout << "  ";
	for (int i = 0; i < board.size(); i++) {
		if (i >= 1 && i <= board.size() - 2) {
			if (i < 10) {
				cout << " " << i;
			}
			else {
				if (i == 10) {
					cout << " ";
				}
				cout << i;
			}
		}
		else {
			cout << "  ";
		}
	}
	cout << "\n";
	for (int i = 0; i < n + 2; i++) {
		if (i >= 1 && i <= board.size() - 2) {
			if (i < 10) {
				cout << " " << i;
			}
			else {
				cout << i;
			}
		}
		else {
			cout << "  ";
		}
		for (int j = 0; j < n + 2; j++) {
			if (board[i][j] == -6) {
				cout << " *";
			}
			else if (board[i][j] == -1) {
				cout << " $";
			}
			else {
				cout << " " << board[i][j];
			}
		}
		cout << "\n";
	}
	
	return 0;
}


//initialization
void init(vector<vector<int> >&board, vector<vector<int> >&record, int mine) {
	srand(time(0));

	//initialize the board
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
			board[i][j] = 0;
		}
	}

	//create wall
	for (int i = 0; i < board.size(); i++) {
		board[0][i] = -6;
		board[i][0] = -6;
		board[board.size() - 1][i] = -6;
		board[i][board.size() - 1] = -6;
	}


	//initialize stepped block record
	for (int i = 0; i < record.size();i++) {
		for (int j = 0; j < record.size(); j++) {
			record[i][j] = 0;
		}
	}
	for (int i = 0; i < record.size(); i++) {
		record[0][i] = 1;
		record[i][0] = 1;
		record[record.size() - 1][i] = 1;
		record[i][record.size() - 1] = 1;
	}

	//set the bomb
	int minecount = 0;
	int temp1;
	int temp2;
	while (minecount != mine) {

		//set bombs randomly
		temp1 = rand() % (board.size() - 2) + 1;
		temp2 = rand() % (board.size() - 2) + 1;
		board[temp1][temp2] = -1;

		//check how many bombs is in mine board(run through the whole board)
		minecount = 0;
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board.size(); j++) {
				if (board[i][j] == -1) {
					minecount++;
				}
			}
		}

	}


	//setup the numbers informations on the board
	for (int i = 1; i < board.size()-1; i++) {
		for (int j = 1; j < board.size()-1; j++) {
			minecount = 0;
			if (board[i][j] != -1) {
				for (int row = i - 1; row <= i + 1; row++) {
					for (int column = j - 1; column <= j + 1; column++) {
						if (board[row][column] == -1) {
							minecount++;
						}
					}
				}
				board[i][j] = minecount;
			}
		}
	}


	return;
}


gamestate step(vector<vector<int> >&board, vector<vector<int> >&record, int row, int column) {
	//check if the block was stepped
	if (record[row][column] == 1) {
		return noresult;
	}

	 //check if the user step on the wall
	if (board[row][column] == -6) {
		return noresult;
	}

	//step on the bomb
	if (board[row][column] == -1) {
		record[row][column] = 1;
		return lose;
	}
	
	//step on a place where has no bombs near
	if (board[row][column] == 0) {
		record[row][column] = 1;
		step(board, record, row + 1, column);
		step(board, record, row + 1, column + 1);
		step(board, record, row + 1, column - 1);
		step(board, record, row, column - 1);
		step(board, record, row, column + 1);
		step(board, record, row - 1, column);
		step(board, record, row - 1, column + 1);
		step(board, record, row - 1, column - 1);
		return noresult;
	}

	//otherwise
	else {
		record[row][column] = 1;
		return noresult;
	}
	
}


//display the board
void display(vector<vector<int> >&board, vector<vector<int> >&record) {
	cout << "  ";
	for (int i = 0; i < board.size(); i++) {
		if (i >= 1 && i <= board.size() - 2) {
			if (i < 10) {
				cout << " " << i;
			}
			else {
				if (i == 10) {
					cout << " ";
				}
				cout << i;
			}
		}
		else {
			cout << "  ";
		}
	}

	cout << "\n";

	for (int i = 0; i < board.size(); i++) {
		if (i >= 1 && i <= board.size() - 2) {
			if (i < 10) {
				cout << " " << i;
			}
			else {
				cout << i;
			}
		}
		else {
			cout << "  ";
		}
		for (int j = 0; j < board.size(); j++) {
			if (board[i][j] == -6) {
				cout << " *";
			}
			else if (record[i][j] == 1) {
				cout << " " << board[i][j];
			}
			else if (record[i][j] == 0) {
				cout << "  ";
			}

		}
		cout << "\n";

	}
}
