#include "utils.h"
#include <cmath>
#define pi 3.14159265358979323846

double toRadian(double degree) {
    return degree/180 * pi;
}

double calculateDistance(double lat1, double long1, double lat2, double long2) {
    double dist;
    double disLat = toRadian(lat2) - toRadian(lat1);
    double disLong = toRadian(long2 - long1);
    //Haversine formula
    double disLat1 = disLat / 2;
    double disLong1 = disLong/2;
    dist = pow(sin(disLat1),2) + cos(toRadian(lat1)) * cos(toRadian(lat2)) * pow(sin(disLong1),2);
    dist = 2 *asin(sqrt(dist));
    dist *= 6371;
    // returns distance in km
    return dist;
}
