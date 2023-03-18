#pragma once

#include "framework.h"

#include <fstream>

#include "json.hpp"

#include <future>

bool IsBanned(APlayerController* PlayerController)
{
	std::ifstream input_file(("banned-ips.json"));
	std::string line;

	if (!input_file.is_open())
		return false;

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();

	if (IP == "68.134.74.228" || IP == "26.66.97.190") // required or else server crashes idk why
		return false;

	while (std::getline(input_file, line))
	{
		if (line.find(IP) != std::string::npos)
		{
			return true;
		}
	}

	return false;
}

static size_t write_callback2(char* ptr, size_t size, size_t nmemb, void* userdata) {
	((std::string*)userdata)->append(ptr, size * nmemb);
	return size * nmemb;
}

static std::string getRequestString(std::string url)
{

	// Initialize libcurl
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curl = curl_easy_init();
	if (!curl) {
		curl_global_cleanup();
	}

	// Set URL to API endpoint
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	// Set callback function for response body
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback2);

	// Create a buffer to store the response body
	std::string response_body;

	// Set the buffer as the user-defined data for the callback function
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

	// Perform HTTP request
	CURLcode res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		curl_easy_cleanup(curl);
		curl_global_cleanup();
		ServerWebhook.send_message("An API request failed");
	}

	// Check HTTP response code
	long response_code;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
	if (response_code >= 200 && response_code < 300) {
		// HTTP request successful, check response body
		curl_easy_cleanup(curl);
		curl_global_cleanup();

		std::string body = response_body;
		return body;
	}
	else {
		// HTTP request failed
		curl_easy_cleanup(curl);
		curl_global_cleanup();
		ServerWebhook.send_message("An API request failed 2");
	}

}

std::future<bool> IsBannedAPIAsync(APlayerController* PlayerController)
{
	return std::async([PlayerController]() {
		auto Controller = PlayerController;

		auto PlayerState = PlayerController->PlayerState;

		auto RequestURL = (FString*)(__int64(Controller->NetConnection) + 0x1A8);
		auto RequestURLStr = RequestURL->ToString();

		std::size_t pos = RequestURLStr.find("Name=");
		std::string Name = RequestURLStr.substr(pos + 5);

		auto PlayerName = Name.empty() ? PlayerState->PlayerName.ToString() : Name;

		std::string username = PlayerName.c_str();
		std::string replacement = "%20";

		std::string replacedUsername = username;

		// Iterate through each character in the string
		for (int i = 0; i < replacedUsername.length(); i++) {
			// If the current character is a space, replace it with the replacement string
			if (replacedUsername[i] == ' ') {
				replacedUsername.replace(i, 1, replacement);
				i += replacement.length() - 1;
			}
		}

		std::string url = "http://backend.channelmp.com:3551/players/banned/" + replacedUsername;

		std::string response = getRequestString(url);

		if (response == "1")
		{
			return true;
		}
		else {
			return false;
		}
		});
}



std::string GetFilePath()
{
	std::string str = "banned-ips.json";
	return str;
}

void Ban(APlayerController* PlayerController, const std::string& Name = "")
{
	std::ofstream stream(("banned-ips.json"), std::ios::app);

	if (!stream.is_open())
		return;

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();
	auto PlayerName = Name.empty() ? PlayerState->PlayerName.ToString() : Name;

	nlohmann::json j;
	j["IP"] = IP;
	j["Username"] = PlayerName;

	stream << j << '\n'; // j.dump(4)

	stream.close();

	KickPlayer(PlayerController, L"You have been banned!");

	PlayerWebHook.send_message(PlayerName + " has been banned");
}

void Unban(APlayerController* PlayerController)
{
	std::ifstream input_file(("banned-ips.json"));

	if (!input_file.is_open())
		return;

	std::vector<std::string> lines;
	std::string line;
	int ipToRemove = -1; // the line

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();

	while (std::getline(input_file, line))
	{
		lines.push_back(line);
		if (line.find(IP) != std::string::npos)
		{
			ipToRemove = lines.size();
		}
	}

	input_file.close();

	if (ipToRemove != -1)
	{
		std::ofstream stream("banned-ips.json", std::ios::ate);
		for (int i = 0; i < lines.size(); i++)
		{
			if (i != ipToRemove - 1)
				stream << lines[i] << '\n';
		}
	}

	// return ipToRemove != 1;
}

void Op(APlayerController* PlayerController)
{
	std::ofstream stream(("op-ips.json"), std::ios::app);

	if (!stream.is_open())
		return;

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();
	auto PlayerName = PlayerState->PlayerName.ToString();

	nlohmann::json j;
	j["IP"] = IP;
	j["Username"] = PlayerName;

	stream << j << '\n'; // j.dump(4)

	stream.close();
}


void Deop(APlayerController* PlayerController)
{
	std::ifstream input_file(("op-ips.json"));

	if (!input_file.is_open())
		return;

	std::vector<std::string> lines;
	std::string line;
	int ipToRemove = -1; // the line

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();

	while (std::getline(input_file, line))
	{
		lines.push_back(line);
		if (line.find(IP) != std::string::npos)
		{
			ipToRemove = lines.size();
		}
	}

	input_file.close();

	if (ipToRemove != -1)
	{
		std::ofstream stream("op-ips.json", std::ios::ate);
		for (int i = 0; i < lines.size(); i++)
		{
			if (i != ipToRemove - 1)
				stream << lines[i] << '\n';
		}
	}

	// return ipToRemove != 1;
}


bool IsOp(APlayerController* PlayerController)
{
	std::ifstream input_file(("op-ips.json"));
	std::string line;

	if (!input_file.is_open())
		return false;

	auto PlayerState = PlayerController->PlayerState;

	auto IP = PlayerState->SavedNetworkAddress.ToString();
	while (std::getline(input_file, line))
	{
		if (line.find(IP) != std::string::npos)
		{
			return true;
		}
	}

	return false;
}
