#include <iostream>
#include <time.h>
#include <math.h>
#include <locale.h>
#include "Sorting.h"

#define N1 10000
#define N2 15000
#define N3 45000
#define N4 135000

using namespace std;

void Selection_Test(string filename, int* Ar1, int* Ar2, int* Ar3, int*Ar4);
void StraightInsertionTest(string filename, int* Ar1, int* Ar2, int* Ar3, int* Ar4);
void BinaryInsertionTest(string filename, int* Ar1, int* Ar2, int* Ar3, int* Ar4);
void ShellSortTest(string filename, int* Ar1, int* Ar2, int* Ar3, int* Ar4);
void ShellSortFibonacciTest(string filename, int* Ar1, int* Ar2, int* Ar3, int* Ar4);

int main()
{
	int i, j, m[N1], arr[N1];
	srand(time(0));
	
	char* locale = setlocale(LC_ALL, "");
	int* Ar1 = new int[N1], * Ar2 = new int[N2], * Ar3 = new int[N3], *
		Ar4 = new int[N4], mode, scan;
	bool running = true;
	char menu;
	string filename;
	filename = "test_numbers.txt";
	if (!(Ar1 && Ar2 && Ar3 && Ar4))
	{
		cout << "Ошибка выделения памяти!" << endl;
		return 1;
	}
	while (running)
	{
		system("cls");
		cout << "Выберите сортировку:" << endl << "1 - Сортировка простыми вставками"<<endl<<"2 - Сортировка бинарными вставками"<<endl<< "3 - Сортировка Шелла (h[k-1] = 2h[k]+1, h[t] = 1, t = log2(2n)-1"<<endl<< "4 - Сортировка Шелла(Фибоначчи)"<<endl<< "5 - Выход" <<endl << endl << "Выберите пункт из меню: ";
		cin >> menu;
		system("cls");
		switch (menu)
		{
		case '1':
			StraightInsertionTest(filename, Ar1, Ar2, Ar3, Ar4);
			break;
		case '2':
			BinaryInsertionTest(filename, Ar1, Ar2, Ar3, Ar4);
			break;
		case '3':
			ShellSortTest(filename, Ar1, Ar2, Ar3, Ar4);
			break;
		case '4':
			ShellSortFibonacciTest(filename, Ar1, Ar2, Ar3, Ar4);
			break;
		case '5':
			running = false;
			cout << "Завершение работы." << endl;
			break;
		default:
			cout << "Введите пункт из меню!" << endl;
		}
		system("pause");
	}
	delete[] Ar1;
	delete[] Ar2;
	delete[] Ar3;
	delete[] Ar4;
	return 0;
}

void Selection_Test(string filename, int* Ar1, int* Ar2, int* Ar3, int* Ar4)
//тестирование сортировки выбором
{
	int* arrs[4] = { Ar1,Ar2,Ar3,Ar4 };
	int n[4] = { N1,N2,N3,N4 };
	unsigned long long int* counters = new unsigned long long int[2];
	time_t timer;
	for (int i = 0; i < 4; i++)
	{
		Ar_Fill(filename, arrs[i], n[i]);
		cout << "Количество присваиваний для массива из " << n[i] << " переменных:" << endl;
			for (int j = 0; j < 3; j++)
			{
				counters[1] = counters[0] = 0;
				timer = clock();
				if (j == 2)
					Ar_Reverse(arrs[i], n[i]);
				StraightSelection(arrs[i], n[i], counters);
				timer = clock() - timer;
				cout << j + 1 << ")" << counters[0] << ", побочных - " <<
					counters[1] << ", время - " << ((double)timer) / CLOCKS_PER_SEC << " секунды"
					<< endl;
			}
		cout << endl;
	}
}

