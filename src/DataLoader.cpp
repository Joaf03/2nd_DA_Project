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

std::vector<Node> DataLoader::getNodes(const string &filename) {
    vector<Node> nodes;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open edges file: " << filename << std::endl;
        return nodes;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Node node;
        char comma;
        if (!(iss >> node.id >> comma >> node.longitude >> comma >> node.latitude)) {
            cerr << "Failed to parse line: " << line << std::endl;
            continue;
        }
        nodes.push_back(node);
    }

    file.close();
    return nodes;
}

std::vector<Node> DataLoader::getLessNodes(const string &filename, int n) {
    vector<Node> nodes;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open edges file: " << filename << std::endl;
        return nodes;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        Node node;
        char comma;
        if (!(iss >> node.id >> comma >> node.longitude >> comma >> node.latitude)) {
            cerr << "Failed to parse line: " << line << std::endl;
            continue;
        }
        nodes.push_back(node);
        count++;
        if(count == n) {
            break;
        }
    }

    file.close();
    return nodes;
}
