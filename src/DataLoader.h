#ifndef TOYGRAPHLOADER_H
#define TOYGRAPHLOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <vector>
using namespace std;

/**
 * @brief Represents an edge in a graph.
 */
struct Edge {
    int source; /**< The ID of the source node of the edge. */
    int destination; /**< The ID of the destination node of the edge. */
    double distance; /**< The distance between the source and destination nodes. */

    /**
     * @brief Default constructor for Edge.
     * Initializes source, destination, and distance to default values.
     */
    Edge() : source(-1), destination(-1), distance(0.0) {};

    /**
     * @brief Parameterized constructor for Edge.
     * @param src The ID of the source node.
     * @param dest The ID of the destination node.
     * @param dist The distance between the source and destination nodes.
     */
    Edge(int src, int dest, double dist) : source(src), destination(dest), distance(dist) {}

    /**
     * @brief Overloaded > operator for comparing Edge objects by distance.
     * @param other The other Edge object to compare against.
     * @return True if this Edge has a greater distance than the other Edge, false otherwise.
     */
    bool operator>(const Edge& other) const {
        return distance > other.distance;
    }
};

/**
 * @brief Represents an edge in a real world graph.
 */
struct EdgeRW {
    int source; /**< The ID of the source node of the edge. */
    int destination; /**< The ID of the destination node of the edge. */
    double distance; /**< The distance between the source and destination nodes. */
};

/**
 * @brief Represents a node in a graph.
 */
struct Node {
    int id; /**< The ID of the node. */
    double longitude; /**< The longitude coordinate of the node. */
    double latitude; /**< The latitude coordinate of the node. */
};

/**
 * @brief Provides methods to load graph data from files.
 */
class DataLoader {
public:
    /**
     * @brief Loads a set of toy edges from a file.
     * @param filename The name of the file containing edge data.
     * @return A vector of Edge objects representing the loaded edges.
     */
    static vector<Edge> loadToyEdges(const std::string& filename);

    /**
     * @brief Loads a set of fully connected edges from a file.
     * @param filename The name of the file containing edge data.
     * @return A vector of Edge objects representing the loaded edges.
     */
    static vector<Edge> loadFullyConnectedEdges(const std::string& filename);

    /**
     * @brief Loads a set of real-world edges from a file.
     * @param filename The name of the file containing edge data.
     * @param nodes A pointer to a vector of Node objects to store the loaded nodes.
     * @param edges A pointer to a vector of EdgeRW objects to store the loaded edges.
     */
    static void loadRealWorldData(const std::string& filename, vector<Node> *nodes, vector<EdgeRW> *edges);

    /**
     * @brief Gets a set of nodes from a file.
     * @param filename The name of the file containing node data.
     * @return A vector of Node objects representing the loaded nodes.
     */
    static std::vector<Node> getNodes(const string &filename);

    /**
     * @brief Gets a set of nodes with a limited by the input number of nodes from a file.
     * @param filename The name of the file containing node data.
     * @param n The number of nodes to load.
     * @return A vector of Node objects representing the loaded nodes.
     */
    static std::vector<Node> getLessNodes(const string &filename, int n);
};

#endif // TOYGRAPHLOADER_H
