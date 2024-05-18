#ifndef INC_2ND_PROJECT_TAH_H
#define INC_2ND_PROJECT_TAH_H

#include <iostream>
#include <fstream>
#include "DistanceCache.h"

/**
 * @brief Represents the Traveling Ant Heuristic algorithm.
 */
class TAH {
public:

    /**
     * @brief Applies the triangular approximation heuristic using a greedy approach.
     * @param nodes The vector of nodes in the graph.
     * @param distanceCache The distance cache for storing precomputed distances between nodes.
     * @param edges The vector of edges in the graph.
     * @return A vector of edges representing the tour generated by the heuristic.
     * @complexity O(n^2) where n is the number of nodes.
     */
    static std::vector<Edge> triangularApproximationHeuristicGreedy(const std::vector<Node>& nodes, DistanceCache& distanceCache, const std::vector<Edge>& edges);

    /**
     * @brief Applies the triangular approximation heuristic using an approximation approach.
     * @param nodes The vector of nodes in the graph.
     * @param distanceCache The distance cache for storing precomputed distances between nodes.
     * @param edges The vector of edges in the graph.
     * @return A vector of edges representing the tour generated by the heuristic.
     * @complexity O(n^2) where n is the number of nodes.
     */
    static std::vector<Edge> triangularApproximationHeuristicApproximation(const std::vector<Node>& nodes, DistanceCache& distanceCache, const std::vector<Edge>& edges);

    /**
     * @brief Calculates the total distance of a given tour.
     * @param tour The vector of edges representing the tour.
     * @return The total distance of the tour.
     * @complexity O(n) where n is the number of edges in the tour.
     */
    static double getTotalDistance(const std::vector<Edge>& tour);

};

#endif //INC_2ND_PROJECT_TAH_H