#include "checkArgs.hh"

CheckArgs::CheckArgs(int _argc, char **_argv) : argc(_argc), argv(_argv), optString("k:j:seh")

{
    parametros.espaciosDisponibles = 0;
    parametros.trabajosAProcesar = 0;
    parametros.randomTest = false;
    parametros.enableSimulatorLogs = false;
    parametros.enableEventsLogs = false;

    static const struct option opts[] = {
        {"espaciosDisponibles", required_argument, nullptr, 'k'},
        {"trabajosAProcesar", required_argument, nullptr, 'j'},
        {"test", no_argument, nullptr, 't'},
        {"slogs", no_argument, nullptr, 's'},
        {"elogs", no_argument, nullptr, 'e'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}};
    optStringLong = opts;
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
        case 'k':
            parametros.espaciosDisponibles = std::atof(optarg);
            break;
        case 'j':
            parametros.trabajosAProcesar = std::atof(optarg);
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
    return parametros;
}

void CheckArgs::printUsage()
{
    std::cout << "Uso: " << argv[0] << " " << opciones << "\n"
              << descripcion << std::endl;
}
