#include "algorithms.h"

void SortingAlgorithms::heapify(std::vector<int>& A, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

void SortingAlgorithms::buildMaxHeap(std::vector<int>& A) {
    int n = A.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i);
    }
}

void SortingAlgorithms::heapSort(std::vector<int>& A, int left, int right) {
    int n = right - left + 1;
    std::vector<int> temp(n);

    for (int i = 0; i < n; i++) {
        temp[i] = A[left + i];
    }

    buildMaxHeap(temp);
    for (int i = n - 1; i > 0; i--) {
        std::swap(temp[0], temp[i]);
        heapify(temp, i, 0);
    }

    for (int i = 0; i < n; i++) {
        A[left + i] = temp[i];
    }
}

void SortingAlgorithms::insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int SortingAlgorithms::quickSort(std::vector<int>& A, int left, int right) {
    // Выбираем случайный опорный элемент
    int randomIndex = left + rand() % (right - left + 1);
    std::swap(A[randomIndex], A[right]);
    int pivot = A[right];

    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (A[j] <= pivot) {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[right]);
    return i + 1;
}

void SortingAlgorithms::hybridSort(std::vector<int>& A, int left, int right, int depth, int maxDepth) {
    // Переключение на Insertion Sort
    if (right - left + 1 < 16) {
        insertionSort(A, left, right);
        return;
    }

    // Переключение на Heap Sort
    if (depth >= maxDepth) {
        heapSort(A, left, right);
        return;
    }

    int pivotIndex = quickSort(A, left, right);

    if (pivotIndex - 1 > left) {
        hybridSort(A, left, pivotIndex - 1, depth + 1, maxDepth);
    }
    if (pivotIndex + 1 < right) {
        hybridSort(A, pivotIndex + 1, right, depth + 1, maxDepth);
    }
}

void SortingAlgorithms::standardQuickSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivotIndex = quickSort(arr, left, right);
        standardQuickSort(arr, left, pivotIndex - 1);
        standardQuickSort(arr, pivotIndex + 1, right);
    }
}

void SortingAlgorithms::introSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int maxDepth = 2 * log2(right - left + 1);
        hybridSort(arr, left, right, 0, maxDepth);
    }
}