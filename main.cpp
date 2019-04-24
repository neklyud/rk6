#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#define PATH "D:\\input2.txt"
#define DIM 30		
int NUM_OF_SPLITTING = 5;
std::vector<int> freeVertex;//список свободных вершин

std::vector<int> subGraphDimensions = { 7, 7, 7, 7, 2 };

std::vector<int> toVector(std::vector<std::vector<int>>& splitted)
{
	std::vector<int> listOfEmployees;
	for (int i = 0; i < NUM_OF_SPLITTING; i++)
	{
		for (int j = 0; j < subGraphDimensions[i]; j++)
			listOfEmployees.push_back(splitted[i][j]);
	}
	listOfEmployees.push_back(-1);
	return listOfEmployees;
}

int getSum(std::vector<int> matrixI, std::vector<int> vertexes)
{
	int sum = 0;
	for (int i = 0; i < DIM; i++)
	{
		auto check = std::find(vertexes.begin(), vertexes.end(), i);
		if (check == vertexes.end())
		{
			sum += matrixI[i];
		}
	}
	return sum;
}

int searchMinValency(std::vector<std::vector<int>> matrix, std::vector<int> vertexes)
{
	int sum = 0;
	int min = INT16_MAX;
	int i_min = 0;
	for (int i = 0; i < DIM; i++)
	{
		auto check = std::find(vertexes.begin(), vertexes.end(), i);
		if (check == vertexes.end())
		{
			sum = getSum(matrix[i], vertexes);
			if (sum < min)
			{
				min = sum;
				i_min = i;
			}
		}
	}
	return i_min;
}

std::vector<int> incidentVertex(std::vector<int> matrixI, std::vector<int> vertexes, int minVertex)
{
	std::vector<int> incident;
	incident.push_back(minVertex);
	for (int i = 0; i < DIM; i++)
	{
		auto check = std::find(vertexes.begin(), vertexes.end(), i);
		if (check == vertexes.end())
		{
			if (matrixI[i] != 0)
			{
				incident.push_back(i);
			}
		}
	}
	return incident;
}

std::vector<std::vector<int>> addVertexes(std::vector<std::vector<int>> spl, std::vector<int> added, int dim)
{
	for (int i = 0; i < added.size();i++) 
	{
		spl[dim].erase(spl[dim].begin());
		spl[dim].push_back(added[i]);
	}
	return spl;
}

int getShortSum(std::vector<int> matrixI, std::vector<int> vertexes, std::vector<int> subGraphSet)
{
	int sum = 0;
	for (int i = subGraphSet[0]; i <= subGraphSet[subGraphSet.size()-1]; i++)
	{
		auto check = std::find(vertexes.begin(), vertexes.end(), i);
		if (check == vertexes.end())
		{
			sum += matrixI[i];
		}
	}
	return sum;
}

std::vector<int> auxCharacter(std::vector<std::vector<int>> matrix, std::vector<int> vertexes, std::vector<int> subGraphSet)
{
	int delta = 0;
	int maxDelta = -1;
	int i_maxDelta = 0;
	int count = 0;
	int i = subGraphSet[0];
	for (auto iter = subGraphSet.begin(); iter != subGraphSet.end(); iter++)
	{
		i = subGraphSet[count];
		delta = getSum(matrix[i], vertexes) - getShortSum(matrix[i], vertexes, subGraphSet);
		if (delta > maxDelta)
		{
			maxDelta = delta;
			i_maxDelta = count;
		}
		count++;
	}
	/*for(int i = subGraphSet[0]; i <= subGraphSet[subGraphSet.size()-1]; i++)
	{
		delta = getSum(matrix[i], vertexes) - getShortSum(matrix[i], vertexes, subGraphSet);
		if (delta > maxDelta)
		{
			maxDelta = delta;
			i_maxDelta = i;
		}
	}*/
	subGraphSet.erase(subGraphSet.begin() + (i_maxDelta));
	return subGraphSet;
}

std::vector<int> addVertex(std::vector<std::vector<int>> matrix, std::vector<int> vertexes, std::vector<int> splitted)
{
	int N = splitted.size();
	for (int i = 1; i < N; i++)
	{
		auto it = splitted.end();
		auto inserted = incidentVertex(matrix[splitted[i]], vertexes, splitted[i]);
		splitted.insert(it, inserted.begin(), inserted.end() );
		std::sort(splitted.begin(), splitted.end());
		auto last = std::unique(splitted.begin(), splitted.end());
		splitted.erase(last, splitted.end());
	}
	return splitted;
}

