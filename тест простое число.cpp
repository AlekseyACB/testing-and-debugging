#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include <chrono>
#pragma warning(disable : 4996)
using namespace std::chrono;
using namespace std;

int STSimple(size_t chislo)
{
	if ((chislo == 1) || (chislo == 2))
	{
		return chislo;
	}
	for (size_t i = 2; i < chislo / 2; i++)
	{
		if (chislo % i == 0)
		{
			return 0;
		}
	}
	return chislo;
}

int Optimized(size_t chislo)
{
	if ((chislo == 1) || (chislo == 2))
	{
		return chislo;
	}
	for (size_t i = 2; i < sqrt(chislo) + 1; i++)
	{
		if (chislo % i == 0)
		{
			return 0;
		}
	}
	return chislo;
}

int rounds = 2;
unsigned long long mulmod(unsigned long long x, unsigned long long y, unsigned long long m)
{
	return (x * y) % m;
}
unsigned long long powmod(unsigned long long x, unsigned long long a, unsigned long long m)
{
	unsigned long long r = 1;
	while (a > 0)
	{
		if (a % 2 != 0)
			r = mulmod(r, x, m);
		a = a >> 1;
		x = mulmod(x, x, m);
	}
	return r;
}

int isprime(unsigned long long p)
{
	unsigned long long q, a;
	unsigned long long i;
	if ((p & 1) != 0 && p > 1)
	{
		q = p - 1;
		do q = q >> 1; while (q % 2 == 0);
		for (i = 1; i < rounds; i++)
		{
			a = rand() % (p - 1) + 2;
			if (powmod(a, p - 1, p) != 1)
			{
				return false;
			}
			a = powmod(a, q, p);
			if (a != 1)
			{
				while (a != 1 && a != p - 1) a = mulmod(a, a, p);
				if (a == 1)
				{
					return false;
				}
			}
		}
		return p;
	}
	else
		return false;
}

