#include "FileManager.h"

FileManager::FileManager(const string &configPath, const string &inputPath, const string &outputPath)
    : configPath(configPath),
      inputPath(inputPath),
      outputPath(outputPath) {}

array<string, 2> FileManager::loadCredentials() const
{
    ifstream confFile(this->configPath);
    if (!confFile.is_open())
    {
        throw Error("Failed to open configuration file \"" + this->configPath + "\"", __func__);
    }

    array<string, 2> credentials;
    string line;
    getline(confFile, line);
    confFile.close();

    istringstream iss(line);
    getline(iss, credentials[0], ':');
    getline(iss, credentials[1]);

    if (credentials[0].empty() || credentials[1].empty())
    {
        throw Error("Missing login or password", __func__);
    }

    return credentials;
}

vector<vector<double>> FileManager::readVectors() const
{
    ifstream inputFile(this->inputPath);
    if (!inputFile.is_open())
    {
        throw Error("Failed to open input file for reading.", __func__);
    }

    uint32_t numVectors;
    inputFile >> numVectors;

    vector<vector<double>> data(numVectors);
    for (uint32_t i = 0; i < numVectors; ++i)
    {
        uint32_t vectorSize;
        inputFile >> vectorSize;

        vector<double> vec(vectorSize);
        for (uint32_t j = 0; j < vectorSize; ++j)
        {
            inputFile >> vec[j];
        }

        data[i] = vec;
    }

    inputFile.close();
    return data;
}

void FileManager::writeVectors(const vector<double> &data) const
{
    ofstream outputFile(this->outputPath, ios::binary);
    if (!outputFile.is_open())
    {
        throw Error("Failed to open output file \"" + this->outputPath + "\"", __func__);
    }

    uint32_t count = data.size();
    outputFile.write(reinterpret_cast<const char *>(&count), sizeof(count));

    for (const auto &num : data)
    {
        outputFile.write(reinterpret_cast<const char *>(&num), sizeof(num));
    }

    outputFile.close();
}

const string &FileManager::getConfigPath() const
{
    return configPath;
}

const string &FileManager::getInputPath() const
{
    return inputPath;
}

const string &FileManager::getOutputPath() const
{
    return outputPath;
}

void printVector(const vector<double> &data)
{
    cout << "[ ";
    for (const auto &val : data)
    {
        cout << fixed << setprecision(2) << val << " ";
    }
    cout << "]";
    cout << endl;
}

void printVectors(const vector<vector<double>> &data)
{
    cout << "[\n";
    for (const auto &vec : data)
    {
        cout << "  [ ";
        for (const auto &val : vec)
        {
            cout << fixed << setprecision(2) << val << " ";
        }
        cout << "]\n";
    }
    cout << "]";
    cout << endl;
}
