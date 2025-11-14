#include "array_generator.h"
#include <ctime>
#include <functional>

ArrayGenerator::ArrayGenerator() {
    initializeRandom();
}

void ArrayGenerator::initializeRandom() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int ArrayGenerator::getRandomNumber(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

std::vector<int> ArrayGenerator::generateRandomArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = getRandomNumber(0, 10000);
    }
    return arr;
}

std::vector<int> ArrayGenerator::generateReverseSortedArray(int size) {
    std::vector<int> arr = generateRandomArray(size);
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    return arr;
}

std::vector<int> ArrayGenerator::generateAlmostSortedArray(int size, int swapCount) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }

    for (int i = 0; i < swapCount; ++i) {
        int idx1 = getRandomNumber(0, size - 1);
        int idx2 = getRandomNumber(0, size - 1);
        std::swap(arr[idx1], arr[idx2]);
    }

    return arr;
}

std::vector<int> ArrayGenerator::getSubArray(const std::vector<int>& sourceArray, int size) {
    if (size >= sourceArray.size()) {
        return sourceArray;
    }
    return std::vector<int>(sourceArray.begin(), sourceArray.begin() + size);
}