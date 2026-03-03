
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT, 
    name TEXT NOT NULL, 
    password TEXT NOT NULL, 
    isAdmin INTEGER 
);  
INSERT INTO users (name, password, isAdmin) VALUES ('test', '12345678', 0);
INSERT INTO users (name, password, isAdmin) VALUES ('admin', '12345678', 1);


CREATE TABLE IF NOT EXISTS music (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);
INSERT INTO music (name) VALUES ('test.mp3');
INSERT INTO music (name) VALUES ('回家.mp3');
INSERT INTO music (name) VALUES ('十年.mp3');

CREATE TABLE IF NOT EXISTS image (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);
INSERT INTO image (name) VALUES ('test.jpeg');
INSERT INTO image (name) VALUES ('花朵.jpeg');
INSERT INTO image (name) VALUES ('蓝色.jpeg');


CREATE TABLE IF NOT EXISTS video (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);
INSERT INTO video (name) VALUES ('test.mp4');
INSERT INTO video (name) VALUES ('英雄传说.mp4');
INSERT INTO video (name) VALUES ('婚礼.mp4');



CREATE TABLE IF NOT EXISTS light (
   id INTEGER PRIMARY KEY AUTOINCREMENT,
   name TEXT NOT NULL,
   lightType INTEGER, 
   duration INTEGER, 
   orderId INTEGER,    
   port1 INTEGER, 
   param1 TEXT,    
   port2 INTEGER, 
   param2 TEXT,    
   port3 INTEGER,  
   param3 TEXT,    
   port4 INTEGER,  
   param4 TEXT 
);
INSERT INTO light ( 
    name, lightType, duration, orderId, 
    port1, param1, port2, param2, port3, param3, port4, param4) 
values ('灯光1',1,40005,0, 1,'1-512', 2,'2-512', 3,'3-512', 4,'4-512');

INSERT INTO light ( 
    name, lightType, duration, orderId, 
    port1, param1, port2, param2, port3, param3, port4, param4) 
values ('灯光2',1,42005,0, 1,'1-256', 2,'2-256', 3,'3-256', 4,'4-256');


INSERT INTO light ( 
    name, lightType, duration, orderId, 
    port1, param1, port2, param2, port3, param3, port4, param4) 
values ('灯具1',2,40005,0, 1,'1-20,30-60', 2,'2-20,30-60', 3,'3-20,30-60', 4,'4-20,30-60');

INSERT INTO light ( 
    name, lightType, duration, orderId, 
    port1, param1, port2, param2, port3, param3, port4, param4) 
values ('灯具2',2,42005,0, 1,'1-22,30-60', 2,'2-22,30-60', 3,'3-22,30-60', 4,'4-22,30-60');

INSERT INTO light ( 
    name, lightType, duration, orderId, 
    port1, param1, port2, param2, port3, param3, port4, param4) 
values ('通道1',3,43005,0, 1,'[20,8,(3,5,6)];[32,10,(4,5,7)]', 2,'[22,8,(3,5,6)];[32,10,(4,5,7)]', 3,'[23,8,(3,5,6)];[32,10,(4,5,7)]', 4,'[24,8,(3,5,6)];[32,10,(4,5,7)]');


CREATE TABLE IF NOT EXISTS program (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    orderId INTEGER NOT NULL,
    lightId INTEGER,
    musicId INTEGER,
    videoId INTEGER,
    imgId INTEGER
);
INSERT INTO program (name, orderId, lightId, musicId, videoId, imgId) VALUES ('测试', 1, 3, 19, 23, 22);
INSERT INTO program (name, orderId, lightId, musicId, videoId, imgId) VALUES ('婚礼', 0, 3, 20, 24, 22);
INSERT INTO program (name, orderId, lightId, musicId, videoId, imgId) VALUES ('拜堂', 1, 3, 21, 25, 22);
INSERT INTO program (name, orderId, lightId, musicId, videoId, imgId) VALUES ('洞房', 1, 3, 22, 26, 22);
INSERT INTO program (name, orderId, lightId, musicId, videoId, imgId) VALUES ('测试', 1, 3, 23, 26, 22);


