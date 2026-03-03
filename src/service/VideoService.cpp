#include "service/VideoService.h"
#include "dao/Globals.h"
#include <sstream>
#include <list>
#include <iostream>
#include <string>
#include <cstdio>

using json = nlohmann::json;
const std::string video_resource_folder = "/app/resource/video/";
const std::string video_backup_folder = "/app/backup/video/";

nlohmann::json VideoService::getVideoList(int includeEmptyItem){
    json result;
    if(includeEmptyItem == 1){
        json itemJson;
        itemJson["id"] = -1;
        itemJson["name"] = "无视频";
        result.push_back(itemJson);    
    }

    std::vector<VideoDto> videos = videoDao.getVideoList();
    for (VideoDto video : videos) {
        json itemJson;
        itemJson["id"] = video.id;
        itemJson["name"] = video.name;
        result.push_back(itemJson);
    }
    return result;
}

json VideoService::getVideoListWithEmpty(){
    json result;
    json itemJson;
    itemJson["id"] = -1;
    itemJson["name"] = "无视频";
    result.push_back(itemJson);

    std::vector<VideoDto> videos = videoDao.getVideoList();
    for (VideoDto video : videos) {
        json itemJson;
        itemJson["id"] = video.id;
        itemJson["name"] = video.name;
        result.push_back(itemJson);
    }
    return result;
}

nlohmann::json VideoService::findVideoList(const std::string& name){
    return videoDao.findVideoList(name);
}

void VideoService::updateVideo(int id, const std::string& newName) {  
    VideoDto video = videoDao.findVideo(id);
    std::string originName = video_resource_folder + video.name;
    std::string destName = video_resource_folder + newName;

    if (std::rename(originName.c_str(), destName.c_str()) == 0) {
        videoDao.updateVideo(id, newName);    
    } else {
        std::perror("文件重命名失败");
    }
}

std::string VideoService::delVideo(int id) {
    std::string message = "success";
    bool isUsed = programDao.findProgram(video_type, id);

    if(isUsed){
        message = "used by program";
    } else {
        VideoDto video = videoDao.findVideo(id);
        std::string name = video_resource_folder + video.name;
    
        if (!std::filesystem::exists(name.c_str()) || std::remove(name.c_str()) == 0) {
            videoDao.delVideo(id);
        } else {
            message = "fail to delete this file";
        }    
    }
    return message;
}


std::string VideoService::delVideos(const std::string& ids) {
    std::string message = "success";    
    std::stringstream ss(ids);
    std::string id;

    while (std::getline(ss, id, '-')) {    
        int i_id = std::stoi(id);        
        bool isUsed = programDao.findProgram(video_type, i_id);
        if(isUsed){
            message = "remaining videos used by program";
        } else {
            VideoDto video = videoDao.findVideo(i_id);
            std::string name = video_resource_folder + video.name;
            
            if (!std::filesystem::exists(name.c_str()) || std::remove(name.c_str()) == 0) {
                videoDao.delVideo(i_id);
            } else {
                std::perror("文件删除失败");
            }            
            std::cout << "delete id: " << id << std::endl;
        }
    }

    return message;
}

// void VideoService::delVideos(const std::string& ids) {
//     std::stringstream ss(ids);
//     std::string id;
//     while (std::getline(ss, id, '-')) {        
//         VideoDto video = videoDao.findVideo(std::stoi(id));
//         std::string name = video_resource_folder + video.name;
        
//         if (std::remove(name.c_str()) == 0) {
//             videoDao.delVideo(std::stoi(id));
//         } else {
//             std::perror("文件删除失败");
//         }            
//         std::cout << "delete id: " << id << std::endl;
//     }
// }


void VideoService::playVideo(int id) {
    printf("play video\n");
    VideoDto video = videoDao.findVideo(id);
    MediaService::instance().play(video_resource_folder + video.name);
}

nlohmann::json VideoService::getToImportedVideos(){    
    const std::vector<std::string> file_extensions = {".mp4"};
    return fileService.getFileNames(video_backup_folder, file_extensions);
}

void VideoService::importVideos(std::vector<std::string> videos){
    printf("import video\n");
    fileService.importFiles(video_backup_folder, video_resource_folder, videos);
    videoDao.insertVideos(videos);
}
