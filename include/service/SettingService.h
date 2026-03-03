#ifndef PISHTTP_SETTING_SERVICE_H
#define PISHTTP_SETTING_SERVICE_H
#include <string>
#include "dao/SettingDao.h"
#include "service/FileService.h"

#pragma once

class SettingService{
    public:
        bool isConsoleDirected;
            
        nlohmann::json getBasicSetting();
        void updateBasicSetting(int newLanguage, int backgroundColour, 
            const std::string& masterIp, const std::string& slaveIp);

        nlohmann::json getScheduledProgram();
        void updateScheduledProgram(const std::string& startTime, const std::string& endTime, int programId, int isRecycled);

        nlohmann::json getBgcolorData();
        nlohmann::json getLanguageData();

        void importAllFiles();
        void backupAllFiles();
    private:
        SettingDao settingDao;        
        FileService fileService;
    };
#endif //PISHTTP_SETTING_SERVICE_H
