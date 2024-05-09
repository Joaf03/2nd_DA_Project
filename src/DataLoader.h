#ifndef TOYGRAPHLOADER_H
#define TOYGRAPHLOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <vector>
using namespace std;

struct Edge {
    int source;
    int destination;
    double distance;
};

class DataLoader {
public:
    static vector<Edge> loadToyEdges(const std::string& filename);
    static vector<Edge> loadFullyConnectedEdges(const std::string& filename);
    static vector<Edge> loadRealWorldEdges(const std::string& filename);
};

#endif // TOYGRAPHLOADER_H
