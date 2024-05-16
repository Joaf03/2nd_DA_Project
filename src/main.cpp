#include <iostream>
#include "DataLoader.h"
#include "TSPSolver.h"

int main() {
    std::vector<Edge> edges = DataLoader::loadToyEdges("../csv_Files/Toy-Graphs/stadiums.csv");

    double minDistance = numeric_limits<double>::max();
    vector<int> optimalTour;
    TSPSolver solver;
    std::vector<int> tour = solver.solveTSP(edges, 0);
    // Start the backtracking algorithm from node 0
    optimalTour = solver.solveTSP(edges, 0);
    // Print the optimal tour
    for (int x : optimalTour)
        cout << x << ',';

    double tourLength = solver.calculateTourLength(tour);
    std::cout << " Length of the tour: " << tourLength << std::endl;

    return 0;
}
