
----------------初始化表-------------------
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT, 
    name TEXT NOT NULL, 
    password TEXT NOT NULL, 
    isAdmin INTEGER 
);  

CREATE TABLE IF NOT EXISTS music (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS image (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS video (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE
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

INSERT OR REPLACE INTO setting_basic (id, languageCode, bgcolourCode, masterip, slaveip) VALUES (1, 1, 1, '192.168.0.20', '192.168.0.21');
