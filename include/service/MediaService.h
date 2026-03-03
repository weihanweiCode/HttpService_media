//
// Created by Administrator on 2025/5/6.
//

#ifndef PLAYER_MEDIASERVICE_H
#define PLAYER_MEDIASERVICE_H

#pragma once
#include <string>
#include <mutex>
#include <atomic>
extern "C" {
    // #include <vlc/vlc.h>
}

class MediaService {
public:
    ~MediaService();

    // 单例访问方法
    static MediaService& instance();

    // 媒体控制接口
    bool play(const std::string& filePath);
    void pause();
    void resume();
    void stop();

    // 状态查询
    bool isPlaying() const;
    int64_t getDuration() const;
    int64_t getPosition() const;

private:
    // 私有构造函数确保单例
    MediaService();

    // VLC核心对象
    // libvlc_instance_t* vlcInstance;
    // libvlc_media_player_t* mediaPlayer;
    // libvlc_media_t* currentMedia;

    // 线程安全机制
    // mutable std::mutex playerMutex;
    // std::atomic<bool> playingStatus{false};

    // 初始化/清理方法
    void initVLC();
    void cleanupVLC();

    // 禁止拷贝
    MediaService(const MediaService&) = delete;
    MediaService& operator=(const MediaService&) = delete;
};

#endif //PLAYER_MEDIASERVICE_H
