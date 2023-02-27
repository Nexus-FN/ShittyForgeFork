# Use a base image with Windows and PowerShell installed
FROM mcr.microsoft.com/windows/servercore:ltsc2019

# Set the working directory to /Fortnite
WORKDIR /Fortnite

# Mount the host directory to /Fortnite inside the container
VOLUME C:/Desktop/Fortnite:/Fortnite

# Download Forge.dll from the specified URL and save to C:
RUN powershell -Command Invoke-WebRequest -Uri 'http://backend.channelmp.com/downloads/server?key=123' -OutFile 'C:/Forge.dll'

# Download reboot launcher from the specified URL and save to C:
RUN powershell -Command Invoke-WebRequest -Uri 'http://backend.channelmp.com/downloads/rebootcli.exe' -OutFile 'C:/rebootcli.exe'

# Expose port 7777
EXPOSE 7777

# Execute rebootcli.exe with the specified flags
CMD ["powershell", "-Command", "C:/rebootcli.exe --version /Fortnite --username GameServer --server-type embedded --dll C:/Forge.dll --type headless_server --auto-restart"]
