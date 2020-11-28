#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

const int sizeI = 3;
int sizeJ;
//Saves all actions in current route 
std::vector <int> currentRoute;
std::vector <int> memoryArr;

void CurrentTable(int** visitedArc)
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < sizeJ; j++) {
			std::cout << visitedArc[i][j] << " ";
		}
		std::cout << "\n";
	}
}

//Checks if nearest unvisited node exist
bool UnvisitedArcExist(int positionSt, int** visitedArc)
{
	int countUnvis = 0;
	for (int i = 0; i < sizeJ; i++) {
		int startArc = visitedArc[0][i] / 10 - 1,
			endArc = visitedArc[0][i] % 10 - 1;
		if ((positionSt == startArc 
			|| positionSt == endArc)
			&& visitedArc[1][i] == 0)
			countUnvis++;
	}
	if (countUnvis >= 1)
		return true;
	else return false;
}
void CheckForUnvArc(int& position, int **visitedArc)
{
	int prevIndex = position;
	if (!UnvisitedArcExist(position, visitedArc)) {
		for (int i = currentRoute.size() - 2; i >= 0; i--) {
			if (UnvisitedArcExist(currentRoute[i] - 1, visitedArc)) {
				position = currentRoute[i] - 1;
				std::cout << position + 1 << " ";
				currentRoute.push_back(position + 1);
			}
			if (prevIndex != position) {
				return;
			}
		}
	}
}
void GoFurtherUntilNodeFound(int **visitedArc, int &position)
{
	int prevPos = position;
	for (int i = 0; i < sizeJ; i++) {
		int startArc = visitedArc[0][i] / 10 - 1,
			endArc = visitedArc[0][i] % 10 - 1;
		if (startArc == position 
			&& visitedArc[1][i] == 0) {
			visitedArc[1][i] = 1;
			position = endArc;
			std::cout << position + 1 << " ";
			currentRoute.push_back(position + 1);
			return;
		}
		else if (endArc == position
			&& visitedArc[1][i] == 0) {
			visitedArc[1][i] = 1;
			position = startArc;
			std::cout << position + 1 << " ";
			currentRoute.push_back(position + 1);
			return;
		}
	}
}
void DFS(int nodeIndex, int ** visitedArc)
{
	currentRoute.clear();
	//First time print index 
	bool firstTime = true;
	int prevPos = nodeIndex;
	while (UnvisitedArcExist(nodeIndex, visitedArc)) {
		if (firstTime)
		{
			std::cout << nodeIndex + 1 << " ";
			currentRoute.push_back(nodeIndex + 1);
		}
		for (int i = 0; i < sizeJ; i++) {
			int startArc = visitedArc[0][i] / 10 - 1,
				endArc = visitedArc[0][i] % 10 - 1;
			if ((startArc == nodeIndex || endArc == nodeIndex) && visitedArc[1][i] == 0) {
				firstTime = false;
				prevPos = nodeIndex;
				if (startArc == nodeIndex) {
					nodeIndex = endArc;
				}
				else if (endArc == nodeIndex) {
					nodeIndex = startArc;
				}
				if ((prevPos == startArc && nodeIndex == endArc)
					|| (prevPos == endArc && nodeIndex == startArc)) {
					visitedArc[1][i] = 1;
				}
				std::cout << nodeIndex + 1 << " ";
				currentRoute.push_back(nodeIndex + 1);
			}
			else if ((startArc == nodeIndex || endArc == nodeIndex) && visitedArc[1][i] == 1 
				&& UnvisitedArcExist(nodeIndex, visitedArc) 
				) 
			{
				GoFurtherUntilNodeFound(visitedArc, nodeIndex);	
			}
		}
		CheckForUnvArc(nodeIndex, visitedArc);
	}

}

