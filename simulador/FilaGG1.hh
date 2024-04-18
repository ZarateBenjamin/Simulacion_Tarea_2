#pragma once

#include "Simulator.hh"
#include "Random.hh"
#include "include/checkArgs.hh"

class FilaGG1 : public Simulator
{
public:
	bool servidorLibre;
	// trabajosEnEspera
	uint32_t trabajosEnEspera;
	// totalAbandonos
	uint32_t totalAbandonos;
	// totalAtendidos
	uint32_t totalAtendidos;

	// espaciosDisponibles
	uint32_t espaciosDisponibles;
	FilaGG1(int argc, char *argv[]);
};

class EventSimConnector
{
public:
	static FilaGG1 *theSim;
};

class Llegada : public EventSimConnector, public Event
{
public:
	Llegada(double tiempo) : Event(tiempo)
	{
		id = theSim->getSizeEventQueue();
	}
	Llegada(double tiempo, uint32_t id) : Event(tiempo, id) {}

	virtual void processEvent();
};

class OcuparServidor : public EventSimConnector, public Event
{
public:
	OcuparServidor(double tiempo, uint32_t id) : Event(tiempo, id)
	{
	}

	virtual void processEvent();
};

class Salir : public EventSimConnector, public Event
{
public:
	Salir(double tiempo, uint32_t id) : Event(tiempo, id)
	{
	}

	virtual void processEvent();
};
