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
    if (n == 0) {
        cout << "Array not created!\n";
        return;
    }

    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Parallel Sum
void findSum() {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    cout << "Sum = " << sum << endl;
}

// Parallel Min
void findMin() {
    int minVal = arr[0];

    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal)
            minVal = arr[i];
    }

    cout << "Minimum = " << minVal << endl;
}

// Parallel Max
void findMax() {
    int maxVal = arr[0];

    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    cout << "Maximum = " << maxVal << endl;
}

// Average
void findAverage() {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    double avg = (double)sum / n;

    cout << "Average = " << avg << endl;
}

int main() {
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Create Array\n";
        cout << "2. Display Array\n";
        cout << "3. Find Sum (Parallel)\n";
        cout << "4. Find Minimum (Parallel)\n";
        cout << "5. Find Maximum (Parallel)\n";
        cout << "6. Find Average (Parallel)\n";
        cout << "7. Exit\n";
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
            findSum();
            break;

        case 4:
            findMin();
            break;

        case 5:
            findMax();
            break;

        case 6:
            findAverage();
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}