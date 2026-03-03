#ifndef PISHTTP_IMAGE_SERVICE_H
#define PISHTTP_IMAGE_SERVICE_H
#include <string>
#include "dao/ImageDao.h"
#include "dao/ProgramDao.h"
#include "service/MediaService.h"
#include "service/FileService.h"

#pragma once

class ImageService{
    public:
        nlohmann::json getImageList(int includeEmptyItem);
        nlohmann::json getImageListWithEmpty();
        nlohmann::json findImageList(const std::string& name);        
        void updateImage(int id, const std::string& name);
        std::string delImage(int id);
        std::string delImages(const std::string& ids);
        void playImage(int id);   
        nlohmann::json getToImportedImages();
        void importImages(std::vector<std::string> images);

    private:
        ImageDao imageDao;        
        ProgramDao programDao;
        FileService fileService;
    };
#endif //PISHTTP_IMAGE_SERVICE_H