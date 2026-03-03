
需求Mock：
https://rp.mockplus.cn/run/-2Hz2ET36a/IViDt4LR-4/scxsce_eZ?cps=expand&rps=expand&nav=1&ha=0&la=0&fc=0&out=0&rt=1&dt=none&as=true

Swagger:
http://localhost:8080/swagger-ui.html#/


//数据库访问
const std::string DB_NAME = "/app/test.db";
sqlite3 /app/test.db
.tables
.schema your_table_name
.quit
.read table.sql


资源保存路径
/app/source/light/
/app/source/music/
/app/source/video/
/app/source/image/


//用户
登陆
http://localhost:8080/user/login
修改密码
http://localhost:8080/user/change_password

//节目播放
节目播放列表
http://localhost:8080/program/list
节目播放
http://localhost:8080/program/play/
暂停
http://localhost:8080/program/pause/
继续播放
http://localhost:8080/program/resume/
循环播放
http://localhost:8080/program/recycle/
黑场
http://localhost:8080/program/blackout/

//场景管理 
场景列表
http://localhost:8080/scene/list
场景搜索
http://localhost:8080/scene/find/
场景下拉列表过滤
http://localhost:8080/scene/filter/
场景播放
http://localhost:8080/scene/play/
场景删除
http://localhost:8080/scene/del/
场景明细(编辑页面显示明细)
http://localhost:8080/scene/find_detail/
场景更新(只更新名称)
http://localhost:8080/scene/update/
场景类别(用以初始化场景下拉列表)
http://localhost:8080/scene/sceneTypes/
场景排序
http://localhost:8080/scene/sort/

//节目管理
节目管理列表
http://localhost:8080/program/manager/list
节目搜索
http://localhost:8080/program/manager/find/
节目播放
http://localhost:8080/program/manager/play/
节目删除
http://localhost:8080/program/manager/del/
节目排序
http://localhost:8080/program/manager/sort/
节目明细（显示在更新页面）
http://localhost:8080/program/manager/find_detail/
节目更新
http://localhost:8080/program/manager/update
节目新建
http://localhost:8080/program/manager/save

//灯光录制
开始灯光录制
http://localhost:8080/light/record/startRecord/
停止录制
http://localhost:8080/light/record/stopRecord/
测试灯光
http://localhost:8080/light/record/testRecord/
停止测试播放
http://localhost:8080/light/record/stopTestRecord/
删除无效dmx灯光(毫秒)
http://localhost:8080/light/record/truncRecord/
保存灯光
http://localhost:8080/light/record/saveRecord/

//灯光管理
灯光列表
http://localhost:8080/light/list
灯光搜索
http://localhost:8080/light/find/
灯光更新
http://localhost:8080/light/update/
灯光播放
http://localhost:8080/light/play/
灯光删除        
http://localhost:8080/light/del/
灯光批量删除
http://localhost:8080/light/batch_del/

//音乐管理
音乐列表
http://localhost:8080/music/list
音乐搜索
http://localhost:8080/music/find/
音乐更新
http://localhost:8080/music/update/
音乐播放
http://localhost:8080/music/play/
音乐删除
http://localhost:8080/music/del/
音乐批量删除
http://localhost:8080/music/batch_del/

//视频管理
视频列表
http://localhost:8080/video/list
视频搜索
http://localhost:8080/video/find/
视频更新
http://localhost:8080/video/update/
视频播放
http://localhost:8080/video/play/
视频删除        
http://localhost:8080/video/del/
视频批量删除
http://localhost:8080/video/batch_del/

//图片管理
图片列表
http://localhost:8080/image/list
图片搜索
http://localhost:8080/image/find/
图片更新
http://localhost:8080/image/update/
图片显示
http://localhost:8080/image/play/
图片删除
http://localhost:8080/image/del/
图片批量删除
http://localhost:8080/image/batch_del/

//电力管理
电柜数量
http://localhost:8080/power/cabinet_num/
每个电柜路线数量
http://localhost:8080/power/routes_per_cabinet/
电力总开关
http://localhost:8080/power/switch_for_all/{status}/
单个路线开关
http://localhost:8080/power/switch_for_single/{cabinetId}/{routeId}/{status}/

//系统设置
系统基本设置    
http://localhost:8080/setting/basic/update
基本设置明细
http://localhost:8080/setting/basic/info
定时设置
http://localhost:8080/setting/schedule/update
定时设置明细
http://localhost:8080/setting/schedule/info
背景颜色列表
http://localhost:8080/setting/bgcolour_data
语言列表
http://localhost:8080/setting/language_data
是否控台直控
http://localhost:8080/setting/console_directed

			



Post请求通过Postman测试
Test:
http://localhost:8083/setting/schedule/update：
{
    "startTime": "2023-08-23 01:20:01",
    "endTime": "2023-08-24 02:20:01",
    "programId": 3,
    "isRecycled": 0
}

http://localhost:8083/setting/basic/update
{
    "language": "chinese",
    "bgcolour": "black",
    "masterIp": "192.168.3.1",
    "slaveIp": "192.168.3.2"
}

http://localhost:8083/user/login
{
    "name": "admin",
    "password": "admin"
}

http://localhost:8083/light/record/saveRecord
{
	"name": "testDevice3", 
	"lightType": 3, 
	"duration": 3.05, 
	"portId1": 1, 
	"recordParam1": "1-512", 
	"portId2": 2, 
	"recordParam2": "2-512", 
	"portId3": 3, 
	"recordParam3": "3-512", 
	"portId4": 4, 
	"recordParam4": "4-512"
}


安卓访问WSL网络：

# 将 Windows 的 8000 端口转发到 WSL2 的 8000 端口
netsh interface portproxy add v4tov4 listenport=8080 connectaddress=192.168.148.121 connectport=8080

# 允许外部设备访问 8000 端口
New-NetFirewallRule -DisplayName "WSL2-HTTP" -Direction Inbound -LocalPort 8080 -Protocol TCP -Action Allow

访问：
http://192.168.0.21:8080/music/list

取消端口转发：
netsh interface portproxy reset 

查看网络转发：
netsh interface portproxy show all
 
安装VLC:
sudo apt install vlc (可以不安装？)
sudo apt update && sudo apt install libvlc-dev 


Git更新：
build.gradle
    dependencies {
        classpath 'com.android.tools.build:gradle:8.3.0' // 修改为对应版本

gradle.wrapper:
distributionUrl=https\://services.gradle.org/distributions/gradle-8.6-bin.zip


