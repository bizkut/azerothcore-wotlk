#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "Configuration/Config.h"

class character_tools : public ItemScript
{
public:
    character_tools() : ItemScript("character_tools") {}

    bool OnUse(Player* p, Item* i, SpellCastTargets const& /*targets*/) override
    {
        p->PlayerTalkClass->ClearMenus();

        if (p->IsInCombat())
            return false;

        if (!sConfigMgr->GetBoolDefault("CharacterTools", true))
            return false;

        p->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/Ability_Paladin_BeaconofLight:50:50|tChange My Race", GOSSIP_SENDER_MAIN, 1);
        p->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/INV_BannerPVP_01:50:50|tChange My Faction", GOSSIP_SENDER_MAIN, 2);
        p->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/Achievement_BG_returnXflags_def_WSG:50:50|tChange My Appearance", GOSSIP_SENDER_MAIN, 3);
        p->ADD_GOSSIP_ITEM(NULL, "|TInterface/Icons/INV_Inscription_Scroll:50:50|tChange My Name", GOSSIP_SENDER_MAIN, 4);
        p->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, i->GetGUID());


        return false; // If item has spell cast it normal.
    }

    void OnGossipSelect(Player* player, Item* item, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case 1:
            player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
            ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for race change.");
            break;
        case 2:
            player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
            ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for faction change.");
            break;
        case 3:
            player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
            ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for Character Customize.");
            break;
        case 4:
            player->SetAtLoginFlag(AT_LOGIN_RENAME);
            ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for name change.");
            break;
        }
    }

};

class character_tools_world : public WorldScript
{
public:
    character_tools_world() : WorldScript("character_tools_world") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string cfg_file = "character_tools.conf";
            std::string cfg_def_file = cfg_file + ".dist";

            sConfigMgr->LoadMore(cfg_def_file.c_str());

            sConfigMgr->LoadMore(cfg_file.c_str());
        }
    }
};

void AddCharacterToolsScripts()
{
    new character_tools();
    new character_tools_world();
}