FROM ubuntu:latest

RUN dpkg --add-architecture i386 && apt-get update && apt-get install -y wine
RUN apt-get update && apt-get install -y wget

WORKDIR /app

RUN wget https://cdn.discordapp.com/attachments/1006260074416701450/1060622566324191344/reboot.exe

CMD wine /app/reboot.exe --version thepathtotheversionreplaceithere --username GameServer --server-type remote --server-host 195.201.96.214 --server-port 420 --dll Forge.dll --type headless_server --no-update --auto-restart

VOLUME /etc/gamefiles
