#include <QApplication>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QMessageBox>
#include <QProcess>

int main(int argc, char *argv[]) {
    // 设置环境变量（在创建 QApplication 之前）
    qputenv("QT_MEDIA_BACKEND", "gstreamer");
    qputenv("GST_PLUGIN_PATH", "/usr/lib/x86_64-linux-gnu/gstreamer-1.0");
    
    QApplication app(argc, argv);
    
    // 启用调试信息
    qDebug() << "=== 启动视频播放器 ===";
    qDebug() << "Qt 版本:" << qVersion();
    qDebug() << "环境变量:";
    qDebug() << "QT_MEDIA_BACKEND:" << qgetenv("QT_MEDIA_BACKEND");
    qDebug() << "GST_PLUGIN_PATH:" << qgetenv("GST_PLUGIN_PATH");
    
    // 创建视频窗口
    QVideoWidget *videoWidget = new QVideoWidget;
    videoWidget->setWindowTitle("视频播放器 (已修复)");
    //videoWidget->resize(800, 600);
	videoWidget->setFullScreen(true);
    videoWidget->show();
    
    // 创建播放器
    QMediaPlayer *player = new QMediaPlayer(videoWidget);
    
    // 连接错误信号
    QObject::connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
        [player, videoWidget](QMediaPlayer::Error error) {
            qDebug() << "播放错误:" << error;
            qDebug() << "错误详情:" << player->errorString();
            
            // 显示错误对话框
            QMessageBox::critical(videoWidget, "播放错误",
                QString("错误: %1\n\n"
                       "可能的原因:\n"
                       "1. 缺少 GStreamer 插件\n"
                       "2. 视频格式不支持\n"
                       "3. 文件路径错误\n\n"
                       "解决方案:\n"
                       "运行: sudo apt install gstreamer1.0-plugins-good gstreamer1.0-plugins-bad")
                .arg(player->errorString()));
        });
    
    // 连接状态变化信号
    QObject::connect(player, &QMediaPlayer::mediaStatusChanged,
        [](QMediaPlayer::MediaStatus status) {
            qDebug() << "媒体状态:" << status;
        });
    
    // 设置视频输出
    player->setVideoOutput(videoWidget);
    
    // 设置音量
    player->setVolume(20);
    
    // 选择视频文件
    QStringList videoFiles = {
        "/home/whw/work/new/test.mp4",
        "./test.avi",
        "./test.mkv",
        "/usr/share/example-content/Ubuntu_Free_Culture_Showcase.webm"
    };
    
    QString selectedFile;
    for (const QString &file : videoFiles) {
        if (QFile::exists(file)) {
            selectedFile = file;
            qDebug() << "find video files:" << file;
            break;
        }
    }
    
    if (selectedFile.isEmpty()) {
        qDebug() << "cannot find video files...";
        
        // 尝试使用命令行创建测试视频
     /*   QProcess process;
        process.start("bash", QStringList() << "-c" << 
            "which ffmpeg && ffmpeg -f lavfi -i testsrc=duration=10:size=640x480:rate=30 -c:v libx264 test.mp4");
        process.waitForFinished(10000);
        
        selectedFile = "./test.mp4";*/
    }
    
    // 设置媒体并播放
    qDebug() << "set Media :" << selectedFile;
    player->setMedia(QUrl::fromLocalFile(selectedFile));
    
    // 延迟播放以确保窗口已显示
    QTimer::singleShot(100, [player]() {
        qDebug() << "start play..";
        player->play();
    });
    
    return app.exec();
}
