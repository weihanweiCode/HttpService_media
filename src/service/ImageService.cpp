#include "service/ImageService.h"
#include "dao/Globals.h"
#include <sstream>
#include <list>
#include <iostream>
#include <string>
#include <cstdio>

using json = nlohmann::json;
const std::string image_resource_folder = "/app/resource/image/";
const std::string image_backup_folder = "/app/backup/image/";

json ImageService::getImageList(int includeEmptyItem){
    json result;
    if(includeEmptyItem == 1){
        json itemJson;
        itemJson["id"] = -1;
        itemJson["name"] = "无图片";
        result.push_back(itemJson);    
    }

    std::vector<ImageDto> images = imageDao.getImageList();
    for (ImageDto image : images) {
        json itemJson;
        itemJson["id"] = image.id;
        itemJson["name"] = image.name;
        result.push_back(itemJson);
    }
    return result;
}

json ImageService::getImageListWithEmpty(){
    json result;
    json itemJson;
    itemJson["id"] = -1;
    itemJson["name"] = "无图片";
    result.push_back(itemJson);

    std::vector<ImageDto> images = imageDao.getImageList();
    for (ImageDto image : images) {
        json itemJson;
        itemJson["id"] = image.id;
        itemJson["name"] = image.name;
        result.push_back(itemJson);
    }
    return result;
}

nlohmann::json ImageService::findImageList(const std::string& name){
    return imageDao.findImageList(name);
}

void ImageService::updateImage(int id, const std::string& newName) {  
    ImageDto image = imageDao.findImage(id);
    std::string originName = image_resource_folder + image.name;
    std::string destName = image_resource_folder + newName;

    if (std::rename(originName.c_str(), destName.c_str()) == 0) {
        imageDao.updateImage(id, newName);    
    } else {
        std::perror("文件重命名失败");
    }
}

std::string ImageService::delImage(int id) {
    bool isUsed = programDao.findProgram(3, id);
    std::string message = "success";

    if(isUsed){
        message = "used by program";
    } else {
        ImageDto image = imageDao.findImage(id);
        std::string name = image_resource_folder + image.name;
    
        if (!std::filesystem::exists(name.c_str()) || std::remove(name.c_str()) == 0) {
            imageDao.delImage(id);
        } else {
            message = "fail to delete this file";
        }
    }
    return message;
}

// void ImageService::delImages(const std::string& ids) {
//     std::stringstream ss(ids);
//     std::string id;
//     while (std::getline(ss, id, '-')) {
//         ImageDto image = imageDao.findImage(std::stoi(id));
//         std::string name = image_resource_folder + image.name;

//         if (std::remove(name.c_str()) == 0) {
//             imageDao.delImage(std::stoi(id));
//         } else {
//             std::perror("文件删除失败");
//         }
//         std::cout << "delete id: " << id << std::endl;
//     }
// }

std::string ImageService::delImages(const std::string& ids) {
    std::string message = "success";    
    std::stringstream ss(ids);
    std::string id;

    while (std::getline(ss, id, '-')) {    
        int i_id = std::stoi(id);    
        bool isUsed = programDao.findProgram(image_type, i_id);
        if(isUsed){
            message = "remaining images used by program";
        } else {
            ImageDto image = imageDao.findImage(i_id);
            std::string name = image_resource_folder + image.name;
            
            if (!std::filesystem::exists(name.c_str()) || std::remove(name.c_str()) == 0) {
                imageDao.delImage(i_id);
            } else {
                std::perror("文件删除失败");
            }            
            std::cout << "delete id: " << id << std::endl;
        }
    }
    
    return message;
}


void ImageService::playImage(int id) {
    ImageDto image = imageDao.findImage(id);
    printf("play image\n");
}


nlohmann::json ImageService::getToImportedImages(){    
    const std::vector<std::string> file_extensions = {".jpeg", ".jpg"};
    return fileService.getFileNames(image_backup_folder, file_extensions);
}

void ImageService::importImages(std::vector<std::string> images){
    printf("import images\n");
    fileService.importFiles(image_backup_folder, image_resource_folder, images);
    imageDao.insertImages(images);
}
