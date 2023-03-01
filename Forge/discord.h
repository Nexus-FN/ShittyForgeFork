#pragma once

#define CURL_STATICLIB

#include <iostream>
#include <string>
#include <curl/curl.h>

#include "xorstr.hpp"

class DiscordWebhook {
public:
    // Parameters:
    // - webhook_url: the discord HostingWebHook url
    DiscordWebhook(const char* webhook_url)
    {
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, webhook_url);

            // Discord webhooks accept json, so we set the content-type to json data.
            curl_slist* headers = curl_slist_append(NULL, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        else {
            std::cerr << "Error: curl_easy_init() returned NULL pointer" << '\n';
        }
    }

    ~DiscordWebhook()
    {
        curl_global_cleanup();
        curl_easy_cleanup(curl);
    }

    bool handleCode(CURLcode res)
    {
        return res == CURLE_OK;
    }

    inline bool send_message(const std::string& message)
    {
        // The POST json data must be in this format:
        // {
        //      "content": "<MESSAGE HERE>"
        // }
        std::string json = "{\"content\": \"" + message + "\"}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());

        bool success = handleCode(curl_easy_perform(curl));

        return success;
    }
    inline bool send_embedjson(const std::string ajson)
    {
        std::string json = ajson.contains("embeds") ? ajson : "{\"content\": " + ajson + "}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());

        bool success = handleCode(curl_easy_perform(curl));

        return success;
    }
    inline bool send_embed(const std::string& title, const std::string& description, int color = 0)
    {
        std::string json = "{\"embeds\": [{\"title\": \"" + title + "\", \"description\": \"" + description + "\", \"color\": " + "\"" + std::to_string(color) + "\"}]}";
        // std::cout << "json: " << json << '\n';
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());

        bool success = handleCode(curl_easy_perform(curl));

        return success;
    }
private:
    CURL* curl;
};

class JsonRequest {
public:
    // Parameters:
    // - webhook_url: the discord HostingWebHook url
    JsonRequest(const char* http_url)
    {
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, http_url);

            // Discord webhooks accept json, so we set the content-type to json data.
            curl_slist* headers = curl_slist_append(NULL, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        else {
            std::cerr << "Error: curl_easy_init() returned NULL pointer" << '\n';
        }
    }

    ~JsonRequest()
    {
        curl_global_cleanup();
        curl_easy_cleanup(curl);
    }

    // Sends the specified message to the HostingWebHook.
    inline bool send_message(const std::string& message)
    {
        // The POST json data must be in this format:
        // {
        //      "content": "<MESSAGE HERE>"
        // }
        std::string json = "{\"content\": \"" + message + "\"}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            // std::cerr << "Error: curl_easy_perform() failed: " << curl_easy_strerror(res) << '\n';
        }

        return res == CURLE_OK;
    }
private:
    CURL* curl;
};

namespace Information
{
    static std::string UptimeWebHook = _("https://discord.com/api/webhooks/1078826894344081480/IqkAES8bZwm6IXbcdmTj3Gkeq8MYmGiCr6uS6zfBQJVTh7-vgjxA1oFrcAiSiEaxpLxa");
    static std::string PlayerWebHook = _("https://discord.com/api/webhooks/1078834262159147059/j777xL-EA4FMXfunD04N1p0Oq83R1AC7z84k3_1z2F_eCDizQty1fJhZfboEiDHE6kdx");
    static std::string BanAPI = _("https://fn.zetax.dev/api/");
    static std::string ServerWebhook = _("https://discord.com/api/webhooks/1080136786417815602/X-8ox6oCDXFo2mJepSGswlg2LJE48hEmM1djZiFr05FeCRmfN6jA_tYf3lORSYRdAelU");
    static std::string DeathWebhook = _("https://discord.com/api/webhooks/1080138055249297438/KpCzKieSGmC3TUHU954l4k0xS8P6jcHUxBf8Wyqk1tqo8e3VmHxBT8sMPfmc9ohuofg6");
}               

static DiscordWebhook UptimeWebHook(Information::UptimeWebHook.c_str());
static DiscordWebhook PlayerWebHook(Information::PlayerWebHook.c_str());
static DiscordWebhook BanAPI(Information::BanAPI.c_str());
static DiscordWebhook ServerWebhook(Information::ServerWebhook.c_str());
static DiscordWebhook DeathWebhook(Information::DeathWebhook.c_str());
