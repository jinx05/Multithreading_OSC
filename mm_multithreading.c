// to compute the product of two matrices using multithreading
// this example works on square matrices of size 10000 x 10000
// number of threads are 25
// the program splits the job in a way such that each thread works on a strip of matrices
// since there are 10000 rows and 25 threads, each thread will work on a strip that is 400 rows wide
// the product of matrices A and B are stored in matrix C
// developer and owner of this program: Shrey S V
// created by alice_v3.0.4 on 10/09/18

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

// make sure that for N x N matrices and number of threads t, N % t = 0

const int n_row = 2, range = 10, n_thread = 1;
int strip_size = n_row / n_thread;
pthread_t * threads;
int a[n_row][n_row], b[n_row][n_row], c[n_row][n_row];

// stores thread information
typedef struct thread
{
	int start_row;
	int thread_no;
} thread;

// fills a matrix with random numbers of between 0 to (range - 1)
void fill_matrix(int a[n_row][n_row])
{
	for(int i = 0; i < n_row; i++)
		for(int j = 0; j < n_row; j++)
			a[i][j] = rand() % range;
}

// prints a matrix
void print_matrix(int a[n_row][n_row])
{
	for(int i = 0; i < n_row; i++)
	{
		for(int j = 0; j < n_row; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
	printf("\n");
}

// does matrix multiplication for a strip of matrices
void* matmul(void* arg)
{
	thread* t = (thread*) arg;
	int row = t -> start_row;
	for(int i = row; i < row + strip_size; i++)
		for(int j = 0; j < n_row; j++)
			for(int k = 0; k < n_row; k++)
				c[i][j] += a[i][k] * b[k][j];
	return NULL;
}

// driver fuction
int main()
{
	// to initialize random numbers
	srand(time(NULL));

	// populate the matrices A and B
	fill_matrix(a);
	fill_matrix(b);
	printf("Matrix A: \n");
	print_matrix(a);
	printf("Matrix B: \n");
	print_matrix(b);

	// create n_thread amount of threads and assign them to solve for their corresponding strips
	for(int i = 0; i < n_thread; i++)
	{
		thread t;
		t.start_row = i * strip_size;
		t.thread_no = i;
		pthread_create(&threads[i], NULL, matmul, (void*) &t);
	}

	// join the threads once the computation is complete
	for(int i = 0; i < n_thread; i++)
		pthread_join(threads[i], NULL);

	// print the resultant matrix C
	printf("Matrix A x B: \n");
	print_matrix(c);
	return 0;
}