//‘ункци€ разбиени€ графа
std::vector<int> splitting(std::vector<std::vector<int>> matrix, int dimension, std::vector<std::vector<int>> spl)
{
	int minVertex = searchMinValency(matrix, toVector(spl));//ѕолучаем индекс вершины с минимальной степенью
	auto splitted = incidentVertex(matrix[minVertex], toVector(spl), minVertex);//получаем вектор смежных вершин, включа€ верш с мин степенью
	
	while (splitted.size() < subGraphDimensions[dimension])
	{
		splitted = addVertex(matrix, toVector(spl), splitted);
	}
	while (splitted.size() > subGraphDimensions[dimension])//удал€ем вершины, пока их число не станет равным размерности группы
	{
		splitted = auxCharacter(matrix,toVector(spl), splitted);//возвращает вектор, с удаленной вершиной, нанос€щей макс вред
	}
	//occupyVertex(splitted);
	return splitted;
}

void printSplit(std::vector<std::vector<int>> splitted)
{
	std::cout << "Current splitting" << std::endl;
	for (int i = 0; i < splitted.size(); i++)
	{
		for (int j = 0; j < splitted[i].size(); j++)
			std::cout << splitted[i][j] << " ";
		std::cout << std::endl;
	}
}

void summ(std::vector<std::vector<int>> matrix)
{
	for (int i = 0; i < DIM; i++)
	{
		int sum = 0;
		for (int j = 0; j < DIM; j++)
		{
			sum += matrix[i][j];
		}
		std::cout << i << " " << sum << std::endl;
	}
}


int summiraze(std::vector<std::vector<int>> matrix, std::vector<int> avoidSubGraph, std::vector<int> interSubGraph, int vertex)
{
	int sum = 0;

		for (int j = 0; j < interSubGraph.size(); j++)
		{
			if (std::find(avoidSubGraph.begin(), avoidSubGraph.end(), interSubGraph[j]) == avoidSubGraph.end())
			{
				sum += matrix[vertex][interSubGraph[j]];
			}
		}
	return sum;
}

std::vector<int> getGroups(std::vector<std::vector<int>> spl, int it)
{
	std::vector<int> first;
	for (int i = 0; i < spl.size(); i++) {
		for (int j = 0; j < spl[i].size(); j++) {
			if (it == spl[i][j]) {
				return spl[i];
			}
		}
	}
}

std::vector<int> getAvoidGroups(std::vector<std::vector<int>> spl, int it)
{
	it = it - 1;
	std::vector<int> first = {};
	if (it == -1) {
		return first;
	}
	for (int i = 0; i < spl.size(); i++) {
		for (int j = 0; j < spl[i].size(); j++) {
			if (it == spl[i][j]) {
				std::vector<int> tmp = {};
				for (int k = 0; k <= i; k++) {
					for (int l = 0; l < spl[k].size(); l++) {
						tmp.push_back(spl[k][l]);
					}
				}
				return tmp;
			}
		}
	}
}

int multDeltaR(int it, int jt, std::vector<std::vector<int>> matrix, std::vector<std::vector<int>> splMatrix, int avoidGroups)
{
	int sum = 0;
	sum += summiraze(matrix, getAvoidGroups(splMatrix, avoidGroups), getGroups(splMatrix, jt), it);
	sum -= summiraze(matrix, getAvoidGroups(splMatrix, avoidGroups), getGroups(splMatrix, it), it);
	sum += summiraze(matrix, getAvoidGroups(splMatrix, avoidGroups), getGroups(splMatrix, it), jt);
	sum	-= summiraze(matrix, getAvoidGroups(splMatrix, avoidGroups), getGroups(splMatrix, jt), jt);
	sum -= 2*matrix[it][jt];
	return sum;
}

std::vector<std::vector<int>> replace(std::vector<std::vector<int>> matrix, int first, int second)
{
	for(int i = 0;  i < matrix.size(); i++)
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == first)
			{
				matrix[i][j] = second;
			} else
			if (matrix[i][j] == second)
			{
				matrix[i][j] = first;
			}
		}
	return matrix;
}

std::vector<int> getRestVertexes(std::vector<std::vector<int>> splMat, int vertex)
{
	std::vector<int> tmp;
	for (int i = vertex + 1; i < splMat.size() && vertex + 1 != splMat.size(); i++)
	{
		for (int j = 0; j < splMat[i].size(); j++)
		{
			tmp.push_back(splMat[i][j]);
		}
	}
	return tmp;
}



