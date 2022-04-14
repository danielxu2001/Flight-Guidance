#pragma once
#include <string>

class Airport {
    public:
        Airport() {} // only for unordered_map
        // We mainly use IACA. If not provided, we use ICAO
        Airport(std::string code) :
                code_(code) {
        }            
        Airport(std::string code, double latitude, double longitutde) :
                code_(code),
                latitude_(latitude),
                longitude_(longitutde) {
        }

        double getLatitude();
        double getLongtitude();

    private:
        std::string code_;
        double latitude_;
        double longitude_;
};