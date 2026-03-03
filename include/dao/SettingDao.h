#ifndef PISHTTP_SETTINGDAO_H
#define PISHTTP_SETTINGDAO_H

#pragma once
#include <sqlite3.h>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "dao/DatabaseConnectionPool.h" 


class SettingDao {
    public:        
        nlohmann::json getBasicSetting();
        void updateBasicSetting(int newLanguage, int backgroundColour, 
            const std::string& masterIp, const std::string& slaveIp);

        nlohmann::json getScheduledProgram();
        void updateScheduledProgram(const std::string& startTime, const std::string& endTime, int programId, int isRecycled);        
    };        
    
#endif //PISHTTP_SETTINGDAO_H
