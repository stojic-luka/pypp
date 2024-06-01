#include "stmt.h"
#include "expr.h"

NodeType Stmt::getKind() const { return kind; };
std::ostream& operator<<(std::ostream& os, const Stmt& node) {
    node.print(os);
    return os;
}