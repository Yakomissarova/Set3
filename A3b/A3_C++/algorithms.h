#ifndef A3_ALGORITHMS_H
#define A3_ALGORITHMS_H

#include <vector>
#include <cmath>
#include <cstdlib>

class SortingAlgorithms {
public:
    static void standardQuickSort(std::vector<int>& arr, int left, int right);
    static void introSort(std::vector<int>& arr, int left, int right);

private:
    static void heapify(std::vector<int>& A, int n, int i);
    static void buildMaxHeap(std::vector<int>& A);
    static void heapSort(std::vector<int>& A, int left, int right);
    static void insertionSort(std::vector<int>& arr, int left, int right);
    static int quickSort(std::vector<int>& A, int left, int right);
    static void hybridSort(std::vector<int>& A, int left, int right, int depth, int maxDepth);
};

#endif //A3_ALGORITHMS_H
