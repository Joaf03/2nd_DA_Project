#include <vector>
#include <chrono>
#include "DataLoader.h"
#include "TAH.h"
#include "DistanceCache.h"
#include "IndexedPrioritityQueue.h"


using namespace std;

std::vector<Edge> TAH::triangularApproximationHeuristicGreedy(const std::vector<Node>& nodes, DistanceCache& distanceCache, const std::vector<Edge>& edges) {
    int n = static_cast<int>(nodes.size());
    std::vector<bool> visited(n, false);
    std::vector<Edge> tour;
    tour.reserve(n);

    // Create an indexed priority queue to store candidate nodes sorted by distance
    IndexedPriorityQueue pq(n);

    int current = 0;
    visited[current] = true;
    int count = 0;

    while (tour.size() < n - 1) {
        // Update distances to adjacent nodes from the current node
        for (int next = 0; next < n; ++next) {
            if (!visited[next]) {
                double distance = distanceCache.getDistance(nodes[current], nodes[next], edges);
                pq.push(next, distance);
            }
        }

        // Extract the shortest edge from the priority queue
        int next = pq.popMin();
        if(pq.empty()) {
            visited[next] = true;
            current = next;
            next = 0;
            double distance = distanceCache.getDistance(nodes[current], nodes[next], edges);
            tour.emplace_back(current, next, distance);
            break;
        }
        double distance = pq.getMinDistance();
        tour.emplace_back(current, next, distance);
        visited[next] = true;
        current = next;
        count++;

        if(count % 10 == 0) {
            cout << '-' << flush;
        }
    }

    // Connect the last node back to the start node to complete the tour
    double distance = distanceCache.getDistance(nodes[current], nodes[0], edges);
    tour.emplace_back(current, 0, distance);

    // Clean up the priority queue before returning
    pq.clear();

    cout << endl;
    return tour;
}

double TAH::getTotalDistance(const vector<Edge>& tour) {
    double totalDistance = 0.0;
    for (const auto& edge : tour) {
        totalDistance += edge.distance;
    }
    return totalDistance;
}

std::vector<Edge> TAH::triangularApproximationHeuristicApproximation(const std::vector<Node>& nodes, DistanceCache& distanceCache, const std::vector<Edge>& edges) {
    int n = static_cast<int>(nodes.size());
    std::vector<bool> visited(n, false);
    std::vector<Edge> tour;
    tour.reserve(n);

    int current = 0;
    visited[current] = true;

    while (tour.size() < n - 1) {
        int next = -1;
        double minDistance = std::numeric_limits<double>::infinity();

        // Find the nearest unvisited neighbor
        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (!visited[neighbor]) {
                double distance = distanceCache.getDistance(nodes[current], nodes[neighbor], edges);
                if (distance < minDistance) {
                    minDistance = distance;
                    next = neighbor;
                }
            }
        }

        // If no unvisited neighbor found, break the loop
        if (next == -1) {
            break;
        }

        // Add the nearest edge to the tour
        tour.emplace_back(current, next, minDistance);
        visited[next] = true;
        current = next;

    }

    // Connect the last node back to the start node to complete the tour
    double distance = distanceCache.getDistance(nodes[current], nodes[0], edges);
    tour.emplace_back(current, 0, distance);


    return tour;
}






