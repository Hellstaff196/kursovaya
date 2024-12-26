#include "Network.h"

// Конструктор
Network::Network(const string &serverAddress, uint16_t serverPort)
    : serverAddress(serverAddress), serverPort(serverPort), serverSocket(-1) {}

// Метод для установки соединения
void Network::connectToServer()
{
    this->serverSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket < 0)
    {
        throw Error("Failed to create socket", __func__);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->serverPort);

    if (inet_pton(AF_INET, this->serverAddress.c_str(), &serverAddr.sin_addr) <= 0)
    {
        throw Error("Invalid address/ Address not supported", __func__);
    }

    if (connect(this->serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        throw Error("Connection failed", __func__);
    }
}

// Метод для аутентификации
void Network::authenticate(const string &username, const string &password)
{
    // Генерация соли
    string salt_hex = salt();

    // Вычисление хеша с использованием SHA224
    string to_hash = salt_hex + password;
    string hash = sha224(to_hash);

    // Формирование сообщения и отправка серверу
    string message = username + salt_hex + hash;
    if (send(this->serverSocket, message.c_str(), message.size(), 0) < 0)
    {
        throw Error("Failed to send authentication message", __func__);
    }

    // Получение ответа от сервера
    char response[1024];
    int response_length = recv(this->serverSocket, response, sizeof(response) - 1, 0);
    if (response_length < 0)
    {
        throw Error("Failed to receive authentication response", __func__);
    }

    response[response_length] = '\0';
    if (string(response) != "OK")
    {
        throw Error("Authentication failed", __func__);
    }
}

vector<double> Network::calculate(const vector<vector<double>> &data)
{
    // Передача количества векторов
    uint32_t numVectors = data.size();
    if (send(this->serverSocket, &numVectors, sizeof(numVectors), 0) < 0)
    {
        throw Error("Failed to send number of vectors", __func__);
    }

    // Передача каждого вектора
    for (const auto &vec : data)
    {
        uint32_t vecSize = vec.size();
        if (send(this->serverSocket, &vecSize, sizeof(vecSize), 0) < 0)
        {
            throw Error("Failed to send vector size", __func__);
        }
        if (send(this->serverSocket, vec.data(), vecSize * sizeof(double), 0) < 0)
        {
            throw Error("Failed to send vector data", __func__);
        }
    }

    // Получение результатов
    vector<double> results(numVectors);
    for (uint32_t i = 0; i < numVectors; ++i)
    {
        if (recv(this->serverSocket, &results[i], sizeof(double), 0) < 0)
        {
            throw Error("Failed to receive result", __func__);
        }
    }

    // Логирование результата
    cout << "Log: \"Network.calculate()\"\n";
    cout << "Results: {";
    for (const auto &val : results)
    {
        cout << val << ", ";
    }
    if (!results.empty())
    {
        cout << "\b\b"; // Удалить последнюю запятую и пробел
    }
    cout << "}\n";

    return results;
}

// Метод для закрытия соединения
void Network::closeConnection()
{
    if (this->serverSocket >= 0)
    {
        ::close(this->serverSocket);
        this->serverSocket = -1;
    }
}

// Методы для получения значений атрибутов
const string &Network::getServerAddress() const
{
    return serverAddress;
}

uint16_t Network::getServerPort() const
{
    return serverPort;
}
