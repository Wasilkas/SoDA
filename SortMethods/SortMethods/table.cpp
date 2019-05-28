#include <iostream> 
#include "table.h" 

void inputTable(table & t)
{
	ifstream f("work.txt");
	if (f.is_open())
		if (f.peek() != EOF)
		{
			bool isFull = false;
			while (!f.eof() && !isFull)
				if (t.n < Nmax)
				{
					product prd;
					int i;
					f >> prd.key >> prd.name >> prd.amt;
					for (i = 0; i < t.n && t.elem[i].key != prd.key; i++);
					if (i == t.n)
						t.elem[t.n++] = prd;
					else
						t.elem[i].amt += prd.amt;
				}
				else
				{
					isFull = true;
					cout << "Table 'Work' is full.\n";
				}
			if (f.eof())
				cout << "All products are included in the table 'Work'.\n";
			else
				cout << "Not all products are included in the table 'Work'.\n";
		}
		else cout << "File 'work.txt' is empty.\n";
	else cout << "File 'work.txt' could not be opened.\n";
	f.close();
}

void inputPriceList(priceList & t)
{
	ifstream f("Price-list.txt");
	if (f.is_open())
		if (f.peek() != EOF)
		{
			bool isFull = false;
			while (!f.eof() && !isFull)
				if (t.n < Nmax)
				{
					price prd;
					f >> prd.key >> prd.value;
					t.elem[t.n++] = prd;
				}
				else
				{
					isFull = true;
					cout << "Table 'Price-list' is full.\n";
				}
			if (f.eof())
				cout << "All products are included in the table 'Price-list'.\n";
			else
				cout << "Not all products are included in the table 'Price-list'.\n";
		}
		else cout << "File 'Price_list.txt' is empty.\n";
	else cout << "File 'Price_list.txt' could not be opened.\n";
	f.close();
}

void inputStockList(table & t)
{
	ifstream f("Stock.txt");
	if (f.is_open())
		if (f.peek() != EOF)
		{
			bool isFull = false;
			while (!f.eof() && !isFull)
				if (t.n < Nmax)
				{
					product prd;
					f >> prd.key >> prd.name >> prd.amt >> prd.value;
					t.elem[t.n++] = prd;
				}
				else
				{
					isFull = true;
					cout << "Table is full 'Stock'.\n";
				}
			if (f.eof())
				cout << "All products are included in the table 'Stock'.\n";
			else
				cout << "Not all products are included in the table 'Stock'.\n";
		}
		else cout << "File 'Store.txt' is empty.\n";
	else cout << "File 'Store.txt' could not be opened.\n";
	f.close();
}

float ValueSearch(const priceList &t, const string &code, int &c)
{
	int i = c, j = t.n - 1;
	while (i != j)
	{
		c = (i + j) / 2;
		if (code <= t.elem[c].key)
			j = c;
		else
			i = c + 1;
	}
	c++;
	if (t.elem[c].key == code)
	{
		return t.elem[c].value;
	}
	else
		return -1;
}

void Unite(table & dest, table &from, const priceList &p)
{
	int n = 0, c = 0;
	float v;
	bool NotAll = false;
	for (int k = 0; k != from.n; k++)
	{
		int i = c, j = dest.n - 1;
		while (i != j)
		{
			c = (i + j) / 2;
			if (dest.elem[c].key >= from.elem[k].key)
				j = c;
			else
				i = c + 1;
		}
		if (dest.elem[c].key == from.elem[k].key)
		{
			dest.elem[c].amt += from.elem[k].amt;
			c++;
		}
		else
			if (dest.n != Nmax)
			{
				v = ValueSearch(p, from.elem[k].key, n);
				if (dest.elem[c].key < from.elem[k].key)
				{
					for (int a = dest.n; a > c; a--)
						dest.elem[a] = dest.elem[a - 1];
					c++;
				}
				else
				{
					for (int a = dest.n; a > c + 1; a--)
						dest.elem[a] = dest.elem[a - 1];
					c += 2;
				}
				dest.elem[c] = from.elem[k];
				dest.elem[c].value = v;
				dest.n++;
			}
			else
				NotAll = true;
	}
	if (NotAll)
		cout << "Table 'Stock' is full! Not all products from 'Work' are included!";
	else
		cout << "All products from 'Work' are included to 'Stock'!";
}

void QuickSort(table & t, const int& b, const int& e, counts & cnt)
{
	if (e - b > 0)
	{
		int m = (b + e) / 2;
		product prd;
		int i = 0, j = 0;
		while (i <= j)
		{
			for (i = b; t.elem[i].key < t.elem[m].key; i++,cnt.cmp++);
			cnt.cmp++;
			for (j = e; t.elem[j].key > t.elem[m].key; j--,cnt.cmp++);
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

void Pyramid(table &t, counts &cnt, const int &i, const int &size)
{
	int child, j = i;
	product prd = t.elem[i];
	static bool inv = true;
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

void HeapSort(table & t, counts & cnt)
{
	product prd;
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

void ShellSort(table & t, counts & cnt)
{
	/*static const int step[] = { 1,4,10,23,57,132,301,701,1750 };*/
	product temp;
	int k, h = 1;
	for (h = 1; h <= t.n / 9; h = 2 * h + 1);
	/*for (num = 0; step[num + 1] < t.n - 1; num++);*/
	for (; h > 0; h = (h - 1) / 2, cnt.views++)
		for (int j = h; j < t.n; j++)
		{
			temp = t.elem[j];
			for (k = j - h; k >= 0 && temp.key < t.elem[k].key; k -= h, cnt.cmp++, cnt.mov++)
				t.elem[k + h] = t.elem[k];
			cnt.cmp++;
			t.elem[k + h] = temp;
			cnt.mov += 2;
		}
}

void print(const table & t, const string & s)
{
	ofstream out(s + ".txt");
	for (int i = 0; i < t.n; i++)
	{
		out << i << "\t"
			<< t.elem[i].key << "\t"
			<< t.elem[i].name << "\t"
			<< t.elem[i].amt << "\t"
			<< t.elem[i].value << endl;
	}
	out.close();
}