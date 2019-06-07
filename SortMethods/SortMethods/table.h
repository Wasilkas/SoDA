#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <fstream>

using namespace std;

const int Nmax = 100000, keyLen = 8, NameSize = 78;

struct counts                     		// Структура подсчета просмотров, сравнений, перемещений
{
	int views, cmp, mov;
	counts(int _views = 0, int _cmp = 0, int _mov = 0) : views(_views), cmp(_cmp), mov(_mov) {}
};

struct wProduct
{
	string key, name;
	int amt = 0;

	wProduct(string _key = "", string _name = "", int _amt = 0): key(_key), name(_name), amt(_amt) {}
};

struct wTable
{
	wProduct *elem[Nmax];
	size_t n;
	wTable(size_t _n = 0) : n(_n)
	{
		for (int i = 0; i < n; i++)
			elem[i] = new wProduct;
	}
	//wTable(const string &fname)            	// Автозаполнение таблицы Work                                          
	//{
	//	ifstream f(fname + ".txt");
	//	if (f.is_open())
	//		if (f.peek() != EOF)
	//		{
	//			bool NotAll = false;
	//			while (!f.eof())
	//			{
	//				wProduct prd;
	//				int i;
	//				f >> prd.key >> prd.name >> prd.amt;
	//				for (i = 0; i < this->n && this->elem[i].key != prd.key; i++);
	//				if (i == this->n)
	//					if (this->n < Nmax)
	//						this->elem[this->n++] = prd;
	//					else
	//						NotAll = true;
	//				else
	//					this->elem[i].amt += prd.amt;
	//			}
	//			if (NotAll)
	//				cout << "Not all products are included in the table 'Work'.\n";
	//			else
	//				cout << "All products are included in the table 'Work'.\n";
	//		}
	//		else cout << "File '" + fname + ".txt' is empty.\n";
	//	else cout << "File '" + fname + ".txt' could not be opened.\n";
	//	f.close();
	//}
	//wTable() {}
};

struct sProduct
{
	string key, name;
	int amt = 0;
	double value = 0;
};

struct sTable
{
	sProduct elem[Nmax];
	size_t n = 0;
	sTable(const string &fname)            	// Автозаполнение таблицы Stock
	{
		ifstream f(fname + ".txt");
		if (f.is_open())
			if (f.peek() != EOF)
			{
				bool isFull = false;
				while (!f.eof() && this->n < Nmax)
				{
					sProduct prd;
					f >> prd.key >> prd.name >> prd.amt >> prd.value;
					this->elem[this->n++] = prd;
				}
				if (f.eof())
					cout << "All products are included in the table 'Stock'.\n";
				else
					cout << "Not all products are included in the table 'Stock'.\n";
			}
			else cout << "File '" + fname + ".txt' is empty.\n";
		else cout << "File '" + fname + ".txt' could not be opened.\n";
		f.close();
	}
	sTable() {}
};

struct price
{
	string key;
	double value = 0;
};

struct priceList
{
	price elem[Nmax];
	size_t n = 0;
	priceList(const string &fname)         	// Автозаполнение таблицы priceList
	{
		ifstream f(fname + ".txt");
		if (f.is_open())
			if (f.peek() != EOF)
			{
				while (!f.eof() && this->n < Nmax)
				{
					price prd;
					f >> prd.key >> prd.value;
					this->elem[this->n++] = prd;
				}
				if (f.eof())
					cout << "All products are included in the table 'Price-list'.\n";
				else
					cout << "Not all products are included in the table 'Price-list'.\n";
			}
			else cout << "File '" + fname + ".txt' is empty.\n";
		else cout << "File '" + fname + ".txt' could not be opened.\n";
		f.close();
	}
	priceList() {}
};

void Unite(sTable &, wTable &, const priceList&);           	// Объединение Work и Stock        
void QuickSort(wTable *, int , int);   	// Быстрая сортировка
void Pyramid(wTable &, counts &, const int &, const int &);    	// Построение пирамиды
void HeapSort(wTable &, counts &);                              	// Пирамидальная сортировка
void ShellSort(wTable &, counts &);                  			// Сортировка методом Шелла                              
int compare(const void *, const void *);					// Функция сравнения для qsort
/*void printWork(const wTable &, const string &);*/            		// Вывод таблицы Work                 
void printStock(const sTable &, const string &);            	// Вывод таблицы Stock              
double ValueSearch(const priceList &, const string &, int &);   	// Поиск цены товара из Work в priceList                
void generator(wTable &, priceList &, sTable &);

#endif
#pragma once
