#pragma once

#include <vector>

#include "property.h"

class ObjectLiteral : public Expr {
private:
    std::vector<Property*> properties;

public:
    ObjectLiteral();
    ObjectLiteral(std::vector<Property*> properties);

    std::vector<Property*> getProperties() const;

    void print(std::ostream& os, int indentation = 0) const override;

    ~ObjectLiteral();
};