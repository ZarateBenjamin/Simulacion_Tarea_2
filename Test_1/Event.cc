#include "Event.hh"

Event::Event(double t, uint32_t id) : time(t), id(id) {}
Event::~Event() {}


/*//<Comentario>
// Event.h - Clases de eventos específicos para el simulador
#include <iostream>
#include <sstream>

class Event {
public:
    double time;  // Tiempo de ocurrencia del evento
    uint32_t id;  // Identificador del evento
    bool itRescheduled;  // Indicador si el evento ha sido reprogramado

    Event(double t, uint32_t id) : time(t), id(id), itRescheduled(false) {}
    virtual ~Event() {}
    virtual void processEvent() = 0;  // Método para procesar el evento
    void log(std::stringstream& tss);  // Método para registrar eventos
};

class LL : public Event {
public:
    LL(double t, uint32_t id) : Event(t, id) {}
    void processEvent() override;  // Implementación específica para Llegada
};

class LLPrime : public Event {
public:
    LLPrime(double t, uint32_t id) : Event(t, id) {}
    void processEvent() override;  // Implementación específica para Espera
};

class IS : public Event {
public:
    IS(double t, uint32_t id) : Event(t, id) {}
    void processEvent() override;  // Implementación específica para Inicio de Servicio
};

class FS : public Event {
public:
    FS(double t, uint32_t id) : Event(t, id) {}
    void processEvent() override;  // Implementación específica para Fin de Servicio
};


*///<Comentario>