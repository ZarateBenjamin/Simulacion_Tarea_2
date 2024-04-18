#include "FilaGG1.hh"
#include "Random.hh"
#include "include/checkArgs.hh"

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

	// Habilitar logs
	Simulator::enableLog = args.getArgs().enableSimulatorLogs;
	Event::enableLog = args.getArgs().enableEventsLogs;

	// Espacios disponibles
	uint32_t espaciosDisponibles = args.getArgs().espaciosDisponibles;

	// Trabajos a procesar
	uint32_t trabajosAProcesar = args.getArgs().trabajosAProcesar;

	// Crear la simulación
	FilaGG1 *GG1Sim = new FilaGG1(espaciosDisponibles);
	EventSimConnector::theSim = GG1Sim;

	// Tiempo de simulación
	GG1Sim->timeMax = 1000000;

	// Tiempo de reschedule
	GG1Sim->rescheduleTime = 1000.0;

	// Tiempo de llegada
	double tArrival = 0.0;

	// Tiempo total entre llegadas
	double tiempoTotalEntreLlegadas = 0.0;

	// Generar los eventos de llegada
	for (size_t id = 0; id < trabajosAProcesar; id += 1)
	{
		// Log de eventos
		std::stringstream ssEvLog;

		// Generar el tiempo de llegada
		double tBetweenArrivals = Random::normal_truncated(5.0, 2.0, 0, 15.0);
		tiempoTotalEntreLlegadas += tBetweenArrivals; // Acumular el tiempo entre llegadas

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

	// Al finalizar el bucle, calcular el tiempo promedio entre llegadas
	double tiempoPromedioEntreLlegadas = tiempoTotalEntreLlegadas / trabajosAProcesar;

	int totalAtendidos = GG1Sim->getTotalAtendidos();
	int totalAbandonos = GG1Sim->getTotalAbandonos();
	int promedioTiempoDeAtencion = GG1Sim->getTiempoPromedioDeAtencion();

	double tiempoFinalSimulacion = GG1Sim->time;

	// Calcular tiempo de ocupación
	double tiempoOcupacion = GG1Sim->tiempoTotalOcupado;
	double tiempoSimulacion = GG1Sim->time;
	double ocupacionPromedio = tiempoOcupacion / tiempoSimulacion;

	double promedioAtendidos = static_cast<double>(totalAtendidos) / tiempoFinalSimulacion;
	double promedioAbandonos = static_cast<double>(totalAbandonos) / tiempoFinalSimulacion;

	std::cout << "Capacidad de la fila: " << espaciosDisponibles << std::endl;
	std::cout << "Promedio entre llegadas: " << tiempoPromedioEntreLlegadas << std::endl;
	std::cout << "Promedio de tiempo de atencion: " << promedioTiempoDeAtencion << std::endl;
	std::cout << "Ocupacion promedio de la fila: " << ocupacionPromedio << std::endl;
	std::cout << "Total de atendidos: " << totalAtendidos << std::endl;
	std::cout << "Total de abandonos: " << totalAbandonos << std::endl;
	std::cout << "Promedio de atendidos: " << promedioAtendidos << std::endl;
	std::cout << "Promedio de abandonos: " << promedioAbandonos << std::endl;

	// Imprimir un mensaje en la consola
	std::cout << "Simulador ejecutado correctamente" << std::endl;

	delete GG1Sim;

	return EXIT_SUCCESS;
}