int main()
{
	srand(time(0));
	size_t downogr = 1;

	cout << "Input n for 1..n test\n";
	size_t upogr;
	cin >> upogr;

	ofstream out;
	out.open("resultat.txt");

	// Стандартный

	
	out << "Проверка всех чисел на простоту от 1 до " << upogr << " проверкой на деление всех чисел от 1 до числа/2\n----------------\n";
	for (size_t i = downogr; i < upogr; i++)
	{
		    auto start = high_resolution_clock::now();
			{
				STSimple(i);
			}
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast <nanoseconds>(stop - start);
			out << STSimple(i) << "  " << duration.count() << " nanoseconds" << endl;
	}

	//оптимизированный

	out << "Проверка всех чисел на простоту от 1 до " << upogr << " проверкой на деление всех чисел от 1 до корня числа\n----------------\n";
	for (size_t i = downogr; i < upogr; i++)
	{
		auto start = high_resolution_clock::now();
		{
			Optimized(i);
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast <nanoseconds>(stop - start);
		out << Optimized(i) << "  " << duration.count() << " nanoseconds" << endl;
	}

	//Миллера, кол-во проверок 4

	out << "Проверка всех чисел на простоту от 1 до " << upogr << " тестом миллера\n----------------\n";
	for (size_t i = downogr; i < upogr; i++)
	{
		auto start = high_resolution_clock::now();
		{
			isprime(i);
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast <nanoseconds>(stop - start);
		out << isprime(i) << "  " << duration.count() << " nanoseconds" << endl;
	}

	// Стандартный
	downogr = pow(2, 16);
	upogr = pow(2, 32);

	out << "Проверка всех чисел на простоту от 2^16 - 1 до 2^32 - 1 проверкой на деление всех чисел от 1 до числа/2\n----------------\n";
	for (unsigned long long i = downogr; i <= upogr; i = i*2)
	{
		auto start = high_resolution_clock::now();
		STSimple (i-1);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast <nanoseconds>(stop - start);
		out << STSimple(i-1) << "  " << duration.count() << " nanoseconds" << endl;
	}

	
	//оптимизированный

	out << "Проверка всех чисел на простоту 2^16 - 1 до 2^32 - 1 проверкой на деление всех чисел от 1 до корня числа\n----------------\n";
	for (size_t i = 16; i <= 32; i++)
	{
		auto start = high_resolution_clock::now();
		{
			Optimized(pow(2, i) - 1);
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast <nanoseconds>(stop - start);
		out << Optimized(i)<< "  " << duration.count() << " nanoseconds" << endl;
	}

	//Миллера

	out << "Проверка всех чисел на простоту от 2^16 - 1 до 2^32 - 1 тестом миллера\n----------------\n";
	for (size_t i = 16; i <= 32; i++)
	{
		auto start = high_resolution_clock::now();
		{
			isprime(pow(2, i) - 1);
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast <nanoseconds>(stop - start);
		out << isprime(i) << "  " << duration.count() << " nanoseconds" << endl;
	}
	
	// Стандартный

	downogr = pow(2, 16)+1;
	upogr = pow(2, 32);

	out << "Проверка всех чисел на простоту от 2^16 + 1 до 2^32 + 1 проверкой на деление всех чисел от 1 до числа/2\n----------------\n";
	for (size_t i = downogr; i < upogr; i = i * 2)
	{
		auto start = high_resolution_clock::now();
		{
			STSimple(i);
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast <nanoseconds>(stop - start);
		out << STSimple(i) << "  " << duration.count() << " nanoseconds" << endl;
	}


	//оптимизированный

	out << "Проверка всех чисел на простоту 2^16 + 1 до 2^32 + 1 проверкой на деление всех чисел от 1 до корня числа\n----------------\n";
	for (size_t i = downogr; i < upogr; i = i * 2)
	{
		auto start = high_resolution_clock::now();
		{
			Optimized(i);
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast <nanoseconds>(stop - start);
		out << Optimized(i) << "  " << duration.count() << " nanoseconds" << endl;
	}

	//Миллера

	out << "Проверка всех чисел на простоту от 2^16 + 1 до 2^32 + 1 тестом миллера\n----------------\n";
	for (size_t i = downogr; i < upogr; i = i * 2)
	{
		auto start = high_resolution_clock::now();
		{
			isprime(i);
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast <nanoseconds>(stop - start);
		out << isprime(i) << "  " << duration.count() << " nanoseconds" << endl;
	}

	// Стандартный

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dist(pow(2, 32), pow(2, 64));

	size_t slych = dist(gen);

	downogr = pow(2, 32) - 1;
	upogr = pow(2, 64) + 1;

	out << "Проверка случайного числа на простоту от 2^32 до 2^64 проверкой на деление всех чисел от 1 до числа/2\n----------------\n";
	{
	auto start = high_resolution_clock::now();
	{
		STSimple(slych);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast <nanoseconds>(stop - start);
	out << STSimple(slych) << "  " << duration.count() << " nanoseconds" << endl;
	}

	//оптимизированный

	
	out << "Проверка случайного числа на простоту 2^32 до 2^64 проверкой на деление всех чисел от 1 до корня числа\n----------------\n";
	{
		auto start = high_resolution_clock::now();
		{
			Optimized(slych);
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast <nanoseconds>(stop - start);
		out << Optimized(slych) << "  " << duration.count() << " nanoseconds" << endl;
	}
	

	//Миллера, кол-во проверок 4

	
	out << "Проверка случайного числа на простоту от 2^32 до 2^64 тестом миллера\n----------------\n";
	{
		auto start = high_resolution_clock::now();
		{
			isprime(slych);
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast <nanoseconds>(stop - start);
		out << isprime(slych)<< "  " << duration.count() << " nanoseconds" << endl;
	}
	out.close();
	return 0;
}
