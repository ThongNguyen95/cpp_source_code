#include <iostream>
#include <climits>
#include <vector>
using namespace std;

void displayPath(vector<int>, int);
void dijkstra(vector<vector<int>>, int);

int main() {
	vector<vector<int>> graph = { {0, 6, 3, INT_MAX}, {INT_MAX, 0, INT_MAX, 5}, {INT_MAX, 1, 0, 1}, 
								{INT_MAX, INT_MAX, INT_MAX, 0} };
	dijkstra(graph, 0);
	return 0;
}
void dijkstra(vector<vector<int>> graph, int startNode) {
	int graphSize = graph[0].size();
	vector<bool> explored(graphSize, false); //explored nodes
	vector<int> parent(graphSize, -1);
	vector<int> costs(graphSize, INT_MAX); //costs to get to the nodes
	costs[startNode] = 0;
	int curIndex;
	
	//Loop until all nodes are explored
	for (int j = 0; j < graphSize; j++) {
		//update current node
		int bestIndex = -1;
		for (int i = 0; i < graphSize; i++) {
			if (!explored[i] && costs[i] != INT_MAX) {
				if (bestIndex == -1) {
					bestIndex = i;
				} else if (costs[i] < costs[bestIndex]) {
					bestIndex = i;
				}
			}
		}
		curIndex = bestIndex;
		explored[curIndex] = true;

		// Update total costs of the nodes connected to current node
		for (int i = 0; i < graphSize; i++) {
			if (!explored[i] && graph[curIndex][i] != INT_MAX) {
				int newCost = costs[curIndex] + graph[curIndex][i];
				if (newCost < costs[i]) {
					costs[i] = newCost;
					parent[i] = curIndex;
				}
			}
		}
	}

	//Print out the paths and costs
	for (int i = 0; i < graphSize; i++) {
		cout << "Node " << i << ":" << endl;
		cout << "Path cost: " << costs[i] << endl;
		cout << "Path: ";
		displayPath(parent, i);
		cout << endl << endl;
	}
}

void displayPath(vector<int> parent, int i) {
	if (parent[i] != -1) {
		displayPath(parent, parent[i]);
		cout << " -> ";
	}
	cout << i;
}