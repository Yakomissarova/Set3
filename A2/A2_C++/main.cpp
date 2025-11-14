#include "tester.h"
#include <iostream>

int main() {
    SortTester tester;

    std::cout << "Generating experimental data for analysis...\n";

    std::cout << "Running threshold analysis...\n";
    tester.testDifferentThresholds();

    std::cout << "Generating comparative analysis data...\n";
    tester.runComparativeAnalysis();

    std::cout << "Data generation complete!\n";
    std::cout << "Generated CSV files:\n";
    std::cout << "  - comparative_analysis.csv: Time measurements for all array types and sizes\n";
    std::cout << "  - threshold_analysis.csv: Threshold analysis\n";
}