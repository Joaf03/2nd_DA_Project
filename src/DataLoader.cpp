#include <vector>
#include <iostream>
#include <unordered_map>
#include "DataLoader.h"

vector<Edge> DataLoader::loadToyEdges(const std::string& filename) {
    vector<Edge> edges;
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open edges file: " << filename << std::endl;
        return edges;
    }

    string line;
    getline(file, line);
    while (std::getline(file, line)) {
        istringstream iss(line);
        Edge edge;
        char comma;
        if (!(iss >> edge.source >> comma >> edge.destination >> comma >> edge.distance)) {
            cerr << "Failed to parse line: " << line << std::endl;
            continue;
        }
        edges.push_back(edge);
    }

    file.close();
    return edges;
}

vector<Edge> DataLoader::loadFullyConnectedEdges(const string &filename) {
    vector<Edge> edges;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open edges file: " << filename << std::endl;
        return edges;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Edge edge;
        char comma;
        if (!(iss >> edge.source >> comma >> edge.destination >> comma >> edge.distance)) {
            cerr << "Failed to parse line: " << line << std::endl;
            continue;
        }
        edges.push_back(edge);
    }

    file.close();
    return edges;
}

void DataLoader::loadRealWorldEdges(const string &dirname, vector<Node> *nodes, vector<EdgeRW> *edges) {
    string filename = dirname + "nodes.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open nodes file: " << filename << std::endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);
        Node node;
        char comma;
        if (!(iss >> node.id >> comma >> node.longitude >> comma >> node.latitude)) {
            cerr << "Failed to parse line: " << line << std::endl;
            continue;
        }
        nodes->push_back(node);
    }

    file.close();

    filename = dirname + "edges.csv";
    ifstream file2(filename);
    if (!file2.is_open()) {
        cerr << "Failed to open edges file: " << filename << std::endl;
        return;
    }

    getline(file2, line);
    while (getline(file2, line)) {
        istringstream iss(line);
        EdgeRW edge;
        char comma;
        if (!(iss >> edge.source >> comma >> edge.destination >> comma >> edge.distance)) {
            cerr << "Failed to parse line: " << line << std::endl;
            continue;
        }
        edges->push_back(edge);
    }

    file2.close();
}