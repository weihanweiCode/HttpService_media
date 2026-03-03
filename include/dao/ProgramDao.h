#ifndef PISHTTP_PROGRAM_H
#define PISHTTP_PROGRAM_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "DatabaseConnectionPool.h"
 
struct ProgramDto {
    int id;
    std::string name;
	int orderId;
	int lightId;
	int musicId;
	int videoId;
	int imgId;
};
 
// SELECT p.id, p.name, orderId, lightId, l.name, musicId, m.name, videoId, v.name, imgId, i.name, l.duration FROM program p 

struct ProgramDetailDto {
    int id;
    std::string name;
	int orderId;
	int lightId;	
	std::string lightName;
	int musicId;
	std::string musicName;
	int videoId;
	std::string videoName;
	int imgId;
	std::string imgName;
	int duration;
};

class ProgramDao {
    
public:    

	nlohmann::json getProgramDetails();
    nlohmann::json getProgramList();
    nlohmann::json findProgramList(const std::string& name);
    void updateProgram(int id, const std::string& name, int lightId, int musicId, int videoId, int imgId);
	void saveProgram(const std::string& name, int lightId, int musicId, int videoId, int imgId);
	ProgramDetailDto findProgram(int id);
    void delProgram(int id);	
	void sortPrograms(std::vector<int> ids);
	bool findProgram(int type, int id);

private:
	std::string extractName(const std::string& filename) {
		if (filename.empty()) {
			return "";
		}
		
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring wfilename = converter.from_bytes(filename);

		size_t dot_pos = wfilename.find(L'.');
		if (dot_pos == std::wstring::npos) return filename;

		return converter.to_bytes(wfilename.substr(0, dot_pos));
	}	
};
#endif //PISHTTP_PROGRAM_H
