CREATE TABLE `currency_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `currency1` varchar(1024) DEFAULT NULL,
    `currency2` varchar(1024) DEFAULT NULL,
    `currency3` varchar(1024) DEFAULT NULL,
    `currency4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX currency_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `currency_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `currency1` varchar(1024) DEFAULT NULL,
    `currency2` varchar(1024) DEFAULT NULL,
    `currency3` varchar(1024) DEFAULT NULL,
    `currency4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX currency_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `currency_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `currency1` varchar(1024) DEFAULT NULL,
    `currency2` varchar(1024) DEFAULT NULL,
    `currency3` varchar(1024) DEFAULT NULL,
    `currency4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX currency_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `cycleevent_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `events` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX cycleevent_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `cycleevent_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `events` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX cycleevent_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `cycleevent_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `events` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX cycleevent_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `equip_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `equip1` varchar(1024) DEFAULT NULL,
    `equip2` varchar(1024) DEFAULT NULL,
    `equip3` varchar(1024) DEFAULT NULL,
    `equip4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX equip_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `equip_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `equip1` varchar(1024) DEFAULT NULL,
    `equip2` varchar(1024) DEFAULT NULL,
    `equip3` varchar(1024) DEFAULT NULL,
    `equip4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX equip_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `equip_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `equip1` varchar(1024) DEFAULT NULL,
    `equip2` varchar(1024) DEFAULT NULL,
    `equip3` varchar(1024) DEFAULT NULL,
    `equip4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX equip_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `food_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `food1` varchar(1024) DEFAULT NULL,
    `food2` varchar(1024) DEFAULT NULL,
    `food3` varchar(1024) DEFAULT NULL,
    `food4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX food_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `food_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `food1` varchar(1024) DEFAULT NULL,
    `food2` varchar(1024) DEFAULT NULL,
    `food3` varchar(1024) DEFAULT NULL,
    `food4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX food_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `food_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `food1` varchar(1024) DEFAULT NULL,
    `food2` varchar(1024) DEFAULT NULL,
    `food3` varchar(1024) DEFAULT NULL,
    `food4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX food_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `hero_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `heros` varchar(1024) DEFAULT NULL,
    `teams` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX hero_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `hero_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `heros` varchar(1024) DEFAULT NULL,
    `teams` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX hero_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `hero_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `heros` varchar(1024) DEFAULT NULL,
    `teams` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX hero_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `login_log_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `action` int DEFAULT 0,
    `online` int DEFAULT 0,
    `ip` varchar(1024) DEFAULT NULL,
    `appid` varchar(1024) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX login_log_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `login_log_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `action` int DEFAULT 0,
    `online` int DEFAULT 0,
    `ip` varchar(1024) DEFAULT NULL,
    `appid` varchar(1024) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX login_log_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `login_log_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `action` int DEFAULT 0,
    `online` int DEFAULT 0,
    `ip` varchar(1024) DEFAULT NULL,
    `appid` varchar(1024) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX login_log_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `mail_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `mail1` varchar(1024) DEFAULT NULL,
    `mail2` varchar(1024) DEFAULT NULL,
    `mail3` varchar(1024) DEFAULT NULL,
    `mail4` varchar(1024) DEFAULT NULL,
    `mail5` varchar(1024) DEFAULT NULL,
    `lastmailid` int DEFAULT 0,
    `snakeid` int DEFAULT 0,
    UNIQUE INDEX mail_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `mail_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `mail1` varchar(1024) DEFAULT NULL,
    `mail2` varchar(1024) DEFAULT NULL,
    `mail3` varchar(1024) DEFAULT NULL,
    `mail4` varchar(1024) DEFAULT NULL,
    `mail5` varchar(1024) DEFAULT NULL,
    `lastmailid` int DEFAULT 0,
    `snakeid` int DEFAULT 0,
    UNIQUE INDEX mail_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `mail_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `mail1` varchar(1024) DEFAULT NULL,
    `mail2` varchar(1024) DEFAULT NULL,
    `mail3` varchar(1024) DEFAULT NULL,
    `mail4` varchar(1024) DEFAULT NULL,
    `mail5` varchar(1024) DEFAULT NULL,
    `lastmailid` int DEFAULT 0,
    `snakeid` int DEFAULT 0,
    UNIQUE INDEX mail_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `material_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `material1` varchar(1024) DEFAULT NULL,
    `material2` varchar(1024) DEFAULT NULL,
    `material3` varchar(1024) DEFAULT NULL,
    `material4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX material_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `material_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `material1` varchar(1024) DEFAULT NULL,
    `material2` varchar(1024) DEFAULT NULL,
    `material3` varchar(1024) DEFAULT NULL,
    `material4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX material_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `material_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `material1` varchar(1024) DEFAULT NULL,
    `material2` varchar(1024) DEFAULT NULL,
    `material3` varchar(1024) DEFAULT NULL,
    `material4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX material_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `npc_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `npcs` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX npc_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `npc_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `npcs` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX npc_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `npc_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `npcs` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX npc_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `res_log_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `action` int DEFAULT 0,
    `cfgtype` int DEFAULT 0,
    `cfgid` int DEFAULT 0,
    `delta` int DEFAULT 0,
    `value` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX res_log_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `res_log_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `action` int DEFAULT 0,
    `cfgtype` int DEFAULT 0,
    `cfgid` int DEFAULT 0,
    `delta` int DEFAULT 0,
    `value` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX res_log_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `res_log_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `action` int DEFAULT 0,
    `cfgtype` int DEFAULT 0,
    `cfgid` int DEFAULT 0,
    `delta` int DEFAULT 0,
    `value` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX res_log_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `roles_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `worldid` bigint DEFAULT 0,
    `dbid` int DEFAULT 0,
    `name` varchar(1024) DEFAULT NULL,
    `charid` int DEFAULT 0,
    `face` varchar(1024) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    INDEX roles_roleid(`roleid`,`userid`),
    PRIMARY KEY (`roleid`,`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `roles_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `worldid` bigint DEFAULT 0,
    `dbid` int DEFAULT 0,
    `name` varchar(1024) DEFAULT NULL,
    `charid` int DEFAULT 0,
    `face` varchar(1024) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    INDEX roles_roleid(`roleid`,`userid`),
    PRIMARY KEY (`roleid`,`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `roles_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `worldid` bigint DEFAULT 0,
    `dbid` int DEFAULT 0,
    `name` varchar(1024) DEFAULT NULL,
    `charid` int DEFAULT 0,
    `face` varchar(1024) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    INDEX roles_roleid(`roleid`,`userid`),
    PRIMARY KEY (`roleid`,`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `role_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `rolename` varchar(1024) DEFAULT NULL,
    `level` int DEFAULT 0,
    `exp` bigint DEFAULT 0,
    `characterid` int DEFAULT 0,
    `gold` int DEFAULT 0,
    `offlinetime` bigint DEFAULT 0,
    `inited` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    `face` varchar(1024) DEFAULT NULL,
    `online` bigint DEFAULT 0,
    `worldid` bigint DEFAULT 0,
    `pttype` int DEFAULT 0,
    UNIQUE INDEX role_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `role_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `rolename` varchar(1024) DEFAULT NULL,
    `level` int DEFAULT 0,
    `exp` bigint DEFAULT 0,
    `characterid` int DEFAULT 0,
    `gold` int DEFAULT 0,
    `offlinetime` bigint DEFAULT 0,
    `inited` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    `face` varchar(1024) DEFAULT NULL,
    `online` bigint DEFAULT 0,
    `worldid` bigint DEFAULT 0,
    `pttype` int DEFAULT 0,
    UNIQUE INDEX role_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `role_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `rolename` varchar(1024) DEFAULT NULL,
    `level` int DEFAULT 0,
    `exp` bigint DEFAULT 0,
    `characterid` int DEFAULT 0,
    `gold` int DEFAULT 0,
    `offlinetime` bigint DEFAULT 0,
    `inited` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    `face` varchar(1024) DEFAULT NULL,
    `online` bigint DEFAULT 0,
    `worldid` bigint DEFAULT 0,
    `pttype` int DEFAULT 0,
    UNIQUE INDEX role_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `scene_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `sceneid` int DEFAULT 0,
    `collects` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX scene_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `scene_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `sceneid` int DEFAULT 0,
    `collects` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX scene_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `scene_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `sceneid` int DEFAULT 0,
    `collects` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX scene_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `skill_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `skill1` varchar(1024) DEFAULT NULL,
    `skill2` varchar(1024) DEFAULT NULL,
    `skill3` varchar(1024) DEFAULT NULL,
    `skill4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX skill_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `skill_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `skill1` varchar(1024) DEFAULT NULL,
    `skill2` varchar(1024) DEFAULT NULL,
    `skill3` varchar(1024) DEFAULT NULL,
    `skill4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX skill_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `skill_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `skill1` varchar(1024) DEFAULT NULL,
    `skill2` varchar(1024) DEFAULT NULL,
    `skill3` varchar(1024) DEFAULT NULL,
    `skill4` varchar(1024) DEFAULT NULL,
    UNIQUE INDEX skill_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `user_0`(
    `version` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `ptid` varchar(1024) DEFAULT NULL,
    `pttype` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX user_userid(`userid`),
    PRIMARY KEY (`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `user_1`(
    `version` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `ptid` varchar(1024) DEFAULT NULL,
    `pttype` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX user_userid(`userid`),
    PRIMARY KEY (`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `user_2`(
    `version` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `ptid` varchar(1024) DEFAULT NULL,
    `pttype` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX user_userid(`userid`),
    PRIMARY KEY (`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
