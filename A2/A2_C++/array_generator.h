#ifndef A2_ARRAY_GENERATOR_H
#define A2_ARRAY_GENERATOR_H
#include <vector>
#include <random>

class ArrayGenerator {
private:
    void initializeRandom();
    int getRandomNumber(int min, int max);

public:
    ArrayGenerator();
    std::vector<int> generateRandomArray(int size);
    std::vector<int> generateReverseSortedArray(int size);
    std::vector<int> generateAlmostSortedArray(int size, int swapCount = 10);
    std::vector<int> getSubArray(const std::vector<int>& sourceArray, int size);
};

#endif //A2_ARRAY_GENERATOR_H
