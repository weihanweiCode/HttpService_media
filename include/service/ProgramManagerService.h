#ifndef PISHTTP_PROGRAM_MANAGER_H
#define PISHTTP_PROGRAM_MANAGER_H
#include <string>
#include "dao/ProgramDao.h"
#include "dao/LightDao.h"
#include "service/MediaService.h"

#pragma once

class ProgramManagerService {
    public: 
        //节目管理页面
        nlohmann::json getProgramList();
        nlohmann::json findProgramList(const std::string& name);
        void delProgram(int id);	
        void playProgram(int programId);        
        void sortPrograms(std::vector<int> ids);
        
        //初始更新页面数据
        nlohmann::json findProgram(int id);

        //更新节目
        void updateProgram(int id, const std::string& name, int lightId, int musicId, int videoId, int imgId);

        //保存新节目
        void saveProgram(const std::string& name, int lightId, int musicId, int videoId, int imgId);        
        
    private:
        LightDao lightDao;
        ProgramDao programDao;        
    };
#endif //PISHTTP_PROGRAM_MANAGER_H
