#include "tester.h"
#include "array_generator.h"
#include "algorithms.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <algorithm>

SortTester::SortTester() : generator(), MEASUREMENT_REPEATS(5) {}

long long SortTester::testStandardQuickSort(const std::vector<int>& arr) {
    std::vector<int> copyArr = arr;
    auto start = std::chrono::high_resolution_clock::now();
    SortingAlgorithms::standardQuickSort(copyArr, 0, copyArr.size() - 1);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

long long SortTester::testIntroSort(const std::vector<int>& arr) {
    std::vector<int> copyArr = arr;
    auto start = std::chrono::high_resolution_clock::now();
    SortingAlgorithms::introSort(copyArr, 0, copyArr.size() - 1);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

long long SortTester::measureMultipleTimes(const std::vector<int>& arr, bool isIntroSort) {
    std::vector<long long> measurements;
    measurements.reserve(MEASUREMENT_REPEATS);

    for (int i = 0; i < MEASUREMENT_REPEATS; ++i) {
        long long time;

        if (isIntroSort) {
            time = testIntroSort(arr);
        } else {
            time = testStandardQuickSort(arr);
        }

        measurements.push_back(time);
    }

    std::sort(measurements.begin(), measurements.end());
    return measurements[MEASUREMENT_REPEATS / 2];
}

void SortTester::runComparativeAnalysis() {
    std::vector<int> sizes;
    for (int size = 500; size <= 100000; size += 100) {
        sizes.push_back(size);
    }

    // Генерация массивов максимальной длины
    std::vector<int> randomMax = generator.generateRandomArray(100000);
    std::vector<int> reverseMax = generator.generateReverseSortedArray(100000);
    std::vector<int> almostMax = generator.generateAlmostSortedArray(100000, 10);

    std::vector<std::vector<long long>> results;

    std::cout << "Running comparative analysis for Quick Sort vs Introsort...\n";

    for (size_t i = 0; i < sizes.size(); ++i) {
        int size = sizes[i];

        std::vector<int> randomArr = generator.getSubArray(randomMax, size);
        std::vector<int> reverseArr = generator.getSubArray(reverseMax, size);
        std::vector<int> almostArr = generator.getSubArray(almostMax, size);

        // Тестируем каждый тип массива
        long long randomStd = measureMultipleTimes(randomArr, false);
        long long randomIntro = measureMultipleTimes(randomArr, true);

        long long reverseStd = measureMultipleTimes(reverseArr, false);
        long long reverseIntro = measureMultipleTimes(reverseArr, true);

        long long almostStd = measureMultipleTimes(almostArr, false);
        long long almostIntro = measureMultipleTimes(almostArr, true);

        results.push_back({static_cast<long long>(size),
                           randomStd, randomIntro,
                           reverseStd, reverseIntro,
                           almostStd, almostIntro});

        if (i % 50 == 0) {
            std::cout << "Progress: " << i << "/" << sizes.size() << " sizes completed\n";
        }
    }

    saveResultsToCSV("../intro_comparative_analysis.csv", results);
}

void SortTester::saveResultsToCSV(const std::string& filename, const std::vector<std::vector<long long>>& results) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    file << "Size,Random_Standard,Random_Intro,Reverse_Standard,Reverse_Intro,Almost_Standard,Almost_Intro\n";
    for (const auto& row : results) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }

    file.close();
    std::cout << "Saved: " << filename << " with " << results.size() << " rows\n";
}