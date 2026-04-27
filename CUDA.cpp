%%writefile vector_add_menu.cu
#include <iostream>
using namespace std;

#define MAX 100

int A[MAX], B[MAX], C[MAX], n = 0;

// CUDA Kernel
__global__ void vectorAdd(int *A, int *B, int *C, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        C[i] = A[i] + B[i];
    }
}

// Create vectors (fixed input for Colab)
void createVectors() {
    n = 5;
    int tempA[5] = {1,2,3,4,5};
    int tempB[5] = {5,4,3,2,1};

    for(int i=0;i<n;i++){
        A[i] = tempA[i];
        B[i] = tempB[i];
    }

    cout << "Vectors created successfully (default values)\n";
}

// Display
void display() {
    if (n == 0) {
        cout << "Create vectors first!\n";
        return;
    }

    cout << "A: ";
    for (int i = 0; i < n; i++) cout << A[i] << " ";

    cout << "\nB: ";
    for (int i = 0; i < n; i++) cout << B[i] << " ";

    cout << endl;
}

// CUDA Addition
void addVectors() {
    if (n == 0) {
        cout << "Create vectors first!\n";
        return;
    }

    int *d_A, *d_B, *d_C;

    cudaMalloc(&d_A, n*sizeof(int));
    cudaMalloc(&d_B, n*sizeof(int));
    cudaMalloc(&d_C, n*sizeof(int));

    cudaMemcpy(d_A, A, n*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, n*sizeof(int), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    vectorAdd<<<blocks, threads>>>(d_A, d_B, d_C, n);

    cudaMemcpy(C, d_C, n*sizeof(int), cudaMemcpyDeviceToHost);

    cout << "Result (A+B): ";
    for (int i = 0; i < n; i++) cout << C[i] << " ";
    cout << endl;

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}

int main() {
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Create Vectors\n";
        cout << "2. Display Vectors\n";
        cout << "3. Add Vectors (CUDA)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: createVectors(); break;
            case 2: display(); break;
            case 3: addVectors(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while(choice != 4);

    return 0;
}


how to run-

!nvcc vector_add_menu.cu -o run
!./run
