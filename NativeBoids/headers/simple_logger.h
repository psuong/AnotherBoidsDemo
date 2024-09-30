#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H

#include <string>
#include <fstream>
using namespace std;

namespace Game {

    enum LogLevel {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    class Logger {
    public:
        static Logger& Instance();
        Logger(const string& filename);
        ~Logger();
        void Log(LogLevel level, const string& message);
    private:
        ofstream logFile;
        string Label(LogLevel level);
    };
}

#endif