#ifndef IMAGE_FETCHER_H
#define IMAGE_FETCHER_H

#include "ImageFetcherInterface.h"
#include <curl/curl.h>

/**
 * @brief Derived class implementing the ImageFetcherInterface for Ubuntu cloud images.
 */
class ImageFetcher : public ImageFetcherInterface {
public:
    /**
     * @brief Constructs a new UbuntuImageFetcher object.
     * @param url The URL of the JSON data.
     */
    ImageFetcher(const std::string& url);

    std::map<std::string, nlohmann::json> get_supported_releases() const override;
    std::tuple<std::string, std::string> get_current_lts_version() const override;
    std::string get_sha256_checksum(const std::string& pubname) const override;

private:
    std::string url;
    nlohmann::json json_data;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
    nlohmann::json fetch_json_data();
};

#endif // IMAGE_FETCHER_H
