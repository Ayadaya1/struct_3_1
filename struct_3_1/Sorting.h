#pragma once
#include <iostream>
#include <fstream>

using namespace std;

int Ar_Fill(string filename, int* Ar, int N);
void Ar_Reverse(int* Ar, int N);
void StraightSelection(int* a, int n, unsigned long long int* counters);
void StraightInsertion(int* a, int n, unsigned long long int* counters);
void BinaryInsertion(int* a, int n, unsigned long long int * counters); /*Сортировка с двоичным включением (бинарными вставками)*/
void ShellSort(int* a, int n, unsigned long long int* counters);
void ShellSortFibonacci(int* a, int n, unsigned long long int* counters);
void CheckIfSorted(int* a, int n);
long long int Fibonacci(int n);