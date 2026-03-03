#ifndef PISHTTP_MUSICDAO_H
#define PISHTTP_MUSICDAO_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "DatabaseConnectionPool.h"
 
struct MusicDto {
    int id;
    std::string name;
};
 
class MusicDao {
    
public:    
    std::vector<MusicDto> getMusicList();
    nlohmann::json findMusicList(const std::string& name);
    void updateMusic(int id, const std::string& name);
    MusicDto findMusic(int id);
    void delMusic(int id);
    void delMusics(const std::string& ids);
    void insertMusics(std::vector<std::string> fileNames);
};
#endif //PISHTTP_MUSICDAO_H