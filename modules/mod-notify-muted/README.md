# PlayerNotSpeak [![Build Status](https://travis-ci.com/Winfidonarleyan/PlayerNotSpeak-module.svg?branch=master)](https://travis-ci.com/Winfidonarleyan/PlayerNotSpeak-module)

### This is a module for [AzerothCore](http://www.azerothcore.org)

### Features:
- This module notifies the player (who wrote a private message) that his interlocutor can not talk (if his chat is not available)

### Config option (PlayerNotSpeak.conf.dist)
- PlayerNotSpeak.Enable (Enable/Disable module)

### This module currently requires:
- AzerothCore v1.0.1+

### How to install
1. Simply place the module under the `modules` folder of your AzerothCore source folder.
2. Re-run cmake and launch a clean build of AzerothCore
3. Apply sql file in DB world `(./sql/world.trinity_string.sql)`
4. (Optional) Edit module configuration (PlayerNotSpeak.conf.dist)
5. Done :)

### Usage
- Write to the player, whose chat is disabled

## Credits
* [Winfidonarleyan](https://github.com/Winfidonarleyan): (author of the module): 
* [BarbzYHOOL](https://github.com/barbzyhool): best guy
* [Talamortis](https://github.com/talamortis): almost best guy

AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)
