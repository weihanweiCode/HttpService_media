cmake_minimum_required(VERSION 3.22)
project(HttpService)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(/usr/include/nlohmann)
include_directories(/local/include/pistache)
include_directories(/local/include)
# include_directories(/usr/include/vlc)
include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(/usr/lib/x86_64-linux-gnu)
link_directories(/usr/local/lib/x86_64-linux-gnu/)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)

# 全局设置静态链接
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

add_executable(HttpService 
src/main.cpp 
src/handler/HttpUtil.cpp
src/handler/ApiHandler.cpp
src/service/ProgramService.cpp
src/service/LightRecordService.cpp
src/service/LightService.cpp
src/service/PowerService.cpp
src/service/MusicService.cpp 
src/service/VideoService.cpp
src/service/ImageService.cpp
src/service/ProgramManagerService.cpp 
src/service/SettingService.cpp
src/service/MediaService.cpp
src/service/FileService.cpp
src/dao/LightDao.cpp
src/dao/UserDao.cpp 
src/dao/MusicDao.cpp 
src/dao/ImageDao.cpp 
src/dao/VideoDao.cpp 
src/dao/ProgramDao.cpp 
src/dao/SettingDao.cpp
src/dao/PowerDao.cpp
src/dao/DatabaseConnectionPool.cpp
src/dao/DbInitializer.cpp
)


# target_link_libraries(HttpService PRIVATE pistache sqlite3)
target_link_libraries(HttpService PRIVATE
    /usr/local/lib/x86_64-linux-gnu/libpistache.a 
    # /usr/local/static-pistache/lib/x86_64-linux-gnu/libpistache.a 
     /usr/local/lib/libsqlite3.a 
    /usr/lib/x86_64-linux-gnu/libssl.a
    /usr/lib/x86_64-linux-gnu/libcrypto.a
    # OpenSSL::SSL
    # OpenSSL::Crypto
    # /usr/lib/x86_64-linux-gnu/libvlc.so /usr/lib/x86_64-linux-gnu/libvlccore.so.9
)


//--------------start------------------
gcc -std=c++17 -static main.cpp service/FileService.cpp service/ImageService.cpp service/LightRecordService.cpp service/LightService.cpp service/MediaService.cpp service/MusicService.cpp  service/PowerService.cpp service/ProgramManagerService.cpp service/ProgramService.cpp service/SettingService.cpp service/VideoService.cpp dao/DatabaseConnectionPool.cpp dao/DbInitializer.cpp  dao/ImageDao.cpp  dao/LightDao.cpp  dao/MusicDao.cpp  dao/PowerDao.cpp  dao/ProgramDao.cpp dao/SettingDao.cpp dao/UserDao.cpp dao/VideoDao.cpp handler/ApiHandler.cpp handler/HttpUtil.cpp  -o mainsevicerstatic /home/whw/work/tool/pistache/build/src/libpistache.a /usr/lib/x86_64-linux-gnu/libm.a /usr/lib/x86_64-linux-gnu/libdl.a /usr/lib/x86_64-linux-gnu/librt.a -pthread -lstdc++  /usr/lib/x86_64-linux-gnu/libssl.a /usr/lib/x86_64-linux-gnu/libcrypto.a /usr/lib/x86_64-linux-gnu/libsqlite3.a /usr/lib/gcc/x86_64-linux-gnu/11/libgcc.a  /usr/lib/gcc/x86_64-linux-gnu/11/libgcc_eh.a /usr/lib/x86_64-linux-gnu/libm.a -I../include/
 1368  vim main.cpp
 1369  gcc -std=c++17 -static main.cpp service/FileService.cpp service/ImageService.cpp service/LightRecordService.cpp service/LightService.cpp service/MediaService.cpp service/MusicService.cpp  service/PowerService.cpp service/ProgramManagerService.cpp service/ProgramService.cpp service/SettingService.cpp service/VideoService.cpp dao/DatabaseConnectionPool.cpp dao/DbInitializer.cpp  dao/ImageDao.cpp  dao/LightDao.cpp  dao/MusicDao.cpp  dao/PowerDao.cpp  dao/ProgramDao.cpp dao/SettingDao.cpp dao/UserDao.cpp dao/VideoDao.cpp handler/ApiHandler.cpp handler/HttpUtil.cpp  -o mainsevicerstatic /home/whw/work/tool/pistache/build/src/libpistache.a /usr/lib/x86_64-linux-gnu/libm.a /usr/lib/x86_64-linux-gnu/libdl.a /usr/lib/x86_64-linux-gnu/librt.a -pthread -lstdc++  /usr/lib/x86_64-linux-gnu/libssl.a /usr/lib/x86_64-linux-gnu/libcrypto.a /usr/lib/x86_64-linux-gnu/libsqlite3.a /usr/lib/gcc/x86_64-linux-gnu/11/libgcc.a  /usr/lib/gcc/x86_64-linux-gnu/11/libgcc_eh.a /usr/lib/x86_64-linux-gnu/libm.a -I../include/
 1370  ./mainsevicerstatic
 1371  vim main.cpp
 1372  ./mainsevicerstatic
 1373  aarch64-linux-gnu-gcc -std=c++17 -static main.cpp service/FileService.cpp service/ImageService.cpp service/LightRecordService.cpp service/LightService.cpp service/MediaService.cpp service/MusicService.cpp service/PowerService.cpp service/ProgramManagerService.cpp service/ProgramService.cpp service/SettingService.cpp service/VideoService.cpp dao/DatabaseConnectionPool.cpp dao/DbInitializer.cpp  dao/ImageDao.cpp  dao/LightDao.cpp  dao/MusicDao.cpp  dao/PowerDao.cpp  dao/ProgramDao.cpp dao/SettingDao.cpp dao/UserDao.cpp dao/VideoDao.cpp handler/ApiHandler.cpp handler/HttpUtil.cpp  -o HttpService /home/whw/work/pistache/build_aarch64/src/libpistache.a /usr/aarch64-linux-gnu/lib/libm.a /usr/aarch64-linux-gnu/lib/libdl.a /usr/aarch64-linux-gnu/lib/librt.a -pthread -lstdc++  /home/whw/aarch64-libs/lib/libssl.a /home/whw/aarch64-libs/lib/libcrypto.a /usr/aarch64-linux-gnu/lib/libsqlite3.a /usr/lib/gcc-cross/aarch64-linux-gnu/11/libgcc.a  /usr/lib/gcc-cross/aarch64-linux-gnu/11/libgcc_eh.a /usr/aarch64-linux-gnu/lib/libm.a -I../include/
//---------------end------------------

g++ mp4play1.cpp -o mp4play1     -fPIC -no-pie     -I/usr/include/x86_64-linux-gnu/qt5     -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets     -I/usr/include/x86_64-linux-gnu/qt5/QtCore     -I/usr/include/x86_64-linux-gnu/qt5/QtGui     -I/usr/include/x86_64-linux-gnu/qt5/QtMultimedia     -I/usr/include/x86_64-linux-gnu/qt5/QtMultimediaWidgets     -L/usr/lib/x86_64-linux-gnu     -lQt5Widgets     -lQt5Multimedia     -lQt5MultimediaWidgets     -lQt5Gui     -lQt5Core     -lGL     -lpthread
