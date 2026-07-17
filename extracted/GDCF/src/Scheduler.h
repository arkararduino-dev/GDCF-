#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Token.h"
#include <Arduino.h>

class Scheduler {
public:
    Scheduler();
    void schedule(Token& token);
    void enableMulticore();
    bool isMulticoreEnabled() const { return useCore1; }

private:
    bool useCore1;
};

#endif