std::vector<std::vector<int>> countErlich(int n, std::vector<int> groupSizes) {
	// let patterns = [];
	//  let splitting = [];
	//  const minTerm = Math.min(...groupSizes);
	//  const maxTerm = Math.max(...groupSizes);
	//  if(maxTerm > n) {
	//    return -1;
	//  }
	//  for(let i = 0; i < Math.floor(n / minTerm); i++) {
	//    splitting.push(minTerm);
	//  }
	//  if(n % minTerm === 0) {
	//    patterns.push(splitting.slice());
	//  } else {
	//    for(let i = 0; i < n % minTerm; i++) {
	//      splitting.push(1);
	//    }
	//  }
	//  while(true) {
	//    if(splitting[0] === maxTerm + 1) {
	//      break;
	//    }
	//    let minEl = Math.min(...splitting.slice(0, -1))
	//    let minPos = splitting.indexOf(minEl);
	//    splitting[minPos]++;
	//    splitting.splice(minPos + 1);
	//    let arrSum = splitting.reduce((acc, el) => acc += el);
	//    let rest = n - arrSum;
	//    for(let i = 0; i < Math.floor(rest / minTerm); i++) {
	//      splitting.push(minTerm);
	//    }
	//    for(let i = 0; i < rest % minTerm; i++) {
	//      splitting.push(1);
	//    }
	//    if(splitting.find((el) => groupSizes.indexOf(el) === -1) === undefined) {
	//      patterns.push(splitting.slice());
	//    }
	//  }
	//  return patterns;
	std::vector<std::vector<int>> patterns;
	std::vector<int> splitting;
	int maxTerm = -100000;
	int minTerm = 100000;
	for (int i = 0; i < groupSizes.size(); i++) {
		if (groupSizes[i] > maxTerm) {
			maxTerm = groupSizes[i];
		}
		if (groupSizes[i] < minTerm) {
			minTerm = groupSizes[i];
		}
	}
	if (maxTerm > n) {
		return patterns;
	}
	for (int i = 0; i < n / minTerm; i++) {
		splitting.push_back(minTerm);
	}
	if (n % minTerm == 0) {
		patterns.push_back(splitting);
	}
	else {
		for (int i = 0; i < n % minTerm; i++) {
			splitting.push_back(1);
		}
	}
	while (true) {
		if (splitting[0] == maxTerm + 1) {
			break;
		}
		int minEl = 100000;
		int minPos;
		for (int i = 0; i < splitting.size() - 1; i++) {
			if (splitting[i] < minEl) {
				minEl = splitting[i];
				minPos = i;
			}
		}
		splitting[minPos]++;
		auto start = splitting.begin() + minPos + 1;
		splitting.erase(start, splitting.end());
		int arrSum = 0;
		for (int i = 0; i < splitting.size(); i++)
		{
			arrSum += splitting[i];
		}
		int rest = n - arrSum;
		for (int i = 0; i < rest / minTerm; i++) {
			splitting.push_back(minTerm);
		}
		for (int i = 0; i < rest % minTerm; i++) {
			splitting.push_back(1);
		}
		int flag = 0;
		for (int i = 0; i < splitting.size(); i++)
		{
			if (std::find(groupSizes.begin(), groupSizes.end(), splitting[i]) == groupSizes.end())
			{
				flag = 1;
				break;
			}
		}
		if(flag == 0)
			patterns.push_back(splitting);
	}
	return patterns;
	}


std::vector<std::vector<int>> genSequence567(std::vector<int> pattern)
{
	std::vector<std::vector<int>> matr;
	std::vector<int> tmp;
	for (int x = 0; x < DIM; x++)
	{
		for (int y = 0; y < DIM; y++)
		{
			for (int z = 0; z < DIM; z++)
			{
				if (5 * x + y * 6 + z * 7 == 30)
				{
					for (int i = 0; i < x; i++) tmp.push_back(5);
					for (int i = 0; i < y; i++) tmp.push_back(6);
					for (int i = 0; i < z; i++) tmp.push_back(7);
					matr.push_back(tmp);
					tmp = {};
				}
			}
		}
	}
	return matr;
}

int getTypesKoef(std::vector<std::vector<int>> matrix, std::vector<std::vector<int>> spl)
{
	int sum = 0; 
	for (int i = 0; i < matrix.size(); i++)
	{
		auto groupIn = getGroups(spl, i);
		for (int j = 0; j < matrix.size(); j++)
		{
			if (std::find(groupIn.begin(), groupIn.end(), j) == groupIn.end())
				sum += matrix[i][j];
		}

	}
	return sum;
}

