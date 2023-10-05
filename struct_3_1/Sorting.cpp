#include <iostream>
#include <fstream>

using namespace std;


int Ar_Fill(string filename, int* Ar, int N) //заполнение массива N элементами из файла test_numbers.txt
{
	int i;
	ifstream Test_File;
	Test_File.open(filename, ios_base::in);
	if (!Test_File)
	{
		cout << "File open Error" << endl;
		return 1;
	}
	for (i = 0; i < N; i++)
	{
		Test_File >> Ar[i];
	}
	Test_File.close();
	return 0;
}

void Ar_Reverse(int* Ar, int N) //представление массива в обратном порядке
{
	int i, tmp;
	for (i = 0; i < N / 2; i++)
	{
		tmp = Ar[i];
		Ar[i] = Ar[N - 1 - i];
		Ar[N - 1 - i] = tmp;
	}
}

void CheckIfSorted(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i] <= a[i + 1])
		{
			cout << "Массив отсортирован неверно!" << endl;
			return;
		}
	}
	cout << "Массив отсортирован верно." << endl;
}


void StraightSelection(int* a, int n, unsigned long long int* counters)
//сортировка выбором
{
	int i, j, tmp, * min;
	for (i = 0; i < n - 1; i++)
	{
		min = a + i;
		counters[1] += 3;
		for (j = i + 1; j < n; j++)
		{
			if (a[j] < *min)
			{
				min = a + j;
				counters[1]++;
			}
			counters[1]++;
		}
		if (*min != a[i])
		{
			tmp = *min;
			*min = a[i];
			a[i] = tmp;
			counters[0] += 3;
		}
	}
	counters[1]++;
}

void StraightInsertion(int* a, int n, unsigned long long int* counters)
{
	int i, j, x;
	for (i = 1; i < n; i++)
	{
		x = a[i];
		for (j = i; j && x > a[j - 1]; j--)
		{
			a[j] = a[j - 1];
			counters[0]++;
		} /* находим место вставки, попутно сдвигая элементы */
		a[j] = x;
		counters[1] ++;
	}
}

void BinaryInsertion(int* a, int n, unsigned long long int* counters)
{
	int i, j, m, left, right, x;
	for (i = 1; i < n; i++)
	{
		x = a[i]; left = 0; right = i;
		while (left < right)	/*пока есть что просматривать*/
		{
			m = left + (right - left) / 2;	/* m = (left+right)/2; делим интервал поиска пополам*/
			if (a[m] >= x)		/*если вставляемое значение больше текущего */
			{
				left = m + 1;		/*искать надо в правой части*/
				counters[0]++;
			}
			else
				right = m;		/*а если нет, то будем искать в левой*/
			counters[1]++;
		}
		for (j = i; j > right; a[j] = a[j - 1], j--);
		{
			a[right] = x;
			counters[1]++;
		}
		counters[1]++;
	}
}

void ShellSort(int* a, int n, unsigned long long int* counters)     /*шаг задается формулой h[t]=1, h[k-1]=3h[k]+1; t=log3(n)-1*/
{
	const int t = (int)(log(n) / log(3)-1);
	int i, j, k, m, x;
	int* h = (int*)malloc(t * sizeof(int));
	h[t - 1] = 1;
	for (m = t - 2; m >= 0; m--)
	{
		h[m] = h[m + 1] * 3 + 1;
		counters[1]++;
	}
	for (m = 0; m < t; m++) 	/*последовательно перебираем все расстояния*/
	{
		k = h[m];
		for (i = k; i < n; i++)	/*до конца цикла метод вставки с учетом шага h[m]*/
		{
			x = a[i]; j = i - k;
			while (j >= 0 && x > a[j])
			{
				a[j + k] = a[j];
				j -= k;
				counters[0]++;
			}
			a[j + k] = x;
			counters[1]++;
		}
		counters[1]++;
	}
	free(h);
}

long long int Fibonacci(int n)
{
	long long int first = 0;
	long long int second = 1;
	for (int i = 1; i < n; i++)
	{
		int temp = first + second;
		first = second;
		second = temp;
	}
	if (n == 0)
		return first;
	return second;
}

void ShellSortFibonacci(int* a, int n, unsigned long long int* counters)     /*шаг задается формулой h[t]=1, h[k-1]=3h[k]+1; t=log3(n)-1*/
{
	int i, j, k, m, x;
	int count = 0;
	i = 1;
	while (count < n) {
		count += Fibonacci(i);
		i++;
		counters[1]++;
	}
	count = i;
	int* h = (int*)malloc(count * sizeof(int));
	for (m = 0; m < count; m++)
	{
		h[m] = Fibonacci(m);
		counters[1]++;
	}

	for (m = 0; m < count; m++) 	/*последовательно перебираем все расстояния*/
	{
		k = h[m];
		for (i = k; i < n; i++)	/*до конца цикла метод вставки с учетом шага h[m]*/
		{
			x = a[i]; j = i - k;
			while (j >= 0 && x > a[j])
			{
				counters[0]++;
				a[j + k] = a[j];
				j -= k;
			}
			a[j + k] = x;
			counters[1]++;
		}
		counters[1]++;
	}
	free(h);
}

