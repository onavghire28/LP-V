#include <iostream>
#include <omp.h>
using namespace std;

int arr[100], n;

// Create array
void createArray() {
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

// Display array
void displayArray() {
    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Merge function
void merge(int a[], int l, int m, int r) {
    int temp[100];
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    for (int i = l; i <= r; i++) {
        a[i] = temp[i];
    }
}

// Sequential Merge Sort
void seqMergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        seqMergeSort(a, l, m);
        seqMergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

// Parallel Merge Sort
void parMergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parMergeSort(a, l, m);

            #pragma omp section
            parMergeSort(a, m + 1, r);
        }

        merge(a, l, m, r);
    }
}

// Sequential wrapper
double sequentialSort() {
    int temp[100];
    for (int i = 0; i < n; i++) temp[i] = arr[i];

    double start = omp_get_wtime();

    seqMergeSort(temp, 0, n - 1);

    double end = omp_get_wtime();

    cout << "Sorted (Sequential): ";
    for (int i = 0; i < n; i++) cout << temp[i] << " ";

    cout << "\nTime: " << end - start << " sec\n";

    return (end - start);
}

// Parallel wrapper
double parallelSort() {
    int temp[100];
    for (int i = 0; i < n; i++) temp[i] = arr[i];

    double start = omp_get_wtime();

    parMergeSort(temp, 0, n - 1);

    double end = omp_get_wtime();

    cout << "Sorted (Parallel): ";
    for (int i = 0; i < n; i++) cout << temp[i] << " ";

    cout << "\nTime: " << end - start << " sec\n";

    return (end - start);
}

// Compare
void compare() {
    double t1 = sequentialSort();
    double t2 = parallelSort();

    cout << "\n--- Comparison ---\n";
    cout << "Sequential Time: " << t1 << " sec\n";
    cout << "Parallel Time: " << t2 << " sec\n";

    if (t2 < t1)
        cout << "Parallel is faster\n";
    else
        cout << "Sequential is faster (small input)\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Create Array\n";
        cout << "2. Display Array\n";
        cout << "3. Sequential Merge Sort\n";
        cout << "4. Parallel Merge Sort\n";
        cout << "5. Compare Performance\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createArray();
            break;

        case 2:
            displayArray();
            break;

        case 3:
            sequentialSort();
            break;

        case 4:
            parallelSort();
            break;

        case 5:
            compare();
            break;

        case 6:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}