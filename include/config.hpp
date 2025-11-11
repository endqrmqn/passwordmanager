#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

namespace config {
    const std::string DATABASE_PATH = "data/passwords.db";
    const size_t KEY_SIZE = 32;  // 256-bit AES or ChaCha20 key
    const size_t NONCE_SIZE = 24;
    const size_t SALT_SIZE = 16;
}

#endif
