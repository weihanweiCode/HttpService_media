#ifndef PISHTTP_LIGHT_SERVICE_H
#define PISHTTP_LIGHT_SERVICE_H
#include <string>
#include <nlohmann/json.hpp>
#include "dao/LightDao.h"
#include "dao/ProgramDao.h"
#include "service/FileService.h"

#pragma once

class LightService{
    public:
        //传入: 灯光，灯具，通道
        nlohmann::json getLightsByType(int lightType);

        //包括：灯具，通道
        nlohmann::json getLightsForScene();
        nlohmann::json findLightList(const std::string& name);
        nlohmann::json findLightsForScene(const std::string& name);
        
        std::string delLight(int id);
        std::string delLights(const std::string& ids);
        void playLight(int id);
        void stopLight(int id);
    
        //用以在修改页面显示场景明细
        nlohmann::json findLight(int id);
        void updateLight(int id, const std::string& newName);

        nlohmann::json getLightTypesOfScene();
        void sortLights(std::vector<int> ids);

        //导入灯光
        nlohmann::json getToImportedLights();
        void importLights(std::vector<std::string> lights);

    private:
        LightDao lightDao;
        ProgramDao programDao;
        FileService fileService;
    };
#endif //PISHTTP_LIGHT_SERVICE_H
