#ifndef PISHTTP_MUSIC_SERVICE_H
#define PISHTTP_MUSIC_SERVICE_H
#include <string>
#include "dao/MusicDao.h"
#include "dao/ProgramDao.h"
#include "service/MediaService.h"
#include "service/FileService.h"

#pragma once

class MusicService{
    public:
        nlohmann::json getMusicList(int includeEmptyItem);
        nlohmann::json getMusicListWithEmpty();
        nlohmann::json findMusicList(const std::string& name);        
        void updateMusic(int id, const std::string& name);
        std::string delMusic(int id);
        std::string delMusics(const std::string& ids);
        void playMusic(int id);   
        nlohmann::json getToImportedMusics();
        void importMusics(std::vector<std::string> musics);

    private:
        MusicDao musicDao;        
        ProgramDao programDao;
        FileService fileService;
    };
#endif //PISHTTP_MUSIC_SERVICE_H
