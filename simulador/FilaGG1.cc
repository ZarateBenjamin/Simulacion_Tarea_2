#include "FilaGG1.hh"
#include "include/checkArgs.hpp"

// Implementación del constructor
FilaGG1::FilaGG1(int argc, char *argv[]) : Simulator()
{
	// Procesar argumentos
	CheckArgs args(argc, argv);
	servidorLibre = true;
	trabajosEnEspera = 0;
	totalAbandonos = 0;
	totalAtendidos = 0;
	espaciosDisponibles = args.getArgs().espaciosDisponibles;
}

// evento de inicio de la simulación
void Llegada::processEvent()
{

	std::stringstream ssEvLog;

	ssEvLog << "==> llega  a la fila.\n";
	this->log(ssEvLog);

	theSim->trabajosEnEspera++;
	theSim->espaciosDisponibles--;

	// Si el servidor está libre, el trabajo pasa directamente al servidor
	if (theSim->servidorLibre)
	{
		theSim->servidorLibre = false;

		ssEvLog << "==> pasa al servidor.\n";
		this->log(ssEvLog);

		Event *ev = new OcuparServidor(time, id);
		ev->itRescheduled = false;
		theSim->scheduleEvent(ev);
	}
	// Si el servidor está ocupado, se debe re-planificar el evento de llegada
	else
	{
		// El evento de llegada debe ser re-planificado.
		// el nuevo tiempo es 'newTime'

		if (theSim->espaciosDisponibles <= 0)
		{
			theSim->espaciosDisponibles = 0;
			theSim->totalAbandonos++;
			theSim->trabajosEnEspera--;
			ssEvLog << "==> abandona la fila.\n";
			this->log(ssEvLog);
		}

		// determinar el tiempo de postergación
		double newTime;
		newTime = time + theSim->rescheduleTime;

		ssEvLog << std::setprecision(6) << std::fixed;
		ssEvLog << "==> servidor ocupado, replanificado para t=" << newTime << "\n";
		this->log(ssEvLog);

		// Se crea un nuevo evento, manteniendo el mismo identificador del
		// evento original
		Event *ev = new Llegada(newTime, id);
		ev->itRescheduled = true;

		// Se planifica el nuevo evento
		theSim->scheduleEvent(ev);

		// Se elimina este evento de la lista de eventos
	}
}

void OcuparServidor::processEvent()
{
	std::stringstream ssEvLog;

	theSim->servidorLibre = false;
	theSim->trabajosEnEspera--;

	// Tiempo de servicio del trabajo actual
	uint32_t Tservicio = Random::exponential(2);

	ssEvLog << "==> empieza a ocupar servidor. Tiempo de servicio:" << Tservicio << "\n";
	this->log(ssEvLog);

	theSim->scheduleEvent(new Salir(time + Tservicio, id));
}

void Salir::processEvent()
{
	std::stringstream ssEvLog;

	theSim->servidorLibre = true;
	theSim->totalAtendidos++;
	theSim->espaciosDisponibles++;

	ssEvLog << "==> Fin servicio.\n";
	this->log(ssEvLog);

	// Debe replanificar los eventos que fueron pospuestos
	theSim->rescheduleDelayedEvents();
}
