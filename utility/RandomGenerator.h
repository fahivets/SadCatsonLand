#ifndef RANDOMGENERATOR_H_INCLUDE
#define RANDOMGENERATOR_H_INCLUDE
#include "NonCopyable.h"
#include "NonMovable.h"

class RandomGenerator : public NonCopyable, public NonMovable
{
public:
	// Functions
	static std::mt19937& getR2D2();
	static int getRandomInt(int from, int to);
	static float getRandomFloat(float from, float to);
	static double getRandomDouble(double from, double to);
	static bool getRandomBool();
	static bool getRandomBoolWhithProb(double prob); // with what probability will be true, probability between 0.0 and 1.0

private:
	std::mt19937 m_R2D2;

	// Constructors/Destructors
	RandomGenerator();
	~RandomGenerator();

	// Private functions
	static RandomGenerator& instance();
};

#endif