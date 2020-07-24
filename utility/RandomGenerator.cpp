#include "stdafx.h"
#include "RandomGenerator.h"

RandomGenerator::RandomGenerator()
{
	std::random_device rd;

	if (rd.entropy() != 0)
	{
		std::seed_seq seed{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
		m_R2D2.seed(seed);
	}
	else
	{
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		m_R2D2.seed(static_cast<std::mt19937::result_type>(seed));
	}
}

RandomGenerator::~RandomGenerator()
{
}

std::mt19937& RandomGenerator::getR2D2()
{
	return (RandomGenerator::instance().m_R2D2);
}

int RandomGenerator::getRandomInt(int from, int to)
{
	std::uniform_int_distribution<int> dist(from, to);
	return (dist(RandomGenerator::instance().getR2D2()));
}

float RandomGenerator::getRandomFloat(float from, float to)
{
	std::uniform_real_distribution<float> dist(from, to);
	return (dist(RandomGenerator::instance().getR2D2()));
}

double RandomGenerator::getRandomDouble(double from, double to)
{
	std::uniform_real_distribution<double> dist(from, to);
	return (dist(RandomGenerator::instance().getR2D2()));
}

bool RandomGenerator::getRandomBool()
{
	std::uniform_int_distribution<int> dist(0, 1);
	return (dist(RandomGenerator::instance().getR2D2()));
}

bool RandomGenerator::getRandomBoolWhithProb(double prob)
{
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	return (dist(RandomGenerator::instance().getR2D2()) <= prob);
}

RandomGenerator& RandomGenerator::instance()
{
	static RandomGenerator sR2D2;
	return (sR2D2);
}