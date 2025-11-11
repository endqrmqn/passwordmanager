#include "crypto.hpp"
#include <stdexcept>
#include <cstring>   // for memset
#include <sodium.h>  // assuming you’re using libsodium

namespace crypto {

// -----------------------------------------------------------------------------
// initialize libsodium or crypto backend
// -----------------------------------------------------------------------------
void init() {
    if (sodium_init() < 0) {
        throw std::runtime_error("libsodium initialization failed");
    }
}

// -----------------------------------------------------------------------------
// derive a key from master password using Argon2id
// -----------------------------------------------------------------------------
std::vector<unsigned char> deriveKey(const std::string& masterPassword,
                                     const std::vector<unsigned char>& salt) {
    std::vector<unsigned char> key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES);

    if (crypto_pwhash(key.data(), key.size(),
                      masterPassword.c_str(), masterPassword.size(),
                      salt.data(),
                      crypto_pwhash_OPSLIMIT_MODERATE,
                      crypto_pwhash_MEMLIMIT_MODERATE,
                      crypto_pwhash_ALG_ARGON2ID13) != 0) {
        throw std::runtime_error("key derivation failed (out of memory?)");
    }

    return key;
}

// -----------------------------------------------------------------------------
// encrypt plaintext using XChaCha20-Poly1305 AEAD
// -----------------------------------------------------------------------------
EncryptedData encrypt(const std::string& plaintext,
                      const std::vector<unsigned char>& key) {
    EncryptedData out;

    // generate salt and nonce
    out.salt.resize(crypto_pwhash_SALTBYTES);
    out.nonce.resize(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES);
    randombytes_buf(out.salt.data(), out.salt.size());
    randombytes_buf(out.nonce.data(), out.nonce.size());

    // prepare ciphertext buffer (+MAC)
    out.ciphertext.resize(plaintext.size() + crypto_aead_xchacha20poly1305_ietf_ABYTES);

    unsigned long long clen = 0;

    if (crypto_aead_xchacha20poly1305_ietf_encrypt(
            out.ciphertext.data(), &clen,
            reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size(),
            nullptr, 0,                   // no AAD
            nullptr, out.nonce.data(), key.data()) != 0) {
        throw std::runtime_error("encryption failed");
    }

    out.ciphertext.resize(clen);
    return out;
}

// -----------------------------------------------------------------------------
// decrypt ciphertext using XChaCha20-Poly1305 AEAD
// -----------------------------------------------------------------------------
std::string decrypt(const EncryptedData& enc,
                    const std::vector<unsigned char>& key) {
    std::string plaintext(enc.ciphertext.size(), '\0');
    unsigned long long mlen = 0;

    if (crypto_aead_xchacha20poly1305_ietf_decrypt(
            reinterpret_cast<unsigned char*>(&plaintext[0]), &mlen,
            nullptr,
            enc.ciphertext.data(), enc.ciphertext.size(),
            nullptr, 0, enc.nonce.data(), key.data()) != 0) {
        throw std::runtime_error("decryption failed or data corrupted");
    }

    plaintext.resize(mlen);
    return plaintext;
}

// -----------------------------------------------------------------------------
// securely zero memory
// -----------------------------------------------------------------------------
void secureZero(void* ptr, size_t len) {
    if (ptr && len > 0) {
        sodium_memzero(ptr, len);
    }
}

} // namespace crypto
