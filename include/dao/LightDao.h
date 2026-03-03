
#ifndef PISHTTP_LIGHT_DAO_H
#define PISHTTP_LIGHT_DAO_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "DatabaseConnectionPool.h"

// 定义 json 类型别名
using json = nlohmann::json;
struct LightDto {
    int id;
    std::string name;
    int lightType;    
    float duration;
    int orderId;
    int port1;
    std::string param1;
    int port2;
    std::string param2;
    int port3;
    std::string param3;
    int port4;
    std::string param4;

    LightDto(){

    }
    
    LightDto(
        std::string name,
        int lightType,
        float duration,
        int port1,
        std::string param1,
        int port2,
        std::string param2,
        int port3,
        std::string param3,
        int port4,
        std::string param4
    ) {
        this-> name = name;
        this-> lightType = lightType;
        this-> duration = duration;
        this-> port1 = port1;
        this-> param1 = param1;
        this-> port2 = port2;
        this-> param2 = param2;
        this-> port3 = port3;
        this-> param3 = param3;
        this-> port4 = port4;
        this-> param4 = param4;        
    }
        
    LightDto(
        std::string name,
        int lightType,
        float duration,
        int port1,
        std::string recordName1,
        std::string param1,
        int port2,
        std::string recordName2,
        std::string param2,
        int port3,
        std::string recordName3,
        std::string param3,
        int port4,
        std::string recordName4,
        std::string param4
    ) {
        this-> name = name;
        this-> lightType = lightType;
        this-> duration = duration;
        this-> port1 = port1;
        this-> param1 = param1;
        this-> port2 = port2;
        this-> param2 = param2;
        this-> port3 = port3;
        this-> param3 = param3;
        this-> port4 = port4;
        this-> param4 = param4;        
    }    
};

class LightDao {
    
public:    
    nlohmann::json  getLightList(int lightType1, int lightType2);
    nlohmann::json findLightList(int lightType1, int lightType2, const std::string& name);

    LightDto findLight(int id);
    void updateLight(int id, const std::string& name);    
    
    void sortLights(std::vector<int> ids);
    void delLight(int id);
    void delLights(const std::string& ids);
    
    void saveLight(LightDto lightDto);

    bool hasDuplicateName(std::string lightName);

};
#endif //PISHTTP_LIGHT_DAO_H

