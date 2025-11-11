#include <sodium.h>
#include <iostream>
int main() {
    if (sodium_init() < 0) {
        std::cerr << "libsodium init failed\n";
        return 1;
    }
    std::cout << "libsodium works!\n";
}
