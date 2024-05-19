#ifndef INC_2ND_PROJECT_DISTANCECACHE_H
#define INC_2ND_PROJECT_DISTANCECACHE_H

#include "GeoData.h"
#include <utility>
#include <functional>
#include "DistanceCache.h"

/**
 * @brief A class for caching distances between nodes.
 */
class DistanceCache {
    /**
     * @brief Functor for hashing pairs.
     */
    struct pair_hash {
        /**
         * @brief Hashes a pair.
         * @param pair The pair to be hashed.
         * @return The hash value of the pair.
         * @complexity O(1)
         */
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2> &pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };
public:
    /**
     * @brief Gets the distance between two nodes.
     * @param node1 The first node.
     * @param node2 The second node.
     * @param edges The list of edges to check for precalculated distances.
     * @return The distance between the two nodes.
     * @complexity O(m) for checking the edges plus O(1) for accessing the cache, where m is the number of edges.
     */
    double getDistance(const Node& node1, const Node& node2, const std::vector<Edge>& edges) {
        // Check if the distance is already calculated and stored in the edges
        for (const auto& edge : edges) {
            if ((edge.source == node1.id && edge.destination == node2.id) ||
                (edge.source == node2.id && edge.destination == node1.id)) {
                return edge.distance;
            }
        }

        // If the distance is not found in the edges, calculate it
        auto key = std::make_pair(node1.id, node2.id);
        if (cache.find(key) == cache.end()) {
            double distance = GeoData::calculeDistance(node1, node2);
            cache[key] = distance;
            cache[std::make_pair(node2.id, node1.id)] = distance;
        }
        return cache[key];
    }

private:
    std::unordered_map<std::pair<int, int>, double, pair_hash> cache; /**< Cache for storing calculated distances. */
};

#endif //INC_2ND_PROJECT_DISTANCECACHE_H
