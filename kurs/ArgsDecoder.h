#pragma once

#include "Error.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

/**
 * @class ArgsDecoder
 * @brief Класс для парсинга аргументов командной строки и хранения параметров конфигурации.
 */
class ArgsDecoder
{
public:
    /**
     * @brief Конструктор по умолчанию, инициализирует параметры с значениями по умолчанию.
     */
    ArgsDecoder();

    /**
     * @brief Возвращает адрес сервера.
     * @return Адрес сервера в виде строки.
     */
    string getServerAddress() const;

    /**
     * @brief Возвращает порт сервера.
     * @return Порт сервера в виде целого числа.
     */
    int getServerPort() const;

    /**
     * @brief Возвращает путь к входному файлу.
     * @return Путь к входному файлу в виде строки.
     */
    string getInputFilePath() const;

    /**
     * @brief Возвращает путь к выходному файлу.
     * @return Путь к выходному файлу в виде строки.
     */
    string getOutputFilePath() const;

    /**
     * @brief Возвращает путь к файлу конфигурации.
     * @return Путь к файлу конфигурации в виде строки.
     */
    string getConfigFilePath() const;

    /**
     * @brief Парсит аргументы командной строки и инициализирует соответствующие параметры.
     * @param argc Количество аргументов.
     * @param argv Массив аргументов.
     * @throws Error Если переданы неверные или недостаточные аргументы.
     */
    void decodeArgs(int argc, char *argv[]);

    /**
     * @brief Отображает справку по использованию программы.
     */
    void displayHelp() const;

private:
    string serverAddress;     ///< Адрес сервера.
    uint16_t serverPort;      ///< Порт сервера.
    string inputFilePath;     ///< Путь к входному файлу.
    string outputFilePath;    ///< Путь к выходному файлу.
    string configFilePath;    ///< Путь к файлу конфигурации.
};
