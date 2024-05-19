#ifndef INC_2ND_PROJECT_ANTCOLONYOPTIMIZATION_H
#define INC_2ND_PROJECT_ANTCOLONYOPTIMIZATION_H

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <random>
#include <algorithm>
#include "DataLoader.h"
#include "DistanceCache.h"
#include <limits>
#include <cmath>

/**
 * @brief Represents an Ant Colony Optimization algorithm for solving the Traveling Salesman Problem.
 */
class AntColonyOptimization {
public:
    /**
     * @brief Constructs an Ant Colony Optimization algorithm.
     * @param nodes The list of nodes representing the cities in the TSP.
     * @param distanceCache The distance cache used to store precomputed distances between nodes.
     * @param numAnts The number of ants to use in the algorithm.
     * @param numIterations The number of iterations to run the algorithm.
     * @param evaporationRate The rate at which pheromones evaporate.
     * @param pheromoneDeposit The amount of pheromone deposited on edges by ants.
     * @param alpha The pheromone influence factor.
     * @param beta The heuristic information influence factor.
     */
    AntColonyOptimization(const std::vector<Node>& nodes, DistanceCache& distanceCache, int numAnts, int numIterations, double evaporationRate, double pheromoneDeposit, double alpha, double beta, const std::vector<Edge>& edges)
            : nodes(nodes), distanceCache(distanceCache), numAnts(numAnts), numIterations(numIterations), evaporationRate(evaporationRate), pheromoneDeposit(pheromoneDeposit), alpha(alpha), beta(beta), edges(edges) {}

    /**
     * @brief Solves the Traveling Salesman Problem using Ant Colony Optimization.
     * @return The best tour found by the algorithm.
     * @complexity O(numIterations * n^2) where n is the number of nodes.
     */
    std::vector<Edge> solve() {
        initializePheromones();
        std::vector<Edge> bestTour;
        double bestTourLength = std::numeric_limits<double>::infinity();

        for (int iter = 0; iter < numIterations; iter++) {
            std::vector<Edge> tour = constructGreedySolution();
            double tourLength = calculateTourLength(tour);
            if (tourLength < bestTourLength) {
                bestTour = tour;
                bestTourLength = tourLength;
                updatePheromones(tour);
            }
        }

        std::cout << std::endl;  // Move to the next line after the loop
        return bestTour;
    }

private:
    std::vector<Node> nodes; /**< The list of nodes representing the cities. */
    std::vector<Edge> edges; /** The list of edges from the csv files */
    DistanceCache& distanceCache; /**< The distance cache storing precomputed distances between nodes. */
    std::vector<std::vector<double>> pheromones; /**< Matrix of pheromone levels on edges. */
    int numAnts; /**< The number of ants used in the algorithm. */
    int numIterations; /**< The number of iterations to run the algorithm. */
    double evaporationRate; /**< The rate at which pheromones evaporate. */
    double pheromoneDeposit; /**< The amount of pheromone deposited on edges by ants. */
    double alpha; /**< The pheromone influence factor. */
    double beta; /**< The heuristic information influence factor. */

    /**
     * @brief Initializes the pheromone levels on edges.
     * @complexity O(n^2) where n is the number of nodes.
     */
    void initializePheromones() {
        int n = static_cast<int>(nodes.size());
        double initialPheromoneLevel = 0.1; // You can adjust this value as needed
        pheromones.assign(n, std::vector<double>(n, initialPheromoneLevel));
    }

