#include "Simulator.hh"

int main() {
    Simulator sim(10);  // Supongamos que K es 10
    sim.scheduleEvent(new LL(0, sim.currentID++));
    sim.run();
    return 0;
}
