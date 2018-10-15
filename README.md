# Multithreading_OSC
Multithreaded code in C for OSC class
// to compute the product of two matrices using multithreading
// this example works on square matrices of size 10000 x 10000
// number of threads are 25
// the program splits the job in a way such that each thread works on a strip of matrices
// since there are 10000 rows and 25 threads, each thread will work on a strip that is 400 rows wide
// the product of matrices A and B are stored in matrix C
// created by alice_v3.0.4 on 10/09/18
