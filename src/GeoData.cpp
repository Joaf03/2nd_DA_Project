#include "GeoData.h"
#include <iostream>
#include <cmath>
#include <vector>

const double EARTH_RADIUS = 6371.0; // Earth's radius in kilometers

double toRadians(const double degree) {
    const double halfC = M_PI / 180;
    return degree * halfC;
}

double GeoData::calculeDistance(Node node1, Node node2) {
    double lat1 = toRadians(node1.latitude);
    double lon1 = toRadians(node1.longitude);
    double lat2 = toRadians(node2.latitude);
    double lon2 = toRadians(node2.longitude);

    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;

    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * asin(sqrt(a));

    return EARTH_RADIUS * c;
}