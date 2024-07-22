#include <iostream>
#include <filesystem>

#include "ImageFetcher.h"

/**
 * @brief Prints the help message.
 * @param program_name The name of the program.
 */
void print_help_message(const std::string& program_name) {
    std::string exec_name = std::filesystem::path(program_name).filename().stem().string();
    std::cout << "Usage: " << exec_name << " [OPTIONS]\n"
        << "Options:\n"
        << "  --releases         List supported releases.\n"
        << "  --versions         List versions of each release. (requires --releases)\n"
        << "  --current          Find the current LTS version.\n"
        << "  --sha256 <pubname> Find the SHA256 checksum of a release by pubname.\n"
        << "  --help             Display this help message.\n\n"
        << "Examples:\n"
        << "  " << exec_name << " --releases\n"
        << "  " << exec_name << " --current\n"
        << "  " << exec_name << " --sha256 ubuntu-lucid-10.04-amd64-server-20150427\n";
}

int main(int argc, char** argv) {
    const std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
    ImageFetcher fetcher(url);


    if (argc < 2) {
        print_help_message(argv[0]);
        return 1;
    }

    std::string arg1 = argv[1];

    if (arg1 == "--releases") {
        auto supported_releases = fetcher.get_supported_releases();
        for (const auto& product : supported_releases) {
            std::cout << product.second.at("release_title").get<std::string>() << " ("
                << product.second.at("release_codename").get<std::string>() << "): " << product.first << "\n";
            if (argc > 2 && std::string(argv[2]) == "--versions") {
                for (const auto& version : product.second.at("versions")) {
                    std::cout << "    " << version.at("version").get<std::string>() << ": "
                        << version.at("pubname").get<std::string>() << "\n";
                }
                std::cout << "\n";
            }
        }
    }
    else if (arg1 == "--current") {
        auto [title, codename] = fetcher.get_current_lts_version();
        if (!title.empty() && !codename.empty()) {
            std::cout << "Current Ubuntu LTS version is " << title << " (" << codename << ")\n";
        }
        else {
            std::cout << "No LTS version found.\n";
        }
    }
    else if (arg1 == "--sha256" && argc > 2) {
        std::string pubname = argv[2];
        std::string sha256 = fetcher.get_sha256_checksum(pubname);
        if (!sha256.empty()) {
            std::cout << "SHA256 checksum for " << pubname << " is " << sha256 << "\n";
        }
        else {
            std::cout << "Ubuntu release for " << pubname << "not found.\n";
        }
    }
    else if (arg1 == "--help") {
        print_help_message(argv[0]);
    }
    else {
        std::cerr << "Invalid arguments.\n";
        print_help_message(argv[0]);
        return 1;
    }

    return 0;
}
