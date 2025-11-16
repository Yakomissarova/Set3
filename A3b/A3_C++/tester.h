#ifndef A3_TESTER_H
#define A3_TESTER_H
#include <vector>
#include <string>
#include "array_generator.h"

class SortTester {
private:
    ArrayGenerator generator;
    const int MEASUREMENT_REPEATS = 5;

public:
    SortTester();

    long long testStandardQuickSort(const std::vector<int>& arr);
    long long testIntroSort(const std::vector<int>& arr);

    long long measureMultipleTimes(const std::vector<int>& arr, bool isIntroSort = false);

    void runComparativeAnalysis();
    void saveResultsToCSV(const std::string& filename, const std::vector<std::vector<long long>>& results);
};

#endif //A3_TESTER_H
