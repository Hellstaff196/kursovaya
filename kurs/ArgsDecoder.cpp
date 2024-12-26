#include "ArgsDecoder.h"

ArgsDecoder::ArgsDecoder()
    : serverAddress("127.0.0.1"), serverPort(33333),
      configFilePath("./config/vclient.conf") {}

string ArgsDecoder::getConfigFilePath() const
{
    return this->configFilePath;
}

string ArgsDecoder::getServerAddress() const
{
    return this->serverAddress;
}

int ArgsDecoder::getServerPort() const
{
    return this->serverPort;
}

string ArgsDecoder::getInputFilePath() const
{
    return this->inputFilePath;
}

string ArgsDecoder::getOutputFilePath() const
{
    return this->outputFilePath;
}

void ArgsDecoder::decodeArgs(int argc, char *argv[])
{
    if (argc == 1)
    {
        displayHelp();
        exit(0);
    }
    
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            displayHelp();
            exit(0);
        }
        else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--address") == 0)
        {
            if (i + 1 < argc)
                this->serverAddress = argv[++i];
            else
                throw Error("Missing value for address parameter", __func__);
        }
        else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0)
        {
            if (i + 1 < argc)
                this->serverPort = stoi(argv[++i]);
            else
                throw Error("Missing value for port parameter", __func__);
        }
        else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0)
        {
            if (i + 1 < argc)
                this->inputFilePath = argv[++i];
            else
                throw Error("Missing value for input parameter", __func__);
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
        {
            if (i + 1 < argc)
                this->outputFilePath = argv[++i];
            else
                throw Error("Missing value for output parameter", __func__);
        }
        else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--config") == 0)
        {
            if (i + 1 < argc)
                this->configFilePath = argv[++i];
            else
                throw Error("Missing value for config parameter", __func__);
        }
        else
        {
            throw Error("Unknown parameter: " + string(argv[i]), __func__);
        }
    }

    if (this->inputFilePath.empty() || this->outputFilePath.empty())
    {
        throw Error("Missing mandatory input or output file path", __func__);
    }
}

void ArgsDecoder::displayHelp() const
{
    cout << "Usage: vclient [options]\n"
         << "Options:\n"
         << "  -h, --help            Show this help message and exit\n"
         << "  -a, --address ADDRESS Server address (default: 127.0.0.1)\n"
         << "  -p, --port PORT       Server port (default: 33333)\n"
         << "  -i, --input PATH      Path to input data file\n"
         << "  -o, --output PATH     Path to output data file\n"
         << "  -c, --config PATH     Path to config file (default: ./config/vclient.conf)\n";
}
