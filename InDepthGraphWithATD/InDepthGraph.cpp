#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Vertex
{
	std::string name;
	bool ifVisited = false;
};

const int sizeI = 3;
int sizeJ = 0;

std::vector <Vertex> vertexes;
std::vector <std::vector<int>> graph(3);
std::vector <std::vector<int>> visitedArc(2);
//Saves all actions in current route 
std::vector <int> currentRoute;
std::vector <int> memoryArr;

void CurrentTable()
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < sizeJ; j++) {
			std::cout << visitedArc[i][j] << " ";
		}
		std::cout << "\n";
	}
}

double FIRST(int v)
{
	double firstInd = std::numeric_limits<double>::infinity();
	for (size_t j = 0; j < sizeJ; j++)
	{
		if (graph[0][j] == v && graph[1][j] != v 
			&& graph[1][j] < firstInd)
		{
			firstInd = graph[1][j];
		}
		else if (graph[1][j] == v && graph[0][j] != v
			&& graph[0][j] < firstInd)
		{
			firstInd = graph[0][j];
		}
	}
	if (firstInd == std::numeric_limits<double>::infinity())
		return 0;
	else return firstInd;
}
double NEXT(int v, int i)
{
	double nextInd = std::numeric_limits<double>::infinity();
	for (size_t j = 0; j < sizeJ; j++)
	{
		if (graph[0][j] == v && graph[1][j] != v
			 && graph[1][j] < nextInd && graph[1][j] > i)
		{
			nextInd = graph[1][j];	
		}
		else if (graph[1][j] == v && graph[0][j] != v
			&& graph[0][j] < nextInd && graph[0][j] > i)
		{
			nextInd = graph[0][j];
		}
	}
	if (nextInd == std::numeric_limits<double>::infinity())
		return 0;
	else return nextInd;
}
Vertex VERTEX(int v, int i)
{
	Vertex vertex;
	for (size_t j = 0; j < sizeJ; j++)
	{
		if ((graph[0][j] == v && graph[1][j] == i))
		{
			i = graph[1][j];
			break;
		}
		else if (graph[1][j] == v && graph[0][j] == i)
		{
			i = graph[0][j];
			break;
		}
	}
	vertex.name = std::to_string(i);
	for (size_t j = 0; j < vertexes.size(); j++)
	{
		if (vertex.name == vertexes[j].name)
		{
			vertex.name = vertexes[j].name;
			vertex.ifVisited = vertexes[j].ifVisited;
			break;
		}
	}
	return vertex;
}
void ADD_V(int v, int mark)
{
	Vertex vertex;
	vertex.name = std::to_string(v);
	vertex.ifVisited = mark;
	vertexes.push_back(vertex);
	std::cout << std::endl << "Vertex " << v << " added";
}
void ADD_E(int v, int w, int c)
{
	if (w > v)
	{
		int transfer = v;
		v = w;
		w = transfer;
	}
	int rowCounter = 0;
	std::vector<int> row;
	for (auto& row : graph)
	{
		if(rowCounter == 0)
		   row.push_back(v);
		if (rowCounter == 1)
			row.push_back(w);
		if (rowCounter == 2)
			row.push_back(c);
		rowCounter++;
	}
	rowCounter = 0;
	int arc = v * 10 + w;
	for (auto& row : visitedArc)
	{
		if (rowCounter == 0)
			row.push_back(arc);
		if (rowCounter == 1)
			row.push_back(0);
		rowCounter++;
	}
	sizeJ++;
	std::cout << std::endl << "Arc from " << v << " to " << w << " added";
}
void DEL_V(int v)
{
	std::vector<int>columnDelVis;
	std::vector<int>columnDelGraph;
	std::vector<int>row;
	std::string name = std::to_string(v);
	int prevSize = vertexes.size();
	for (size_t i = 0; i < vertexes.size(); i++)
	{
		if (vertexes[i].name == name)
		{
			vertexes.erase(vertexes.begin() + i);
		}
	}
	if (vertexes.size() == prevSize)
	{
		std::cout << "Inexistent vertex" << std::endl;
	}
	for (size_t i = 0; i < sizeJ; i++)
	{
		int startArc = visitedArc[0][i] / 10;
		int endArc = visitedArc[0][i] % 10;
		if (v == startArc || v == endArc)
		{
			columnDelVis.push_back(i);
		}
	}
	columnDelGraph = columnDelVis;
	for (auto& row : visitedArc)
	{
		int offsetInVectors = 0;
		for (size_t i = 0; i < columnDelVis.size(); i++)
		{
			row.erase(row.begin() + (columnDelVis[i] - offsetInVectors));
			columnDelVis.erase(columnDelVis.begin());
			i = -1;
			offsetInVectors++;
		}
		columnDelVis = columnDelGraph;
	}
	for (auto& row : graph)
	{
		int offsetInVectors = 0;
		for (size_t i = 0; i < columnDelGraph.size(); i++)
		{
			row.erase(row.begin() + (columnDelGraph[i] - offsetInVectors));
			columnDelGraph.erase(columnDelGraph.begin());
			i = -1;
			offsetInVectors++;
		}
		columnDelGraph = columnDelVis;
	}
	sizeJ -= columnDelGraph.size();
	std::cout << std::endl << "Vertex " << v << " deleted";
}
void DEL_E(int v, int w)
{
	int columnToDelete = -1;
	int rowCounter = 0;
	std::vector<int> row;
	for (size_t i = 0; i < sizeJ; i++)
	{
		if ((graph[0][i] == v && graph[1][i] == w)
			|| (graph[0][i] == w && graph[1][i] == v))
		{
			columnToDelete = i;
			break;
		}
	}
	if (columnToDelete == -1)
	{
		std::cout << "Inexisent arc" << std::endl;
		return;
	}
	for (auto& row : graph)
	{
		row.erase(row.begin() + columnToDelete);
	}
	for (auto& row : visitedArc)
	{
		row.erase(row.begin() + columnToDelete);
	}
	sizeJ--;
	std::cout << std::endl << "Arc from " << v << " to " << w << " deleted";
}
void EDIT_V(int v, int mark)
{
	std::string name = std::to_string(v);
	Vertex vertex;
	vertex.ifVisited = mark;
	for (size_t i = 0; i < vertexes.size(); i++)
	{
		if (vertexes[i].name == name)
		{
			vertexes[i].ifVisited = mark;
		}
	}
	std::cout << std::endl << "Vertex " << v << " changed";
}
void EDIT_E(int v, int w, int c)
{
	for (size_t i = 0; i < sizeJ; i++)
	{
		if (graph[0][i] == v
			&& graph[1][i] == w)
		{
			graph[2][i] = c;
		}
	}
	std::cout << std::endl << "Arc from " << v << " to " << w << " changed";
}

