#include <iostream>
#include <vector>
const int sizeI = 3;
const int sizeJ = 8;
//Arc list
int graph[sizeI][sizeJ] =
{
{1, 2, 4, 4, 1, 3, 1, 1},
{2, 3, 5, 2, 5, 6, 7, 8},
{4, 6, 2, 3, 12, 8, 45, 56}
};
//If been in this condition
int beenThere = 0;
//Saves visited nodes in "bool" type
bool visited[sizeJ] = { false };
//Checks if exist unvisited node 
std::vector <int> beenNodes;
//First time print index 
bool firstTime = true;
//Checks if nearest unvisited node exist
bool UnvisitedExist(int position)
{
	int countUnvis = 0;
	for (int i = 0; i < sizeJ; i++)
		if (graph[0][i] == position + 1 && visited[graph[1][i] - 1] == false)
			countUnvis++;
		else if (graph[1][i] == position + 1 && visited[graph[0][i] - 1] == false)
			countUnvis++;
	if (countUnvis >= 1)
		return true;
	else return false;
}
//Checks for visited nodes. If all visited returns "true", if not all or all visited returns "false"
bool allVisited()
{
	int visitedCounter = 0;
	for (int i = 0; i < sizeJ; i++)
		if (visited[i] == true)
			visitedCounter++;
	if (visitedCounter == sizeJ)
		return true;
	else return false;
}
//Depth-first search
void DFS(int nodeIndex)
{
	while (!allVisited()) {
		if (firstTime)
		{
			std::cout << nodeIndex + 1 << " ";
			beenNodes.push_back(nodeIndex + 1);
		}
		visited[nodeIndex] = true;
		for (int i = 0; i < sizeJ; i++) {
			int prevStartIndexNode = graph[0][i];
			int prevEndIndNode = graph[1][i];
			if (prevStartIndexNode == nodeIndex + 1 && visited[prevEndIndNode - 1] == false) {
				firstTime = false;
				nodeIndex = prevEndIndNode - 1;
				visited[nodeIndex] = true;
				std::cout << nodeIndex + 1 << " ";
				beenNodes.push_back(nodeIndex + 1);
			}
			else if (prevEndIndNode == nodeIndex + 1 && visited[prevStartIndexNode - 1] == false) {
				firstTime = false;
				nodeIndex = prevStartIndexNode - 1;
				visited[nodeIndex] = true;
				std::cout << nodeIndex + 1 << " ";		
				beenNodes.push_back(nodeIndex + 1);
			}
			else if (prevEndIndNode == nodeIndex + 1 && visited[ prevStartIndexNode- 1] == true && !UnvisitedExist(nodeIndex)) {
				firstTime = false;
				nodeIndex = prevStartIndexNode - 1;
				visited[nodeIndex] = true;
				std::cout << nodeIndex + 1 << " ";
			}
			else if (prevStartIndexNode == nodeIndex + 1 && visited[prevEndIndNode - 1] == true && !UnvisitedExist(nodeIndex)) {
				firstTime = false;
				nodeIndex = prevEndIndNode - 1;
				visited[nodeIndex] = true;
				std::cout << nodeIndex + 1 << " ";
			}
		}
	}
}

void Cyclomatic()
{
	int countVertex = 0;
	int cyclo;
	for (size_t i = 0; i < beenNodes.size(); i++)
		countVertex++;
	cyclo = sizeJ - countVertex + 1;
	std::cout << std::endl << "Cyclomatic is: " << cyclo;
}
int main()
{
	int start;
	std::cout << "List arc graph: " << std::endl;
	for (int i = 0; i < sizeI; i++)
	{
		for (int j = 0; j < sizeJ; j++)
			std::cout << " " << graph[i][j];
		std::cout << std::endl;
	}
	std::cout << "Start vertex: ";
	std::cin >> start;
	std::cout << "Bypass order: ";
	DFS(start - 1);
	Cyclomatic();
	return 0;
}