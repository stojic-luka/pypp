#ifndef NATIVEFUNCS_H
#define NATIVEFUNCS_H

#include <memory>
#include <vector>

class Environment;
class RuntimeVal;

RuntimeVal* printNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env);

RuntimeVal* sqrtNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env);
RuntimeVal* cbrtNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env);

RuntimeVal* maxNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env);
RuntimeVal* minNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env);

RuntimeVal* sleepNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env);
RuntimeVal* timerStartNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env);
RuntimeVal* timerStopNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env);
RuntimeVal* durationNativeFunc(const std::vector<RuntimeVal*>& args, Environment* env);

#endif  // NATIVEFUNCS_H
