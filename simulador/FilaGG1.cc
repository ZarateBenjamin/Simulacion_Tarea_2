#include "FilaGG1.hh"
#include "include/checkArgs.hh"

// Implementación del constructor
FilaGG1::FilaGG1(int espaciosDisponibles) : Simulator()
{
	this->espaciosDisponibles = espaciosDisponibles;
	servidorLibre = true;
	trabajosEnEspera = 0;
	totalAbandonos = 0;
	totalAtendidos = 0;

	tiempoTotalDeAtencion = 0;
	totalTrabajosAtendidos = 0;

	tiempoEntradaFila = time;

	tiempoInicioOcupacion = 0;
	tiempoTotalOcupado = 0;
}

// evento de inicio de la simulación
void Llegada::processEvent()
{

	std::stringstream ssEvLog;

	ssEvLog
		<< "==> llega  a la fila, espacios restantes:"
		<< theSim->espaciosDisponibles << std::endl;
	this->log(ssEvLog);

	// Si el servidor está libre, el trabajo pasa directamente al servidor
	if (theSim->servidorLibre)
	{
		theSim->servidorLibre = false;
		theSim->tiempoInicioOcupacion = time;

		ssEvLog << "==> pasa al servidor.\n";

		this->log(ssEvLog);

		Event *ev = new OcuparServidor(time, id);
		ev->itRescheduled = false;
		theSim->scheduleEvent(ev);
	}
	// Si el servidor está ocupado, se debe re-planificar el evento de llegada
	else
	{

		if (theSim->espaciosDisponibles <= 0)
		{

			theSim->scheduleEvent(new Abandono(time, id));
		}
		// Verificar si espaciosDisponibles es mayor que 0 antes de disminuir su valor
		if (theSim->espaciosDisponibles > 0)
		{
			theSim->espaciosDisponibles--;
		}

		// El evento de llegada debe ser re-planificado.
		// el nuevo tiempo es 'newTime'

		theSim->trabajosEnEspera++;

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

	theSim->tiempoEntradaFila += time - theSim->tiempoEntradaFila;

	// Tiempo de servicio del trabajo actual
	double Tservicio = Random::exponential(0.5); // una media de 2 minutos (1/0.5)

	// Acumular tiempo de atención
	theSim->tiempoTotalDeAtencion += Tservicio;
	theSim->totalTrabajosAtendidos++;

	ssEvLog << "==> empieza a ocupar servidor. Tiempo de servicio:" << Tservicio << "\n";
	this->log(ssEvLog);

	theSim->scheduleEvent(new Salir(time + Tservicio, id));
}

void Salir::processEvent()
{
	std::stringstream ssEvLog;

	theSim->servidorLibre = true;
	double periodoOcupacion = time - theSim->tiempoInicioOcupacion;
	theSim->tiempoTotalOcupado += periodoOcupacion;

	theSim->totalAtendidos++;
	theSim->espaciosDisponibles++;

	ssEvLog << "==> Fin servicio.\n";
	this->log(ssEvLog);

	// Debe replanificar los eventos que fueron pospuestos
	theSim->rescheduleDelayedEvents();
}

// Evento salida abandono
void Abandono::processEvent()
{
	std::stringstream ssEvLog;

	theSim->totalAbandonos++;
	ssEvLog << "==> abandona la fila.\n";
	this->log(ssEvLog);
	theSim->removeEvent(id);
}