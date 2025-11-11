#ifndef APP_HPP
#define APP_HPP

#include <string>
#include <vector>
#include "storage.hpp"
#include "crypto.hpp"

namespace app {

// initialize app (load libsodium, set paths)
void init();

// master unlock: derive key from user password
std::vector<unsigned char> unlock(const std::string& masterPassword);

// core functions
void createEntry(const std::string& name,
                 const std::string& username,
                 const std::string& password,
                 const std::vector<unsigned char>& key);

void listEntries(const std::vector<unsigned char>& key);
void deleteEntry(const std::string& name, const std::vector<unsigned char>& key);

// run loop or GUI start
void run();

} // namespace app

#endif
