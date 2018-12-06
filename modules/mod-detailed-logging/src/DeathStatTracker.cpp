#include "Configuration/Config.h"
#include "Player.h"
#include "ScriptMgr.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

using std::stringstream;

class DeathStatTracker : public PlayerScript {
public:

  stringstream fullStream;
  bool loggingEnabled = sConfigMgr->GetBoolDefault("KillDetailedLogging.enabled", true);
  int logDumpSize = sConfigMgr->GetIntDefault("KillDetailedLogging.dumpSize", 0);

  DeathStatTracker() : PlayerScript("DeathStatTracker") {

    // If the file doesn't exist we will create it and add the appropriate headers

    ifstream ifile("deaths.log");
    if (!ifile) {
       fullStream << "timestamp,player,faction,level,maxhealth,currenthealth,creature,creaturefaction,creaturemaxhealth,zoneid,areaid,isgamemaster\n";
       StringDump();
    }

  }

  void OnPlayerKilledByCreature(Creature *creature, Player *player) override{
    if (loggingEnabled){
      stringstream killStream;

      auto t = std::time(nullptr);
      auto tm = *std::localtime(&t);

      killStream << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ",";
      killStream << player->GetName() << "," << player->getFaction() << "," << player->getLevel() << "," << player->GetMaxHealth() << "," << player->GetHealth() << ",";
      killStream << creature->GetName() << "," << creature->getFaction() << "," << creature->GetMaxHealth() << ",";
      killStream << player->GetZoneId() << "," << player->GetAreaId() << "," << player->IsGameMaster();
      killStream << "\n";

      fullStream << killStream.str();
      StringDump();
    }
  }

 
private:

  int insertCount = 0;

  void StringDump(){

    insertCount++;

    if (insertCount > logDumpSize){
      // Dump to log
      ofstream logFile;
      logFile.open ("deaths.log", ofstream::app);
      logFile << fullStream.rdbuf();
      logFile.close();

      // Reset the buffer
      fullStream.str("");
      fullStream.clear();

      // Reset line count
      insertCount = 0;
    }
  }
};

class death_logging_conf : public WorldScript
{
public:
    death_logging_conf() : WorldScript("death_logging_conf") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/detail_logging.conf";
#ifdef WIN32
            cfg_file = "detail_logging.conf";
#endif
            std::string cfg_def_file = cfg_file + ".dist";

            sConfigMgr->LoadMore(cfg_def_file.c_str());

            sConfigMgr->LoadMore(cfg_file.c_str());
        }
    }
};

void AddDeathStatTrackerScripts() { 
  new DeathStatTracker(); 
  new death_logging_conf();
  }
