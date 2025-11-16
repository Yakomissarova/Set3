#include "tester.h"
#include <iostream>

int main() {
    SortTester tester;

    std::cout << "Algorithm Analysis: Quick Sort vs Introsort\n\n";

    std::cout << "Running comparative analysis for all array types and sizes...\n";
    tester.runComparativeAnalysis();

    std::cout << "\nAnalysis complete!\n";
    std::cout << "Generated file: intro_comparative_analysis.csv\n";
}