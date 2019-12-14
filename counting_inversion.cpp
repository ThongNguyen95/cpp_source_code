/**Thong Nguyen - Counting Inversion**/
#include<iostream>
#include<vector>
using namespace std;

//Function Prototypes
int countInversion(vector<int>, int, int);
int mergeInversion(vector<int>, int, int, int);

int main() {
	vector<int> arr = { 2, 6, 1, 5, 4, 3 };
	cout << "array: [ ";
	for (int val : arr) {
		cout << val << " ";
	}
	cout << "]" << endl;
	cout << "Inversion count: " << countInversion(arr, 0, arr.size()-1) << endl;
	return 0;
}

int countInversion(vector<int> arr, int first, int last) {
	if (first == last)	//list only has 1 element
		return 0;
	int invCount = 0;
	int mid = (first + last) / 2;
	invCount += countInversion(arr, first, mid);	//Work with the first half
	invCount += countInversion(arr, mid + 1, last);	//Work with the second half
	invCount += mergeInversion(arr, first, mid, last);	// count and merging

	return invCount;
}

int mergeInversion(vector<int> arr, int first, int mid, int last) {
	//Compare each element in the first half with each element in the second half
	int invCount = 0;
	for (int i = first; i <= mid; i++) {
		for (int j = mid + 1; j <= last; j++) {
			if (arr[i] > arr[j])
				invCount++;
		}
	}
	return invCount;
}