// Estimating the Value of Pi, Parallel Program powered by OpenMP.
// Owner: https://github.com/muzammilmalik01

#include <iostream>
#include <omp.h>
#include <chrono> // using for calculating execution time.
using namespace std::chrono; // for chrono
using namespace std;

int main() {

    int *num_steps = new int(2000000000);
    double step = 1.0 / *num_steps;
    double pi = 0.0;

    cout << "Parallel Program: " << endl;
    int user_threads = 0; //initializing the number of threads to be used.
    cout << "\nPlease enter the number of threads you want to use (1, 2, 4, 8 or Max Available.): ";
    cin >> user_threads; // taking input of threads to use.

    omp_set_num_threads(user_threads); // setting the number of threads to use.

    auto start = high_resolution_clock::now(); // time at the starting of the execution

    // What is reduction(+ : pi)? 
    // To avoid the race condition while threads access the variable 'Pi', we add reduction(+ : pi) clause.
    // This creates a private copy of the Pi for each thread. In the end this variable is combined.
    #pragma omp parallel reduction(+ : pi) // Parallel Part of the Program.
    {
        int from = omp_get_thread_num() * (*num_steps / user_threads); // setting the start range of the array.
        int to = (omp_get_thread_num() + 1) * (*num_steps / user_threads); // setting the stop range for the array.
        for (from; from < to; from++){
            double x = (from + 0.5) * step;
            pi = pi + 4.0 / (1.0 + x * x);
        }
    }

    pi = pi * step;
    auto stop = high_resolution_clock::now(); // time at the ending of the execution
    auto duration = duration_cast<milliseconds>(stop - start).count(); // Calculcating execution time of parallel search.

    cout << "Number of Cores used: " << user_threads << endl;
    cout << "Estimated pi: " << pi << endl; // Esitmated Value of Pi
    cout << "Execution Time: " << duration << " ms" << endl;

    return 0;
}