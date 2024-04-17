#pragma once
#include <iostream>

class Event {
public:
    double time;
    uint32_t id;
    Event(double t, uint32_t id);
    virtual ~Event();
    virtual void processEvent() = 0;
};
