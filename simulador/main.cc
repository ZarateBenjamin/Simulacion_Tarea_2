/**********************************************************************************************
 *
 * Ejemplo de implementación de fila G/G/1/inf
 *
 **********************************************************************************************/

#include <FilaGG1.hh>
#include <Random.hh>
#include <checkArgs.hpp>

// Variables globales estaticas
FilaGG1 *EventSimConnector::theSim;
bool Event::enableLog;
bool Simulator::enableLog;

// trabajosEnEspera
uint32_t FilaGG1::trabajosEnEspera = 0;
// totalAbandonos
uint32_t FilaGG1::totalAbandonos = 0;
// totalAtendidos
uint32_t FilaGG1::totalAtendidos = 0;

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

	//
	Simulator::enableLog = args.getArgs().enableSimulatorLogs;
	Event::enableLog = args.getArgs().enableEventsLogs;

	// Crear la simulación
	FilaGG1 *GG1Sim = new FilaGG1();
	EventSimConnector::theSim = GG1Sim;

	// Tiempo de simulación
	GG1Sim->timeMax = 1000000;

	// Tiempo de reschedule
	GG1Sim->rescheduleTime = 1000.0;

	// Obtener los argumentos de la simulación

	// Tasa de llegada
	double rate = args.getArgs().tasaLlegada;
	// espaciosDisponibles
	uint32_t espaciosDisponibles = args.getArgs().espaciosDisponibles;

	// Tiempo de llegada
	double tArrival = 0.0;

	// Generar los eventos de llegada
	for (size_t id = 0; id < args.getArgs().totalTrabajos; id += 1)
	{
		// Log de eventos
		std::stringstream ssEvLog;

		// Generar el tiempo de llegada
		double tBetweenArrivals;
		tBetweenArrivals = Random::exponential(rate);

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
