#include "nativeFuncs.h"

#include <math.h>

#include <iostream>
#include <thread>
#include <vector>

#include "../globalVars.h"
#include "environment.h"
#include "values.h"

RuntimeVal* printNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env) {
    if (args.size() == 0) {
        std::cout << std::endl;
        return new NoneVal();
    }

    std::string separator = ", ";
    bool printLast = true;
    if (args[args.size() - 1]->getType() == ValueType::Characters) {
        std::string lastElemVal = static_cast<CharactersVal*>(args[args.size() - 1])->getValue();
        if (lastElemVal.rfind("sep=", 0) == 0) {
            separator = lastElemVal.substr(4);
            printLast = false;
        }
    }

    for (size_t i = 0; i < args.size() - (printLast ? 0 : 1); i++)
        std::cout << *(args[i]) << (i < args.size() - (printLast ? 1 : 2) ? separator : "");
    std::cout << "\n";
    return new NoneVal();
};

////////////////////////////////

RuntimeVal* sqrtNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env) {
    if (args.size() != 1)
        throw std::runtime_error("There be only one value passed to sqrt function");

    double val = static_cast<NumberVal*>(args[0])->getValue();
    return new NumberVal(sqrt(val));
}
RuntimeVal* cbrtNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env) {
    if (args.size() != 1)
        throw std::runtime_error("There be only one value passed to cbrt function");

    double val = static_cast<NumberVal*>(args[0])->getValue();
    return new NumberVal(cbrt(val));
}

////////////////////////////////

RuntimeVal* maxNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env) {
    if (args.size() == 0)
        std::runtime_error("There are no arguments passed to max function");

    double maxVal = static_cast<NumberVal*>(args[0])->getValue();
    for (size_t i = 1; i < args.size(); ++i) {
        double val = static_cast<NumberVal*>(args[i])->getValue();
        maxVal = std::max(maxVal, val);
    }
    return new NumberVal(maxVal);
}
RuntimeVal* minNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env) {
    if (args.size() == 0)
        std::runtime_error("There are no arguments passed to min function");

    double minVal = static_cast<NumberVal*>(args[0])->getValue();
    for (size_t i = 1; i < args.size(); ++i) {
        double val = static_cast<NumberVal*>(args[i])->getValue();
        minVal = std::min(minVal, val);
    }
    return new NumberVal(minVal);
}

////////////////////////////////

RuntimeVal* sleepNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env) {
    if (args.size() != 1)
        throw std::runtime_error("There be only one value passed to sleep function");

    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int64_t>(static_cast<NumberVal*>(args[0])->getValue())));
    return new NoneVal();
}

RuntimeVal* timerStartNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env) {
    Stopwatch::getInstance().setTimeStart();
    return new NoneVal();
}
RuntimeVal* timerStopNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env) {
    Stopwatch::getInstance().setTimeEnd();
    return new NoneVal();
}
RuntimeVal* durationNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env) {
    return Stopwatch::getInstance().getDuration();
}
