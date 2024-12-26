#pragma once

#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Error.h"

using namespace std;

/**
 * @class FileManager
 * @brief Класс для управления файлами конфигурации, входных и выходных данных.
 */
class FileManager
{
public:
    /**
     * @brief Конструктор класса FileManager.
     * 
     * @param configPath Путь к файлу конфигурации.
     * @param inputPath Путь к входному файлу.
     * @param outputPath Путь к выходному файлу.
     */
    FileManager(const string &configPath, const string &inputPath, const string &outputPath);

    /**
     * @brief Загрузка учетных данных из файла конфигурации.
     * 
     * @return Массив строк, содержащий учетные данные (логин и пароль).
     * @throws Error Если файл конфигурации не найден или содержит ошибки.
     */
    array<string, 2> loadCredentials() const;

    /**
     * @brief Чтение векторов из входного файла.
     * 
     * @return Вектор векторов, содержащий данные.
     * @throws Error Если входной файл не найден или содержит ошибки.
     */
    vector<vector<double>> readVectors() const;

    /**
     * @brief Запись векторов в выходной файл.
     * 
     * @param data Вектор, содержащий данные для записи.
     * @throws Error Если выходной файл недоступен для записи.
     */
    void writeVectors(const vector<double> &data) const;

    /**
     * @brief Возвращает путь к файлу конфигурации.
     * 
     * @return Путь к файлу конфигурации.
     */
    const string &getConfigPath() const;

    /**
     * @brief Возвращает путь к входному файлу.
     * 
     * @return Путь к входному файлу.
     */
    const string &getInputPath() const;

    /**
     * @brief Возвращает путь к выходному файлу.
     * 
     * @return Путь к выходному файлу.
     */
    const string &getOutputPath() const;

private:
    string configPath;    ///< Путь к файлу конфигурации.
    string inputPath;     ///< Путь к входному файлу.
    string outputPath;    ///< Путь к выходному файлу.
};

/**
 * @brief Выводит содержимое вектора на экран.
 * 
 * @param data Вектор, содержащий данные для вывода.
 */
void printVector(const vector<double> &data);

/**
 * @brief Выводит содержимое вектора векторов на экран.
 * 
 * @param data Вектор векторов, содержащий данные для вывода.
 */
void printVectors(const vector<vector<double>> &data);
