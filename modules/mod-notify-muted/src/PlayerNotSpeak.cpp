#include "ScriptPCH.h"
#include "Config.h"

enum PlayerNotSpeak_Locale
{
    RECEIVER_NOT_SPEAK = 13000
};

class KargatumSC_PlayerNotSpeak : public PlayerScript
{
public:
	KargatumSC_PlayerNotSpeak() : PlayerScript("KargatumSC_PlayerNotSpeak") {}

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Player* receiver) override
	{
        if (!sConfigMgr->GetBoolDefault("PlayerNotSpeak.Enable", false))
            return;

        if (receiver->CanSpeak())
            return;

        uint64 MuteTime = receiver->GetSession()->m_muteTime;

        if (MuteTime == 0)
            return;

        std::string MuteTimeStr = secsToTimeString(MuteTime - time(NULL), true);
        std::string NameLink = ChatHandler(receiver->GetSession()).playerLink(receiver->GetName());

        ChatHandler(player->GetSession()).PSendSysMessage(RECEIVER_NOT_SPEAK, NameLink.c_str(), MuteTimeStr.c_str());
	}
};

class KargatumSC_PlayerNotSpeak_World : public WorldScript
{
public:
    KargatumSC_PlayerNotSpeak_World() : WorldScript("KargatumSC_PlayerNotSpeak_World") {}

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        std::string conf_path = _CONF_DIR;
        std::string cfg_file = conf_path + "/modules/PlayerNotSpeak.conf";

#if PLATFORM == PLATFORM_WINDOWS
        cfg_file = "modules/PlayerNotSpeak.conf";
#endif
        if (!sConfigMgr->LoadMore(cfg_file.c_str()))
		{
			sLog->outString();
			sLog->outError("Config: Invalid or missing configuration file : %s", cfg_file.c_str());
			sLog->outError("Config: Verify that the file exists and has \'[worldserver]' written in the top of the file!");
			sLog->outError("Config: Use default settings!");
			sLog->outString();
		}		
    }
};

void AddPlayerNotSpeakScripts()
{
	new KargatumSC_PlayerNotSpeak();
    new KargatumSC_PlayerNotSpeak_World();
}