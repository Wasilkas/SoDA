#include <iostream>
#include <random>
#include <string.h>
#include "table.h" 

float ValueSearch(const priceList &t, const string &code, int &c)
{
	int i = c, j = t.n - 1;
	while (i <= j)
	{
		c = (i + j) / 2;
		if (code < t.elem[c].key)
			j = c - 1;
		else
			if (code > t.elem[c].key)
				i = c + 1;
			else
				return (t.elem[c].value);
	}
	return -1;
}

void Unite(sTable &dest, wTable &from, const priceList &p)
{
	int n = 0, c = 0;
	float v;
	bool NotAll = false, isFound = false;
	for (int k = 0; k != from.n; k++)
	{
		isFound = false;
		int i = c, j = dest.n - 1;
		while (i <= j && !isFound)
		{
			c = (i + j) / 2;
			if (dest.elem[c].key > from.elem[k].key)
				j = c - 1;
			else
				if (dest.elem[c].key < from.elem[k].key)
					i = c + 1;
				else
				{
					dest.elem[c].amt += from.elem[k].amt;
					c++;
					isFound = true;
				}
		}
		if (dest.n != Nmax && !isFound)
		{
			v = ValueSearch(p, from.elem[k].key, n);
			if (dest.elem[c].key > from.elem[k].key)
			{
				for (int a = dest.n; a > c; a--)
					dest.elem[a] = dest.elem[a - 1];
			}
			else
			{
				for (int a = dest.n; a > c + 1; a--)
					dest.elem[a] = dest.elem[a - 1];
				c++;
			}
			dest.elem[c] = { from.elem[k].key , from.elem[k].name, from.elem[k].amt, v };
			dest.n++;
		}
		else
			if (dest.n == Nmax)
				NotAll = true;
	}
	if (NotAll)
		cout << "Table 'Stock' is full! Not all products from 'Work' are included!";
	else
		cout << "All products from 'Work' are included to 'Stock'!";
}

void QuickSort(wTable &t, const int &b, const int &e, counts &cnt)
{
	if (e - b > 0)
	{
		int m = (b + e) / 2;
		wProduct prd;
		int i = 0, j = 0;
		while (i <= j)
		{
			for (i = b; t.elem[i].key < t.elem[m].key; i++, cnt.cmp++);
			cnt.cmp++;
			for (j = e; t.elem[j].key > t.elem[m].key; j--, cnt.cmp++);
			cnt.cmp++;
			if (i <= j)
			{
				prd = t.elem[i];
				t.elem[i] = t.elem[j];
				t.elem[j] = prd;
				i++;
				j--;
				cnt.mov += 3;
			}
		}
		if (b < j) QuickSort(t, b, j, cnt);
		if (e > i) QuickSort(t, i, e, cnt);
		++cnt.views;
	}
}

void Pyramid(wTable &t, counts &cnt, const int &i, const int &size)
{
	int child, j = i;
	wProduct prd = t.elem[i];
	bool inv = true;
	while (j <= size / 2 - 1 && inv)
	{
		child = 2 * j + 1;
		if (child + 1 < size && t.elem[child].key < t.elem[child + 1].key)
			child++;
		cnt.cmp++;
		if (prd.key < t.elem[child].key)
		{
			t.elem[j] = t.elem[child];
			j = child;
			++cnt.mov;
		}
		else
			inv = false;
		++cnt.cmp;
	}
	t.elem[j] = prd;
	cnt.mov += 2;
}

void HeapSort(wTable &t, counts &cnt)
{
	wProduct prd;
	for (int i = t.n / 2 - 1; i >= 0; i--)
		Pyramid(t, cnt, i, t.n);
	++cnt.views;
	for (int i = t.n - 1; i > 0; i--, ++cnt.views)
	{
		prd = t.elem[0];
		t.elem[0] = t.elem[i];
		t.elem[i] = prd;
		cnt.mov += 3;
		Pyramid(t, cnt, 0, i);
	}
}

