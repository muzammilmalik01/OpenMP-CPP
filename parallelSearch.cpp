// Searching a Vector, Parallel Program powered by OpenMP.
// Owner: https://github.com/muzammilmalik01
 
#include <omp.h> 
#include <iostream>
#include <chrono> // using for calculating execution time.
using namespace std::chrono; // for chrono
using namespace std;

int main(){

    // initializing an array of 6,400,000 ints :)
    // we cannot declear a large array (6400000) in the local scope as stack doesn't have that much of the space
    // so, we use Dynamic Memory Allocation on Heap.

    // dynamic allocating array on heap.
    int* array = new int[6400000]; 

    // initializtion of the array.
    for (int i = 0; i < 6400000; i++){
        array[i] = i;
    }
    
    // getting the max number of threads (CPUs) available.
    int no_of_threads = omp_get_max_threads(); 
    cout<<"\nMax Threads / CPUs available: "<< no_of_threads <<endl;

    int* number_to_find = new int; // dynamic allocation of number to find. (max can be 6400000 so allocated dynamically.)
    cout << "\nPlease enter the number to find (0 - 6400000): ";
    cin >> *number_to_find; // taking user's input for the number to find.

    int user_threads = 0;
    cout << "\nPlease enter the number of threads you want to use (1, 2, 4, 8 or Max Available.): ";
    cin >> user_threads; // taking input of threads to use.

    omp_set_num_threads(user_threads); // setting the number of threads to use.

    bool number_found = false;
    auto start = high_resolution_clock::now(); // taking time at start of parallel search.
    #pragma omp parallel // parallel part of the program
    {
        int from = omp_get_thread_num() * (6400000 / user_threads); // setting the start range of the array.
        int to = (omp_get_thread_num() + 1) * (6400000 / user_threads); // setting the stop range for the array.

        for (from; from < to; from++){
            if (number_found == false){ // if number is not found.
                if (array[from] == *number_to_find){ // if user's number is found.
                    number_found = true; // set the number_found variable.
                    cout << "\nThe number "<< *number_to_find << " been found by thread# " << omp_get_thread_num() << endl;   
                    break;
                }
            }
            else{ // if the number has been found, exit the for loop and end the search.
                break;
            }
        }
    }

    auto stop = high_resolution_clock::now(); // taking time at end of parallel search.
    auto duration = duration_cast<milliseconds>(stop - start); // Calculcating execution time of parallel search.
    cout <<"Execution time: " <<duration.count() << " ms" << endl;
    delete[] array; // proper deallocation.
}