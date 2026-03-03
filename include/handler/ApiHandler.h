#ifndef PISHTTP_APIHANDLER_H
#define PISHTTP_APIHANDLER_H
#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include "dao/UserDao.h"
#include "dao/LightDao.h"
#include "dao/MusicDao.h"
#include "dao/ImageDao.h"
#include "dao/VideoDao.h"
#include "dao/ProgramDao.h"
#include "dao/Globals.h"
#include "service/ProgramService.h"
#include "service/ProgramManagerService.h"
#include "service/LightService.h"
#include "service/LightRecordService.h"
#include "service/PowerService.h"
#include "service/MusicService.h"
#include "service/VideoService.h"
#include "service/ImageService.h"
#include "service/SettingService.h"

#pragma once
using namespace Pistache;

class ApiHandler : public Http::Handler {
    public:
        HTTP_PROTOTYPE(ApiHandler)      
        void onRequest(const Http::Request& request, Http::ResponseWriter response) override;
        
    private:
        UserDao userDao; 
        ProgramService programService;
        ProgramManagerService programManagerService;
        LightService lightService;
        LightRecordService lightRecordService;
        PowerService powerService;
        MusicService musicService;
        VideoService videoService;
        ImageService imageService;
        SettingService settingService;
    };    
#endif //PISHTTP_APIHANDLER_H
