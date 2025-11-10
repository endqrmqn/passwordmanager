# Personal Password Manager

A lightweight C++ password manager and generator with local encryption and a simple GUI.  
This project is designed as a **personal educational tool** to explore secure storage,
encryption, and systems-level design — not as a production password manager.

---

## Features
- AES-256 or ChaCha20-Poly1305 encryption using libsodium/OpenSSL  
- Argon2id key derivation from a master password  
- Local encrypted storage (SQLite or binary format)  
- Configurable password generation (length, symbols, entropy)  
- Clipboard copy with auto-clear  
- Optional Qt or Dear ImGui interface  

---

## Project Structure

---

## Educational Purpose
This project was built by **Adi Jha** for personal use and learning purposes.
It serves as a hands-on exploration of:
- Cryptographically secure random number generation  
- Key derivation and symmetric encryption  
- Secure memory handling and file storage in C++  
- GUI integration with backend encryption systems  

---

## Disclaimer
This software is **not intended for production use** or the storage of real credentials.  
It is provided *as is*, without warranty of any kind.  
Use or modification is at your own risk.

> **In short:** this is a personal project that I (Adi Jha) use to experiment with encryption and local storage — not a secure password manager. Do **not** use it to store actual passwords or sensitive data.

---

## License
This project is licensed under the [MIT License](./LICENSE).

See the [LICENSE](./LICENSE) file for full details.
