#ifndef A2_ALGORITHMS_H
#define A2_ALGORITHMS_H
#include <vector>

class SortingAlgorithms {
public:
    static void mergeSort(std::vector<int>& arr, int left, int right);
    static void mergeInsertionSort(std::vector<int>& arr, int left, int right, int threshold = 15);

private:
    static void merge(std::vector<int>& arr, int left, int mid, int right);
    static void insertionSort(std::vector<int>& arr, int left, int right);
};

#endif //A2_ALGORITHMS_H
