#include "service/LightService.h"
#include "dao/Globals.h"
#include <sstream>
#include <list>
#include <iostream>
#include <string>
#include <cstdio>

using json = nlohmann::json;
const std::string light_resource_folder = "/app/resource/light/"; 
const std::string light_backup_folder = "/app/backup/light/"; 

//传入: 灯光，灯具，通道
nlohmann::json LightService::getLightsByType(int lightType) {
    return lightDao.getLightList(lightType, lightType);
}

//包括：灯具，通道
nlohmann::json LightService::getLightsForScene(){
    return lightDao.getLightList(light_type_scene_lamp, light_type_scene_channel);
}

nlohmann::json LightService::findLightList(const std::string& name){
    return lightDao.findLightList(light_type_light, light_type_light, name);
}

nlohmann::json LightService::findLightsForScene(const std::string& name){
    return lightDao.findLightList(light_type_scene_lamp, light_type_scene_channel, name);
}

//用以在修改页面显示场景明细
json LightService::findLight(int id) {
    LightDto lightDto = lightDao.findLight(id);
    nlohmann::json itemjson;

    if(lightDto.id > 0) {
        itemjson["id"] = lightDto.id;
        itemjson["name"] = lightDto.name;
        itemjson["lightType"] = lightDto.lightType;
        itemjson["portId1"] = lightDto.port1;
        itemjson["recordParam1"] = lightDto.param1;
        itemjson["portId2"] = lightDto.port2;
        itemjson["recordParam2"] = lightDto.param2;
        itemjson["portId3"] = lightDto.port3;
        itemjson["recordParam3"] = lightDto.param3;
        itemjson["portId4"] = lightDto.port4;
        itemjson["recordParam4"] = lightDto.param4;        
    }
    return itemjson;    
}

void LightService::updateLight(int id, const std::string& newName) {  
    lightDao.updateLight(id, newName);        
    // LightDto light = lightDao.findLight(id);
    // std::string originName = light_resource_folder + light.name;
    // std::string destName = light_resource_folder + newName;

    // if (std::rename(originName.c_str(), destName.c_str()) == 0) {
    //     lightDao.updateLight(id, newName);        
    // } else {
    //     std::perror("文件重命名失败");
    // }
}

std::string LightService::delLight(int id) {
    std::string message = "success";
    bool isUsed = programDao.findProgram(light_type, id);

    if(isUsed){
        message = "used by program";
    } else {
        LightDto light = lightDao.findLight(id);
        std::string name = light_resource_folder + light.name;
    
        if (!std::filesystem::exists(name.c_str()) || std::remove(name.c_str()) == 0) {
            lightDao.delLight(id);
        } else {
            std::perror("文件删除失败");
        }
    }
    return message;
}


// std::string LightService::delLights(const std::string& ids) {
//     std::stringstream ss(ids);
//     std::string id;
//     while (std::getline(ss, id, '-')) {
//         LightDto light = lightDao.findLight(std::stoi(id));
//         std::string name = light_resource_folder + light.name;

//         if (std::remove(name.c_str()) == 0) {
//             lightDao.delLight(std::stoi(id));
//         } else {
//             std::perror("文件删除失败");
//         }                    
//         std::cout << "delete id: " << id << std::endl;
//     }
// }


std::string LightService::delLights(const std::string& ids) {
    std::string message = "success";    
    std::stringstream ss(ids);
    std::string id;

    while (std::getline(ss, id, '-')) {    
        int i_id = std::stoi(id);        
        bool isUsed = programDao.findProgram(video_type, i_id);
        if(isUsed){
            message = "remaining lights used by program";
        } else {
            LightDto light = lightDao.findLight(std::stoi(id));
            std::string name = light_resource_folder + light.name;
                
            if (!std::filesystem::exists(name.c_str()) || std::remove(name.c_str()) == 0) {
                lightDao.delLight(std::stoi(id));
            } else {
                std::perror("文件删除失败");
            }            
            std::cout << "delete id: " << id << std::endl;
        }
    }

    return message;
}


void LightService::playLight(int id) {    
    // std::cout << "playLight: "  << light_resource_folder + name << std::endl;
    LightDto lightDto = lightDao.findLight(id);
}

void LightService::stopLight(int id) {    
    // std::cout << "playLight: "  << light_resource_folder + name << std::endl;
    LightDto lightDto = lightDao.findLight(id);
}

nlohmann::json LightService::getLightTypesOfScene(){
    nlohmann::json itemJson;
    itemJson["1"] = "light";    
    itemJson["2"] = "channel";    
    return itemJson;    
}

void LightService::sortLights(std::vector<int> ids){
    lightDao.sortLights(ids);
}

nlohmann::json LightService::getToImportedLights(){    
    const std::vector<std::string> file_extensions = {".rec"};
    return fileService.getFileNames(light_backup_folder, file_extensions);
}

void LightService::importLights(std::vector<std::string> lights){
    printf("import light\n");
    fileService.importFiles(light_backup_folder, light_resource_folder, lights);
}
