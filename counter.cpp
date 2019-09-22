///** Thong Nguyen
///** Analysis of Algorithm Homework
///** Counter

#include <iostream>
using namespace std;

void counter1(int num);
void counter2(int num);

int main() {
	int vals[] = { 3, 4, 5, 7 };

	for (int num : vals) {
		cout << "num: " << num << endl;
		counter1(num);
		cout << endl;
		counter2(num);
		cout << endl << endl;
	}
	return 0;
}

void counter1(int num) {
	if (num > 0) {
		counter1(num - 1);
		cout << num << ", ";
	}
}

void counter2(int num) {
	if (num > 0) {
		cout << num << ", ";
		counter2(num - 1);
	}
}