#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <pthread.h>
using namespace std;
static int count_line = 1;//schetchik liniy(potokov)
void *multvv(void *a)
{
 cout << "multiplying line #" << count_line << "( TID: ";
 cout << pthread_self() << " ) start!\n";
 int *args = (int *) a;
 int answer = 0;
 int size = args[0];
 for (int i = 1; i <= size; i++)
 {
 answer = answer + args[i]*args[i+size*count_line];
 }
 cout << "Result of multiplying line #" << count_line;
 cout << ": "<< answer << endl; 
 count_line++;
 pthread_exit(0);
}
int main()
{
 vector<vector<int>> M {{1, 2, 3, 1}, {2, 2, 10, 1}, {-2, 6, 0, 7}};
 vector<int> vector {5, 2, 3, 4};
 int lines = M.size(); // kol-vo strok
 int v_size = vector.size(); // razmer vektorov
 int argc = v_size*(lines+1)+1; // kolvo peredaushihsya argumentov
 int *args = new int [argc];
 args[0] = v_size;
 cout << "Vector : [ ";
 for (int j = 1; j <= v_size; j++) //add vector in args
 {
 args[j] = vector[j-1];
 cout << args[j] << " ";
 }
 cout << "]\n";
 cout << "Matrix: [ ";
 for ( int i = 1; i <= lines; i++ )
 {
 cout << "[ ";
 for (int j = 1; j <= v_size; j++)
 {
 args[j+v_size*i] = M[i-1][j-1]; //add lines in args
 cout << M[i-1][j-1] << " ";
 }
 cout << "] "; 
 }
 cout << "]\n";
 cout << "Multiplication start! \n";
 pthread_t *tid = new pthread_t [lines];
 for (int i = 0; i < lines; i++)
 {
 int status = pthread_create(&tid[i], NULL, multvv, (void*)args);
 if (status != 0)
 {
 perror("pthread create\n");
 exit(EXIT_FAILURE);
 }
 }
 for (int i = 0; i < lines; i++)
 {
 pthread_join(tid[i], NULL);
 cout << i+1 << " thread exit!\n";
 }
 return( EXIT_SUCCESS );
}