    /**
     * @brief Constructs a solution using Ant Colony Optimization.
     * @return The constructed tour.
     * @complexity O(n^2) where n is the number of nodes.
     */
    std::vector<Edge> constructGreedySolution() {
        int n = static_cast<int>(nodes.size());
        std::vector<Edge> bestTour;
        double bestTourLength = std::numeric_limits<double>::infinity();

        // Initialize pheromones and visibility (heuristic information)
        initializePheromones();

        // Create a single tour
        std::vector<int> tour;
        tour.reserve(n);
        std::vector<bool> visited(n, false);

        // Choose a random starting node
        int current = rand() % n;
        tour.push_back(current);
        visited[current] = true;

        int count = 0;
        // Build the solution greedily
        while (tour.size() < n) {
            // Compute probabilities for selecting the next node greedily
            std::vector<double> probabilities = computeGreedyProbabilities(tour.back(), visited);

            // Select the next node greedily
            int next = selectGreedyNextNode(probabilities, visited);

            // Update the solution and visited nodes
            tour.push_back(next);
            visited[next] = true;
            count++;
            if(count % 10 == 0) {
                std::cout << '-';
                std::cout.flush();
            }
        }

        // Update the best tour found so far
        std::vector<Edge> edgeTour;
        edgeTour.reserve(n);
        for (int i = 0; i < n - 1; ++i) {
            int source = tour[i];
            int destination = tour[i + 1];
            double distance = distanceCache.getDistance(nodes[source], nodes[destination], edges);
            edgeTour.emplace_back(source, destination, distance);
        }
        // Connect the last node back to the start node to complete the tour
        int lastNode = tour.back();
        int firstNode = tour.front();
        double distance = distanceCache.getDistance(nodes[lastNode], nodes[firstNode], edges);
        edgeTour.emplace_back(lastNode, firstNode, distance);

        double tourLength = calculateTourLength(edgeTour);
        if (tourLength < bestTourLength) {
            bestTourLength = tourLength;
            bestTour = edgeTour;
        }

        // Update pheromones based on the greedy solution
        updatePheromones(bestTour);

        return bestTour;
    }

    /**
     * @brief Calculates the total length of a tour.
     * @param tour The tour for which to calculate the length.
     * @return The total length of the tour.
     * @complexity O(n) where n is the number of nodes.
     */
    static double calculateTourLength(const std::vector<Edge>& tour) {
        double tourLength = 0.0;

        for (const auto& edge : tour) {
            tourLength += edge.distance;
        }

        return tourLength;
    }

    /**
     * @brief Updates the pheromone levels on edges based on the given tour.
     * @param tour The tour used to update pheromone levels.
     * @complexity O(n^2) where n is the number of nodes.
     */
    void updatePheromones(const std::vector<Edge>& tour) {
        // Evaporate pheromones on all edges
        for (auto& row : pheromones) {
            for (double& pheromoneLevel : row) {
                pheromoneLevel *= (1.0 - evaporationRate);
            }
        }

        // Deposit pheromones on edges used by ants
        for (const auto& edge : tour) {
            pheromones[edge.source][edge.destination] += pheromoneDeposit;
            pheromones[edge.destination][edge.source] += pheromoneDeposit; // Assuming undirected graph
        }
    }

    /**
     * @brief Computes probabilities for selecting the next node based on pheromone levels and heuristic information.
     * @param currentNode The current node.
     * @param visited A boolean vector indicating visited nodes.
     * @return A vector of probabilities for selecting the next node.
     * @complexity O(n) where n is the number of nodes.
     */
    std::vector<double> computeGreedyProbabilities(int currentNode, const std::vector<bool>& visited) {
        int n = static_cast<int>(nodes.size());
        std::vector<double> probabilities(n, 0.0);
        double totalProbability = 0.0;

        // Compute probabilities for unvisited nodes
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                double pheromoneFactor = pow(pheromones[currentNode][i], alpha);
                double heuristicFactor = pow(1.0 / distanceCache.getDistance(nodes[currentNode], nodes[i], edges), beta);
                probabilities[i] = pheromoneFactor * heuristicFactor;
                totalProbability += probabilities[i];
            }
        }

        // Normalize probabilities
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && totalProbability > 0) {
                probabilities[i] /= totalProbability;
            }
        }

        return probabilities;
    }

    /**
     * @brief Selects the next node based on the given probabilities.
     * @param probabilities The probabilities for selecting each node.
     * @param visited A boolean vector indicating visited nodes.
     * @return The index of the selected node.
     * @complexity O(n) where n is the number of nodes.
     */
    static int selectGreedyNextNode(const std::vector<double>& probabilities, const std::vector<bool>& visited) {
        double maxProbability = -1.0;
        int nextNode = -1;

        // Select the node with the highest probability
        for (int i = 0; i < probabilities.size(); ++i) {
            if (!visited[i] && probabilities[i] > maxProbability) {
                maxProbability = probabilities[i];
                nextNode = i;
            }
        }

        return nextNode;
    }
};

#endif //INC_2ND_PROJECT_ANTCOLONYOPTIMIZATION_H