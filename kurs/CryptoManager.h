#pragma once

#include <string>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;

/**
 * @brief Генерирует случайную соль в шестнадцатеричном формате.
 * 
 * @return Строка, содержащая соль в шестнадцатеричном формате.
 */
string salt();

/**
 * @brief Вычисляет SHA224 хеш для переданной строки.
 * 
 * @param data Ссылка на строку, для которой необходимо вычислить хеш.
 * @return Строка, содержащая шестнадцатеричное представление хеша SHA224.
 */
string sha224(string &data);
