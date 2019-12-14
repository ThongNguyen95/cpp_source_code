#include<iostream>
#include<vector>
using namespace std;
//Function Prototypes
void display_board(const vector<string>&);
bool check_input(const vector<string>& board, int move);
int minimax(vector<string>&);
int min_val(vector<string>&);
int max_val(vector<string>&);
int utility(const vector<string>& board);
bool terminal_test(const vector<string>& board);

int main() {
	vector<string> board(9, "-");
	bool end = false;
	int turn = 0;
	int move;
	display_board(board);
	while (!end) {
		if (turn == 0) {
			cout << "Turn: X (Player)" << endl;
			cout << "Enter position (0-8): ";
			cin >> move;
			if (check_input(board, move)) {
				board[move] = "X";
				turn = 1;
			}
		}
		else {
			cout << "Turn: X (Player)" << endl;
			cout << "Enter position (0-8): ";
			move = minimax(board);
			cout << move << endl;
			if (check_input(board, move)) {
				board[move] = "O";
				turn = 0;
			}
		}
		cout << endl << endl << endl;
		display_board(board);
		end = terminal_test(board);
	}
	cout << "Game Ended" << endl;
	return 0;
}

void display_board(const vector<string>& board) {
	cout << "-----------------\n";
	for (int i = 0; i <= 2; i++) {
		cout << "| ";
		for (int j = 0; j <= 2; j++) {
			int temp = i * 3 + j;
			cout << board[temp] << " | ";
		}
		cout << "\n-----------------\n";
	}
}

bool check_input(const vector<string>& board, int move) {
	if (board[move] == "-") return true;
	cout << "Retry. Invalid Move" << endl;
	return false;
}

bool terminal_test(const vector<string>& board) {
	int count = 0;
	for (int i = 0; i <= 8; i++) {
		if (board[i] == "-") {
			count++;
			i = 9;
		}
	}
	if (count == 0) return true;

	for (int i = 0; i <= 2; i++) {
		string a = board[3 * i + 0];
		string b = board[3 * i + 1];
		string c = board[3 * i + 2];
		if ((a == b && b == c) && (a == "X" || a == "O")) {
			return true;
		}
		a = board[3 * 0 + i];
		b = board[3 * 1 + i];
		c = board[3 * 2 + i];
		if ((a == b && b == c) && (a == "X" || a == "O")) {
			return true;
		}
	}

	string a = board[0];
	string b = board[4];
	string c = board[8];
	if ((a == b && b == c) && (a == "X" || a == "O")) {
		return true;
	}

	a = board[2];
	b = board[4];
	c = board[6];
	if ((a == b && b == c) && (a == "X" || a == "O")) {
		return true;
	}

	return false;
}

int utility(const vector<string>& board) {
	for (int i = 0; i <= 2; i++) {
		string a = board[3 * i + 0];
		string b = board[3 * i + 1];
		string c = board[3 * i + 2];
		if (a == b && b == c) {
			if (a == "X") return 1;
			else if (a == "O") return -1;
		}
		a = board[3 * 0 + i];
		b = board[3 * 1 + i];
		c = board[3 * 2 + i];
		if (a == b && b == c) {
			if (a == "X") return 1;
			else if (a == "O") return -1;
		}
	}

	string a = board[0];
	string b = board[4];
	string c = board[8];
	if (a == b && b == c) {
		if (a == "X") return 1;
		else if (a == "O") return -1;
	}

	a = board[2];
	b = board[4];
	c = board[6];
	if (a == b && b == c) {
		if (a == "X") return 1;
		else if (a == "O") return -1;
	}

	return 0;
}

int minimax(vector<string>& board) {
	int score = 2;
	int move = -1;
	for (int i = 0; i <= 8; i++) {
		if (board[i] == "-") {
			cout << "minimax: " << i << endl;
			board[i] = "O";
			int temp = max_val(board);
			board[i] = "-";
			if (temp < score) {
				score = temp;
				move = i;
			}
			if (score == -1) return move;
		}
	}
	return move;
}

int max_val(vector<string>& board) {
	if (terminal_test(board)) {
		return utility(board);
	}
	int score = -2;
	for (int i = 0; i <= 8; i++) {
		if (board[i] == "-") {
			board[i] = "X";
			int temp = min_val(board);
			board[i] = "-";
			if (temp == 1) return temp;
			if (temp > score) {
				score = temp;
			}
		}
	}
	return score;
}
int min_val(vector<string>& board) {
	if (terminal_test(board)) {
		return utility(board);
	}
	int score = 2;
	for (int i = 0; i <= 8; i++) {
		if (board[i] == "-") {
			board[i] = "O";
			int temp = max_val(board);
			board[i] = "-";
			if (temp == -1) return temp;
			if (temp < score) {
				score = temp;
			}
		}
	}
	return score;
}
