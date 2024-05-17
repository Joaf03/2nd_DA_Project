#include "RealWorld.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <limits>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

double RealWord::getDistance(int node1, int node2) {
    for(EdgeRW edge : edges){
        if(edge.source == node1 && edge.destination == node2) return edge.distance;
    }
    return -1;
}

vector<int> RealWord::getNeighbors(int node) {
    vector<int> neighbors;
    for (EdgeRW edge : edges) {
        if (edge.source == node) neighbors.push_back(edge.destination);
    }
    return neighbors;
}

pair<vector<int>, double> RealWord::solveTSP(vector<Node> nodes, vector<EdgeRW> edges, int startNode) {
    this->nodes = nodes;
    this->edges = edges;

    int n = nodes.size();
    vector<int> tour;
    unordered_set<int> visited;
    stack<int> backtrackStack;
    int currentNode = startNode;

    tour.push_back(currentNode);
    visited.insert(currentNode);
    double totalDistance = 0;

    while (visited.size() < n) {
        int nextNode = -1;
        double minDistance = numeric_limits<double>::max();

        for (int neighbor : getNeighbors(currentNode)) {
            if (visited.find(neighbor) == visited.end() && getDistance(currentNode, neighbor) < minDistance) {
                nextNode = neighbor;
                minDistance = getDistance(currentNode, neighbor);
            }
        }

        if (nextNode == -1) {
            // If no unvisited neighbors, backtrack to the last node with unvisited neighbors
            while (!backtrackStack.empty()) {
                currentNode = backtrackStack.top();
                backtrackStack.pop();

                for (const auto& neighbor : getNeighbors(currentNode)) {
                    double distance = getDistance(currentNode, neighbor);
                    if (distance < minDistance && (visited.find(neighbor) == visited.end() || visited.size() < n)) {
                        nextNode = neighbor;
                        minDistance = distance;
                        break;
                    }
                }
                if (nextNode != -1) break;
            }
        }

        if (nextNode == -1) {
            cerr << "No valid tour found - " << currentNode << endl;
            return {tour, -1};
        }

        backtrackStack.push(currentNode);
        tour.push_back(nextNode);
        visited.insert(nextNode);
        totalDistance += minDistance;
        currentNode = nextNode;
    }

    double returnDistance = getDistance(currentNode, startNode);
    if (returnDistance == -1) {
        cerr << "No valid return path found." << endl;
        return {tour, -1};
    }

    totalDistance += returnDistance;
    tour.push_back(startNode);

    return {tour, totalDistance};
}
