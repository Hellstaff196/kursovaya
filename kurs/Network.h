#pragma once

#include "Error.h"
#include "CryptoManager.h"
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <unistd.h>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

/**
 * @class Network
 * @brief Класс для управления сетевым подключением к серверу.
 */
class Network
{
public:
    /**
     * @brief Конструктор класса Network.
     * 
     * @param serverAddress Адрес сервера.
     * @param serverPort Порт сервера.
     */
    Network(const string &serverAddress, uint16_t serverPort);

    /**
     * @brief Устанавливает соединение с сервером.
     * 
     * @throws Error Если не удалось установить соединение.
     */
    void connectToServer();

    /**
     * @brief Аутентифицирует пользователя на сервере.
     * 
     * @param username Имя пользователя.
     * @param password Пароль пользователя.
     * @throws Error Если аутентификация не удалась.
     */
    void authenticate(const string &username, const string &password);

    /**
     * @brief Отправляет данные на сервер и получает результат вычислений.
     * 
     * @param data Вектор векторов, содержащий данные для отправки.
     * @return Вектор, содержащий результаты вычислений.
     * @throws Error Если произошла ошибка при отправке данных или получении результатов.
     */
    vector<double> calculate(const vector<vector<double>> &data);

    /**
     * @brief Закрывает соединение с сервером.
     */
    void closeConnection();

    /**
     * @brief Возвращает адрес сервера.
     * 
     * @return Адрес сервера в виде строки.
     */
    const string &getServerAddress() const;

    /**
     * @brief Возвращает порт сервера.
     * 
     * @return Порт сервера в виде целого числа.
     */
    uint16_t getServerPort() const;

private:
    string serverAddress; ///< Адрес сервера.
    uint16_t serverPort;  ///< Порт сервера.
    int serverSocket;     ///< Сокет подключения.
};
