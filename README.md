# Channel Private Version

<img src="https://cdn.zetax.dev/A8LHbkJu3gtZ/direct" alt= "Channel logo" width="250" height="250">

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

[![MSBuild](https://github.com/Channelmp/GameserverPrivate/actions/workflows/msbuild.yml/badge.svg)](https://github.com/Channelmp/GameserverPrivate/actions/workflows/msbuild.yml)

### 10.40 private gameserver forked from Forge by ForgeFN

Most code is skidded from [here](https://github.com/ForgeFN/Forge)

Features marked with + are added by me

With following features:

- Auto starting with defined amount of players +
- Checking if a player is banned via an API +
- Changing your skin via Discord bot command and website +
- Proper looting
- Chest stars
- Vending machine colors
- Teams
- Reboot cards
- Directional fix + weakspot fix
- Vehicles
- Semi working creative (framework.h)
- Some little gameplay features
- Pretty accurate harvesting rate
- Run over ammo & mats
- Pickup delay
- Repairing
- S8+ map markers
- Killfeed

### To do

- [ ] Auto restarting after round ends
- [x] Call an API for required players instead of text file
- [ ] Make playground work

#### How to use the cheat commands

If you are hosting the server on a vps, then go to admin.h, it should be around line #17 and you should see "IPStr == "127.0.0.1".
Right after this you want to add || "YOURIPHERE". So it would look something like 	
```
if (IPStr == "127.0.0.1" || IPStr == "29.238.102.57" || .....)
```

![](https://komarev.com/ghpvc/?username=Finninn)
