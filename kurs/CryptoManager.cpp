#include "CryptoManager.h"

string salt()
{       
    CryptoPP::byte salt[8];      
    AutoSeededRandomPool prng;   
    string salt_hex;   
    prng.GenerateBlock(salt, 8); 

    ArraySource(salt, 8, true, new HexEncoder(new StringSink(salt_hex), true));

    return salt_hex;
};

string sha224(string &data)
{
    SHA224 type;
    string hash;

    StringSource(data, true, new HashFilter(type, new HexEncoder(new StringSink(hash), true)));

    return hash;
};