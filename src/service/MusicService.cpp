#include "service/MusicService.h"
#include <sstream>
#include <list>
#include <iostream>
#include <string>
#include <cstdio>
#include "service/FileService.h"
#include "dao/Globals.h"

using json = nlohmann::json;
const std::string music_resource_folder = "/app/resource/music/";
const std::string music_backup_folder = "/app/backup/music/";

nlohmann::json MusicService::getMusicList(int includeEmptyItem){
    json result;
    if(includeEmptyItem == 1){
        json itemJson;
        itemJson["id"] = -1;
        itemJson["name"] = "无音乐";
        result.push_back(itemJson);    
    }

    std::vector<MusicDto> musics = musicDao.getMusicList();
    for (MusicDto music : musics) {
        json itemJson;
        itemJson["id"] = music.id;
        itemJson["name"] = music.name;
        result.push_back(itemJson);
    }
    return result;
}

json MusicService::getMusicListWithEmpty(){
    json result;
    json itemJson;
    itemJson["id"] = -1;
    itemJson["name"] = "无音乐";
    result.push_back(itemJson);

    std::vector<MusicDto> musics = musicDao.getMusicList();
    for (MusicDto music : musics) {
        json itemJson;
        itemJson["id"] = music.id;
        itemJson["name"] = music.name;
        result.push_back(itemJson);
    }
    return result;
}

nlohmann::json MusicService::findMusicList(const std::string& name){
    return musicDao.findMusicList(name);
}

void MusicService::updateMusic(int id, const std::string& newName) {  
    MusicDto music = musicDao.findMusic(id);
    std::string originName = music_resource_folder + music.name;
    std::string destName = music_resource_folder + newName;

    if (std::rename(originName.c_str(), destName.c_str()) == 0) {
        musicDao.updateMusic(id, newName);       
    } else {
        std::perror("文件重命名失败");
    }
}

std::string MusicService::delMusic(int id) {
    std::string message = "success";
    bool isUsed = programDao.findProgram(music_type, id);    

    if(isUsed){
        message = "used by program";
    } else {
        MusicDto music = musicDao.findMusic(id);
        std::string name = music_resource_folder + music.name;
    
        if (!std::filesystem::exists(name.c_str()) || std::remove(name.c_str()) == 0) {
            musicDao.delMusic(id);
        } else {
            message = "fail to delete this file";
        }        
    }

    return message;
}


std::string MusicService::delMusics(const std::string& ids) {
    std::string message = "success";    
    std::stringstream ss(ids);
    std::string id;
    while (std::getline(ss, id, '-')) {  
        int i_id = std::stoi(id);              
        bool isUsed = programDao.findProgram(music_type, i_id);
        if(isUsed){
            message = "remaining music used by program";
        } else {
            MusicDto music = musicDao.findMusic(i_id);
            std::string name = music_resource_folder + music.name;          

            if (!std::filesystem::exists(name.c_str()) || std::remove(name.c_str()) == 0) {
                musicDao.delMusic(i_id);
            } else {
                std::perror("文件删除失败");
            }
            std::cout << "delete id: " << id << std::endl;
        }
    }
    return message;
}

void MusicService::playMusic(int id) {
    printf("play music\n");
    MusicDto music = musicDao.findMusic(id);
    MediaService::instance().play(music_resource_folder + music.name);
}

nlohmann::json MusicService::getToImportedMusics(){    
    const std::vector<std::string> file_extensions = {".mp3", ".wav", ".flac", ".aac", ".ogg"};
    return fileService.getFileNames(music_backup_folder, file_extensions);
}

void MusicService::importMusics(std::vector<std::string> musics){
    printf("import music\n");
    fileService.importFiles(music_backup_folder, music_resource_folder, musics);
    musicDao.insertMusics(musics);
}
