# Channel

<img src="https://cdn.zetax.dev/A8LHbkJu3gtZ/direct" alt= "Channel logo" width="200" height="200">

#### 10.40 gameserver forked from Forge by ForgeFN

*Please note that I am shit at C++ and don't really have any idea what I'm doing*

Most code is skidded from [here](https://github.com/ForgeFN/Forge)

With following features:

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

#### How to use the cheat commands

If you are hosting the server on a vps, then go to admin.h, it should be around line #17 and you should see "IPStr == "127.0.0.1".
Right after this you want to add || "YOURIPHERE". So it would look something like 	
```
if (IPStr == "127.0.0.1" || IPStr == "29.238.102.57" || .....)
```
