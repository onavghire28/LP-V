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

// Sequential Bubble Sort
double sequentialSort() {
    int temp[100];
    for (int i = 0; i < n; i++) temp[i] = arr[i];

    double start = omp_get_wtime();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                swap(temp[j], temp[j + 1]);
            }
        }
    }

    double end = omp_get_wtime();

    cout << "Sorted (Sequential): ";
    for (int i = 0; i < n; i++) cout << temp[i] << " ";

    cout << "\nTime: " << end - start << " sec\n";

    return (end - start);
}

// Parallel Bubble Sort
double parallelSort() {
    int temp[100];
    for (int i = 0; i < n; i++) temp[i] = arr[i];

    double start = omp_get_wtime();

    for (int i = 0; i < n; i++) {

        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {
            if (temp[j] > temp[j + 1]) {
                swap(temp[j], temp[j + 1]);
            }
        }

        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {
            if (temp[j] > temp[j + 1]) {
                swap(temp[j], temp[j + 1]);
            }
        }
    }

    double end = omp_get_wtime();

    cout << "Sorted (Parallel): ";
    for (int i = 0; i < n; i++) cout << temp[i] << " ";

    cout << "\nTime: " << end - start << " sec\n";

    return (end - start);
}

// Compare both
void compare() {
    double t1 = sequentialSort();
    double t2 = parallelSort();

    cout << "\n--- Comparison ---\n";
    cout << "Sequential Time: " << t1 << " sec\n";
    cout << "Parallel Time: " << t2 << " sec\n";

    if (t2 < t1)
        cout << "Parallel is faster\n";
    else
        cout << "Sequential is faster (small input overhead)\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Create Array\n";
        cout << "2. Display Array\n";
        cout << "3. Sequential Bubble Sort\n";
        cout << "4. Parallel Bubble Sort\n";
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