bool UnvisitedArcExist(int positionSt)
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
void CheckForUnvArc(int& position)
{
	int prevIndex = position;
	if (!UnvisitedArcExist(position)) {
		for (int i = currentRoute.size() - 2; i >= 0; i--) {
			if (UnvisitedArcExist(currentRoute[i] - 1)) {
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
void GoFurtherUntilNodeFound(int &position)
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
void DFS(int nodeIndex)
{
	Vertex vertex;
	currentRoute.clear();
	//First time print index 
	bool firstTime = true;
	int prevPos = nodeIndex;
	while (UnvisitedArcExist(nodeIndex)) {
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
				&& UnvisitedArcExist(nodeIndex) 
				) 
			{
				GoFurtherUntilNodeFound(nodeIndex);	
			}
		}
		CheckForUnvArc(nodeIndex);
	}

}

void GoFurther(int& position)
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
void CheckUnvArc(int& position)
{
	int prevIndex = position;
	if (!UnvisitedArcExist(position)) {
		for (int i = currentRoute.size() - 2; i >= 0; i--) {
			if (UnvisitedArcExist(currentRoute[i] - 1)) {
				position = currentRoute[i] - 1;
				currentRoute.push_back(position + 1);
			}
			if (prevIndex != position) {
				return;
			}
		}
	}
}
void SearchforCount(int nodeIndex)
{
	currentRoute.clear();
	for (int i = 0; i < sizeJ; i++)
	{
		visitedArc[1][i] = 0;
	}
	//First time print index 
	bool firstTime = true;
	int prevPos = nodeIndex;
	while (UnvisitedArcExist(nodeIndex)) {
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
				&& UnvisitedArcExist(nodeIndex)
				)
			{
				GoFurther(nodeIndex);
			}
		}
		CheckUnvArc(nodeIndex);
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

int CountConnectComponent()
{
	int connectComp = 1;
	SearchforCount(0);
	SortCopyArr();
	memoryArr = currentRoute;
	for (int i = 1; i < sizeJ; i++) 
	{
		SearchforCount(i);
		SortCopyArr();
		if (memoryArr != currentRoute)
		{
			memoryArr = currentRoute;
			connectComp++;
		}
	}
	return connectComp;
}
int CountGraphVertex()
{
	int connectComp = 1;
	SearchforCount(0);
	SortCopyArr();
	memoryArr = currentRoute;
	int allVertex = currentRoute.size();
	for (int i = 1; i < sizeJ; i++)
	{
		SearchforCount(i);
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
void Cyclomatic()
{
	int cyclo = sizeJ - CountGraphVertex() + CountConnectComponent();
	std::cout << std::endl << "Cyclomatic is: " << cyclo;
}
void GetValuesForVisitedArc()
{
	for (int i = 0; i < sizeJ; i++) {
		visitedArc[0][i] = graph[0][i] * 10 + graph[1][i];
	}
}
void PrintArcList()
{
	for (int i = 0; i < sizeI; i++) {
		for (int j = 0; j < sizeJ; j++) {
			std::cout << graph[i][j] << " ";
		}
		std::cout << "\n";
	}
}
void DeleteSimilarElem(std::vector<int> &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		int counter = 0;
		int num = vec[i];
		for (int j = 0; j < vec.size(); j++)
		{
			if (num == vec[j])
			{
				counter++;
			}
			if (counter == 2 && num == vec[j])
			{
				counter = 0;
				vec.erase(vec.begin() + j);
				j = -1;
			}
		}
	}
}
void CreateMatrix(std::vector<std::vector<int>> &matrix, size_t row)
{
	for (size_t i = 0; i < row; ++i)
	{
		matrix[i].resize(sizeJ);
		for (int j = 0; j < sizeJ; ++j)
			std::cin >> matrix[i][j];
	}
}
void CopyFromVisitedArc()
{
	for (size_t j = 0; j < vertexes.size(); j++)
	{
		int num = std::stoi(vertexes[j].name);
		for (size_t i = 0; i < sizeJ; i++)
		{
			int startArc = visitedArc[0][i] / 10,
				endArc = visitedArc[0][i] % 10;
			if ((num == startArc || num == endArc)
				&& visitedArc[1][i] == 1)
			{
				vertexes[j].ifVisited = true;
			}
		}
	}
}
int main()
{
	//Temporary vector for vertexes list 
	std::vector <int> tempVector;
	int start;
	Vertex vertex;
	std::cout << "Type amount of arcs: ";
	std::cin >> sizeJ;
	CreateMatrix(graph, 3);
	for (size_t i = 0; i < 2; ++i)
	{
		visitedArc[i].resize(sizeJ);
		for (int j = 0; j < sizeJ; ++j)
			visitedArc[i][j] = 0;
	}
	GetValuesForVisitedArc();
	for (size_t j = 0; j < sizeJ; j++)
	{ 
		tempVector.push_back(visitedArc[0][j] / 10);
		tempVector.push_back(visitedArc[0][j] % 10);
	}
	DeleteSimilarElem(tempVector);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		vertex.name = std::to_string(tempVector[i]);
		vertexes.push_back(vertex);
	}
	std::cout << "List arc graph: " << std::endl;
	PrintArcList();
	std::cout << "Start vertex: ";
	std::cin >> start;
	std::cout << "Bypass order: ";
	DFS(start - 1);
	CopyFromVisitedArc();
	Cyclomatic();

	int forFIRST;
	std::cout << std:: endl << "Type index: ";
	std::cin >> forFIRST;
	std::cout << std:: endl << forFIRST << " index: " << FIRST(forFIRST);

	int forNEXTv, forNEXTi;
	std::cout << std::endl << "Type adjacent vertex and index: ";
	std::cin >> forNEXTv >> forNEXTi;
	std::cout << std:: endl << "Next index to " << forNEXTv << " after " << forNEXTi << " : " << NEXT(forNEXTv, forNEXTi);

	int forVERTEXv, forVERTEXi;
	std::cout << std::endl << "Type adjacent vertex and index: ";
	std::cin >> forVERTEXv >> forVERTEXi;
	std::cout << std:: endl << "About vertex " << forVERTEXi <<" : " << std::endl;
	vertex = VERTEX(forVERTEXv, forVERTEXi);
	std::cout << "\tName is: " << vertex.name;
	std::cout << std::endl << "\tVisited: " << std::boolalpha << vertex.ifVisited;

	int forADDvV, forADDvMark;
	std::cout << std::endl << "Type vertex and mark to add: ";
	std::cin >> forADDvV >> forADDvMark;
	ADD_V(forADDvV, forADDvMark);

	int forADDeV, forADDeW, forADDeC;
	std::cout << std::endl << "Type start vertex, end vertex and weight to add: ";
	std::cin >> forADDeV >> forADDeW >> forADDeC;
	ADD_E(forADDeV, forADDeW, forADDeC);

	int forDELvV;
	std::cout << std::endl << "Type vertex to delete: ";
	std::cin >> forDELvV;
	DEL_V(forDELvV);

	int forDELeV, forDELeW;
	std::cout << std::endl << "Type start vertex and end vertex to delete: ";
	std::cin >> forDELeV >> forDELeW;
	DEL_E(forDELeV, forDELeW);

	int forEDITvV, forEDITvMark;
	std::cout << std::endl << "Type vertex and mark to edit: ";
	std::cin >> forEDITvV >> forEDITvMark;
	EDIT_V(forEDITvV, forEDITvMark);

	int forEDITeV, forEDITeW, forEDITeC;
	std::cout << std::endl << "Type start vertex, end vertex and weight to edit: ";
	std::cin >> forEDITeV >> forEDITeW >> forEDITeC;
	EDIT_E(forEDITeV, forEDITeW, forEDITeC);
	return 0;
}