void GoFurther(int** visitedArc, int& position)
{
	int prevPos = position;
	for (int i = 0; i < sizeJ; i++) {
		int startArc = visitedArc[0][i] / 10 - 1,
			endArc = visitedArc[0][i] % 10 - 1;
		if (startArc == position
			&& visitedArc[1][i] == 0) {
			visitedArc[1][i] = 1;
			position = endArc;
			currentRoute.push_back(position + 1);
			return;
		}
		else if (endArc == position
			&& visitedArc[1][i] == 0) {
			visitedArc[1][i] = 1;
			position = startArc;
			currentRoute.push_back(position + 1);
			return;
		}
	}
}
void CheckUnvArc(int& position, int** visitedArc)
{
	int prevIndex = position;
	if (!UnvisitedArcExist(position, visitedArc)) {
		for (int i = currentRoute.size() - 2; i >= 0; i--) {
			if (UnvisitedArcExist(currentRoute[i] - 1, visitedArc)) {
				position = currentRoute[i] - 1;
				currentRoute.push_back(position + 1);
			}
			if (prevIndex != position) {
				return;
			}
		}
	}
}
void SearchforCount(int nodeIndex, int ** visitedArc)
{
	currentRoute.clear();
	for (int i = 0; i < sizeJ; i++)
	{
		visitedArc[1][i] = 0;
	}
	//First time print index 
	bool firstTime = true;
	int prevPos = nodeIndex;
	while (UnvisitedArcExist(nodeIndex, visitedArc)) {
		if (firstTime)
		{
			currentRoute.push_back(nodeIndex + 1);
		}
		for (int i = 0; i < sizeJ; i++) {
			int startArc = visitedArc[0][i] / 10 - 1,
				endArc = visitedArc[0][i] % 10 - 1;
			if ((startArc == nodeIndex || endArc == nodeIndex) && visitedArc[1][i] == 0) {
				firstTime = false;
				prevPos = nodeIndex;
				if (startArc == nodeIndex) {
					nodeIndex = endArc;
				}
				else if (endArc == nodeIndex) {
					nodeIndex = startArc;
				}
				if ((prevPos == startArc && nodeIndex == endArc)
					|| (prevPos == endArc && nodeIndex == startArc)) {
					visitedArc[1][i] = 1;
				}
				currentRoute.push_back(nodeIndex + 1);
			}
			else if ((startArc == nodeIndex || endArc == nodeIndex) && visitedArc[1][i] == 1
				&& UnvisitedArcExist(nodeIndex, visitedArc)
				)
			{
				GoFurther(visitedArc, nodeIndex);
			}
		}
		CheckUnvArc(nodeIndex, visitedArc);
	}
}

void SortCopyArr() 
{
	int dupl;
	//Delete duplicates
	for (size_t i = 0; i < currentRoute.size(); i++)
	{
		int duplCount = 0;
		dupl = currentRoute[i];
		for (size_t j = 0; j < currentRoute.size(); j++)
		{
			if (dupl == currentRoute[j]) {
				duplCount++;
			}
			if (dupl == currentRoute[j] && duplCount >= 2) {
				std::swap(currentRoute[j], currentRoute[currentRoute.size() - 1]);
				currentRoute.pop_back();
			}
		}
	}
	std::sort(currentRoute.begin(), currentRoute.end());
}
int CountConnectComponent(int** visitedArc)
{
	int connectComp = 1;
	SearchforCount(0, visitedArc);
	SortCopyArr();
	memoryArr = currentRoute;
	for (int i = 1; i < sizeJ; i++) 
	{
		SearchforCount(i, visitedArc);
		SortCopyArr();
		if (memoryArr != currentRoute)
		{
			memoryArr = currentRoute;
			connectComp++;
		}
	}
	return connectComp;
}
int CountGraphVertex(int **visitedArc)
{
	int connectComp = 1;
	SearchforCount(0, visitedArc);
	SortCopyArr();
	memoryArr = currentRoute;
	int allVertex = currentRoute.size();
	for (int i = 1; i < sizeJ; i++)
	{
		SearchforCount(i, visitedArc);
		SortCopyArr();
		if (memoryArr != currentRoute)
		{
			allVertex += currentRoute.size();
			memoryArr = currentRoute;
			connectComp++;
		}
	}
	return allVertex;
}
void Cyclomatic(int **visitedArc)
{
	int cyclo = sizeJ - CountGraphVertex(visitedArc) + CountConnectComponent(visitedArc);
	std::cout << std::endl << "Cyclomatic is: " << cyclo;
}
int MaxIndex(int **graph)
{
	int maxInd = graph[0][0];
	for (int i = 0; i < sizeJ; i++) {
		if (graph[0][i] > maxInd) {
			maxInd = graph[0][i];
		}
		else if (graph[1][i] > maxInd) {
			maxInd = graph[1][i];
		}
	}
	return maxInd;
}
void GetValuesForVisitedArc(int ** &visitedArc, int **graph)
{
	for (int i = 0; i < sizeJ; i++) {
		visitedArc[0][i] = graph[0][i] * 10 + graph[1][i];
		visitedArc[1][i] = 0;
	}

}
void PrintArcList(int **graph)
{
	for (int i = 0; i < sizeI; i++) {
		for (int j = 0; j < sizeJ; j++) {
			std::cout << graph[i][j] << " ";
		}
		std::cout << "\n";
	}
}
int main()
{
	int start;
	//Amount of arcs
	std::cin >> sizeJ;
 	int** graph = new int* [sizeI];
	for (int i = 0; i < sizeI; i++) {
		graph[i] = new int[sizeJ];
	}

	int** visitedArc = new int* [2];
	for (int i = 0; i < 2; i++) {
		visitedArc[i] = new int[sizeJ];
	}

	for (int i = 0; i < sizeI; i++) {
		for (int j = 0; j < sizeJ; j++) {
			std::cin >> graph[i][j];
		}
	}
	GetValuesForVisitedArc(visitedArc, graph);
	std::cout << "List arc graph: " << std::endl;
	PrintArcList(graph);
	std::cout << "Start vertex: ";
	std::cin >> start;
	std::cout << "Bypass order: ";
	DFS(start - 1, visitedArc);
	Cyclomatic(visitedArc);
	delete[] graph;
	delete[] visitedArc;
	return 0;
}