#include "Random.hh"

// Genera un número aleatorio que sigue una distribución exponencial
double Random::exponential(double rate)
{
	// Motor de generación de números aleatorios
	std::random_device rd;	// Dispositivo para obtener una semilla
	std::mt19937 gen(rd()); // Motor Mersenne Twister

	std::exponential_distribution<> dist(1 / rate);

	return (dist(gen));
}

double Random::normal(double mean, double std)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<double> normalDistro(mean, std);

	return (normalDistro(gen));
}

// Tiempo aleatorio truncado entre llegadas
double Random::normal_truncated(double mu, double sigma, double lower_bound, double upper_bound)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::normal_distribution<> dist(mu, sigma);

	double number;
	do
	{
		number = dist(gen);
	} while (number < lower_bound || number >= upper_bound);
	return number;
}

double Random::uniform(double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> uniformDistro(min, max);

	return (uniformDistro(gen));
}

int Random::integer(int32_t min, int32_t max)
{
	std::random_device rd;	// Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}

double Random::logNormal(double mean, double std)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::lognormal_distribution<double> logNormalDistro(mean, std);

	return (logNormalDistro(gen));
}

double Random::rayleigh(double sd)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> rayleighNumber(0.0, 1.0);

	double number = rayleighNumber(gen);

	return (sd * sqrt(-2.0 * log(number)));
}

void Random::test(uint32_t totalPoints, const std::string &pathFileOut, bool exitAtFinish)
{
	double numberExpo, numberLogNormal, numberRayleigh;
	std::stringstream sOut;

	sOut << "exponential\tlognormal\trayleigh\n";
	for (size_t i = 0; i < totalPoints; i++)
	{
		numberExpo = Random::exponential(1.0 / 5.0);
		numberLogNormal = Random::logNormal(6.383, 0.1655);
		numberRayleigh = Random::rayleigh(1.0);

		sOut << numberExpo << "\t" << numberLogNormal << "\t" << numberRayleigh << "\n";
	}

	std::ofstream outClearFile(pathFileOut);
	outClearFile << sOut.str();
	outClearFile.close();

	if (exitAtFinish)
	{
		exit(EXIT_SUCCESS);
	}
}
