#ifndef BASEEXC_H
#define BASEEXC_H

#include <stdexcept>
#include <string>

class Exception : public std::exception {
   private:
    std::string message, fileName;
    int errorCode, lineNumber;

   public:
    Exception(const std::string& msg, int code, const std::string& file, int line)
        : message(msg), errorCode(code), fileName(file), lineNumber(line) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif  // BASEEXC_H