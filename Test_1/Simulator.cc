#include "Simulator.hh"
#include "Event.hh"

Simulator::Simulator(int K) : espaciosDisponibles(K), servidorLibre(true), trabajosEnEspera(0), totalAbandonos(0), totalAtendidos(0), currentID(0) {
    auto cmp = [](Event* left, Event* right) { return left->time > right->time; };
    eventQueue = std::priority_queue<Event*, std::vector<Event*>, decltype(cmp)>(cmp);
}

void Simulator::scheduleEvent(Event* ev) {
    eventQueue.push(ev);
}

void Simulator::run() {
    while (!eventQueue.empty()) {
        Event* ev = eventQueue.top();
        eventQueue.pop();
        ev->processEvent();
        delete ev;
    }
}
