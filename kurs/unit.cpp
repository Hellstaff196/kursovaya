#include <UnitTest++/UnitTest++.h>
#include "FileManager.h"
#include "Network.h"
#include "ArgsDecoder.h"
#include "Error.h"
#include "CryptoManager.h"

/**
 * @brief Набор тестов для класса FileManager.
 */
SUITE(FileManagerTests)
{
    /**
     * @brief Тест конструктора класса FileManager.
     */
    TEST(ConstructorTest)
    {
        FileManager fileManager("./config/vclient.conf", "./input.txt", "./output.bin");
        CHECK_EQUAL("./config/vclient.conf", fileManager.getConfigPath());
        CHECK_EQUAL("./input.txt", fileManager.getInputPath());
        CHECK_EQUAL("./output.bin", fileManager.getOutputPath());
    }

    /**
     * @brief Тест загрузки учетных данных из файла конфигурации.
     */
    TEST(LoadCredentialsTest)
    {
        FileManager fileManager("./config/vclient.conf", "./input.txt", "./output.bin");
        array<string, 2> credentials = fileManager.loadCredentials();
        CHECK_EQUAL("user", credentials[0]);
        CHECK_EQUAL("P@ssW0rd", credentials[1]);
    }

    /**
     * @brief Тест чтения данных из входного файла.
     */
    TEST(ReadVectorsTest)
    {
        FileManager fileManager("./config/vclient.conf", "./input.txt", "./output.bin");
        vector<vector<double>> data = fileManager.readVectors();
        CHECK_EQUAL(2, data.size()); // Предполагается, что файл содержит 2 вектора
        CHECK_EQUAL(3, data[0].size());
        CHECK_CLOSE(82345.2, data[0][0], 0.1);
        CHECK_CLOSE(23123.3, data[0][1], 0.1);
        CHECK_CLOSE(8838.21, data[0][2], 0.01);
    }

    /**
     * @brief Тест записи данных в выходной файл.
     */
    TEST(WriteVectorsTest)
    {
        FileManager fileManager("./config/vclient.conf", "./input.txt", "./output.bin");
        vector<double> result = {1.0, 2.0, 3.0};
        fileManager.writeVectors(result);

        // Проверка, что данные были записаны корректно
        ifstream outputFile("./output.bin", ios::binary);
        uint32_t size;
        outputFile.read(reinterpret_cast<char *>(&size), sizeof(size));
        CHECK_EQUAL(3, size);

        double value;
        outputFile.read(reinterpret_cast<char *>(&value), sizeof(value));
        CHECK_EQUAL(1.0, value);
        outputFile.read(reinterpret_cast<char *>(&value), sizeof(value));
        CHECK_EQUAL(2.0, value);
        outputFile.read(reinterpret_cast<char *>(&value), sizeof(value));
        CHECK_EQUAL(3.0, value);
        outputFile.close();
    }

    /**
     * @brief Тест выброса исключения при отсутствии файла конфигурации.
     */
    TEST(CheckThrowFileNotFound)
    {
        FileManager fileManager("./config/invalid.conf", "./input.txt", "./output.bin");
        CHECK_THROW(fileManager.loadCredentials(), Error);
    }
}

/**
 * @brief Набор тестов для класса Network.
 */
SUITE(NetworkTests)
{
    /**
     * @brief Тест конструктора класса Network.
     */
    TEST(ConstructorTest)
    {
        Network network("127.0.0.1", 33333);
        CHECK_EQUAL("127.0.0.1", network.getServerAddress());
        CHECK_EQUAL(33333, network.getServerPort());
    }
}

/**
 * @brief Набор тестов для класса ArgsDecoder.
 */
