#include "service/MediaService.h"
#include <stdexcept>

MediaService::MediaService() {
    initVLC();
}

MediaService::~MediaService() {
    cleanupVLC();
}

void MediaService::initVLC() {
//    const char* vlcArgs[] = {
//            "--no-xlib",             // 禁用GUI组件
//            "--aout=opensles",       // 音频输出引擎[4]()
//            "--network-caching=300", // 网络缓冲时间(ms)
//            "--avcodec-threads=4"    // 解码线程数
//    };
//
//    vlcInstance = libvlc_new(sizeof(vlcArgs)/sizeof(vlcArgs[0]), vlcArgs);

    // vlcInstance = libvlc_new(0, nullptr);
    // if (!vlcInstance) {
    //     throw std::runtime_error("Failed to initialize VLC");
    // }

    // mediaPlayer = nullptr;
    // currentMedia = nullptr;
}

void MediaService::cleanupVLC() {
    // std::lock_guard<std::mutex> lock(playerMutex);
    // if (mediaPlayer) {
    //     libvlc_media_player_release(mediaPlayer);
    // }
    // if (currentMedia) {
    //     libvlc_media_release(currentMedia);
    // }
    // libvlc_release(vlcInstance);
}

MediaService& MediaService::instance() {
    // static MediaService instance;
    // return instance;
}

bool MediaService::play(const std::string& filePath) {
//    std::lock_guard<std::mutex> lock(playerMutex);

//    stop(); // 停止当前播放

    // currentMedia = libvlc_media_new_path(vlcInstance, filePath.c_str());
    // if (!currentMedia) return false;

    // mediaPlayer = libvlc_media_player_new_from_media(currentMedia);
    // if (!mediaPlayer) return false;

    // int ret = libvlc_media_player_play(mediaPlayer);
    // playingStatus.store(ret  == 0);
    // return ret == 0;
    return true;
}

void MediaService::pause() {
    // std::lock_guard<std::mutex> lock(playerMutex);
    // if (mediaPlayer && libvlc_media_player_can_pause(mediaPlayer)) {
    //     libvlc_media_player_pause(mediaPlayer);
    //     playingStatus.store(false);
    // }
}

void MediaService::resume() {
    // std::lock_guard<std::mutex> lock(playerMutex);
    // if (mediaPlayer && !libvlc_media_player_is_playing(mediaPlayer)) {
    //     libvlc_media_player_play(mediaPlayer);
    //     playingStatus.store(true);
    // }
}

void MediaService::stop() {
    // std::lock_guard<std::mutex> lock(playerMutex);
    // if (mediaPlayer) {
    //     libvlc_media_player_stop(mediaPlayer);
    //     libvlc_media_player_release(mediaPlayer);
    //     mediaPlayer = nullptr;
    // }
    // if (currentMedia) {
    //     libvlc_media_release(currentMedia);
    //     currentMedia = nullptr;
    // }
    // playingStatus.store(false);
}

// 状态查询方法实现 
bool MediaService::isPlaying() const {
    // return playingStatus.load();
    return true;
}

int64_t MediaService::getDuration() const {
    // std::lock_guard<std::mutex> lock(playerMutex);
    // return mediaPlayer ? libvlc_media_player_get_length(mediaPlayer) : -1;
    return 1;
}

int64_t MediaService::getPosition() const {
    // std::lock_guard<std::mutex> lock(playerMutex);
    // return mediaPlayer ? libvlc_media_player_get_time(mediaPlayer) : -1;
    return 1;
}