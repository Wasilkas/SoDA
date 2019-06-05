#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <fstream>

using namespace std;

const int Nmax = 20, keyLen = 8, NameSize = 78;

struct counts
{
	int views, cmp, mov;
	counts(int _views = 0, int _cmp = 0, int _mov = 0) : views(_views), cmp(_cmp), mov(_mov) {}
};

struct wProduct
{
	string key, name;
	int amt;

	wProduct(string _key = "", string _name = "", int _amt = 0) : key(_key), name(_name), amt(_amt) {}
};

struct wTable
{
	wProduct elem[Nmax];
	size_t n = 0;
	wTable(const string &fname)
	{
		ifstream f(fname + ".txt");
		if (f.is_open())
			if (f.peek() != EOF)
			{
				bool NotAll = false;
				while (!f.eof())
				{
					wProduct prd;
					size_t i;
					f >> prd.key >> prd.name >> prd.amt;
					for (i = 0; i < this->n && this->elem[i].key != prd.key; i++);
					if (i == this->n)
						if (this->n < Nmax)
							this->elem[this->n++] = prd;
						else
							NotAll = true;
					else
						this->elem[i].amt += prd.amt;
				}
				if (NotAll)
					cout << "Not all products are included in the table 'Work'.\n";
				else
					cout << "All products are included in the table 'Work'.\n";
			}
			else cout << "File '" + fname + ".txt' is empty.\n";
		else cout << "File '" + fname + ".txt' could not be opened.\n";
		f.close();
	}
	wTable() {}
};

struct sProduct
{
	string key, name;
	int amt;
	float value;

	sProduct(string _key = "", string _name = "", int _amt = 0, float _value = 0) : key(_key), name(_name), amt(_amt), value(_value) {}
};

struct sTable
{
	sProduct elem[Nmax];
	size_t n = 0;
	sTable(const string &fname)
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
	float value;

	price(string _key = "", float _value = 0): key(_key), value(_value) {}
};

struct priceList                     // Прейскурант
{
	price elem[Nmax];
	size_t n = 0;
	priceList(const string &fname)
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

void Unite(sTable &, wTable &, const priceList&);
void QuickSort(wTable &, const int &, const int &, counts &);
void Pyramid(wTable &, counts &, const int &, const int &);
void HeapSort(wTable &, counts &);
void ShellSort(wTable &, counts &);
void ShellSort(priceList &);
int compare(const void *, const void *);
void printWork(const wTable &, const string &);
void printStock(const sTable &, const string &);
float ValueSearch(const priceList &, const string &, int &);
void generator(const string &, const string &, const string &);

#endif

