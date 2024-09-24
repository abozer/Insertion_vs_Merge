#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <time.h>

using namespace std::chrono;
using namespace std;

typedef int64_t i64;

// function to handle the display
// not used in the homework assignment
void display(i64 *array, long int size) {
    for(long int i = 0; i<size; i++)
        cout << array[i] << " ";
    cout << endl;
}

//
void insertionSort(i64 *A, long int size){
    i64 key, j;
    for(long int i = 1; i<size; i++) {
        key = A[i];//take the value
        j = i;
        while(j > 0 && A[j-1]>key) {
            A[j] = A[j-1];
            j--;
        }
        A[j] = key;   //insert key in the correct place
    }
}

// merges two subarrays L and R into A
// p = starting index
// q = middle index
// r = ending index

void merge(i64 *A, long int p, long int q, long int r) {

    // Create copies of the Left and Right portion.
    long int nL = q - p + 1;
    long int nR = r - q;

    i64 L[nL], R[nR];

    // Left portion comes from p...q-1
    for (long int i = 0; i < nL; i++)
        L[i] = A[p + i];
    // Right portion comes from q...r-1
    for (long int j = 0; j < nR; j++)
        R[j] = A[q + 1 + j];

    // Initialize the current index of sub-arrays and main array
    long int i, j, k;
    i = 0; // index for L
    j = 0; // index for R
    k = p; // index for A from p...r-1

    // Until we reach the end of either L or R,
    // choose the larger element from L and R
    // and copy it to the correct position inside A
    while (i < nL && j < nR) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // When we are done with elements of either L or R,
    // copy the remaining elements to A

    // case when R was finished first
    while (i < nL) {
        A[k] = L[i];
        i++;
        k++;
    }
    // case when L was finished first
    while (j < nR) {
        A[k] = R[j];
        j++;
        k++;
    }
}

// Divide the array into two subarrays, sort them and merge them
// l is the starting index to merge sort
// r is the ending index to merge sort
void mergeSort(i64 *A, long int l, long int r) {
    if (l < r) {
        // m is the index where we split the original array
        long int m = l + (r - l) / 2;

        mergeSort(A, l, m);
        mergeSort(A, m + 1, r);

        // Merge the sorted subarrays
        merge(A, l, m, r);
    }
}




int main() {

    //seed the randomizer.
    srand(time(NULL));


    fstream input_file;


    // Below is the block to choose which file you want to sort in a fast way.
    // If you are going to use this portion, you need to comment out the line:
    //input_file.open("input.txt",ios::in);

    // string filenames[] ={"input_10_random.txt","input_10_sorted.txt","input_10_reverse_sorted.txt",
    //                      "input_1000_random.txt","input_1000_sorted.txt","input_1000_reverse_sorted.txt",
    //                      "input_100000_random.txt","input_100000_sorted.txt","input_100000_reverse_sorted.txt" };

    //input_file.open(filenames[7],ios::in);

    cout << "Hello!\n";
    cout <<"=========================================================================\n";


    cout << "Preparing input file.\n";
    input_file.open("input.txt",ios::in);

    if (!input_file ) {
        cout << "File opening problems!";
        return 1;
    }

    long int n; //size of the array, read from the input.txt file below

    // read the size from the first line of the file
    input_file >> n ;
    if (n<=0)
        return 1; //there's a problem in the file




    cout << "Read n = " << n <<" from input.txt" << endl;
    i64 arr_i[n], arr_m[n]; //one for insertion sort, one for merge sort

    long int i;
    for(i=0; i<n ; i++) {
        input_file >> arr_i[i];
        arr_m[i] = arr_i[i];

        // check for EOF
        if (input_file.eof()){

            cout << "End of file reached\n";
            break;
        }
    }
    if (i!=n){
        cout << "Read " << i <<" elements from input.txt, but the n = " << n << ".\nStopping execution!\n" ;
        return 1;
    }


    cout << "Successfully read " << n <<" elements from input.txt" << endl;
    input_file.close();

//    cout << "Array before sorting: " << endl;
//    display(arr_m, n);

    // insertion sort testing
    auto insertion_start = high_resolution_clock::now();
    insertionSort(arr_i, n);
    auto insertion_stop = high_resolution_clock::now();

    auto insertion_duration_nano = duration_cast<nanoseconds>(insertion_stop - insertion_start);
    cout <<"=========================================================================\n";
    cout << "It took "<< insertion_duration_nano.count() << " nanoseconds to sort " << n << " elements using insertion sort." << endl;

    // merge sort testing
    auto merge_start = high_resolution_clock::now();
    mergeSort(arr_m, 0, n-1 );
    auto merge_stop = high_resolution_clock::now();

    auto merge_duration_nano = duration_cast<nanoseconds>(merge_stop - merge_start);
    cout << "It took "<< merge_duration_nano.count() << " nanoseconds to sort " << n << " elements using merge sort." << endl;
    cout <<"=========================================================================\n";


    fstream output_file;
    output_file.open("output.txt",ios::out);
    if (!output_file) {
        cout << "File opening problems!";
        return 1;
    }

    cout << "Preparing output file.\n";
    for(long int i=0; i<n ; i++) {
        output_file << arr_m[i] <<endl;
    }
    output_file.close();

    cout << "Successfully written output.txt\n";
    cout <<"=========================================================================\n";
    cout << "Have a nice day ☺\n";
//    cout << "Array after Sorting: " << endl;
//    display(arr_m, n);

    return 0;

}
