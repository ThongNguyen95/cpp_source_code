#include <iostream>
#include <array>
#include <time.h>
#include <algorithm>
using namespace std;

//Function Prototypes
int getSeed(int);

class CostTable {
	int cities[9][9];

public:
	CostTable() {
		cities[1][2] = cities[2][1] = 1;
		cities[1][3] = cities[3][1] = 10;
		cities[1][4] = cities[4][1] = 2;
		cities[1][5] = cities[5][1] = 17;
		cities[1][6] = cities[6][1] = 13;
		cities[1][7] = cities[7][1] = 19;
		cities[1][8] = cities[8][1] = 11;
		cities[2][3] = cities[3][2] = 12;
		cities[2][4] = cities[4][2] = 9;
		cities[2][5] = cities[5][2] = 4;
		cities[2][6] = cities[6][2] = 2;
		cities[2][7] = cities[7][2] = 7;
		cities[2][8] = cities[8][2] = 19;
		cities[3][4] = cities[4][3] = 4;
		cities[3][5] = cities[5][3] = 18;
		cities[3][6] = cities[6][3] = 20;
		cities[3][7] = cities[7][3] = 1;
		cities[3][8] = cities[8][3] = 4;
		cities[4][5] = cities[5][4] = 5;
		cities[4][6] = cities[6][4] = 3;
		cities[4][7] = cities[7][4] = 11;
		cities[4][8] = cities[8][4] = 14;
		cities[5][6] = cities[6][5] = 11;
		cities[5][7] = cities[7][5] = 5;
		cities[5][8] = cities[8][5] = 8;
		cities[6][7] = cities[7][6] = 18;
		cities[6][8] = cities[8][6] = 6;
		cities[7][8] = cities[8][7] = 20;
	}

	int getCost(int cityA, int cityB) const {
		return cities[cityA][cityB];
	}

};



class Path {
	array<int, 8> sol = { 1,2,3,4,5,6,7,8 };
	int pathCost;		//Fitness
public:
	Path() {}

	Path(bool randomized) {
		if (randomized)
			this->randomize();
	}

	//Constructor to create child from parents
	Path(const Path& ind1, const Path& ind2, unsigned int splPoint) {
		if (splPoint < 8) {
			for (int i = 0; i <= splPoint; i++)
				sol[i] = ind1.getElement(i);
			for (int i = splPoint + 1; i < 8; i++)
				sol[i] = ind2.getElement(i);
		}
		else
			Path();
	}

	int getElement(unsigned int index) const {
		if (index < sol.size()) return sol[index];
		else return -1;
	}


	void randomize() {
		random_shuffle(sol.begin(), sol.end(),getSeed);
	}

	void setPathCost(const CostTable& costTable) {
		pathCost = 0;
		for (int i = 0; i < sol.size() - 1; i++) {
			int cost = costTable.getCost(sol[i], sol[i + 1]);
			pathCost = pathCost + cost;
		}
	}

	int getPathCost() { return pathCost; }

	void displayPath() {
		cout << "Order: ";
		for (int i = 0; i < sol.size(); i++) {
			cout << sol[i];
			if (i < sol.size() - 1) cout << "->";
		}
		cout << endl;
	}
};

int main() {
	srand(time(NULL)); // for randomization
	CostTable* costTable = new CostTable();
	Path path1(true);
	path1.displayPath();
	Path path2(true);
	path2.displayPath();
	Path path3(path1, path2, 4);
	path3.displayPath();
	delete costTable;
	return 0;
}

int getSeed(int i) { return rand()%i; }