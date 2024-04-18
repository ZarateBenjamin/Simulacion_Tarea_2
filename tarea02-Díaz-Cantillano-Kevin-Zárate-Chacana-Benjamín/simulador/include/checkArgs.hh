#pragma once

#include <string>
#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include <cstdint>

class CheckArgs
{
public:
	CheckArgs(int argc, char **argv);
	~CheckArgs();
	void loadArgs();
	typedef struct args_t
	{
		uint32_t espaciosDisponibles;
		uint32_t trabajosAProcesar;
		bool randomTest;
		bool enableSimulatorLogs;
		bool enableEventsLogs;
	} args_t;

	args_t getArgs();

private:
	int argc;
	char **argv;
	void printUsage();

	std::string optString;
	const struct option *optStringLong;
	std::string opciones;
	std::string descripcion;

	args_t parametros;
};