#include "FilaGG1.hh"
#include "Random.hh"
#include "include/checkArgs.hpp"

// Variables globales estaticas
FilaGG1 *EventSimConnector::theSim;
bool Event::enableLog;
bool Simulator::enableLog;

int main(int argc, char *argv[])
{
	// Procesar argumentos
	CheckArgs args(argc, argv);

	// Si se solicita un test de números aleatorios
	if (args.getArgs().randomTest)
	{
		Random::test(10000 /*cantidad de nros*/, "randomTest.txt" /*archivo de salida*/, true /*salir al terminar*/);
	}

	// Contador de la fila
	std::cout << "Fila de atención simple\n";

	// Habilitar logs
	Simulator::enableLog = args.getArgs().enableSimulatorLogs;
	Event::enableLog = args.getArgs().enableEventsLogs;

	// Crear la simulación
	FilaGG1 *GG1Sim = new FilaGG1(argc, argv);
	EventSimConnector::theSim = GG1Sim;

	// Tiempo de simulación
	GG1Sim->timeMax = 1000000;

	// Tiempo de reschedule
	GG1Sim->rescheduleTime = 1000.0;

	// Tiempo de llegada
	double tArrival = 0.0;

	// Generar los eventos de llegada
	for (size_t id = 0; id < 1000; id += 1)
	{
		// Log de eventos
		std::stringstream ssEvLog;

		// Generar el tiempo de llegada
		double tBetweenArrivals;
		double tBetweenArrivals = Random::normal_truncated(5, 2, 0, 15);

		// Calcular el tiempo de llegada
		tArrival += tBetweenArrivals;

		// Crear el evento de llegada
		Event *ev = new Llegada(tArrival, id);

		// Log de eventos
		ssEvLog << "Agregando en la FEL evento id=" << ev->id << ", timeArrive=" << ev->time << '\n';

		// Log de eventos
		GG1Sim->log(ssEvLog);

		// Agregar el evento a la FEL
		GG1Sim->scheduleEvent(ev);
	}

	// Ejecutar la simulación
	GG1Sim->run();

	delete GG1Sim;

	return EXIT_SUCCESS;
}
