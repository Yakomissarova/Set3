#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void heapify(vector<int>& A, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i) {
        swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

void buildMaxHeap(vector<int>& A) {
    int n = A.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i);
    }
}

void heapSort(vector<int>& A, int left, int right) {
    int n = right - left + 1;
    vector<int> temp(n);

    for (int i = 0; i < n; i++) {
        temp[i] = A[left + i];
    }

    buildMaxHeap(temp);
    for (int i = n - 1; i > 0; i--) {
        swap(temp[0], temp[i]);
        heapify(temp, i, 0);
    }

    for (int i = 0; i < n; i++) {
        A[left + i] = temp[i];
    }
}

void insertionSort(vector<int>& arr, int left, int right) {
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

int quickSort(vector<int>& A, int left, int right) {
    // Выбираем случайный опорный элемент
    int randomIndex = left + rand() % (right - left + 1);
    swap(A[randomIndex], A[right]);
    int pivot = A[right];

    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (A[j] <= pivot) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[right]);
    return i + 1;
}



void hybridSort(vector<int>& A, int left, int right, int depth, int maxDepth) {

    // Переключений на Insertion Sort
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

int main() {

    int n;
    cin >> n;

    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    if (n > 0) {
        int maxDepth = 2 * log2(n);
        hybridSort(A, 0, n - 1, 0, maxDepth);
    }

    for (int i = 0; i < n; i++) {
        cout << A[i];
        if (i < n - 1) {
            cout << " ";
        }
    }
    cout << endl;
}