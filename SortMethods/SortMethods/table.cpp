#include <iostream> 
#include <random>
#include "table.h" 

double ValueSearch(const priceList &t, const string &code, int &c)
{
	int i = c, j = t.n - 1;                        			// i � ������ ������� ������, j - �����
	while (i <= j)
	{
		c = (i + j) / 2;                        				// � � ����� ������� ������
		if (code < t.elem[c].key)                     			// ���� ����� > �������� �����
			j = c - 1;                           				// �-1 ���������� ������ ������� ������
		else
			if (code > t.elem[c].key)                  			// ���� ����� < �������� �����
				i = c + 1;                        				// �+1 ���������� ������� ������� ������
			else
				return (t.elem[c].value);                  		// ����� ������� ������
	}
	return -1;
}

//void Unite(sTable &dest, wTable &from, const priceList &p)
//{
//	int n = 0, c = 0;									// n � ������ ������ � ������ ����, � - 
//	double v;										// ������ ������ � ������ �����,v - ����
//	bool NotAll = false, isFound = false;					// NotAll � �������� �� ��� �� Work � St
//	for (int k = 0; k != from.n; k++)						// ���� �� ����������� ��� �� Work
//	{
//		isFound = false;
//		int i = c, j = dest.n - 1;
//		while (i <= j && !isFound)							// ����� ����� � Stock �������� �������
//		{
//			c = (i + j) / 2;
//			if (dest.elem[c].key > from.elem[k].key)
//				j = c - 1;
//			else
//				if (dest.elem[c].key < from.elem[k].key)
//					i = c + 1;
//				else
//				{
//					dest.elem[c].amt += from.elem[k].amt;
//					c++;
//					isFound = true;
//				}
//		}
//		if (dest.n != Nmax && !isFound)						// ���� ������� �� ����� � ������� ��
//		{											// �� ������
//			v = ValueSearch(p, from.elem[k].key, n);			// ����� ���� � ������������
//			if (dest.elem[c].key > from.elem[k].key)			// ���� ���� ������������ ��. < ���� ��.
//			{											// �� ���������� �������, ��
//				for (int a = dest.n; a > c; a--)				// ����� ������ ������� ������� ��. � 
//					dest.elem[a] = dest.elem[a - 1];				// �������� � �� 1 ������
//			}
//			else
//			{
//				for (int a = dest.n; a > c + 1; a--)				// ����� ����� ����� �� �� ��.� ��������
//					dest.elem[a] = dest.elem[a - 1];				// � + 1 �� 1 ������
//				c++;										// �������� ������ ��� ������� �� 1
//			}
//			dest.elem[c] = { from.elem[k].key , from.elem[k].name, from.elem[k].amt, v };
//			dest.n++;									// ������� ������� � �������� ����.
//		}											// ������ �� 1
//		else
//			if (dest.n == Nmax)							// ����� ���� ������� Stock �����
//				NotAll = true;								// ���������� ��� �� ��� �������� ��
//	}												// Work �������� � Stock
//	if (NotAll)
//		cout << "Table 'Stock' is full! Not all products from 'Work' are included!";
//	else
//		cout << "All products from 'Work' are included to 'Stock'!";
//}

void QuickSort(wTable *t,int b, int e)	// b � ������ ������ ������� �����-
{													// �����, � - �����									// ���� ������� ���������� ��������												// ����� ��� 1 �������
		int m = (b + e) / 2;									// m � ������� �������
		wProduct *prd;
		int i = b, j = e;									// i � ������ �������� ����� �� m
		while (i <= j)										// j � ������, ���� ��� �� �������
		{												// ���� �����
			for (i = b; _stricmp(t->elem[i]->key.c_str(), t->elem[m]->key.c_str()) < 0; i++);
			//while (_stricmp(t->elem[i]->key.c_str(), t->elem[m]->key.c_str()) < 0)
				//i++;
			for (j = e; _stricmp(t->elem[j]->key.c_str(), t->elem[m]->key.c_str()) > 0; j--);
			//while (_stricmp(t->elem[j]->key.c_str(), t->elem[m]->key.c_str()) > 0)
				//j--;
			if (i <= j)										// ���� i �� ������ ��� j
			{
				prd = t->elem[i];								// �� �������� �� �������
				t->elem[i] = t->elem[j];
				t->elem[j] = prd;
				i++;											// � ���������� �����
				j--;
			}
		}												// ���� ������� ����� ��������
		if (b < j) QuickSort(t, b, j);						// ����� 1 ��. �� ����� � ������ j
		if (e > i) QuickSort(t, i, e);						// ���������� ���� -/- �� �����										// � ������� � i
}

