#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Creature.h"
#include "AccountMgr.h"
#include "Define.h"
#include "GossipDef.h"
#include "DataMap.h"
class QuickTeleport : public CommandScript{
public:

    QuickTeleport() : CommandScript("QuickTeleport") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> TeleportTable =
        {

            { "home", SEC_PLAYER, false, &HandleHomeTeleportCommand, "" },
            { "arena", SEC_PLAYER, false, &HandleArenaTeleportCommand, ""}

        };
        return TeleportTable;
    }

    static bool HandleHomeTeleportCommand(ChatHandler* handler, char const* args)
    {
        Player* me = handler->GetSession()->GetPlayer();
        std::string home = sConfigMgr->GetStringDefault("QuickTeleport.homeLocation", "");
        bool enabled = sConfigMgr->GetBoolDefault("QuickTeleport.enabled", true);

        QueryResult result = WorldDatabase.PQuery("SELECT `map`, `position_x`, `position_y`, `position_z`, `orientation` FROM game_tele WHERE name = '%s'", home.c_str());

        if (!enabled)
            return false;

        if (!me)
            return false;

        if (me->IsInCombat())
            return false;

        if (!result)
            return false;

        do
        {
            Field* fields = result->Fetch();
            uint32 map = fields[0].GetUInt32();
            float position_x = fields[1].GetFloat();
            float position_y = fields[2].GetFloat();
            float position_z = fields[3].GetFloat();
            float orientation = fields[4].GetFloat();

            me->TeleportTo(map, position_x, position_y, position_z, orientation);
        } while (result->NextRow());
        return true;
    }

    static bool HandleArenaTeleportCommand(ChatHandler* handler, char const* args)
    {
        bool enabled = sConfigMgr->GetBoolDefault("QuickTeleport.enabled", false);
        std::string arena = sConfigMgr->GetStringDefault("QuickTeleport.arenaLocation", "");

        QueryResult result = WorldDatabase.PQuery("SELECT `map`, `position_x`, `position_y`, `position_z`, `orientation` FROM game_tele WHERE name = '%s'", arena.c_str());
        Player* p = handler->GetSession()->GetPlayer();

        if (!enabled)
            return false;

        if (!p)
            return false;

        if (p->IsInCombat())
            return false;

        if (!result)
            return false;

        do
        {
            Field* fields = result->Fetch();
            uint32 map = fields[0].GetUInt32();
            float position_x = fields[1].GetFloat();
            float position_y = fields[2].GetFloat();
            float position_z = fields[3].GetFloat();
            float orientation = fields[4].GetFloat();

            p->TeleportTo(map, position_x, position_y, position_z, orientation);
        } while (result->NextRow());
        return true;
    }

};

class quick_teleport_conf : public WorldScript
{
public:
    quick_teleport_conf() : WorldScript("quick_teleport_conf") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/quick_teleport.conf";

#ifdef WIN32
            cfg_file = "quick_teleport.conf";
#endif

            std::string cfg_def_file = cfg_file + ".dist";
            sConfigMgr->LoadMore(cfg_def_file.c_str());
            sConfigMgr->LoadMore(cfg_file.c_str());
        }
    }
};

void AddQuickTeleportScripts() {
    new QuickTeleport();
    new quick_teleport_conf();
}

