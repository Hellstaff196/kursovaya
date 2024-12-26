#include "Error.h"
#include "FileManager.h"
#include "Network.h"
#include "ArgsDecoder.h"
#include <array>
#include <iostream>

using namespace std;

/**
 * @brief Основная функция программы.
 * 
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Код завершения программы (0 - успешно, 1 - ошибка).
 */
int main(int argc, char *argv[])
{
    try
    {
        // Инициализация декодера аргументов
        cout << "[INFO] Initializing arguments decoder..." << endl;
        ArgsDecoder argsDecoder;
        argsDecoder.decodeArgs(argc, argv);

        cout << "[INFO] Configuration Path: " << argsDecoder.getConfigFilePath() << endl;
        cout << "[INFO] Input File Path: " << argsDecoder.getInputFilePath() << endl;
        cout << "[INFO] Output File Path: " << argsDecoder.getOutputFilePath() << endl;
        cout << "[INFO] Server Address: " << argsDecoder.getServerAddress() << endl;
        cout << "[INFO] Server Port: " << argsDecoder.getServerPort() << endl;

        // Подключение к серверу
        cout << "[INFO] Connecting to server at " << argsDecoder.getServerAddress() << ":" << argsDecoder.getServerPort() << "..." << endl;
        Network network(argsDecoder.getServerAddress(), argsDecoder.getServerPort());
        network.connectToServer();

        // Загрузка конфигурации
        cout << "[INFO] Loading configuration from " << argsDecoder.getConfigFilePath() << "..." << endl;
        FileManager fileManager(argsDecoder.getConfigFilePath(), argsDecoder.getInputFilePath(), argsDecoder.getOutputFilePath());

        array<string, 2> userpass = fileManager.loadCredentials();
        cout << "[INFO] Username: " << userpass[0] << endl;

        // Аутентификация пользователя
        cout << "[INFO] Authenticating user " << userpass[0] << "..." << endl;
        network.authenticate(userpass[0], userpass[1]);

        // Чтение данных из входного файла
        cout << "[INFO] Reading data from " << argsDecoder.getInputFilePath() << "..." << endl;
        vector<vector<double>> vectors = fileManager.readVectors();
        cout << "[INFO] Read data: " << endl;
        printVectors(vectors);

        // Расчет результатов
        cout << "[INFO] Calculating results..." << endl;
        vector<double> result = network.calculate(vectors);
        cout << "[INFO] Calculated results: " << endl;
        printVector(result);

        // Запись результатов в выходной файл
        cout << "[INFO] Writing results to " << argsDecoder.getOutputFilePath() << "..." << endl;
        fileManager.writeVectors(result);

        cout << "[INFO] Operation completed successfully!" << endl;
    }
    catch (const Error &e)
    {
        cerr << "[ERROR] Runtime error: " << e.what() << endl;
        return 1;
    }
    catch (const exception &e)
    {
        cerr << "[ERROR] Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