void Pyramid(wTable &t, counts &cnt, const int &i, const int &size)
{
	int child, j = i;										// Child ������ �������, i -  
	wProduct *prd = t.elem[i];								// ������ ����. ��.
	bool inv = true;
	while (j <= size / 2 - 1 && inv)							// ���� � j ���� ������ � ��������
	{
		child = 2 * j + 1;									// ��������� ������ �������
		if (child + 1 < size && t.elem[child]->key < t.elem[child + 1]->key)
			child++;										// �������� max �� ��������
		cnt.cmp++;
		if (prd->key < t.elem[child]->key)						// ���� ������� ������ ������
		{
			t.elem[j] = t.elem[child];							// ������ ������ �� ����� �������
			j = child;
			++cnt.mov;
		}
		else
			inv = false;										// ����� ������� ��� �������� ���
		++cnt.cmp;
	}
	t.elem[j] = prd;										// ������ ����������� ��. �� 
	cnt.mov += 2;											// ���� �����
}

void HeapSort(wTable &t, counts &cnt)
{
	wProduct *prd;
	for (int i = t.n / 2 - 1; i >= 0; i--)				// ���������� ��������, ������� � ���������� 
		Pyramid(t, cnt, i, t.n);						// �������� � ���������, ���������� ������
	++cnt.views;
	for (int i = t.n - 1; i > 0; i--, ++cnt.views)
	{
		prd = t.elem[0];							// ������ �������� ����� ������ � ����������
		t.elem[0] = t.elem[i];						// �������� �������, � �������� � ����.
		t.elem[i] = prd;							// ��������
		cnt.mov += 3;
		Pyramid(t, cnt, 0, i);						// ��������������� ������� ��� ��������
	}											// �������� � ��������������� ��������,
}											// ��������� �������� �������� ����� ���

void ShellSort(wTable &t, counts &cnt)
{
	/*static const int step[] = { 1,4,10,23,57,132,301,701,1750 };*/	// ������ ������������������ �����-
	wProduct *temp;										// �� � ������ �. ����� 2001�.
	int k;												// k � ������ ����������� ��������
	size_t h = 1;											// h � ����� h-�����
	for (h = 1; h <= t.n / 9; h = 2 * h + 1);					// ������� ���������� ����� ��� 
	/*for (num = 0; step[num + 1] < t.n - 1; num++);*/				// h - �����
	for (; h > 0; h = (h - 1) / 2, cnt.views++)					// ������������� ���� h > 0
		for (size_t j = h; j < t.n; j++)						// �������������� ������ ��.
		{												// ������� � h-����
			temp = t.elem[j];									// �������� �������� �������
			for (k = j - h; k >= 0 && temp->key < t.elem[k]->key; k -= h,	// ��������� ��� ������� j
				cnt.cmp++, cnt.mov++)
				t.elem[k + h] = t.elem[k];
			cnt.cmp++;
			t.elem[k + h] = temp;
			cnt.mov += 2;
		}
}

int compare(const void *arg1, const void *arg2)
{
	wProduct *t1 = *(wProduct **)arg1;							// ������������� t1 � t2, ���� �� 
	wProduct *t2 = *(wProduct **)arg2;							// ���� ��� � ���������
	return _stricmp(t1->key.c_str(), t2->key.c_str());				// t1 ������ ��� t2, ������� 1, 
}													// t1 = t2 � 0, ����� -1

//void printWork(const wTable &t, const string &s)
//{
//	ofstream out(s + ".txt");
//	out << "�\t" << "CIPHER\t\t" << "NAME\t" << "AMOUNT\n";
//	for (size_t i = 0; i < t.n; i++)
//	{
//		out << i << "\t"
//			<< t.elem[i].key << "\t"
//			<< t.elem[i].name << "\t"
//			<< t.elem[i].amt << endl;
//	}
//	out.close();
//}

//void printStock(const sTable &t, const string &s)
//{
//	ofstream out(s + ".txt");
//	out << "�\t" << "CIPHER\t\t" << "NAME\t" << "AMOUNT\t" << "COST\n";
//	for (size_t i = 0; i < t.n; i++)
//		out << i << "\t"
//		<< t.elem[i].key << "\t"
//		<< t.elem[i].name << "\t"
//		<< t.elem[i].amt << "\t"
//		<< t.elem[i].value << endl;
//}

