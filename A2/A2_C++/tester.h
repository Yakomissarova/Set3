#ifndef A2_TESTER_H
#define A2_TESTER_H

#include <vector>
#include <string>
#include "array_generator.h"

class SortTester {
private:
    class ArrayGenerator generator;
    const int MEASUREMENT_REPEATS = 25;

public:
    SortTester();

    long long testStandardMergeSort(const std::vector<int>& arr);
    long long testHybridMergeSort(const std::vector<int>& arr, int threshold = 40);

    long long measureMultipleTimes(const std::vector<int>& arr, bool isHybrid = false, int threshold = 40);

    void runComparativeAnalysis();
    void testDifferentThresholds();
    void saveResultsToCSV(const std::string& filename, const std::vector<std::vector<long long>>& results);
};

#endif //A2_TESTER_H
