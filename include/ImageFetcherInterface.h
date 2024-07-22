#ifndef IMAGE_FETCHER_INTERFACE_H
#define IMAGE_FETCHER_INTERFACE_H

#include <string>
#include <map>
#include <tuple>
#include <nlohmann/json.hpp>

/**
 * @brief Interface class defining the methods for fetching Ubuntu cloud image data.
 */
class ImageFetcherInterface {
public:
    virtual ~ImageFetcherInterface() = default;

    /**
     * @brief Gets the list of supported releases.
     * @return A map of supported releases and their details.
     */
    virtual std::map<std::string, nlohmann::json> get_supported_releases() const = 0;

    /**
     * @brief Gets the current LTS version.
     * @return A tuple containing the LTS release title and codename.
     */
    virtual std::tuple<std::string, std::string> get_current_lts_version() const = 0;

    /**
     * @brief Gets the SHA256 checksum for the specified release by pubname.
     * @param pubname The pubname of the release.
     * @return The SHA256 checksum.
     */
    virtual std::string get_sha256_checksum(const std::string& pubname) const = 0;
};

#endif // IMAGE_FETCHER_INTERFACE_H
