#include <iostream>
#include <vector>
#include <chrono>
#include "DataLoader.h"
#include "DistanceCache.h"
#include "TAH.h"
#include "AntColonyOptimization.h"

using namespace std;

int main() {
    // Load the nodes and edges from the csv files
    vector<Edge> edges = DataLoader::loadFullyConnectedEdges("../csv_Files/Extra_Fully_Connected_Graphs/edges_25.csv");
    vector<Node> nodes = DataLoader::getLessNodes("../csv_Files/Extra_Fully_Connected_Graphs/nodes.csv", 1000);

    // Run the Triangular Approximation Heuristic algorithm (Greedy Version)
    DistanceCache distanceCache;
    auto startTAH = std::chrono::high_resolution_clock::now();
    std::vector<Edge> tour = TAH::triangularApproximationHeuristicGreedy(nodes, distanceCache, edges);
    auto endTAH = std::chrono::high_resolution_clock::now();
    auto durationTAH = std::chrono::duration_cast<std::chrono::seconds>(endTAH - startTAH).count();

    cout << "Distance using Triangular Approximation Heuristic (Greedy Version): " << TAH::getTotalDistance(tour) << endl;
    cout << "Execution time for TAH (Greedy Version): " << durationTAH << " seconds" << endl;

    // Define the parameters for the Ant Colony Optimization algorithm

    /* numAnts: This parameter defines the number of ants that will traverse the graph
     * in each iteration of the algorithm. In ACO, each ant constructs a solution (tour)
     * by probabilistically choosing edges based on pheromone levels and heuristic information.
     *
     *
     * numIterations: This parameter defines the number of iterations (epochs) that the
     * algorithm will run for. In each iteration, the ants construct solutions, and the
     * pheromone levels are updated based on the quality of the solutions.
     *
     *
     * evaporationRate: This parameter defines the rate at which pheromones evaporate on
     * the edges. Evaporation helps prevent stagnation by reducing the influence of old
     * pheromone trails.
     *
     *
     * pheromoneDeposit: This parameter defines the amount of pheromone deposited on edges
     * by the ants. The pheromone deposit amount is typically adjusted based on the quality
     * of the solutions found by the ants.
     *
     *
     * alpha: This parameter defines the influence of pheromone levels on edge selection.
     * A higher alpha value gives more weight to pheromone levels, encouraging exploration
     * of edges with higher pheromone levels.
     *
     *
     * beta: This parameter defines the influence of heuristic information on edge selection.
     * A higher beta value gives more weight to the heuristic information (e.g., distance
     * between nodes), encouraging exploitation of shorter edges.
     */

    int numAnts = 10;
    int numIterations = 1;
    double evaporationRate = 0.1;
    double pheromoneDeposit = 2.0;
    double alpha = 2.0;
    double beta = 1.0;

    DistanceCache distanceCacheACO;
    AntColonyOptimization ACO(nodes, distanceCacheACO, numAnts, numIterations, evaporationRate, pheromoneDeposit, alpha, beta, edges);
    auto startACO = std::chrono::high_resolution_clock::now();
    std::vector<Edge> bestTour = ACO.solve();
    auto endACO = std::chrono::high_resolution_clock::now();
    auto durationACO = std::chrono::duration_cast<std::chrono::seconds>(endACO - startACO).count();

    cout << "Distance using Ant Colony Optimization: " << TAH::getTotalDistance(bestTour) << endl;
    cout << "Execution time for ACO: " << durationACO << " seconds" << endl;

    return 0;
}