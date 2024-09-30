#include "../headers/simple_logger.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

namespace Game {
    Logger& Logger::Instance()
    {
        static Logger instance = Logger("boids.log");
        return instance;
    }

    Logger::Logger(const string& f)
    {
        this->logFile.open(f, ios::app);
    }

    Logger::~Logger()
    {
        this->logFile.close();
    }

    void Logger::Log(LogLevel level, const string& message)
    {
        time_t now = time(0);
        tm* timeInfo = localtime(&now);
        char timeStamp[20];
        strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%d %H:%M:%S", timeInfo);

        ostringstream logEntry;
        logEntry << "[" << timeStamp << "] "
            << Label(level) << ": " << message
            << endl;

        if (logFile.is_open()) {
            logFile << logEntry.str();
            logFile.flush(); // Ensure immediate write to file
        }
    }

    string Logger::Label(LogLevel level)
    {
        switch (level)
        {
        case Game::DEBUG:
            return "DEBUG";
        case Game::INFO:
            return "INFO";
        case Game::WARN:
            return "WARN";
        default:
            return "ERROR";
        }
    }
}
