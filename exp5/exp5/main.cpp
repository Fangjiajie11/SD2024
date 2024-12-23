#include <iostream>
#include <cassert>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace chrono;

// Ωªªª∫Ø ˝
void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// √∞≈›≈≈–Ú
void BubbleSort(int* a, int n) {
    assert(a);
    for (int i = 0; i < n - 1; i++) {
        bool flag = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                Swap(&a[j], &a[j + 1]);
                flag = true;
            }
        }
        if (!flag) {
            break;
        }
    }
}

// ≤Â»Î≈≈–Ú
void InsertSort(int* a, int n) {
    assert(a);
    for (int i = 1; i < n; i++) {
        int x = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > x) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }
}

// —°‘Ò≈≈–Ú
void SelectSort(int* a, int n) {
    assert(a);
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Swap(&a[i], &a[minIndex]);
        }
    }
}

// πÈ≤¢≈≈–Ú÷˙÷˙∫Ø ˝
void _MergeSort(int* a, int left, int right, int* tmp) {
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    _MergeSort(a, left, mid, tmp);
    _MergeSort(a, mid + 1, right, tmp);
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        tmp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
    }
    while (i <= mid) {
        tmp[k++] = a[i++];
    }
    while (j <= right) {
        tmp[k++] = a[j++];
    }
    for (int p = left; p <= right; p++) {
        a[p] = tmp[p];
    }
}

void MergeSort(int* a, int n) {
    assert(a);
    int* tmp = (int*)malloc(sizeof(int) * n);
    _MergeSort(a, 0, n - 1, tmp);
    free(tmp);
}

// øÏÀŸ≈≈–Ú
int PartSort(int* a, int left, int right) {
    int pivot = a[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (a[j] < pivot) {
            Swap(&a[++i], &a[j]);
        }
    }
    Swap(&a[++i], &a[right]);
    return i;
}

void QuickSort(int* a, int left, int right) {
    if (left < right) {
        int pivot = PartSort(a, left, right);
        QuickSort(a, left, pivot - 1);
        QuickSort(a, pivot + 1, right);
    }
}

// ∂—≈≈–Ú
void AdjustDown(int* a, int n, int root) {
    int parent = root;
    int child = parent * 2 + 1;
    while (child < n) {
        if (child + 1 < n && a[child + 1] > a[child]) {
            child++;
        }
        if (a[child] > a[parent]) {
            Swap(&a[child], &a[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else {
            break;
        }
    }
}

void HeapSort(int* a, int n) {
    for (int i = (n - 2) / 2; i >= 0; i--) {
        AdjustDown(a, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        Swap(&a[i], &a[0]);
        AdjustDown(a, i, 0);
    }
}

void PrintArray(int* a, int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void TestSort(void (*sortFunc)(int*, int), int* arr, int n, const string& sortName) {
    int* copy = (int*)malloc(sizeof(int) * n);
    memcpy(copy, arr, sizeof(int) * n);
    auto start = high_resolution_clock::now();
    sortFunc(copy, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << sortName << " Time: " << duration.count()/1000.00 << " ms" << endl;
    free(copy);
}

int main() {

    

    int arr1[] = { 5, 3, 8, 6, 2, 7, 4, 1, 9, 10, 11, 15, 14, 13, 12 };
    int arr2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int arr3[] = { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int n = sizeof(arr1) / sizeof(arr1[0]);
    cout << "√∞≈›≈≈–Ú£®¬“–Ú£¨À≥–Ú£¨ƒÊ–Ú£©£∫" << endl;
    TestSort(BubbleSort, arr1, n, "BubbleSort");
    TestSort(BubbleSort, arr2, n, "BubbleSort");
    TestSort(BubbleSort, arr3, n, "BubbleSort");

    cout << "≤Â»Î≈≈–Ú£®¬“–Ú£¨À≥–Ú£¨ƒÊ–Ú£©£∫" << endl;
    TestSort(InsertSort, arr1, n, "InsertSort");
    TestSort(InsertSort, arr2, n, "InsertSort");
    TestSort(InsertSort, arr3, n, "InsertSort");

    cout << "—°‘Ò≈≈–Ú£®¬“–Ú£¨À≥–Ú£¨ƒÊ–Ú£©£∫" << endl;
    TestSort(SelectSort, arr1, n, "SelectSort");
    TestSort(SelectSort, arr2, n, "SelectSort");
    TestSort(SelectSort, arr3, n, "SelectSort");

    cout << "πÈ≤¢≈≈–Ú£®¬“–Ú£¨À≥–Ú£¨ƒÊ–Ú£©£∫" << endl;
    TestSort(MergeSort, arr1, n, "MergeSort");
    TestSort(MergeSort, arr2, n, "MergeSort");
    TestSort(MergeSort, arr3, n, "MergeSort");

    cout << "øÏÀŸ≈≈–Ú£®¬“–Ú£¨À≥–Ú£¨ƒÊ–Ú£©£∫" << endl;
    TestSort([](int* a, int n) { QuickSort(a, 0, n - 1); }, arr1, n, "QuickSort");
    TestSort([](int* a, int n) { QuickSort(a, 0, n - 1); }, arr2, n, "QuickSort");
    TestSort([](int* a, int n) { QuickSort(a, 0, n - 1); }, arr3, n, "QuickSort");

    cout << "∂—≈≈–Ú£®¬“–Ú£¨À≥–Ú£¨ƒÊ–Ú£©£∫" << endl;
    TestSort(HeapSort, arr1, n, "HeapSort");
    TestSort(HeapSort, arr2, n, "HeapSort");
    TestSort(HeapSort, arr3, n, "HeapSort");

    return 0;
}
