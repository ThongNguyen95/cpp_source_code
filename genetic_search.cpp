#include <iostream>
#include <array>
#include <vector>
#include <time.h>
#include <algorithm>
#include <string>
using namespace std;

#define POPULATION_SIZE 100
#define GENERATIONS 100

//Function Prototypes
class Path;
class CostTable;
int getSeed(int);
Path* reproduce(const Path*, const Path*);
void mutate(Path*);
Path* genetic_search(vector<Path*>&, const CostTable*);
void cleanup(vector<Path*>);
bool sortMethod(Path* a, Path* b);
bool find(array<int, 8>, int first, int size, int val);

//This is used as a reference to calculate the path cost
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

// This is the data structure that hold each individual in the population
class Path {
	array<int, 8> sol = { 1,2,3,4,5,6,7,8 };
	int pathCost = 0;		//Fitness
public:
	Path() {}

	//Copy Constructor
	Path(Path* other) {
		array<int, 8> temp = other->getSol();
		for (unsigned int i = 0; i < temp.size(); i++) {
			sol[i] = temp[i];
		}
		pathCost = other->getPathCost();
	}
	Path(bool randomized) {
		if (randomized)
			this->randomize();
	}

	//Constructor to create child from parents
	Path(const Path* ind1, const Path* ind2, unsigned int splPoint) {
		for (unsigned int i = 0; i < 8; i++) {
			if (i <= splPoint) {
				sol[i] = ind1->getElement(i);
			}
			else {
				int temp = ind2->getElement(i);
				bool found = find(sol, 0, i, temp);
				if (!found) {
					sol[i] = temp;
				}
				else {
					for (int k = 0; k < 8; k++) {
						temp = ind2->getElement(k);
						found = find(sol, 0, i, temp);
						if (!found) {
							sol[i] = temp;
							break;
						}
					}
				}
			}
		}
	}

	array<int, 8> getSol() { return sol; }

	int getElement(unsigned int index) const {
		if (index < sol.size()) return sol[index];
		else return -1;
	}


	void randomize() {
		random_shuffle(sol.begin(), sol.end(),getSeed);
	}

	void setPathCost(const CostTable* costTable) {
		pathCost = 0;
		for (unsigned int i = 0; i < sol.size() - 1; i++) {
			int cost = costTable->getCost(sol[i], sol[i + 1]);
			pathCost = pathCost + cost;
		}
	}

	int getPathCost() const { return pathCost; }

	void displayPath() {
		cout << "Order: ";
		for (unsigned int i = 0; i < sol.size(); i++) {
			cout << sol[i];
			if (i < sol.size() - 1) cout << "->";
		}
		cout << endl;
	}

	void swapElements(unsigned int i, unsigned int j) {
		if (i != j && i < 8 && j < 8) {
			int temp = sol[i];
			sol[i] = sol[j];
			sol[j] = temp;
		}
	}
};


int main() {
	srand(time(NULL)); // for randomization
	CostTable* costTable = new CostTable();
	vector<Path*> population;
	for (int i = 0; i < POPULATION_SIZE; i++) {
		Path* temp = new Path(true);	//generate random paths
		temp->setPathCost(costTable);
		population.push_back(temp);
	}
	Path* result = genetic_search(population, costTable);

	cout << "\nResult: " << endl;
	result->displayPath();
	cout << "Cost: " << result->getPathCost() << endl;

	delete costTable;
	cleanup(population);
	return 0;
}

// The actual genetic algorithm
Path* genetic_search(vector<Path*>& population, const CostTable* costTable) {
	vector<Path*> new_population;
	int pop_size = population.size();
	int bestCost = population.front()->getPathCost();
	int i = 0;
	while (bestCost > 20 && i < GENERATIONS) {	// Run the algorithm until path cost found is no greater than 20
												// or until some certain time (100 GENERATIONS in this case)
		for (int j = 0; j < pop_size; j++) {		//Produce new offsprings
			Path* parent1 = population[j];			//Selection for reproducing
			int temp_index = (j < pop_size - 1) ? (j + 1) : (pop_size - 1);
			Path* parent2 = population[temp_index];	//Selection for reproducing
			Path* child = reproduce(parent1, parent2);	//Crossover
			mutate(child);								//Mutation
			child->setPathCost(costTable);
			new_population.push_back(child);
		}
		
		cleanup(population);	//Cleanup allocated memory
		population = new_population;
		new_population.clear();

		sort(population.begin(), population.end(), sortMethod);	//sort based on fitness test(path-cost)
		cout << "Generation #" << i + 1 << ". Best path cost: "
			<< population.front()->getPathCost() << endl;
		bestCost = population.front()->getPathCost();
		i++;
	}
	return population.front();
}

Path* reproduce(const Path* parent1, const Path* parent2) {
	int index = rand() % 8;
	return new Path(parent1, parent2, index);
}

void mutate(Path* child) {
	int index1 = rand() % 8;
	int index2;
	do { index2 = rand() % 8; } while (index1 == index2);
	child->swapElements(index1, index2);	//Swap element at 2 random indexes
}

void cleanup(vector<Path*> population) {
	while (!population.empty()) {
		Path* temp = population.back();
		population.pop_back();
		delete temp;
	}
}
bool sortMethod(Path* a, Path* b) {		//Use with the built-in sort algorithm to sort the population
	if (a->getPathCost() < b->getPathCost()) return true;
	else return false;
}
int getSeed(int i) { return rand()%i; }	//Seed for generating random value

bool find(array<int, 8> arr, int first, int size, int val) { //Check if a value is in an array
	for (int i = first; i < size; i++) {
		if (arr[i] == val) return true;
	}
	return false;
}