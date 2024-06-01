#include "evalIdentifier.h"

RuntimeVal* evaluateIdentifier(Identifier* ident, Environment* env) {
    return env->lookup(ident->getSymbol())->getValue();
}