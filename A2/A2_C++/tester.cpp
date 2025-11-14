#include "tester.h"
#include "array_generator.h"
#include "algorithms.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

SortTester::SortTester() : generator(), MEASUREMENT_REPEATS(25) {}

long long SortTester::testStandardMergeSort(const std::vector<int>& arr) {
    std::vector<int> copyArr = arr;
    auto start = std::chrono::high_resolution_clock::now();
    SortingAlgorithms::mergeSort(copyArr, 0, copyArr.size() - 1);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

long long SortTester::testHybridMergeSort(const std::vector<int>& arr, int threshold) {
    std::vector<int> copyArr = arr;
    auto start = std::chrono::high_resolution_clock::now();
    SortingAlgorithms::mergeInsertionSort(copyArr, 0, copyArr.size() - 1, threshold);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

long long SortTester::measureMultipleTimes(const std::vector<int>& arr, bool isHybrid, int threshold) {
    std::vector<long long> measurements;
    measurements.reserve(MEASUREMENT_REPEATS);

    for (int i = 0; i < MEASUREMENT_REPEATS; ++i) {
        long long time;

        if (isHybrid) {
            time = testHybridMergeSort(arr, threshold);
        } else {
            time = testStandardMergeSort(arr);
        }

        measurements.push_back(time);
    }

    // Усреднение используем медиану
    std::sort(measurements.begin(), measurements.end());
    return measurements[MEASUREMENT_REPEATS / 2];
}

void SortTester::runComparativeAnalysis() {
    std::vector<int> sizes;
    for (int size = 500; size <= 10000; size += 100) {
        sizes.push_back(size);
    }

    // Генерация массивов максимальной длины
    std::vector<int> randomMax = generator.generateRandomArray(100000);
    std::vector<int> reverseMax = generator.generateReverseSortedArray(100000);
    std::vector<int> almostMax = generator.generateAlmostSortedArray(100000, 10);

    std::vector<std::vector<long long>> results;

    std::cout << "Running comparative analysis with " << MEASUREMENT_REPEATS << " measurements per test...\n";

    for (size_t i = 0; i < sizes.size(); ++i) {
        int size = sizes[i];

        std::vector<int> randomArr = generator.getSubArray(randomMax, size);
        std::vector<int> reverseArr = generator.getSubArray(reverseMax, size);
        std::vector<int> almostArr = generator.getSubArray(almostMax, size);

        long long randomStd = measureMultipleTimes(randomArr, false);  // Standard
        long long randomHyb = measureMultipleTimes(randomArr, true);   // Hybrid

        long long reverseStd = measureMultipleTimes(reverseArr, false);
        long long reverseHyb = measureMultipleTimes(reverseArr, true);

        long long almostStd = measureMultipleTimes(almostArr, false);
        long long almostHyb = measureMultipleTimes(almostArr, true);

        results.push_back({static_cast<long long>(size),
                           randomStd, randomHyb,
                           reverseStd, reverseHyb,
                           almostStd, almostHyb});

        if (i % 20 == 0) {
            std::cout << "Progress: " << i << "/" << sizes.size() << " sizes completed\n";
        }
    }

    saveResultsToCSV("../comparative_analysis.csv", results);
}

void SortTester::testDifferentThresholds() {
    std::vector<int> thresholds = {5, 10, 15, 20, 25, 30, 40, 50, 75, 100, 200, 300, 350, 400, 450, 500};

    std::cout << "Testing threshold values...\n";

    std::vector<int> testArray = generator.generateRandomArray(50000);
    std::vector<std::vector<long long>> results;

    long long standardTime = measureMultipleTimes(testArray, false);
    results.push_back({1000, standardTime});

    for (int threshold : thresholds) {
        long long time = measureMultipleTimes(testArray, true, threshold);
        results.push_back({static_cast<long long>(threshold), time});
        std::cout << "  Threshold " << threshold << ": " << time << " microseconds\n";
    }

    std::string filename = "../threshold_analysis.csv";
    saveResultsToCSV(filename, results);

    std::cout << "Threshold analysis completed!\n";
}



void SortTester::saveResultsToCSV(const std::string& filename, const std::vector<std::vector<long long>>& results) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    if (filename.find("../threshold_analysis") != std::string::npos) {
        file << "Threshold,Time(microseconds)\n";
        for (const auto& row : results) {
            file << row[0] << "," << row[1] << "\n";
        }
    } else if (filename == "../comparative_analysis.csv") {
        file << "Size,Random_Standard,Random_Hybrid,Reverse_Standard,Reverse_Hybrid,Almost_Standard,Almost_Hybrid\n";
        for (const auto& row : results) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) file << ",";
            }
            file << "\n";
        }
    }

    file.close();
    std::cout << "Saved: " << filename << " with " << results.size() << " rows\n";
}