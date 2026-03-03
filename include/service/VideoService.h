#ifndef PISHTTP_VIDEO_SERVICE_H
#define PISHTTP_VIDEO_SERVICE_H
#include <string>
#include "dao/VideoDao.h"
#include "dao/ProgramDao.h"
#include "service/MediaService.h"
#include "service/FileService.h"

#pragma once

class VideoService{
    public:
        nlohmann::json getVideoList(int includeEmptyItem);
        nlohmann::json getVideoListWithEmpty();
        nlohmann::json findVideoList(const std::string& name);        
        void updateVideo(int id, const std::string& name);
        std::string delVideo(int id);
        std::string delVideos(const std::string& ids);
        void playVideo(int id);   
        nlohmann::json getToImportedVideos();
        void importVideos(std::vector<std::string> videos);

    private:
        VideoDao videoDao;     
        ProgramDao programDao;
        FileService fileService;   
    };
#endif //PISHTTP_VIDEO_SERVICE_H