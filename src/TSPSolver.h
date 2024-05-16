#ifndef INC_2ND_PROJECT_TSPSOLVER_H
#define INC_2ND_PROJECT_TSPSOLVER_H

#include "DataLoader.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class TSPSolver {
public:
    std::vector<int> solveTSP(const std::vector<Edge>& edges, int startNode);
    double calculateTourLength(const std::vector<int>& tour);
    int getMaxNodeIndex();
    void backtrack(double currentLength, std::vector<int>& currentTour, std::vector<bool>& visited);
    double getDistance(int source, int destination);

private:
    std::vector<Edge> edges;
    int startNode;
    int numNodes;
    std::vector<int> bestTour;
    double bestTourLength;
};

#endif
