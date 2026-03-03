#ifndef PISHTTP_PROGRAM_SERVICE_H
#define PISHTTP_PROGRAM_SERVICE_H
#include "dao/ProgramDao.h"
#include "dao/LightDao.h"
#include "service/MediaService.h"

#pragma once

class ProgramService{
    public:
        nlohmann::json getProgramDetails();
        void playProgram(int id);
        void pauseProgram(int id);
        void resumeProgram(int id);
        void recycleProgram(int id);
        void blackout(int status);
        void adjustVolume(int volumn);
    private:
        LightDao lightDao;
        ProgramDao programDao; 
    };    
#endif //PISHTTP_PROGRAM_SERVICE_H
