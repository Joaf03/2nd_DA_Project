#include "TSPSolver.h"



vector<int> TSPSolver::solveTSP(const vector<Edge>& edges, int startNode) {
    this->edges = edges;
    this->startNode = startNode;
    this->numNodes = getMaxNodeIndex() + 1;
    this->bestTourLength = numeric_limits<double>::max();
    vector<int> currentTour;
    vector<bool> visited(numNodes, false);
    visited[startNode] = true;
    currentTour.push_back(startNode);
    backtrack(0, currentTour, visited);
    return bestTour;
}

int TSPSolver::getMaxNodeIndex() {
    int maxIndex = 0;
    for (const Edge& edge : edges) {
        maxIndex = max({maxIndex, edge.source, edge.destination});
    }
    return maxIndex;
}

double TSPSolver::calculateTourLength(const vector<int>& tour) {
    double tourLength = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        int source = tour[i];
        int destination = tour[i + 1];
        for (const Edge& edge : edges) {
            if ((edge.source == source && edge.destination == destination) ||
                (edge.source == destination && edge.destination == source)) {
                tourLength += edge.distance;
                break;
            }
        }
    }
    return tourLength;
}

void TSPSolver::backtrack(double currentLength, vector<int>& currentTour, vector<bool>& visited) {
    if (currentTour.size() == numNodes) {
        // Complete tour found, update best tour if shorter
        currentLength += getDistance(currentTour.back(), startNode);
        if (currentLength < bestTourLength) {
            bestTourLength = currentLength;
            bestTour = currentTour;
        }
        return;
    }

    int lastNode = currentTour.back();
    for (int nextNode = 0; nextNode < numNodes; ++nextNode) {
        if (!visited[nextNode]) {
            double newLength = currentLength + getDistance(lastNode, nextNode);
            if (newLength < bestTourLength) {
                visited[nextNode] = true;
                currentTour.push_back(nextNode);
                backtrack(newLength, currentTour, visited);
                currentTour.pop_back();
                visited[nextNode] = false;
            }
        }
    }
}

double TSPSolver::getDistance(int source, int destination) {
    for (const Edge& edge : edges) {
        if ((edge.source == source && edge.destination == destination) ||
            (edge.source == destination && edge.destination == source)) {
            return edge.distance;
        }
    }
    return numeric_limits<double>::max(); // Should not happen
}