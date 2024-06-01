#pragma once

#include <vector>

#include "stmt.h"

class Program : public Stmt {
private:
    std::vector<Stmt*> body;

public:
    Program();
    Program(std::vector<Stmt*> body);

    std::vector<Stmt*> getBody() const;
    void bodyPush(Stmt* p);

    void print(std::ostream& os, int indentation = 0) const override;

    ~Program();
};