#include <iostream>
#include <string>
#include <fstream>

namespace nm {
    // different logging verbosity levels
    enum class LoggingLevels {
        LOG_INFO,
        LOG_WARNING,
        LOG_ALL
    };
    const std::string defaultlogfile = "defaultlogfile.txt";
    class MyLogger {
    private:
        std::fstream fs;
        std::string messagestart;
    public:
        void logToFile(const std::string& message);
        void logToConsole(const std::string& message);
        void logWithLevel(const std::string& message, LoggingLevels loglevel);
        void logToAll(const std::string& message);
        MyLogger(); // User-provided default constructor
        explicit MyLogger(const std::string& customlogfile);
        MyLogger(const MyLogger& rhs) = delete; // Disable the copy constructor
        MyLogger& operator = (const MyLogger& rhs) = delete; // Disable the copy assignment operator
        MyLogger(MyLogger&& rhs) noexcept; // Move constructor
        MyLogger& operator=(MyLogger&& rhs) noexcept; // Move assignment operator
        ~MyLogger();
    };

    void MyLogger::logToFile(const std::string &message) {
        messagestart = "FILE log: ";
        fs << message << '\n';
    }
    void MyLogger::logToConsole(const std::string &message) {
        messagestart = "CONSOLE log: ";
        std::cout << messagestart << message << '\n';
    }
    void MyLogger::logWithLevel(const std::string &message, LoggingLevels loglevel) {
        switch (loglevel) {
        case LoggingLevels::LOG_INFO:
            logToConsole("Log level INFO: " + message);
            break;
        case LoggingLevels::LOG_WARNING:
            logToConsole("Log level WARNING: " + message);
            break;
        case LoggingLevels::LOG_ALL:
            logToConsole("Log level ALL: " + message);
            break;
        default:
            logToConsole("No logging level: " + message);
            break;
        }
    }
    void MyLogger::logToAll(const std::string& message) {
        logToConsole(message);
        logToFile(message);
    }

    // Default constructor
    MyLogger::MyLogger() {
        fs.open(defaultlogfile, std::ios::app);
        messagestart = "Started logging to a default file. ";
    }

    // User-provided constructor
    MyLogger::MyLogger(const std::string& customlogfile) {
        messagestart = "Started logging. ";
        fs.open(customlogfile, std::ios::app);
    }
    
    // Move constructor
    MyLogger::MyLogger(MyLogger&& rhs) noexcept:fs{std::move(rhs.fs)}, messagestart{rhs.messagestart}
    {}
    
    // Move assignment operator
    MyLogger& MyLogger::operator=(MyLogger&& rhs) noexcept {
        messagestart = std::move(rhs.messagestart);
        fs = std::move(rhs.fs);
        return *this;
    }

    // Destructor
    MyLogger::~MyLogger() {
        fs.close();
    }
}

int main() {
    // Create an object using the default log file name
    nm::MyLogger o1;
    o1.logToConsole("Console log message 1. ");
    o1.logToFile("Default line name log message 1. ");
    o1.logWithLevel("Console log message 2. ", nm::LoggingLevels::LOG_INFO);
    o1.logToAll("Logging to both the console and a file from o1. ");
    
    // Create an object using a custom log file name
    nm::MyLogger o2{"mylogfile.txt"};
    o2.logToConsole("Console log message 1. ");
    o2.logToConsole("Custom file name log message 1. ");
    o2.logWithLevel("Console log message 3. ", nm::LoggingLevels::LOG_WARNING);
    o2.logToAll("Logging to both the console and a file from o2. ");
    
    // Create an object using a move operation
    nm::MyLogger o3 = std::move(o2);
    o3.logToAll("Logging to both the console and a file from o3. ");
}
