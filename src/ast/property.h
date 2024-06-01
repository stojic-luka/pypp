#pragma once

#include "expr.h"

class Property : public Expr {
private:
    std::string key;
    Expr* value;

public:
    Property();
    Property(std::string key);
    Property(std::string key, Expr* value);

    std::string getKey() const;
    Expr* getValue() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~Property();
};
