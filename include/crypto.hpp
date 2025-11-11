#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <string>
#include <vector>

namespace crypto {

struct EncryptedData {
    std::vector<unsigned char> ciphertext;
    std::vector<unsigned char> nonce;
    std::vector<unsigned char> salt;
};

// initialize libsodium or crypto library
void init();

// derive a key from master password (Argon2id)
std::vector<unsigned char> deriveKey(const std::string& masterPassword,
                                     const std::vector<unsigned char>& salt);

// encrypt/decrypt using AEAD (AES-GCM or XChaCha20-Poly1305)
EncryptedData encrypt(const std::string& plaintext,
                      const std::vector<unsigned char>& key);

std::string decrypt(const EncryptedData& enc,
                    const std::vector<unsigned char>& key);

// secure memory wipe
void secureZero(void* ptr, size_t len);

} // namespace crypto

#endif
