#pragma once

#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

extern char *optarg;
extern int optind, opterr, optopt;

// Parametros que debe recibir el programa
// espaciosDisponibles (k)
// cantidadDeTrabajo (j)

class CheckArgs
{
private:
	// 1) Modificar esta sección
	const std::string optString = "k:j:t:seh";

	const struct option optStringLong[7] = {
		{"espaciosDisponibles", required_argument, nullptr, 'k'}, // Nuevo argumento para la cantidad de espacios disponibles
		{"test", required_argument, nullptr, 't'},
		{"slogs", no_argument, nullptr, 's'},
		{"elogs", no_argument, nullptr, 'e'},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, no_argument, nullptr, 0}};

	const std::string opciones = "--espaciosDisponibles <espacios disponibles> [--test][--simlogs][--eventslogs][--help]";
	const std::string descripcion = "Descripción:\n"
									"\t--espaciosDisponibles espacios disponibles en la fila.\n"
									"\t--test     genera archivo de pruebas de nros aleatorios y termina.\n"
									"\t--slogs    habilita logs del simulador en pantalla.\n"
									"\t--elogs    habilita logs de los eventos en pantalla.\n"
									"\t-h         Muestra esta salida y termina.\n";

	typedef struct args_t
	{
		uint32_t espaciosDisponibles;
		bool randomTest;
		bool enableSimulatorLogs;
		bool enableEventsLogs;
	} args_t;

	args_t parametros;

	int argc;
	char **argv;

public:
	CheckArgs(int _argc, char **_argv);
	~CheckArgs();
	void loadArgs();
	args_t getArgs();

private:
	void printUsage();
};

CheckArgs::CheckArgs(int _argc, char **_argv)
{
	parametros.espaciosDisponibles = 0;
	parametros.randomTest = false;
	parametros.enableSimulatorLogs = false;
	parametros.enableEventsLogs = false;

	argc = _argc;
	argv = _argv;

	loadArgs();
}

CheckArgs::~CheckArgs()
{
}

void CheckArgs::loadArgs()
{
	int opcion;
	int option_index;
	while ((opcion = getopt_long(argc, argv, optString.c_str(), optStringLong, &option_index)) != -1)
	{
		switch (opcion)
		{
		// Nuevo argumento para la cantidad de espacios disponibles
		case 'k':
			parametros.espaciosDisponibles = std::atof(optarg);
			break;
		case 's':
			parametros.enableSimulatorLogs = true;
			break;
		case 'e':
			parametros.enableEventsLogs = true;
			break;
		case 't':
			parametros.randomTest = true;
			break;
		case 'h':
		default:
			printUsage();
			exit(EXIT_FAILURE);
		}
	}

	if (parametros.espaciosDisponibles == 0)
	{
		printUsage();
		exit(EXIT_FAILURE);
	}
}

CheckArgs::args_t CheckArgs::getArgs()
{
	return (parametros);
}

void CheckArgs::printUsage()
{
	std::cout << "Uso: " << argv[0] << " " << opciones << "\n"
			  << descripcion << std::endl;
}
