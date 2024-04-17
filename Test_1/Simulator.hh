#pragma once
#include <queue>
#include <vector>
#include <functional>
#include "Event.hh"

class Simulator {
public:
    std::priority_queue<Event*, std::vector<Event*>, std::function<bool(Event*, Event*)>> eventQueue;
    bool servidorLibre;
    int trabajosEnEspera;
    int totalAbandonos;
    int totalAtendidos;
    int espaciosDisponibles;
    uint32_t currentID;

    Simulator(int K);
    void scheduleEvent(Event* ev);
    void run();
};
