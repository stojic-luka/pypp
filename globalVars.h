#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include <chrono>
#include <memory>

class RuntimeVal;

class Stopwatch {
   private:
    using chronoTimePoint = std::chrono::high_resolution_clock::time_point;

    chronoTimePoint timeStart;
    chronoTimePoint timeEnd;

    bool isRunning;

    Stopwatch();

   public:
    static Stopwatch& getInstance();

    chronoTimePoint getTimeStart() const;
    chronoTimePoint getTimeEnd() const;
    RuntimeVal* getDuration() const;
    bool getIsRunning() const;

    void setTimeStart();
    void setTimeEnd();
};

extern bool isDebug;

#endif  // GLOBALVARS_H