#ifndef INC_2ND_PROJECT_REALWORLD_H
#define INC_2ND_PROJECT_REALWORLD_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "DataLoader.h"

using namespace std;

class RealWord{
public:
    double getDistance(int node1, int node2);
    vector<int> getNeighbors(int node);
    pair<vector<int>, double> solveTSP(vector<Node> nodes, vector<EdgeRW> edges, int startNode);
    
private:
vector<EdgeRW> edges;
vector<Node> nodes;
vector<int> bestTour;
};

#endif //INC_2ND_PROJECT_REALWORLD_H
