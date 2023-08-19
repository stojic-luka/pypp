#include "GlobalVars.h"

#include <iostream>
#include <memory>
#include <unordered_map>

#include "runtime/values.h"

Stopwatch::Stopwatch() : isRunning(false) {}
Stopwatch& Stopwatch::getInstance() {
    static Stopwatch instance;
    return instance;
}

Stopwatch::chronoTimePoint Stopwatch::getTimeStart() const { return timeStart; }
Stopwatch::chronoTimePoint Stopwatch::getTimeEnd() const { return timeEnd; }

RuntimeVal* Stopwatch::getDuration() const {
    auto duration = std::chrono::duration(timeEnd - timeStart);
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    return new ObjectVal(std::unordered_map<std::string, RuntimeVal*>{
        {"microseconds", new NumberVal(static_cast<double>(microseconds))},
        {"milliseconds", new NumberVal(static_cast<double>(milliseconds))},
    });
}
bool Stopwatch::getIsRunning() const { return isRunning; }

void Stopwatch::setTimeStart() {
    timeStart = std::chrono::high_resolution_clock::now();
    isRunning = true;
}
void Stopwatch::setTimeEnd() {
    timeEnd = std::chrono::high_resolution_clock::now();
    isRunning = false;
}
