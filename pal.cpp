///** Thong Nguyen
///** Analysis of Algorithm Homework
///** Palindrome

#include <iostream>
using namespace std;

bool palindrome(int);

int main()
{
	int valArray[] = { 0, 1234554321, 123454321, 1221, 1234, 7676,
		-121, -456 };
	cout << "**Thong Nguyen**\n" << endl;
	cout << "Palindrome?\n" << endl;
	for (int val : valArray)
		cout << val << " : " << boolalpha << palindrome(val) << endl;

	return 0;
}

bool palindrome(int n) {
	if (n < 0) n = -n;	//calculate absolute value
	if (n < 10)
		return true;
	else {
		int right_most = n % 10;	//extract the right_most digit
		n = n / 10;
		int left_most = n;	//extract the left_most digit
		int mod_val = 1;
		while (left_most >= 10) {
			left_most = left_most / 10;
			mod_val *= 10;
		}
		n = n % mod_val;
		if (left_most != right_most) return false;	//Compare the left-most and right-most digits 
		else return palindrome(n);
	}
}