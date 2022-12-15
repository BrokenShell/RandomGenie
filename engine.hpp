#include <random>

class RandomNumberEngine
{
public:
  // Constructor
  RandomNumberEngine()
  {
    // Seed the engine with the current time
    engine_.seed(std::chrono::system_clock::now().time_since_epoch().count());
  }

  // Generate a random integer in the specified range
  int generateInt(int min, int max)
  {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine_);
  }

  // Generate a random floating point value in the specified range
  double generateDouble(double min, double max)
  {
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(engine_);
  }

private:
  std::mt19937 engine_; // Mersenne Twister engine
};
