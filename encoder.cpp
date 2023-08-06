#include "encoder.h"

std::string Encoder::base64Encode(const std::string& stringToEncode) {
    std::string output;
    const unsigned long long length = stringToEncode.length();
    const unsigned long long numCompleteBlocks = length / 3;
    const unsigned int leftover = length % 3;
    const unsigned long long outputLength = numCompleteBlocks * 4 + (leftover > 0 ? 4 : 0);

    if(outputLength > 0)
        output.resize(outputLength);

    for(auto i = 0, j = 0; i < length; i += 3, j += 4) {
        auto c1 = stringToEncode[i];
        auto c2 = i + 1 < length ? stringToEncode[i + 1] : 0x00;
        auto c3 = i + 2 < length ? stringToEncode[i + 2] : 0x00;

        output[j] = base64EncodingTable[(c1 & 0xFC) >> 2];
        output[j + 1] = base64EncodingTable[((c1 & 0x03) << 4) | ((c2 & 0xF0) >> 4)];
        output[j + 2] = base64EncodingTable[((c2 & 0x0F) << 2) | ((c3 & 0xC0) >> 6)];
        output[j + 3] = base64EncodingTable[c3 & 0x3F];
    }

    if(leftover == 1) {
        output[outputLength - 1] = '=';
        output[outputLength - 2] = '=';
    } else if(leftover == 2) {
        output[outputLength - 1] = '=';
    }

    return output;
}

std::string Encoder::base64Decode(const std::string& stringToDecode) {
    std::string output;
    const unsigned long long length = stringToDecode.length();
    unsigned int padding = 0;
    if(length > 0)
        padding = stringToDecode[length - 1] == '=' ? 1 : padding;
    if(length > 1)
        padding = stringToDecode[length - 2] == '=' ? 2 : padding;
    const unsigned long long numCompleteBlocks = length / 4;
    const unsigned long long outputLength = numCompleteBlocks * 3 - padding;
    
    if(outputLength > 0)
        output.resize(outputLength);

    for(int i = 0, j = 0; i < length; i += 4, j += 3) {
        auto c1 = base64DecodingTable[stringToDecode[i]];
        auto c2 = base64DecodingTable[stringToDecode[i + 1]];
        auto c3 = base64DecodingTable[stringToDecode[i + 2]];
        auto c4 = base64DecodingTable[stringToDecode[i + 3]];

        output[j] = (c1 << 2) | ((c2 & 0x30) >> 4);
        output[j + 1] = ((c2 & 0x0F) << 4) | ((c3 & 0x3C) >> 2);
        output[j + 2] = ((c3 & 0x03) << 6) | c4;
    }

    return output;
}