-- DB update 2018_01_21_00 -> 2018_09_17_00
DROP PROCEDURE IF EXISTS `updateDb`;
DELIMITER //
CREATE PROCEDURE updateDb ()
proc:BEGIN DECLARE OK VARCHAR(100) DEFAULT 'FALSE';
SELECT COUNT(*) INTO @COLEXISTS
FROM information_schema.COLUMNS
WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'version_db_auth' AND COLUMN_NAME = '2018_01_21_00';
IF @COLEXISTS = 0 THEN LEAVE proc; END IF;
START TRANSACTION;
ALTER TABLE version_db_auth CHANGE COLUMN 2018_01_21_00 2018_09_17_00 bit;
SELECT sql_rev INTO OK FROM version_db_auth WHERE sql_rev = '1534268747940576100'; IF OK <> 'FALSE' THEN LEAVE proc; END IF;
--
-- START UPDATING QUERIES
--

INSERT INTO version_db_auth (`sql_rev`) VALUES ('1534268747940576100');

ALTER TABLE `account` 
ADD COLUMN `totaltime` int(10) UNSIGNED NOT NULL DEFAULT 0 AFTER `recruiter`;

--
-- END UPDATING QUERIES
--
COMMIT;
END //
DELIMITER ;
CALL updateDb();
DROP PROCEDURE IF EXISTS `updateDb`;
