#ifndef PISHTTP_LIGHT_RECORD_SERVICE_H
#define PISHTTP_LIGHT_RECORD_SERVICE_H
#include <string>
#include <nlohmann/json.hpp>
#include "dao/LightDao.h"

#pragma once

class LightRecordService{
    public:    
        //灯光录制页面
        bool startRecordLight(int lightType, LightDto lightDto);
        void stopRecordLight(int lightType);
        void testRecordedLight(int lightType);
        void stopTestRecordedLight(int lightType);
        void truncRecordedLight(int lightType, int milliSeconds);
        void saveLight(int lightType,LightDto lightDto);
        std::string verifyLightName(std::string lightName);
    private:
        LightDao lightDao;
        std::string parseMappingName(int lightType);
    };
#endif //PISHTTP_LIGHT_RECORD_SERVICE_H