void generator(wTable &wTbl, priceList &pl, sTable &sTbl)
{
	ifstream name("Names.txt");
	string A[NameSize] = {};
	string s = "";

	if (name.is_open())
		for (int i = 0; !name.eof(); i++)
			name >> A[i];
	else
		cout << "File 'Names.txt' could not be opened.\n";

	size_t n = 0;

	cout << "Enter size of table 'Work' and table 'Price_list': ";
	cin >> n;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> ltr('a', 'z');
	uniform_int_distribution<> dgt('0', '9');
	uniform_int_distribution<> ltrOrDgt(false, true);
	uniform_int_distribution<> nm(0, NameSize - 1);
	uniform_int_distribution<> amt(1, 200);
	uniform_real_distribution<> val(1, 200);

	for (int i = 0; wTbl.n < n && wTbl.n < Nmax; i++)    	// ��������� Work � Price-list
	{
		s = "";
		for (int j = 0; j < keyLen; j++)
		{
			if (ltrOrDgt(gen))
				s += ltr(gen);
			else
				s += dgt(gen);
		}
		wTbl.elem[i] =  new wProduct(s, A[nm(gen)], amt(gen));
		wTbl.n++;
	//	if (pl.n < Nmax && pl.n)						// ���������� � ������. ��������� ����������
	//	{
	//		int b = 0, e = pl.n - 1, c = 0;
	//		bool isFound = false;
	//		while (b <= e && !isFound)
	//		{
	//			c = (b + e) / 2;
	//			if (pl.elem[c].key > s)
	//				e = c - 1;
	//			else
	//				if (pl.elem[c].key < s)
	//					b = c + 1;
	//				else
	//					isFound = true;
	//		}
	//		if (pl.elem[c].key > s)
	//		{
	//			for (int a = pl.n; a > c; a--)
	//				pl.elem[a] = pl.elem[a - 1];
	//		}
	//		else
	//		{
	//			for (int a = pl.n; a > c + 1; a--)
	//				pl.elem[a] = pl.elem[a - 1];
	//			c++;
	//		}
	//		pl.elem[c] = { s,val(gen) };
	//		pl.n++;
	//	}
	//	else
	//		if (!pl.n)
	//		{
	//			pl.elem[i] = { s, val(gen) };
	//			pl.n++;
	//		}
	//}

	//cout << "Enter size of table 'Stock': ";
	//cin >> n;

	//for (int i = 0; sTbl.n < n && sTbl.n <= Nmax; i++)		// ��������� Stock
	//{										  	// ���������� Wotk � Price-list
	//	s = "";
	//	for (int j = 0; j < keyLen; j++)
	//	{
	//		if (ltrOrDgt(gen))
	//			s += ltr(gen);
	//		else
	//			s += dgt(gen);
	//	}
	//	if (sTbl.n < Nmax && sTbl.n)
	//	{
	//		int b = 0, e = sTbl.n - 1, c = 0;
	//		bool isFound = false;
	//		while (b <= e && !isFound)
	//		{
	//			c = (b + e) / 2;
	//			if (sTbl.elem[c].key > s)
	//				e = c - 1;
	//			else
	//				if (sTbl.elem[c].key < s)
	//					b = c + 1;
	//				else
	//				{
	//					sTbl.elem[c].amt += amt(gen);
	//					isFound = true;
	//				}
	//		}
	//		if (sTbl.elem[c].key > s)
	//		{
	//			for (int a = sTbl.n; a > c; a--)
	//				sTbl.elem[a] = sTbl.elem[a - 1];
	//		}
	//		else
	//		{
	//			for (int a = sTbl.n; a > c + 1; a--)
	//				sTbl.elem[a] = sTbl.elem[a - 1];
	//			c++;
	//		}
	//		sTbl.elem[c] = { s, A[nm(gen)],amt(gen), val(gen) };
	//		sTbl.n++;
	//	}
	//	else
	//		if (!sTbl.n)
	//		{
	//			sTbl.elem[i] = { s, A[nm(gen)],amt(gen), val(gen) };
	//			sTbl.n++;
	//		}
	}

	cout << "Generation is completed.";
}
