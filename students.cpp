#include<stdio.h>
#include<mpi.h>
#include<iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{	

    const int STUDENTS_NUM = 10;

	//For MPI
	MPI_Status status;
	int pid;	
	int TAG = 0;
    int threads = 0;
    int students[STUDENTS_NUM] = { 0 };
    int tmp = 0;
    int filled = 0;


    //Fill array with random
    srand( time(NULL) );
    while( filled < STUDENTS_NUM ){
        tmp = rand() % STUDENTS_NUM + 1; //Number from [1..10]
        bool find = false;
        for( int i = 0; i < STUDENTS_NUM; i++ ){
            if ( students[i] == tmp ) {
                find = true;
                break;
            }
        }
        if ( !find ) {
            students[filled] = tmp;
            filled++;
        }
    }

	//Enter the MPI:
	MPI_Init( &argc, &argv );
    MPI_Comm_size(MPI_COMM_WORLD, &threads);
	MPI_Comm_rank( MPI_COMM_WORLD, &pid);
	if ( pid != 0){
        //Student code here:
        cout << pid << " have a ticket!" << endl;
        MPI_Send( &pid, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
	} else {
        //Conductor code here:
        int student = 0;
        for (int i = 0; i < STUDENTS_NUM; i++){
            MPI_Recv( &student, 1, MPI_INT, students[i], TAG, MPI_COMM_WORLD, &status );
            cout << student << " student come!" << endl;
        }
        cout << "Ended!";
    }
    MPI_Finalize();
}

