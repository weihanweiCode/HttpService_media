#ifndef PISHTTP_POWER_H
#define PISHTTP_POWER_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "DatabaseConnectionPool.h"
 
struct PowerDto {
    int id;    
    std::string name;
    int cabinetId;
};
 
class PowerDao {
    
public:    
    nlohmann::json getRouteList(int cabinetId);
    void updateRoute(int id, const std::string& name);
};
#endif //PISHTTP_POWER_H
