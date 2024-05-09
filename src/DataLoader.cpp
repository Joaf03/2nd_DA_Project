#include <vector>
#include <iostream>
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

vector<Edge> DataLoader::loadRealWorldEdges(const string &filename) {
    vector<Edge> edges;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open edges file: " << filename << std::endl;
        return edges;
    }

    string line;
    getline(file, line);
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