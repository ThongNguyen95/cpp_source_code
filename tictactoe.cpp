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
int turn_count = 0;
int depth = 0;

int main() {
	//vector<string> board = { "X", "O", "X", "O", "-", "X", "O", "-", "-", "-", "-", "-", "-", "-", "-", "-" };
	vector<string> board(16, "-");
	bool end = false;
	int turn = 0;
	turn_count = 0;
	int move;
	display_board(board);
	while (!end) {
		if (turn == 0) {
			cout << "Turn: X (Player)" << endl;
			cout << "Enter position (0-15): ";
			cin >> move;
			if (check_input(board, move)) {
				turn_count++;
				board[move] = "X";
				turn = 1;
			}
		} else {
			cout << "Turn: O (Computer): " << turn_count << endl;
			depth = 0;
			cout << "Calculating move..." << endl;
			move = minimax(board);
			cout << "Enter position (0-15): ";
			cout << move << endl;
			if (check_input(board, move)) {
				turn_count++;
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
	for (int i = 0; i <= 3; i++) {
		cout << "| ";
		for (int j = 0; j <= 3; j++) {
			int temp = i * 4 + j;
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
	for (int i = 0; i <= 15; i++) {
		if (board[i] == "-") {
			count++;
			i = 16;
		}
	}
	if (count == 0) return true;

	for (int i = 0; i <= 3; i++) {
		string a = board[4 * i + 0];
		string b = board[4 * i + 1];
		string c = board[4 * i + 2];
		string d = board[4 * i + 3];
		if ((a == b && b == c && c == d) && (a == "X" || a == "O")) {
			return true;
		}
		a = board[4 * 0 + i];
		b = board[4 * 1 + i];
		c = board[4 * 2 + i];
		d = board[4 * 3 + i];
		if ((a == b && b == c && c == d) && (a == "X" || a == "O")) {
			return true;
		}
	}

	string a = board[0];
	string b = board[5];
	string c = board[10];
	string d = board[15];
	if ((a == b && b == c && c == d) && (a == "X" || a == "O")) {
		return true;
	}

	a = board[3];
	b = board[6];
	c = board[9];
	d = board[12];
	if ((a == b && b == c && c == d) && (a == "X" || a == "O")) {
		return true;
	}

	return false;
}

int utility(const vector<string>& board) {
	for (int i = 0; i <= 3; i++) {
		string a = board[4 * i + 0];
		string b = board[4 * i + 1];
		string c = board[4 * i + 2];
		string d = board[4 * i + 3];
		if (a == b && b == c && c == d) {
			if (a == "X") return 1;
			else if (a == "O") return -1;
		}
		a = board[4 * 0 + i];
		b = board[4 * 1 + i];
		c = board[4 * 2 + i];
		d = board[4 * 3 + i];
		if (a == b && b == c && c == d) {
			if (a == "X") return 1;
			else if (a == "O") return -1;
		}
	}

	string a = board[0];
	string b = board[5];
	string c = board[10];
	string d = board[15];
	if (a == b && b == c && c == d) {
		if (a == "X") return 1;
		else if (a == "O") return -1;
	}

	a = board[3];
	b = board[6];
	c = board[9];
	d = board[12];
	if (a == b && b == c && c == d) {
		if (a == "X") return 1;
		else if (a == "O") return -1;
	}

	return 0;
}

int minimax(vector<string>& board) {
	int score = 2;
	int move = -1;
	for (int i = 0; i <= 15; i++) {
		if (board[i] == "-") {
			cout << "minimax: " << i << endl;
			board[i] = "O";
			int temp = max_val(board);
			if (temp < score) {
				score = temp;
				move = i;
			}
			board[i] = "-";
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
	if (depth > 2 && turn_count < 5) return 0;
	if (depth > 3 && turn_count < 8) return 0;
	for (int i = 0; i <= 15; i++) {
		if (board[i] == "-") {
			board[i] = "X";
			depth++;
			int temp = min_val(board);
			depth--;
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
	if (depth > 2 && turn_count < 5) return 0;
	if (depth > 3 && turn_count < 8) return 0;
	for (int i = 0; i <= 15; i++) {
		if (board[i] == "-") {
			board[i] = "O";
			depth++;
			int temp = max_val(board);
			depth--;
			board[i] = "-";
			if (temp == -1) return temp;
			if (temp < score) {
				score = temp;
			}
		}
	}
	return score;
}