int main()
{
	std::vector<std::vector<int>> matrixAdj;//матрица смежности
	std::vector<std::vector<int>> splittedCpy;//матрица разбиениz
	std::vector<std::vector<int>> splitted;
	std::ifstream in;
	in.open(PATH);
	int tmp = 0;
	for (int i = 0; i < DIM; i++)
	{
		std::vector<int> tmpVect;
		for (int j = 0; j < DIM; j++)
		{
			in >> tmp;
			tmpVect.push_back(tmp);
		}
		matrixAdj.push_back(tmpVect);
	}
	in.close();
	auto seq = countErlich(DIM,{ 5,6,7 });
	for (int i = 0; i < seq.size(); i++) {
		for (int j = 0; j < seq[i].size(); j++)
			std::cout << seq[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < seq.size(); i++)
	{
		//¬ыбираем последовательность
		subGraphDimensions = seq[i];
		NUM_OF_SPLITTING = seq[i].size();
		splittedCpy = {};
		splitted = {};
		for (int i = 0; i < NUM_OF_SPLITTING; i++)
		{
			std::vector<int> tmp;
			for (int j = 0; j < subGraphDimensions[i]; j++)
				tmp.push_back(-1);
			splittedCpy.push_back(tmp);
		}
		summ(matrixAdj);
		for (int i = 0; i < NUM_OF_SPLITTING; i++)
		{
			splitted.push_back(splitting(matrixAdj, i, splittedCpy));
			splittedCpy[i].erase(splittedCpy[i].begin(), splittedCpy[i].end());
			splittedCpy[i].insert(splittedCpy[i].begin(), splitted[i].begin(), splitted[i].end());
		}
		std::cout << "Split for : ";
		for (int i = 0; i < subGraphDimensions.size(); i++)
			std::cout << subGraphDimensions[i] << " ";
		std::cout << std::endl;
		printSplit(splitted);
		std::cout << "-----------" << std::endl;
		std::vector<std::vector<int>> matrix = matrixAdj;
		std::vector<std::vector<int>> deltaR;
		int dim = 0;
		int  next = -1;
		std::vector<int> sgDim = { 2,3,3 };

		std::vector<std::vector<int>> splMat = splitted;
		for (int i = 0; i < splMat.size(); i++)
		{
			do
			{
				int deltaR = INT16_MIN;
				int firstSw;
				int secondSw;
				for (int j = 0; j < splMat[i].size(); j++)
				{
					auto  linear = getRestVertexes(splMat, i);
					for (int k = 0; k < linear.size(); k++)
					{
						int ij = splMat[i][j];
						int lk = linear[k];
						int tmpDeltaR = multDeltaR(splMat[i][j], linear[k], matrix, splMat, i);
						if (tmpDeltaR > deltaR)
						{
							deltaR = tmpDeltaR;
							firstSw = splMat[i][j];
							secondSw = linear[k];
						}
					}
				}
				if (deltaR > 0)
				{
					splMat = replace(splMat, firstSw, secondSw);//переделать!!!
					//printNumTypes(splMat);
					printSplit(splMat);
				}
				else
				{
					break;
				}
			} while (true);
		}
		std::cout<<"Number outer types: "<< getTypesKoef(matrixAdj, splMat);
	}

	/*summ(matrixAdj);
	for (int i = 0; i < NUM_OF_SPLITTING; i++)
	{
		splitted.push_back(splitting(matrixAdj, i, splittedCpy));
		splittedCpy[i].erase(splittedCpy[i].begin(), splittedCpy[i].end());
		splittedCpy[i].insert(splittedCpy[i].begin(), splitted[i].begin(), splitted[i].end());
	}
	printSplit(splitted);
	std::cout << "-----------" << std::endl;
	std::vector<std::vector<int>> matrix = matrixAdj;
	std::vector<std::vector<int>> deltaR;
	int dim = 0;
	int  next =-1;
	std::vector<int> sgDim = {2,3,3};

	std::vector<std::vector<int>> splMat = splitted;
	for (int i = 0; i < splMat.size(); i++)
	{
		do
		{
			int deltaR = INT16_MIN;
			int firstSw;
			int secondSw;
			for (int j = 0; j < splMat[i].size(); j++)
			{
				auto  linear = getRestVertexes(splMat, i);
				for (int k = 0; k < linear.size(); k++)
				{
					int ij = splMat[i][j];
					int lk = linear[k];
					int tmpDeltaR = multDeltaR(splMat[i][j], linear[k], matrix, splMat, i);
					if (tmpDeltaR > deltaR)
					{
						deltaR = tmpDeltaR;
						firstSw = splMat[i][j];
						secondSw = linear[k];
					}
				}
			}
			if (deltaR > 0)
			{
				splMat = replace(splMat, firstSw, secondSw);//переделать!!!
				//printNumTypes(splMat);
				printSplit(splMat);
			} 
			else
			{
				break;
			}
		} while (true);
	}*/

	return 0;
}