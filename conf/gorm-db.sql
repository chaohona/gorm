CREATE TABLE `currency_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `currency1` blob,
    `currency2` blob,
    `currency3` blob,
    `currency4` blob,
    UNIQUE INDEX currency_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `currency_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `currency1` blob,
    `currency2` blob,
    `currency3` blob,
    `currency4` blob,
    UNIQUE INDEX currency_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `currency_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `currency1` blob,
    `currency2` blob,
    `currency3` blob,
    `currency4` blob,
    UNIQUE INDEX currency_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `cycleevent_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `events` blob,
    UNIQUE INDEX cycleevent_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `cycleevent_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `events` blob,
    UNIQUE INDEX cycleevent_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `cycleevent_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `events` blob,
    UNIQUE INDEX cycleevent_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `equip_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `equip1` blob,
    `equip2` blob,
    `equip3` blob,
    `equip4` blob,
    UNIQUE INDEX equip_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `equip_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `equip1` blob,
    `equip2` blob,
    `equip3` blob,
    `equip4` blob,
    UNIQUE INDEX equip_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `equip_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `equip1` blob,
    `equip2` blob,
    `equip3` blob,
    `equip4` blob,
    UNIQUE INDEX equip_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `food_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `food1` blob,
    `food2` blob,
    `food3` blob,
    `food4` blob,
    UNIQUE INDEX food_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `food_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `food1` blob,
    `food2` blob,
    `food3` blob,
    `food4` blob,
    UNIQUE INDEX food_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `food_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `food1` blob,
    `food2` blob,
    `food3` blob,
    `food4` blob,
    UNIQUE INDEX food_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `hero_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `heros` blob,
    `teams` blob,
    UNIQUE INDEX hero_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `hero_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `heros` blob,
    `teams` blob,
    UNIQUE INDEX hero_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `hero_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `heros` blob,
    `teams` blob,
    UNIQUE INDEX hero_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `login_log_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `action` int DEFAULT 0,
    `online` int DEFAULT 0,
    `ip` varchar(255) DEFAULT NULL,
    `appid` varchar(255) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX login_log_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `login_log_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `action` int DEFAULT 0,
    `online` int DEFAULT 0,
    `ip` varchar(255) DEFAULT NULL,
    `appid` varchar(255) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX login_log_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `login_log_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `action` int DEFAULT 0,
    `online` int DEFAULT 0,
    `ip` varchar(255) DEFAULT NULL,
    `appid` varchar(255) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    UNIQUE INDEX login_log_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `mail_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `mail1` blob,
    `mail2` blob,
    `mail3` blob,
    `mail4` blob,
    `mail5` blob,
    `lastmailid` int DEFAULT 0,
    `snakeid` int DEFAULT 0,
    UNIQUE INDEX mail_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `mail_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `mail1` blob,
    `mail2` blob,
    `mail3` blob,
    `mail4` blob,
    `mail5` blob,
    `lastmailid` int DEFAULT 0,
    `snakeid` int DEFAULT 0,
    UNIQUE INDEX mail_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `mail_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `mail1` blob,
    `mail2` blob,
    `mail3` blob,
    `mail4` blob,
    `mail5` blob,
    `lastmailid` int DEFAULT 0,
    `snakeid` int DEFAULT 0,
    UNIQUE INDEX mail_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `material_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `material1` blob,
    `material2` blob,
    `material3` blob,
    `material4` blob,
    UNIQUE INDEX material_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `material_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `material1` blob,
    `material2` blob,
    `material3` blob,
    `material4` blob,
    UNIQUE INDEX material_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `material_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `material1` blob,
    `material2` blob,
    `material3` blob,
    `material4` blob,
    UNIQUE INDEX material_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `npc_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `npcs` blob,
    UNIQUE INDEX npc_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `npc_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `npcs` blob,
    UNIQUE INDEX npc_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `npc_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `npcs` blob,
    UNIQUE INDEX npc_roleid(`roleid`)
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
    UNIQUE INDEX res_log_roleid(`roleid`)
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
    UNIQUE INDEX res_log_roleid(`roleid`)
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
    UNIQUE INDEX res_log_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `interaction_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `interaction1` blob,
    `interaction2` blob,
    `interaction3` blob,
    `interaction4` blob,
    UNIQUE INDEX interaction_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `interaction_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `interaction1` blob,
    `interaction2` blob,
    `interaction3` blob,
    `interaction4` blob,
    UNIQUE INDEX interaction_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `interaction_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `interaction1` blob,
    `interaction2` blob,
    `interaction3` blob,
    `interaction4` blob,
    UNIQUE INDEX interaction_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `roles_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `worldid` bigint DEFAULT 0,
    `dbid` int DEFAULT 0,
    `name` varchar(255) DEFAULT NULL,
    `charid` int DEFAULT 0,
    `face` varchar(1024) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    INDEX roles_roleid(`roleid`,`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `roles_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `worldid` bigint DEFAULT 0,
    `dbid` int DEFAULT 0,
    `name` varchar(255) DEFAULT NULL,
    `charid` int DEFAULT 0,
    `face` varchar(1024) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    INDEX roles_roleid(`roleid`,`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `roles_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `worldid` bigint DEFAULT 0,
    `dbid` int DEFAULT 0,
    `name` varchar(255) DEFAULT NULL,
    `charid` int DEFAULT 0,
    `face` varchar(1024) DEFAULT NULL,
    `createtime` bigint DEFAULT 0,
    INDEX roles_roleid(`roleid`,`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `role_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `rolename` varchar(255) DEFAULT NULL,
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
    `userid` bigint DEFAULT 0,
    `proceedslv` int DEFAULT 0,
    UNIQUE INDEX role_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `role_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `rolename` varchar(255) DEFAULT NULL,
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
    `userid` bigint DEFAULT 0,
    `proceedslv` int DEFAULT 0,
    UNIQUE INDEX role_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `role_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `rolename` varchar(255) DEFAULT NULL,
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
    `userid` bigint DEFAULT 0,
    `proceedslv` int DEFAULT 0,
    UNIQUE INDEX role_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `scene_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `sceneid` int DEFAULT 0,
    `collects` blob,
    `season` blob,
    UNIQUE INDEX scene_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `scene_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `sceneid` int DEFAULT 0,
    `collects` blob,
    `season` blob,
    UNIQUE INDEX scene_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `scene_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `sceneid` int DEFAULT 0,
    `collects` blob,
    `season` blob,
    UNIQUE INDEX scene_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `skill_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `skill1` blob,
    `skill2` blob,
    `skill3` blob,
    `skill4` blob,
    UNIQUE INDEX skill_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `skill_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `skill1` blob,
    `skill2` blob,
    `skill3` blob,
    `skill4` blob,
    UNIQUE INDEX skill_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `skill_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `skill1` blob,
    `skill2` blob,
    `skill3` blob,
    `skill4` blob,
    UNIQUE INDEX skill_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `ptuser_0`(
    `version` bigint DEFAULT 0,
    `ptid` varchar(255) DEFAULT NULL,
    `pttype` int ,
    `userid` bigint DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `ptuser_1`(
    `version` bigint DEFAULT 0,
    `ptid` varchar(255) DEFAULT NULL,
    `pttype` int ,
    `userid` bigint DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `ptuser_2`(
    `version` bigint DEFAULT 0,
    `ptid` varchar(255) DEFAULT NULL,
    `pttype` int ,
    `userid` bigint DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `user_0`(
    `version` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `ptid` varchar(255) DEFAULT NULL,
    `pttype` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    `rolesdata` blob
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `user_1`(
    `version` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `ptid` varchar(255) DEFAULT NULL,
    `pttype` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    `rolesdata` blob
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `user_2`(
    `version` bigint DEFAULT 0,
    `userid` bigint DEFAULT 0,
    `ptid` varchar(255) DEFAULT NULL,
    `pttype` int DEFAULT 0,
    `createtime` bigint DEFAULT 0,
    `rolesdata` blob
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `mainlinetask_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `runningtask` int DEFAULT 0,
    `compleatetask0` blob,
    `compleatetask1` blob,
    `compleatetask2` blob,
    `compleatetask3` blob,
    `compleatetask4` blob,
    `compleatetask5` blob,
    `compleatetask6` blob,
    `compleatetask7` blob,
    `compleatetask8` blob,
    `compleatetask9` blob,
    `unlockfuncs` blob,
    UNIQUE INDEX mainlinetask_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `mainlinetask_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `runningtask` int DEFAULT 0,
    `compleatetask0` blob,
    `compleatetask1` blob,
    `compleatetask2` blob,
    `compleatetask3` blob,
    `compleatetask4` blob,
    `compleatetask5` blob,
    `compleatetask6` blob,
    `compleatetask7` blob,
    `compleatetask8` blob,
    `compleatetask9` blob,
    `unlockfuncs` blob,
    UNIQUE INDEX mainlinetask_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `mainlinetask_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `runningtask` int DEFAULT 0,
    `compleatetask0` blob,
    `compleatetask1` blob,
    `compleatetask2` blob,
    `compleatetask3` blob,
    `compleatetask4` blob,
    `compleatetask5` blob,
    `compleatetask6` blob,
    `compleatetask7` blob,
    `compleatetask8` blob,
    `compleatetask9` blob,
    `unlockfuncs` blob,
    UNIQUE INDEX mainlinetask_roleid(`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `pubmail_0`(
    `version` bigint DEFAULT 0,
    `mailid` int DEFAULT 0,
    `addresser` varchar(255) DEFAULT NULL,
    `title` varchar(255) DEFAULT NULL,
    `body` varchar(1024) DEFAULT NULL,
    `roles` varchar(1024) DEFAULT NULL,
    `attachment` varchar(512) DEFAULT NULL,
    `dt` bigint DEFAULT 0,
    `del` int DEFAULT 0,
    UNIQUE INDEX pubmail_mailid(`mailid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `pubmail_1`(
    `version` bigint DEFAULT 0,
    `mailid` int DEFAULT 0,
    `addresser` varchar(255) DEFAULT NULL,
    `title` varchar(255) DEFAULT NULL,
    `body` varchar(1024) DEFAULT NULL,
    `roles` varchar(1024) DEFAULT NULL,
    `attachment` varchar(512) DEFAULT NULL,
    `dt` bigint DEFAULT 0,
    `del` int DEFAULT 0,
    UNIQUE INDEX pubmail_mailid(`mailid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `pubmail_2`(
    `version` bigint DEFAULT 0,
    `mailid` int DEFAULT 0,
    `addresser` varchar(255) DEFAULT NULL,
    `title` varchar(255) DEFAULT NULL,
    `body` varchar(1024) DEFAULT NULL,
    `roles` varchar(1024) DEFAULT NULL,
    `attachment` varchar(512) DEFAULT NULL,
    `dt` bigint DEFAULT 0,
    `del` int DEFAULT 0,
    UNIQUE INDEX pubmail_mailid(`mailid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
