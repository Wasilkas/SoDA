#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <fstream>

using namespace std;

const int Nmax = 20, keyLen = 8;

struct counts
{
	int views, cmp, mov;
	counts(int _views = 0, int _cmp = 0, int _mov = 0) : views(_views), cmp(_cmp), mov(_mov) {}
};

struct product
{
	string key, name;
	int amt = 0;
	float value = 0;
};

struct table
{
	product elem[Nmax];
	int n;
};

struct price
{
	string key;
	float value = 0;
};

struct priceList                     // Прейскурант
{
	price elem[Nmax];
	int n = 0;
};

void inputUnorderedTable(table &);
void inputPriceList(priceList &);
void Unite(table &, table &);
void QuickSort(table &, const int &, const int &, counts &);
void HeapSort(table &, counts &);
void ShellSort(table &, counts &);
void print(const table &, const string &);
float ValueSearch(const priceList &, const string &, int &);
void Unite(table &, table &, const priceList &);

#endif

