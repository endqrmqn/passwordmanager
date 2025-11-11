#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <vector>
#include "crypto.hpp"

namespace storage {

struct Entry {
    std::string name;    // e.g. "GitHub"
    std::string username;
    std::string password; // plaintext only while editing
};

// load all entries from encrypted DB file
std::vector<Entry> loadDatabase(const std::string& filePath,
                                const std::vector<unsigned char>& key);

// save all entries to encrypted DB file
bool saveDatabase(const std::string& filePath,
                  const std::vector<Entry>& entries,
                  const std::vector<unsigned char>& key);

// simple helper for checking file existence
bool fileExists(const std::string& path);

} // namespace storage

#endif
