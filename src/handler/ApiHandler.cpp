#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <nlohmann/json.hpp>
#include "handler/HttpUtil.h"
#include "handler/ApiHandler.h"
#include <sstream> 

using namespace Pistache;
using json = nlohmann::json;
std::string success = "success";


void ApiHandler::onRequest(const Http::Request& request, Http::ResponseWriter response) 
{
    auto path = urlDecode(request.resource());
    auto method = request.method();
    std::cout << "---------path: "  << path << std::endl;

    //用户登陆
    if (path == "/user/login" && method == Http::Method::Post) {     
        json data = json::parse(request.body());
        std::cout << "user name: "  << data["username"] << std::endl;
        std::cout << "user password: "  << data["password"] << std::endl;

        json user = userDao.verifyUser(data["username"], data["password"]);
        std::cout << "login result: "  << user << std::endl;
        sendResponse(response, user.dump());
        // sendResponse(response, std::to_string(0));
    //修改密码
    } else if (path == "/user/change_password" && method == Http::Method::Post) {        
        json data = json::parse(request.body());
        std::cout << "---------change password: "  << data << std::endl;
        int id = std::stoi(data["id"].get<std::string>());
        bool ret = userDao.updatePassword(id, data["originalPassword"], data["newPassword"]);
        // sendResponse(response, std::to_string(ret));
        sendResponse(response, boolToStr(ret));
        
    //节目播放列表
    } else if (path.find("/program/list")  == 0) { 
        sendResponse(response, programService.getProgramDetails().dump());
    //节目播放
    } else if (path.find("/program/play/")  == 0) {
        int id = std::stoi(path.substr(14));
        programService.playProgram(id);
        sendResponse(response, success);
    //暂停
    } else if (path.find("/program/pause/")  == 0) { 
        int id = std::stoi(path.substr(15));  
        programService.pauseProgram(id);        
        sendResponse(response, success);
    //继续播放
    } else if (path.find("/program/resume/")  == 0) { 
        int id = std::stoi(path.substr(16));  
        programService.resumeProgram(id);        
        sendResponse(response, success);
    //循环播放
    } else if (path.find("/program/recycle/")  == 0) { 
        int id = std::stoi(path.substr(17));  
        programService.recycleProgram(id);        
        sendResponse(response, success);
    //黑场
    } else if (path.find("/program/blackout/")  == 0) { 
        int status = std::stoi(path.substr(18));  
        programService.blackout(status);
        sendResponse(response, success);
    //音量调整
    } else if (path.find("/program/adjust_volume/")  == 0) { 
        int volume = std::stoi(path.substr(23));  
        programService.adjustVolume(volume);
        sendResponse(response, success);
    //节目中停止场景
    } else if (path.find("/scene/pause/")  == 0) { 
        lightService.stopLight(std::stoi(path.substr(12)));  
        sendResponse(response, success);

    //场景列表
    } else if (path  == "/scene/list") {
        auto sceneList = lightService.getLightsForScene();  
        sendResponse(response, sceneList.dump());  
    //场景搜索
    } else if (path.find("/scene/find/")  == 0) {     
        std::string name = path.substr(12);   
        auto sceneList = lightService.findLightsForScene(name);  
        sendResponse(response, sceneList.dump());  
    //场景下拉列表过滤
    } else if (path.find("/scene/filter/")  == 0) {         
        int sceneId = std::stoi(path.substr(14));  
        auto sceneList = lightService.getLightsByType(sceneId);   
        sendResponse(response, sceneList.dump());          
    //场景播放
    } else if (path.find("/scene/play/")  == 0) { 
        lightService.playLight(std::stoi(path.substr(12)));  
        sendResponse(response, success);
    //场景删除
    } else if (path.find("/scene/del/")  == 0) { 
        int id = std::stoi(path.substr(11));  
        lightService.delLight(id);  
        sendResponse(response, success);   
    //场景明细(编辑页面显示明细)
    } else if (path.find("/scene/find_detail/")  == 0) { 
        int id = std::stoi(path.substr(19)); 
        auto sceneDetail = lightService.findLight(id);  
        sendResponse(response, sceneDetail.dump());           
    //场景更新(只更新名称)
    } else if (path.find("/scene/update/")  == 0) { 
        std::istringstream iss(path.substr(14));  
        std::string idStr, name; 
        std::getline(iss, idStr, '/'); 
        std::getline(iss, name); 
        int id = std::stoi(idStr); 
        lightService.updateLight(id,  name); 
        sendResponse(response, success);               
    //场景类别(用以初始化场景下拉列表)
    } else if (path.find("/scene/sceneTypes/")  == 0) {         
        auto sceneList = lightService.getLightTypesOfScene();   
        sendResponse(response, sceneList.dump());  
    //场景排序
    } else if (path.find("/scene/sort")  == 0) { 
        json data = json::parse(request.body());
        std::cout << "---------scene sort: "  << data << std::endl;
        std::vector<int> ids = data["newSceneIds"].get<std::vector<int>>();        
        lightService.sortLights(ids);
        sendResponse(response, success);

/*
    //开始录制场景
    } else if (path.find("/scene/record/startRecord/")  == 0) { 
        std::string name = lightService.startRecordLight();        
        sendResponse(response, success);
    //停止录制
    } else if (path.find("/scene/record/stopRecord/")  == 0) {         
        lightService.stopRecordLight("tmp.rec");
        sendResponse(response, success);
    //测试播放
    } else if (path.find("/scene/record/testRecord/")  == 0) {         
        lightService.testRecordedLight("tmp.rec");
        sendResponse(response, success);     
    //停止测试播放
    } else if (path.find("/scene/record/stopTestRecord/")  == 0) {         
        lightService.stopTestRecordedLight("tmp.rec");
        sendResponse(response, success);     
    //删除无效dmx灯光(毫秒)
    } else if (path.find("/scene/record/truncRecord/")  == 0) {            
        int milliseconds = std::stoi(path.substr(26));  
        lightService.truncRecordedLight("tmp.rec", milliseconds);
        sendResponse(response, success);                        
    //保存场景
    } else if (path.find("/scene/record/saveRecord")  == 0) {    
        json data = json::parse(request.body());
        LightDto lightDto(
            data["name"], getOptionalInt(data, "lightType"), data["duration"].get<float>(), 
            getOptionalInt(data, "portId1"), getOptionalString(data, "recordParam1"),
            getOptionalInt(data, "portId2"), getOptionalString(data, "recordParam2"), 
            getOptionalInt(data, "portId3"), getOptionalString(data, "recordParam3"), 
            getOptionalInt(data, "portId4"), getOptionalString(data, "recordParam4")
        );
        lightService.saveLight(lightDto);
        sendResponse(response, success);
*/

    //节目管理列表
    } else if (path  == "/program/manager/list") {
        auto programList = programManagerService.getProgramList();  
        sendResponse(response, programList.dump());  
    //节目搜索
    } else if (path.find("/program/manager/find/")  == 0) { 
        std::string name = path.substr(22);
        auto programList = programManagerService.findProgramList(name);  
        sendResponse(response, programList.dump());  
    //节目播放
    } else if (path.find("/program/manager/play/")  == 0) { 
        int id = std::stoi(path.substr(22));
        programManagerService.findProgram(id);  
        sendResponse(response, success);
    //节目删除
    } else if (path.find("/program/manager/del/")  == 0) {
        int id = std::stoi(path.substr(21));
        programManagerService.delProgram(id);  
        sendResponse(response, success);
    //节目排序
    } else if (path.find("/program/manager/sort")  == 0) { 
        json data = json::parse(request.body());
        std::cout << "---------program sort data: "  << data << std::endl;
        std::vector<int> ids = data["newSceneIds"].get<std::vector<int>>();
        programManagerService.sortPrograms(ids);
        sendResponse(response, success);
    //节目明细（显示在更新页面）
    } else if (path.find("/program/manager/find_detail/")  == 0) { 
        int id = std::stoi(path.substr(29)); 
        auto programDetail = programManagerService.findProgram(id);  
        std::cout << "---------program manager detail: "  << programDetail << std::endl;
        sendResponse(response, programDetail.dump());    
    //节目更新
    } else if (path == "/program/manager/update" && method == Http::Method::Post) {
        json data = json::parse(request.body());
        std::cout << "---------program manager update data: "  << data << std::endl;
        programManagerService.updateProgram(data["id"], data["name"], getOptionalInt(data, "lightId"), 
            getOptionalInt(data, "musicId"), getOptionalInt(data, "videoId"), getOptionalInt(data, "imgId"));
        sendResponse(response, success);
    //节目新建
    } else if (path == "/program/manager/save" && method == Http::Method::Post) {
        json data = json::parse(request.body());        
        programManagerService.saveProgram(data["name"], getOptionalInt(data, "lightId"), 
            getOptionalInt(data, "musicId"), getOptionalInt(data, "videoId"), getOptionalInt(data, "imgId"));
        sendResponse(response, success);

    //开始灯光录制
    } else if (path == "/light/record/startRecord") {
        json data = json::parse(request.body());
        std::cout << "startRecord: "  << data << std::endl;             

        int lightType = getOptionalInt(data, "lightType");
        LightDto lightDto(
            "", lightType, 0, 
            getOptionalInt(data, "portId1"), getOptionalString(data, "recordParam1"), 
            getOptionalInt(data, "portId2"), getOptionalString(data, "recordParam2"), 
            getOptionalInt(data, "portId3"), getOptionalString(data, "recordParam3"), 
            getOptionalInt(data, "portId4"), getOptionalString(data, "recordParam4")
        );
                
        lightRecordService.startRecordLight(lightType, lightDto);
        sendResponse(response, success);
    //停止录制
    } else if (path.find("/light/record/stopRecord/")  == 0) {     
        int lightType = std::stoi(path.substr(25));      
        lightRecordService.stopRecordLight(lightType);
        sendResponse(response, success);
    //测试灯光
    } else if (path.find("/light/record/testRecord/")  == 0) {  
        int lightType = std::stoi(path.substr(25));         
        lightRecordService.testRecordedLight(lightType);
        sendResponse(response, success);        
    //停止测试播放
    } else if (path.find("/light/record/stopTestRecord/")  == 0) {   
        int lightType = std::stoi(path.substr(29));        
        lightRecordService.stopTestRecordedLight(lightType);
        sendResponse(response, success);     
    //删除无效dmx灯光(毫秒)
    } else if (path.find("/light/record/truncRecord/")  == 0) {  
        std::istringstream iss(path.substr(26));  
        std::string lightType, milliseconds; 
        std::getline(iss, lightType, '/'); 
        std::getline(iss, milliseconds);
        lightRecordService.truncRecordedLight(std::stoi(lightType), std::stoi(milliseconds));
        sendResponse(response, success);
    //保存灯光
    } else if (path.find("/light/record/saveRecord")  == 0) {
        json data = json::parse(request.body());
        std::cout << "saveRecord: "  << data << std::endl;

        int lightType = getOptionalInt(data, "lightType");
        LightDto lightDto(
            data["name"], lightType, data["duration"].get<float>(), 
            getOptionalInt(data, "portId1"), getOptionalString(data, "recordParam1"), 
            getOptionalInt(data, "portId2"), getOptionalString(data, "recordParam2"), 
            getOptionalInt(data, "portId3"), getOptionalString(data, "recordParam3"), 
            getOptionalInt(data, "portId4"), getOptionalString(data, "recordParam4")
        );
        lightRecordService.saveLight(lightType, lightDto);
        sendResponse(response, success);
    } else if (path.find("/light/record/verifyName/")  == 0) {           
        std::string isValidName = lightRecordService.verifyLightName(path.substr(25));
        sendResponse(response, isValidName);             

    //灯光列表
    } else if (path.find("/light/list")  == 0) {
        auto lightList = lightService.getLightsByType(light_type_light);  
        sendResponse(response, lightList.dump());  
    //灯光搜索
    } else if (path.find("/light/find/")  == 0) { 
        // std::string name = urlDecode(path.substr(21));          
        std::string name = path.substr(12);
        auto lightList = lightService.findLightList(name);  
        sendResponse(response, lightList.dump());  
    //灯光更新
    } else if (path.find("/light/update/")  == 0) { 
        std::istringstream iss(path.substr(14));  
        std::string idStr, name; 
        std::getline(iss, idStr, '/'); 
        std::getline(iss, name); 
        lightService.updateLight(std::stoi(idStr),  name); 
        sendResponse(response, success);
    //灯光播放
    } else if (path.find("/light/play/")  == 0) {
        lightService.playLight(std::stoi(path.substr(12)));  
        sendResponse(response, success);
    //灯光删除        
    } else if (path.find("/light/del/")  == 0) { 
        int id = std::stoi(path.substr(11));  
        lightService.delLight(id);  
        sendResponse(response, success);
    //灯光批量删除
    } else if (path.find("/light/batch_del/")  == 0) { 
        std::string ids = path.substr(17);  
        lightService.delLights(ids);  
        sendResponse(response, success);
    //灯光待导入列表
    } else if (path.find("/light/to_import")  == 0) {
        std::cout << "---------light to_import: "  << lightService.getToImportedLights() << std::endl;
        sendResponse(response, lightService.getToImportedLights().dump());
    //灯光导入
    } else if (path.find("/light/import")  == 0) {  
        json data = json::parse(request.body());
        std::vector<std::string> lights = data.get<std::vector<std::string>>();
        lightService.importLights(lights);
        sendResponse(response, success);

    
    //音乐列表
    } else if (path.find("/music/list/")  == 0) {
        sendResponse(response, musicService.getMusicList(std::stoi(path.substr(12))).dump());
    //音乐下拉（带空选项）
    // } else if (path  == "/music/list_with_empty") {
    //     auto musicList = musicService.getMusicListWithEmpty();  
    //     sendResponse(response, musicList.dump());                       
    //音乐搜索
    } else if (path.find("/music/find/")  == 0) { 
        std::string name = path.substr(12);          
        auto musicList = musicService.findMusicList(name);  
        sendResponse(response, musicList.dump());  
    //音乐更新
    } else if (path.find("/music/update/")  == 0) { 
        std::istringstream iss(path.substr(14));  
        std::string idStr, name; 
        std::getline(iss, idStr, '/'); 
        std::getline(iss, name); 
        musicService.updateMusic(std::stoi(idStr),  name); 
        sendResponse(response, success);
    //音乐播放
    } else if (path.find("/music/play/")  == 0) { 
        musicService.playMusic(std::stoi(path.substr(12)));  
        sendResponse(response, success);
    //音乐删除
    } else if (path.find("/music/del/")  == 0) { 
        std::cout << "---------music path: "  << path << std::endl;
        int id = std::stoi(path.substr(11));  
        std::cout << "music del id: "  << id << std::endl;
        musicService.delMusic(id);   
        sendResponse(response, success);
    //音乐批量删除
    } else if (path.find("/music/batch_del/")  == 0) {  
        std::string ids = path.substr(17);  
        musicService.delMusics(ids);
        sendResponse(response, success);
    //音乐待导入列表
    } else if (path.find("/music/to_import")  == 0) {
        sendResponse(response, musicService.getToImportedMusics().dump());
    //音乐导入
    } else if (path.find("/music/import")  == 0) {  
        json data = json::parse(request.body());
        std::vector<std::string> musics = data.get<std::vector<std::string>>();
        musicService.importMusics(musics);
        sendResponse(response, success);

    
    //视频列表
    } else if (path.find("/video/list/")  == 0) {
        auto videoList = videoService.getVideoList(std::stoi(path.substr(12)));  
        sendResponse(response, videoList.dump());  
    //视频下拉（带空选项）
    // } else if (path  == "/video/list_with_empty") {
    //     auto videoList = videoService.getVideoListWithEmpty();  
    //     sendResponse(response, videoList.dump());                               
    //视频搜索
    } else if (path.find("/video/find/")  == 0) { 
        std::string name = path.substr(12);          
        auto videoList = videoService.findVideoList(name);  
        sendResponse(response, videoList.dump());  
    //视频更新
    } else if (path.find("/video/update/")  == 0) { 
        std::istringstream iss(path.substr(14));  
        std::string idStr, name; 
        std::getline(iss, idStr, '/'); 
        std::getline(iss, name); 
        videoService.updateVideo(std::stoi(idStr),  name); 
        sendResponse(response, success);
    //视频播放
    } else if (path.find("/video/play/")  == 0) { 
        videoService.playVideo(std::stoi(path.substr(12)));  
        sendResponse(response, success);
    //视频删除        
    } else if (path.find("/video/del/")  == 0) { 
        int id = std::stoi(path.substr(11));  
        videoService.delVideo(id);  
        sendResponse(response, success);
    //视频批量删除
    } else if (path.find("/video/batch_del/")  == 0) { 
        std::string ids = path.substr(17);  
        videoService.delVideos(ids);  
        sendResponse(response, success);        
    //视频待导入列表
    } else if (path.find("/video/to_import")  == 0) {
        sendResponse(response, videoService.getToImportedVideos().dump());
    //视频导入
    } else if (path.find("/video/import")  == 0) {  
        json data = json::parse(request.body());
        std::vector<std::string> videos = data.get<std::vector<std::string>>();
        videoService.importVideos(videos);
        sendResponse(response, success);
         

    //图片列表
    } else if (path.find("/image/list/")  == 0) {
        auto imageList = imageService.getImageList(std::stoi(path.substr(12)));  
        sendResponse(response, imageList.dump());  
    //图片下拉（带空选项）
    // } else if (path  == "/image/list_with_empty") {
    //     auto imageList = imageService.getImageListWithEmpty();  
    //     sendResponse(response, imageList.dump());          
    //图片搜索
    } else if (path.find("/image/find/")  == 0) { 
        std::string name = path.substr(12);
        auto imageList = imageService.findImageList(name);  
        sendResponse(response, imageList.dump());  
    //图片更新
    } else if (path.find("/image/update/")  == 0) { 
        std::istringstream iss(path.substr(14));  
        std::string idStr, name; 
        std::getline(iss, idStr, '/'); 
        std::getline(iss, name); 
        imageService.updateImage(std::stoi(idStr),  name); 
        sendResponse(response, success);
    //图片显示
    } else if (path.find("/image/play/")  == 0) { 
        imageService.playImage(std::stoi(path.substr(12)));
        sendResponse(response, success);
    //图片删除
    } else if (path.find("/image/del/")  == 0) { 
        int id = std::stoi(path.substr(11));            
       sendResponse(response, imageService.delImage(id));
    //图片批量删除
    } else if (path.find("/image/batch_del/")  == 0) { 
        std::string ids = path.substr(17);  
        imageService.delImages(ids);
        sendResponse(response, success);
    //图片待导入列表
    } else if (path.find("/image/to_import")  == 0) {
        sendResponse(response, imageService.getToImportedImages().dump());
    //图片导入
    } else if (path.find("/image/import")  == 0) {  
        json data = json::parse(request.body());
        std::vector<std::string> images = data.get<std::vector<std::string>>();
        imageService.importImages(images);
        sendResponse(response, success);

    //电柜数量
    } else if (path.find("/power/cabinet_num")  == 0) { 
    //     std::cout << "---------power find--"   << std::endl;
    // } else if (path == "/power/cabinet_num" == 0) { 
        // std::cout << "---------call: /power/cabinet_num--" << std::endl;
        int cabinetNum = powerService.getCabinetNumber();
        sendResponse(response, std::to_string(cabinetNum));
    //每个电柜路线数量
    // } else if (path.find("/power/routes_per_cabinet/")  == 0) {    
    //     int routesPerCabinet = powerService.getRoutesPerCabinet();          
    //     sendResponse(response, std::to_string(routesPerCabinet));
    //电力总开关
    } else if (path.find("/power/switch_for_all/")  == 0) {
        int status = std::stoi(path.substr(22));
        powerService.switchPowerForAll(status);
        sendResponse(response, success);
    //单个路线开关
    // } else if (path.find("/power/switch_for_single/{id}/{status}/")  == 0) { 
    } else if (path.find("/power/switch_for_single/")  == 0) { 
        std::istringstream iss(path.substr(25));  
        std::string idStr, status;
        std::getline(iss, idStr, '/'); 
        std::getline(iss, status); 
        powerService.switchPowerForSingle(std::stoi(idStr),  std::stoi(status));
        sendResponse(response, success);
    // } else if (path  == "/power/routes_by_cabinet/{cabinetId}") {
    // } else if (path  == "/power/routes_by_cabinet/") {
    } else if (path.find("/power/routes_by_cabinet/")  == 0) { 
        // std::cout << "---------call: /power/routes_by_cabinet--"   << std::endl;
        int cabinetId = std::stoi(path.substr(25));
        auto routeList = powerService.getRouteList(cabinetId);  
        std::cout << "---------routeList.dump(): "  << routeList.dump() << std::endl;
        sendResponse(response, routeList.dump());
    } else if (path.find("/power/update/")  == 0) { 
        std::istringstream iss(path.substr(14));  
        std::string idStr, name; 
        std::getline(iss, idStr, '/'); 
        std::getline(iss, name); 
        int id = std::stoi(idStr); 
        powerService.updateRoute(id,  name); 
        sendResponse(response, success);

    //系统基本设置
    } else if (path == "/setting/basic/update" && method == Http::Method::Post) {        
        json data = json::parse(request.body());
        std::cout << "---------basic/update: "  << data << std::endl;
        settingService.updateBasicSetting(getOptionalInt(data, "language"), getOptionalInt(data, "backgroundColour"), 
            getOptionalString(data, "consoleMasterIp"), getOptionalString(data, "consoleSlaveIp"));
        sendResponse(response, success);
    //基本设置明细
    } else if (path == "/setting/basic/info") {        
        auto basicInfo = settingService.getBasicSetting();
        std::cout << "---------basicInfo: "  << basicInfo << std::endl;
        sendResponse(response, basicInfo.dump());  
    //定时设置
    } else if (path == "/setting/schedule/update" && method == Http::Method::Post) {        
        json data = json::parse(request.body());
        std::cout << "---------schedule/update: "  << data << std::endl;
        settingService.updateScheduledProgram(data["startTime"], data["stopTime"], getOptionalInt(data, "programId"), data["recycle"]);
        sendResponse(response, success);
    //定时设置明细
    } else if (path == "/setting/schedule/info") {
        auto scheduleInfo = settingService.getScheduledProgram();
        std::cout << "---------scheduleInfo: "  << scheduleInfo << std::endl;
        sendResponse(response, scheduleInfo.dump());          
    //背景颜色列表
    } else if (path == "/setting/bgcolour_data") {
        auto bgcolorData = settingService.getBgcolorData();
        sendResponse(response, bgcolorData.dump());          
    //语言列表
    } else if (path == "/setting/language_data") {
        auto languageData = settingService.getLanguageData();
        sendResponse(response, languageData.dump());          
    //是否控台直控
    } else if (path.find("/setting/console_directed") == 0) {
        settingService.isConsoleDirected = false;
        std::cout << "---------console: "  << path.substr(26) << std::endl;
        if(path.substr(26) == "true") {
            settingService.isConsoleDirected = true;
        }
        sendResponse(response, success);

    } else if (path.find("/setting/shutdown") == 0) {
        int result = std::system("sudo shutdown -h now");
        
        if (result == 0) {
            sendResponse(response, "正在关机...\n");
        } else {
            sendResponse(response, "关机命令执行失败\n");
        }

    } else if (path.find("/setting/import_all_file") == 0) {      
        settingService.importAllFiles();
        sendResponse(response, success);
    } else if (path.find("/setting/backup_all_file") == 0) {
        settingService.backupAllFiles();
        sendResponse(response, success);

    //未匹配到页面
    } else {
        response.send(Http::Code::Not_Found, "Not Found");
    }
}

