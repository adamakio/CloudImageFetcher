#include "ImageFetcher.h"
#include <stdexcept>
#include <iostream>

/**
 * @brief Constructs a new UbuntuImageFetcher object.
 * @param url The URL of the JSON data.
 */
ImageFetcher::ImageFetcher(const std::string& url) : url(url) {
    json_data = fetch_json_data();
}

size_t ImageFetcher::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t total_size = size * nmemb;
    s->append(static_cast<char*>(contents), total_size);
    return total_size;
}

nlohmann::json ImageFetcher::fetch_json_data() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            throw std::runtime_error("Failed to download the JSON file");
        }
    }

    return nlohmann::json::parse(readBuffer);
}

std::map<std::string, nlohmann::json> ImageFetcher::get_supported_releases() const {
    std::map<std::string, nlohmann::json> supported_releases;
    for (const auto& product : json_data["products"].items()) {
        if (product.value().at("supported").get<bool>()) {
            supported_releases[product.key()] = {
                {"release_codename", product.value().at("release_codename")},
                {"release_title", product.value().at("release_title")},
                {"versions", nlohmann::json::array()}
            };
            for (const auto& version : product.value().at("versions").items()) {
                supported_releases[product.key()]["versions"].push_back({
                    {"version", version.key()},
                    {"pubname", version.value().at("pubname")}
                    });
            }
        }
    }
    return supported_releases;
}

std::tuple<std::string, std::string> ImageFetcher::get_current_lts_version() const {
    std::string latest_lts_title;
    std::string latest_lts_codename;
    std::string latest_version;

    for (const auto& product : json_data["products"].items()) {
        const auto& details = product.value();
        if (details.contains("release_title") && details["release_title"].get<std::string>().find("LTS") != std::string::npos) {
            std::string version = details["version"].get<std::string>();
            // Assuming we want the latest major version and not the latest release date
            if (latest_version.empty() || details["version"].get<std::string>() > latest_version) {
                latest_version = version;
                latest_lts_title = details["release_title"].get<std::string>();
                latest_lts_codename = details["release_codename"].get<std::string>();
            }
        }
    }

    return { latest_lts_title, latest_lts_codename };
};

std::string ImageFetcher::get_sha256_checksum(const std::string& pubname) const {
    return "";
};
