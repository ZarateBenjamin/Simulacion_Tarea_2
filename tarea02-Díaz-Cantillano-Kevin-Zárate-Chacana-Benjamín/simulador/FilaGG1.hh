#pragma once

#include "Simulator.hh"
#include "Random.hh"

class FilaGG1 : public Simulator
{
public:
	FilaGG1(int espaciosDisponibles);
	bool servidorLibre;
	// trabajosEnEspera
	uint32_t trabajosEnEspera;
	// totalAbandonos
	uint32_t totalAbandonos;
	// totalAtendidos
	uint32_t totalAtendidos;

	// espaciosDisponibles
	uint32_t espaciosDisponibles;

	int getTotalAtendidos() const { return totalAtendidos; }
	int getTotalAbandonos() const { return totalAbandonos; }

	double tiempoTotalDeAtencion;
	int totalTrabajosAtendidos;

	double getTiempoPromedioDeAtencion() const
	{
		if (totalTrabajosAtendidos > 0)
		{
			return tiempoTotalDeAtencion / totalTrabajosAtendidos;
		}
		else
		{
			return 0.0;
		}
	}
	double tiempoEntradaFila;

	double tiempoInicioOcupacion;
	double tiempoTotalOcupado;
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

class Abandono : public EventSimConnector, public Event
{
public:
	Abandono(double tiempo, uint32_t id) : Event(tiempo, id)
	{
	}

	virtual void processEvent();
};