SUITE(ArgsDecoderTests)
{
    /**
     * @brief Тест конструктора класса ArgsDecoder.
     */
    TEST(ConstructorTest)
    {
        ArgsDecoder argsDecoder;
        CHECK_EQUAL("127.0.0.1", argsDecoder.getServerAddress());
        CHECK_EQUAL(33333, argsDecoder.getServerPort());
        CHECK_EQUAL("./config/vclient.conf", argsDecoder.getConfigFilePath());
        CHECK_EQUAL("", argsDecoder.getInputFilePath());
        CHECK_EQUAL("", argsDecoder.getOutputFilePath());
    }

    /**
     * @brief Тест парсинга всех аргументов командной строки.
     */
    TEST(DecodeArgs_AllParamsTest)
    {
        ArgsDecoder argsDecoder;
        const char *argv[] = {
            "program", "-a", "192.168.0.1", "-p", "8080",
            "-i", "input.txt", "-o", "output.bin",
            "-c", "custom.conf"};
        argsDecoder.decodeArgs(11, const_cast<char **>(argv));
        CHECK_EQUAL("192.168.0.1", argsDecoder.getServerAddress());
        CHECK_EQUAL(8080, argsDecoder.getServerPort());
        CHECK_EQUAL("input.txt", argsDecoder.getInputFilePath());
        CHECK_EQUAL("output.bin", argsDecoder.getOutputFilePath());
        CHECK_EQUAL("custom.conf", argsDecoder.getConfigFilePath());
    }

    /**
     * @brief Тест выброса исключения при неизвестном параметре командной строки.
     */
    TEST(DecodeArgs_UnknownParamTest)
    {
        ArgsDecoder argsDecoder;
        const char *argv[] = {"program", "--unknown"};
        CHECK_THROW(argsDecoder.decodeArgs(2, const_cast<char **>(argv)), Error);
    }

    /**
     * @brief Тест выброса исключения при отсутствии значения для адреса сервера.
     */
    TEST(DecodeArgs_MissingAddressValueTest)
    {
        ArgsDecoder argsDecoder;
        const char *argv[] = {"program", "-a"};
        CHECK_THROW(argsDecoder.decodeArgs(2, const_cast<char **>(argv)), Error);
    }

    /**
     * @brief Тест выброса исключения при отсутствии значения для порта сервера.
     */
    TEST(DecodeArgs_MissingPortValueTest)
    {
        ArgsDecoder argsDecoder;
        const char *argv[] = {"program", "-p"};
        CHECK_THROW(argsDecoder.decodeArgs(2, const_cast<char **>(argv)), Error);
    }

    /**
     * @brief Тест выброса исключения при отсутствии значения для входного файла.
     */
    TEST(DecodeArgs_MissingInputValueTest)
    {
        ArgsDecoder argsDecoder;
        const char *argv[] = {"program", "-i"};
        CHECK_THROW(argsDecoder.decodeArgs(2, const_cast<char **>(argv)), Error);
    }

    /**
     * @brief Тест выброса исключения при отсутствии значения для выходного файла.
     */
    TEST(DecodeArgs_MissingOutputValueTest)
    {
        ArgsDecoder argsDecoder;
        const char *argv[] = {"program", "-o"};
        CHECK_THROW(argsDecoder.decodeArgs(2, const_cast<char **>(argv)), Error);
    }

    /**
     * @brief Тест выброса исключения при отсутствии значения для конфигурационного файла.
     */
    TEST(DecodeArgs_MissingConfigValueTest)
    {
        ArgsDecoder argsDecoder;
        const char *argv[] = {"program", "-c"};
        CHECK_THROW(argsDecoder.decodeArgs(2, const_cast<char **>(argv)), Error);
    }

    /**
     * @brief Тест выброса исключения при отсутствии обязательных параметров.
     */
    TEST(CheckThrowMissingMandatoryParameters)
    {
        ArgsDecoder argsDecoder;
        const char *argv[] = {"program", "-a", "192.168.0.1"};
        CHECK_THROW(argsDecoder.decodeArgs(3, const_cast<char **>(argv)), Error);
    }
}

/**
 * @brief Набор тестов для функций из CryptoManager.
 */
SUITE(CryptoManagerTests)
{
    /**
     * @brief Тест генерации соли.
     */
    TEST(SaltTest)
    {
        string salt1 = salt();
        string salt2 = salt();
        CHECK_EQUAL(16, salt1.size());
        CHECK_EQUAL(16, salt2.size());
        CHECK(salt1 != salt2); // Соли должны быть уникальными
    }

    /**
     * @brief Тест вычисления хеша SHA224.
     */
    TEST(Sha224Test)
    {
        string data = "test_data";
        string hash = sha224(data);
        // Проверка хеша для заданных данных
        CHECK_EQUAL("D4EEFAFB8AE4DA3649DC0A2337EFEFC58F8FF65226C28004849378C2", hash);
    }
}

/**
 * @brief Основная функция для запуска всех тестов.
 * 
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Код завершения тестов (0 - успешно, 1 - ошибка).
 */
int main(int argc, char *argv[])
{
    return UnitTest::RunAllTests();
}