void ShellSort(wTable &t, counts &cnt)
{
	/*static const int step[] = { 1,4,10,23,57,132,301,701,1750 };*/
	wProduct temp;
	int k;
	size_t h = 1;
	for (h = 1; h <= t.n / 9; h = 2 * h + 1);
	/*for (num = 0; step[num + 1] < t.n - 1; num++);*/
	for (; h > 0; h = (h - 1) / 2, cnt.views++)
		for (size_t j = h; j < t.n; j++)
		{
			temp = t.elem[j];
			for (k = j - h; k >= 0 && temp.key < t.elem[k].key; k -= h, cnt.cmp++, cnt.mov++)
				t.elem[k + h] = t.elem[k];
			cnt.cmp++;
			t.elem[k + h] = temp;
			cnt.mov += 2;
		}
}

void ShellSort(priceList &t)
{
	/*static const int step[] = { 1,4,10,23,57,132,301,701,1750 };*/
	price temp;
	int k;
	size_t h = 1;
	for (h = 1; h <= t.n / 9; h = 2 * h + 1);
	/*for (num = 0; step[num + 1] < t.n - 1; num++);*/
	for (; h > 0; h = (h - 1) / 2)
		for (size_t j = h; j < t.n; j++)
		{
			temp = t.elem[j];
			for (k = j - h; k >= 0 && temp.key < t.elem[k].key; k -= h, cnt.cmp++, cnt.mov++)
				t.elem[k + h] = t.elem[k];
			cnt.cmp++;
			t.elem[k + h] = temp;
			cnt.mov += 2;
		}
}

int compare(const void *arg1, const void *arg2)
{
	wProduct t1 = *(wProduct *)arg1;
	wProduct t2 = *(wProduct *)arg2;
	return stricmp(t1.key.c_str(), t2.key.c_str());
}

void printWork(const wTable &t, const string &s)
{
	ofstream out(s + ".txt");
	out << "¹\t" << "CIPHER\t\t" << "NAME\t" << "AMOUNT\n";
	for (size_t i = 0; i < t.n; i++)
	{
		out << i << "\t"
			<< t.elem[i].key << "\t"
			<< t.elem[i].name << "\t"
			<< t.elem[i].amt << endl;
	}
	out.close();
}

void printStock(const sTable &t, const string &s)
{
	ofstream out(s + ".txt");
	out << "¹\t" << "CIPHER\t\t" << "NAME\t" << "AMOUNT\t" << "COST\n";
	for (size_t i = 0; i < t.n; i++)
		out << i << "\t"
		<< t.elem[i].key << "\t"
		<< t.elem[i].name << "\t"
		<< t.elem[i].amt << "\t"
		<< t.elem[i].value << endl;
}

void generator(wTable &wTbl, priceList &pl, sTable &sTbl)
{
	//ofstream work(wname + ".txt");
	//ofstream price_list(plname + ".txt");
	//ofstream stock(sname + ".txt");
	
	ifstream name("Names.txt");
	string A[NameSize] = {};
	string s = "";

	if (name.is_open())
		for (int i = 0; !name.eof(); i++)
			name >> A[i];
	else
		cout << "File 'Names.txt' could not be opened.\n";

	int n = 0;

	cout << "Enter size of table 'Work' and table 'Price_list': ";
	cin >> n;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> ltr('a', 'z');
	uniform_int_distribution<> dgt('0', '9');
	uniform_int_distribution<> ltrOrDgt(false, true);
	uniform_int_distribution<> nm(0, 77);
	uniform_int_distribution<> amt(1, 200);
	uniform_real_distribution<> val(1, 200);

	if (n <= Nmax)
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < keyLen; j++)
			{
				if (ltrOrDgt(gen))
					s += ltr(gen);
				else
					s += dgt(gen);
			}
			wProduct wPrd(s, A[nm(gen)], amt(gen));
			wTbl.elem[i] = wPrd;
			wTbl.n++;
			price wPrice(s, val(gen));
			pl.elem[i] = wPrice;
			pl.n++;
			ShellSort(pl);
		}

	cout << "Enter size of table 'Stock': ";
	cin >> n;
}