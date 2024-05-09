#include <iostream>
#include "DataLoader.h"

int main() {

    std::vector<Edge> edges = DataLoader::loadRealWorldEdges("../csv_Files/Real-world Graphs/graph1/edges.csv");

    for (const Edge& edge : edges) {
        std::cout << "Source: " << edge.source << ", Destination: " << edge.destination << ", Distance: " << edge.distance << std::endl;
    }

    return 0;
}