void StraightInsertionTest(string filename, int* Ar1, int* Ar2, int* Ar3, int* Ar4)
{
	int* arrs[4] = { Ar1,Ar2,Ar3,Ar4 };
	int n[4] = { N1,N2,N3,N4 };
	unsigned long long int* counters = new unsigned long long int[2];
	time_t timer;
	for (int i = 0; i < 4; i++)
	{
		Ar_Fill(filename, arrs[i], n[i]);
		cout << "Количество присваиваний для массива из " << n[i] << " переменных:" << endl;
		for (int j = 0; j < 3; j++)
		{
			counters[1] = counters[0] = 0;
			timer = clock();
			if (j == 2)
				Ar_Reverse(arrs[i], n[i]);
			StraightInsertion(arrs[i], n[i], counters);
			timer = clock() - timer;
			cout << j + 1 << ")" << counters[0] << ", побочных - " <<
				counters[1] << ", время - " << ((double)timer) / CLOCKS_PER_SEC << " секунды"
				<< endl;
		}
		cout << endl;
	}
}

void BinaryInsertionTest(string filename, int* Ar1, int* Ar2, int* Ar3, int* Ar4)
{
	int* arrs[4] = { Ar1,Ar2,Ar3,Ar4 };
	int n[4] = { N1,N2,N3,N4 };
	unsigned long long int* counters = new unsigned long long int[2];
	time_t timer;
	for (int i = 0; i < 4; i++)
	{
		Ar_Fill(filename, arrs[i], n[i]);
		cout << "Количество присваиваний для массива из " << n[i] << " переменных:" << endl;
		for (int j = 0; j < 3; j++)
		{
			counters[1] = counters[0] = 0;
			timer = clock();
			if (j == 2)
				Ar_Reverse(arrs[i], n[i]);
			BinaryInsertion(arrs[i], n[i], counters);
			timer = clock() - timer;
			CheckIfSorted(arrs[i], n[i]);
			cout << j + 1 << ")" << counters[0] << ", побочных - " <<
				counters[1] << ", время - " << ((double)timer) / CLOCKS_PER_SEC << " секунды"
				<< endl;
		}
		cout << endl;
	}
}

void ShellSortTest(string filename, int* Ar1, int* Ar2, int* Ar3, int* Ar4)
{
	int* arrs[4] = { Ar1,Ar2,Ar3,Ar4 };
	int n[4] = { N1,N2,N3,N4 };
	unsigned long long int* counters = new unsigned long long int[2];
	time_t timer;
	for (int i = 0; i < 4; i++)
	{
		Ar_Fill(filename, arrs[i], n[i]);
		cout << "Количество присваиваний для массива из " << n[i] << " переменных:" << endl;
		for (int j = 0; j < 3; j++)
		{
			counters[1] = counters[0] = 0;
			timer = clock();
			if (j == 2)
				Ar_Reverse(arrs[i], n[i]);
			ShellSort(arrs[i], n[i], counters);
			timer = clock() - timer;
			CheckIfSorted(arrs[i], n[i]);
			cout << j + 1 << ")" << counters[0] << ", побочных - " <<
				counters[1] << ", время - " << ((double)timer) / CLOCKS_PER_SEC << " секунды"
				<< endl;
		}
		cout << endl;
	}
}

void ShellSortFibonacciTest(string filename, int* Ar1, int* Ar2, int* Ar3, int* Ar4)
{
	int* arrs[4] = { Ar1,Ar2,Ar3,Ar4 };
	int n[4] = { N1,N2,N3,N4 };
	unsigned long long int* counters = new unsigned long long int[2];
	time_t timer;
	for (int i = 0; i < 4; i++)
	{
		Ar_Fill(filename, arrs[i], n[i]);
		cout << "Количество присваиваний для массива из " << n[i] << " переменных:" << endl;
		for (int j = 0; j < 3; j++)
		{
			counters[1] = counters[0] = 0;
			timer = clock();
			if (j == 2)
				Ar_Reverse(arrs[i], n[i]);
			ShellSortFibonacci(arrs[i], n[i], counters);
			timer = clock() - timer;
			CheckIfSorted(arrs[i], n[i]);
			cout << j + 1 << ")" << counters[0] << ", побочных - " <<
				counters[1] << ", время - " << ((double)timer) / CLOCKS_PER_SEC << " секунды"
				<< endl;
		}
		cout << endl;
	}
}
