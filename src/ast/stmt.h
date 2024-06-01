#pragma once

#include "../types/nodeType.h"

class Stmt {
protected:
    NodeType kind;

public:
    NodeType getKind() const;

    virtual void print(std::ostream& os, int indentation = 0) const = 0;   
};

std::ostream& operator<<(std::ostream& os, const Stmt& node);
