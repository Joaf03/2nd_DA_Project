#include <iostream>
#include <unordered_map>
#include "DataLoader.h"
#include "TSPSolver.h"
#include "menu.h"
#include "RealWorld.h"

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

            //call method

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

            //call method

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

            //call method

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
            DataLoader::loadRealWorldEdges("../csv_Files/Real-world Graphs/graph1/", &nodes, &edges);

            int userInput;
            cout << "\nEnter the starting node: ";
            cin >> userInput;

            RealWord realWorld;
            pair<vector<int>, double> result = realWorld.solveTSP(nodes, edges, userInput);

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

    double minDistance = numeric_limits<double>::max();
    vector<int> optimalTour;
    TSPSolver solver;
    vector<int> tour = solver.solveTSP(edges, 0);
    // Start the backtracking algorithm from node 0
    optimalTour = solver.solveTSP(edges, 0);
    // Print the optimal tour
    for (int x : optimalTour)
        cout << x << ',';

    double tourLength = solver.calculateTourLength(tour);
    cout << " Length of the tour: " << tourLength << endl;

    return 0;
}
