CREATE TABLE `currency_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `currency1` varchar(4096) DEFAULT NULL,
    `currency2` varchar(4096) DEFAULT NULL,
    `currency3` varchar(4096) DEFAULT NULL,
    `currency4` varchar(4096) DEFAULT NULL,
    UNIQUE INDEX currency_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `currency_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `currency1` varchar(4096) DEFAULT NULL,
    `currency2` varchar(4096) DEFAULT NULL,
    `currency3` varchar(4096) DEFAULT NULL,
    `currency4` varchar(4096) DEFAULT NULL,
    UNIQUE INDEX currency_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `currency_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `snakeid` int DEFAULT 0,
    `currency1` varchar(4096) DEFAULT NULL,
    `currency2` varchar(4096) DEFAULT NULL,
    `currency3` varchar(4096) DEFAULT NULL,
    `currency4` varchar(4096) DEFAULT NULL,
    UNIQUE INDEX currency_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `cycleevent_0`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `events` varchar(4096) DEFAULT NULL,
    UNIQUE INDEX cycleevent_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `cycleevent_1`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `events` varchar(4096) DEFAULT NULL,
    UNIQUE INDEX cycleevent_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
CREATE TABLE `cycleevent_2`(
    `version` bigint DEFAULT 0,
    `roleid` bigint DEFAULT 0,
    `events` varchar(4096) DEFAULT NULL,
    UNIQUE INDEX cycleevent_roleid(`roleid`),
    PRIMARY KEY (`roleid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