CREATE TABLE IF NOT EXISTS setting_basic (
    id INTEGER PRIMARY KEY,
    languageCode INTEGER NOT NULL,
    bgcolourCode INTEGER NOT NULL,
    masterip TEXT,  
    slaveip TEXT
);
INSERT OR REPLACE INTO setting_basic (id, languageCode, bgcolourCode, masterip, slaveip) VALUES (1, 1, 1, '192', '193');



CREATE TABLE IF NOT EXISTS setting_schedule (
    id INTEGER PRIMARY KEY,
    starttime TEXT not null,
    endtime TEXT not null,
    programId INTEGER not null,  
    is_recycled INTEGER not null 
);
INSERT OR REPLACE INTO setting_schedule (id, starttime, endtime, programId, is_recycled) VALUES (1, '2023.08.23 00:20:01', '2023.08.23 01:20:01', 20, 1);


CREATE TABLE IF NOT EXISTS power_route (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    cabinetId INTEGER NOT NULL,
    name TEXT NOT NULL
);
INSERT INTO power_route (cabinetId, name) VALUES (1, 'r01');
INSERT INTO power_route (cabinetId, name) VALUES (1, 'r0102');
INSERT INTO power_route (cabinetId, name) VALUES (1, 'r0103');
INSERT INTO power_route (cabinetId, name) VALUES (1, 'r0104');
INSERT INTO power_route (cabinetId, name) VALUES (2, 'r02');

INSERT INTO power_route (cabinetId, name) VALUES (0, 'r0c1');
INSERT INTO power_route (cabinetId, name) VALUES (0, 'r0c2');

INSERT INTO power_route (cabinetId, name) VALUES (3, 'r3c1');
INSERT INTO power_route (cabinetId, name) VALUES (3, 'r3c2');

INSERT INTO power_route (cabinetId, name) VALUES (4, 'r4c1');
INSERT INTO power_route (cabinetId, name) VALUES (5, 'r5c2');

INSERT INTO power_route (cabinetId, name) VALUES (6, 'r6c1');
INSERT INTO power_route (cabinetId, name) VALUES (7, 'r7c2');

INSERT INTO power_route (cabinetId, name) VALUES (8, 'r8c1');
INSERT INTO power_route (cabinetId, name) VALUES (8, 'r8c2');



----------------初始化表-------------------
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT, 
    name TEXT NOT NULL, 
    password TEXT NOT NULL, 
    isAdmin INTEGER 
);  

CREATE TABLE IF NOT EXISTS music (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS image (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS video (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS light (
   id INTEGER PRIMARY KEY AUTOINCREMENT,
   name TEXT NOT NULL,
   lightType INTEGER, 
   duration INTEGER, 
   orderId INTEGER,    
   port1 INTEGER, 
   param1 TEXT,    
   port2 INTEGER, 
   param2 TEXT,    
   port3 INTEGER,  
   param3 TEXT,    
   port4 INTEGER,  
   param4 TEXT 
);

CREATE TABLE IF NOT EXISTS program (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    orderId INTEGER NOT NULL,
    lightId INTEGER,
    musicId INTEGER,
    videoId INTEGER,
    imgId INTEGER
);

CREATE TABLE IF NOT EXISTS setting_basic (
    id INTEGER PRIMARY KEY,
    languageCode INTEGER NOT NULL,
    bgcolourCode INTEGER NOT NULL,
    masterip TEXT,  
    slaveip TEXT
);

CREATE TABLE IF NOT EXISTS setting_schedule (
    id INTEGER PRIMARY KEY,
    starttime TEXT not null,
    endtime TEXT not null,
    programId INTEGER not null,  
    is_recycled INTEGER not null 
);

CREATE TABLE IF NOT EXISTS power_route (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    cabinetId INTEGER NOT NULL,
    name TEXT NOT NULL
);

-------------初始化数据---------------
INSERT INTO users (name, password, isAdmin) VALUES ('test', '12345678', 0);
INSERT INTO users (name, password, isAdmin) VALUES ('admin', '12345678', 1);

INSERT OR REPLACE INTO setting_basic (id, languageCode, bgcolourCode, masterip, slaveip) VALUES (1, 1, 1, '192', '193');
