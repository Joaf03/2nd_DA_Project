#ifndef INC_2ND_PROJECT_GEODATA_H
#define INC_2ND_PROJECT_GEODATA_H
#include "DataLoader.h"

class GeoData {
    public:
        static double calculeDistance(Node node1, Node node2);
        static vector<Edge> findMissingEdges(vector<Node> nodes, vector<Edge> edges);

};


#endif //INC_2ND_PROJECT_GEODATA_H
