#ifndef PISHTTP_POWER_SERVICE_H
#define PISHTTP_POWER_SERVICE_H
#include "dao/PowerDao.h"

#pragma once

class PowerService{
    public:
        int getCabinetNumber();
        // int getRoutesPerCabinet();
        nlohmann::json getRouteList(int cabinetId);
        void updateRoute(int id, const std::string& name);        
        void switchPowerForAll(int statusCode);
        void switchPowerForSingle(int id, int status);
    private:
        PowerDao powerDao;
    };    
#endif //PISHTTP_POWER_SERVICE_H
