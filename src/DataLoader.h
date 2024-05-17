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

struct EdgeRW {
    int source;
    int destination;
    double distance;
};

struct Node {
    int id;
    double latitude;
    double longitude;
};

class DataLoader {
public:
    static vector<Edge> loadToyEdges(const std::string& filename);
    static vector<Edge> loadFullyConnectedEdges(const std::string& filename);
    static void loadRealWorldEdges(const std::string& filename, vector<Node> *nodes, vector<EdgeRW> *edges);
};

#endif // TOYGRAPHLOADER_H
