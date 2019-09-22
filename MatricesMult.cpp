//** Thong Nguyen
//** Matrices Multiplication

#include <iostream>
#include <vector>
using namespace std;

//Function Prototypes
void displayMatrix(vector<vector<int>>);
vector<vector<int>> multiplyMatrices(const vector<vector<int>> &mat1, const vector<vector<int>> &mat2);

int main() {

	cout << "**Thong Nguyen\n**Matrices Multiplication\n**Output\n" << endl;

	vector<vector<int>> matr1(2, vector<int>(3, 0));
	matr1[0][0] = 1; matr1[0][1] = 2; matr1[0][2] = 3;
	matr1[1][0] = 4; matr1[1][1] = 5; matr1[1][2] = 6;
	cout << "Matrix 1: \n";
	displayMatrix(matr1);
	cout << endl;

	vector<vector<int>> matr2(3, vector<int>(2, 0));
	matr2[0][0] = 1; matr2[0][1] = 2;
	matr2[1][0] = 3; matr2[1][1] = 4;
	matr2[2][0] = 5; matr2[2][1] = 6;
	cout << "Matrix 2: \n";
	displayMatrix(matr2);
	cout << endl;

	cout << "Multiplication result: \n";
	vector<vector<int>> result = multiplyMatrices(matr1, matr2);
	if (!result.empty()) displayMatrix(result);
	cout << endl;

	return 0;
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>> &mat1, const vector<vector<int>> &mat2) {
	int width_1 = mat1[0].size();
	int height_1 = mat1.size();
	int width_2 = mat2[0].size();
	int height_2 = mat2.size();
	vector<vector<int>> result;

	//If # of columns in the 1st matrix is not the same as # of rows in 2nd matrix
	//Return empty vector
	if (width_1 != height_2) 
		return result;

	result.resize(height_1);
	for (unsigned int i = 0; i < result.size(); i++) {
		result[i].resize(width_2);
		for (unsigned int j = 0; j < result[i].size(); j++) {
			result[i][j] = 0;
			for (int k = 0; k < width_1; k++)
				result[i][j] += (mat1[i][k] * mat2[k][j]);
		}
	}
	
	return result;
}

void displayMatrix(vector<vector<int>> matr) {
	for (unsigned int i = 0; i < matr.size(); i++) {
		for (unsigned int j = 0; j < matr[i].size(); j++) {
			cout << matr[i][j] << " ";
		}
		cout << endl;
	}
}