#include <iostream>
#include "DataLoader.h"
#include "TSPSolver.h"
#include "menu.h"
#include "RealWorld.h"
#include <vector>
#include <chrono>
#include "DistanceCache.h"
#include "TAH.h"
#include "AntColonyOptimization.h"

using namespace std;

int main() {
    vector<Edge> edges = DataLoader::loadToyEdges("../csv_Files/Toy-Graphs/stadiums.csv");

    int filter;
    int again = 1;

    while (again == 1) {

        cout << endl;
        menu::Menu(); //Call menu

        cout << "Please choose the option you prefer by writing the number that corresponds to it and then pressing return: " << endl;
        cin >> filter;

        if (filter == 1) {

            vector<int> optimalTour;
            TSPSolver solver;
            vector<int> tour = solver.solveTSP(edges, 0);
            // Start the backtracking algorithm from node 0
            optimalTour = solver.solveTSP(edges, 0);

            // Print the optimal tour
            cout << endl << "Optimal Tour: ";
            for (int x : optimalTour) {
                if (x != optimalTour.back()) cout << x << " -> ";
                else cout << x;
            }

            double tourLength = solver.calculateTourLength(tour);
            cout << "\n\n\tLength of the tour: " << tourLength << endl;

            int userInput;
            cout << "\nType 1 to return: ";
            cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                cout << "Invalid input. Type 1 to return: ";
                cin >> userInput;
            }
        }

        if (filter == 2) {

            // Load the nodes and edges from the csv files
            vector<Edge> edges = DataLoader::loadFullyConnectedEdges("../csv_Files/Extra_Fully_Connected_Graphs/edges_25.csv");
            vector<Node> nodes = DataLoader::getLessNodes("../csv_Files/Extra_Fully_Connected_Graphs/nodes.csv", 1000);

            // Run the Triangular Approximation Heuristic algorithm (Greedy Version)
            DistanceCache distanceCache;
            auto startTAH = chrono::high_resolution_clock::now();
            vector<Edge> tour = TAH::triangularApproximationHeuristicGreedy(nodes, distanceCache, edges);
            auto endTAH = chrono::high_resolution_clock::now();
            auto durationTAH = chrono::duration_cast<chrono::seconds>(endTAH - startTAH).count();

            cout << "Distance using Triangular Approximation Heuristic (Greedy Version): " << TAH::getTotalDistance(tour) << endl;
            cout << "Execution time for TAH (Greedy Version): " << durationTAH << " seconds" << endl;

            int userInput;
            cout << "\nType 1 to return: ";
            cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                cout << "Invalid input. Type 1 to return: ";
                cin >> userInput;
            }
        }

        if (filter == 3) {

            vector<Edge> edges = DataLoader::loadFullyConnectedEdges("../csv_Files/Extra_Fully_Connected_Graphs/edges_25.csv");
            vector<Node> nodes = DataLoader::getLessNodes("../csv_Files/Extra_Fully_Connected_Graphs/nodes.csv", 1000);

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
            auto startACO = chrono::high_resolution_clock::now();
            vector<Edge> bestTour = ACO.solve();
            auto endACO = chrono::high_resolution_clock::now();
            auto durationACO = chrono::duration_cast<chrono::seconds>(endACO - startACO).count();

            cout << "Distance using Ant Colony Optimization: " << TAH::getTotalDistance(bestTour) << endl;
            cout << "Execution time for ACO: " << durationACO << " seconds" << endl;

            int userInput;
            cout << "\nType 1 to return: ";
            cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                cout << "Invalid input. Type 1 to return: ";
                cin >> userInput;
            }
        }

        if (filter == 4) {
            vector<Node> nodes;
            vector<EdgeRW> edges;
            DataLoader::loadRealWorldData("../csv_Files/Real-world Graphs/graph1/", &nodes, &edges);

            int userInput;
            cout << "\nEnter the starting node: ";
            cin >> userInput;

            RealWord realWorld;
            pair<vector<int>, double> result = realWorld.solveTSP(nodes, edges, userInput);

            for (int x : result.first)
                cout << x << ',';

            cout << "\nType 1 to return: ";
            cin >> userInput;

            // Validate user input if necessary
            while (userInput != 1) {
                cout << "Invalid input. Type 1 to return: ";
                cin >> userInput;
            }
        }

        //END THE PROGRAM
        if (filter == 0) {
            cout << "Thank you!";
            again = 0;
        }
    }

    return 0;
}
