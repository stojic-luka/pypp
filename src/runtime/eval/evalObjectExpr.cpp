#include "evalObjectExpr.h"

#include "../interpreter.h"

RuntimeVal* evaluateObjectExpr(ObjectLiteral* obj, Environment* env) {
    std::unordered_map<std::string, RuntimeVal*> props;
    for (auto const& property : obj->getProperties()) {
        RuntimeVal* runtimeVal = property->getValue() == NULL ? env->lookup(property->getKey())->getValue() : evaluate(property->getValue(), env);
        props.insert(std::make_pair(property->getKey(), runtimeVal));
    }
    return new ObjectVal(props);
}