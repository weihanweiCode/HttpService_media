#include "service/PowerService.h"
#include <sstream>
#include <list>
#include <iostream>
#include <string>

int PowerService::getCabinetNumber(){
    return 8;
}

// int PowerService::getRoutesPerCabinet(){
//     return 24;
// }


nlohmann::json PowerService::getRouteList(int cabinetId){
    return powerDao.getRouteList(cabinetId);    
}

void PowerService::updateRoute(int id, const std::string& name){
    powerDao.updateRoute(id, name);
}

void PowerService::switchPowerForAll(int statusCode){

}

void PowerService::switchPowerForSingle(int id, int status){

}