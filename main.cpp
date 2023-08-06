#include "encoder.h"

int main() {
    Encoder encoder;
    const auto& decodedOutput = encoder.base64Decode("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
    std::cout << decodedOutput << std::endl;
    return 0;
}