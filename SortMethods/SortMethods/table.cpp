#include <iostream> 
#include <random>
#include "table.h" 

double ValueSearch(const priceList &t, const string &code, int &c)
{
	int i = c, j = t.n - 1;                        			// i – начало области поиска, j - конец
	while (i <= j)
	{
		c = (i + j) / 2;                        				// с – центр области поиска
		if (code < t.elem[c].key)                     			// если центр > искомого ключа
			j = c - 1;                           				// с-1 становится концом области поиска
		else
			if (code > t.elem[c].key)                  			// если центр < искомого ключа
				i = c + 1;                        				// с+1 становится началом области поиска
			else
				return (t.elem[c].value);                  		// иначе элемент найден
	}
	return -1;
}

//void Unite(sTable &dest, wTable &from, const priceList &p)
//{
//	int n = 0, c = 0;									// n – индекс начала в поиске цены, с - 
//	double v;										// индекс начала в поиске места,v - цена
//	bool NotAll = false, isFound = false;					// NotAll – включены ли все из Work в St
//	for (int k = 0; k != from.n; k++)						// Пока не просмотрены все из Work
//	{
//		isFound = false;
//		int i = c, j = dest.n - 1;
//		while (i <= j && !isFound)							// Поиск места в Stock бинарным поиском
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
//		if (dest.n != Nmax && !isFound)						// Если таблица не полна и элемент не
//		{											// не найден
//			v = ValueSearch(p, from.elem[k].key, n);			// Поиск цены в прейскуранте
//			if (dest.elem[c].key > from.elem[k].key)			// Если ключ вставляемого эл. < ключ эл.
//			{											// на подходящей позиции, то
//				for (int a = dest.n; a > c; a--)				// сдвиг хвоста таблицы включая эл. с 
//					dest.elem[a] = dest.elem[a - 1];				// индексом с на 1 вправо
//			}
//			else
//			{
//				for (int a = dest.n; a > c + 1; a--)				// иначе также сдвиг но до эл.с индексом
//					dest.elem[a] = dest.elem[a - 1];				// с + 1 на 1 вправо
//				c++;										// увеличим индекс для вставки на 1
//			}
//			dest.elem[c] = { from.elem[k].key , from.elem[k].name, from.elem[k].amt, v };
//			dest.n++;									// Вставим элемент и увеличим факт.
//		}											// размер на 1
//		else
//			if (dest.n == Nmax)							// Иначе если таблица Stock полна
//				NotAll = true;								// запоминаем что не все элементы из
//	}												// Work включены в Stock
//	if (NotAll)
//		cout << "Table 'Stock' is full! Not all products from 'Work' are included!";
//	else
//		cout << "All products from 'Work' are included to 'Stock'!";
//}

void QuickSort(wTable *t,int b, int e)	// b – индекс начала области сорти-
{													// ровки, е - конца									// Если область сортировки включает												// более чем 1 элемент
		int m = (b + e) / 2;									// m – делящий элемент
		wProduct *prd;
		int i = b, j = e;									// i – индекс элемента слева от m
		while (i <= j)										// j – справа, пока они не перешли
		{												// друг друга
			for (i = b; _stricmp(t->elem[i]->key.c_str(), t->elem[m]->key.c_str()) < 0; i++);
			//while (_stricmp(t->elem[i]->key.c_str(), t->elem[m]->key.c_str()) < 0)
				//i++;
			for (j = e; _stricmp(t->elem[j]->key.c_str(), t->elem[m]->key.c_str()) > 0; j--);
			//while (_stricmp(t->elem[j]->key.c_str(), t->elem[m]->key.c_str()) > 0)
				//j--;
			if (i <= j)										// Если i не правее чем j
			{
				prd = t->elem[i];								// то поменять их местами
				t->elem[i] = t->elem[j];
				t->elem[j] = prd;
				i++;											// и продолжить поиск
				j--;
			}
		}												// если область слева включает
		if (b < j) QuickSort(t, b, j);						// более 1 эл. то вызов с концом j
		if (e > i) QuickSort(t, i, e);						// аналогично если -/- то вызов										// с началом в i
}

void Pyramid(wTable &t, counts &cnt, const int &i, const int &size)
{
	int child, j = i;										// Child индекс потомка, i -  
	wProduct *prd = t.elem[i];								// индекс сорт. эл.
	bool inv = true;
	while (j <= size / 2 - 1 && inv)							// Пока у j есть соседи и инверсия
	{
		child = 2 * j + 1;									// Вычисляем индекс потомка
		if (child + 1 < size && t.elem[child]->key < t.elem[child + 1]->key)
			child++;										// Выбираем max из потомков
		cnt.cmp++;
		if (prd->key < t.elem[child]->key)						// Если потомок больше предка
		{
			t.elem[j] = t.elem[child];							// Ставим предка на место потомка
			j = child;
			++cnt.mov;
		}
		else
			inv = false;										// Иначе отметим что инверсии нет
		++cnt.cmp;
	}
	t.elem[j] = prd;										// Ставим сортируемый эл. на 
	cnt.mov += 2;											// свое место
}

void HeapSort(wTable &t, counts &cnt)
{
	wProduct *prd;
	for (int i = t.n / 2 - 1; i >= 0; i--)				// Построение пирамиды, начиная с последнего 
		Pyramid(t, cnt, i, t.n);						// элемента с потомками, заканчивая корнем
	++cnt.views;
	for (int i = t.n - 1; i > 0; i--, ++cnt.views)
	{
		prd = t.elem[0];							// Меняем значения корня дерева и последнего
		t.elem[0] = t.elem[i];						// элемента массива, и забываем о посл.
		t.elem[i] = prd;							// элементе
		cnt.mov += 3;
		Pyramid(t, cnt, 0, i);						// восстанавливаем таблицу без забытого
	}											// элемента и восстанавливаем пирамиду,
}											// просеивая корневое значение через нее

void ShellSort(wTable &t, counts &cnt)
{
	/*static const int step[] = { 1,4,10,23,57,132,301,701,1750 };*/	// Данная последовательность описа-
	wProduct *temp;										// на в статье М. Циуры 2001г.
	int k;												// k – индекс включаемого элемента
	size_t h = 1;											// h – длина h-серии
	for (h = 1; h <= t.n / 9; h = 2 * h + 1);					// находим подходящую длину для 
	/*for (num = 0; step[num + 1] < t.n - 1; num++);*/				// h - серии
	for (; h > 0; h = (h - 1) / 2, cnt.views++)					// просматриваем пока h > 0
		for (size_t j = h; j < t.n; j++)						// рассматирмваем каждый эл.
		{												// начиная с h-того
			temp = t.elem[j];									// Проводим операцию прямого
			for (k = j - h; k >= 0 && temp->key < t.elem[k]->key; k -= h,	// включения для каждого j
				cnt.cmp++, cnt.mov++)
				t.elem[k + h] = t.elem[k];
			cnt.cmp++;
			t.elem[k + h] = temp;
			cnt.mov += 2;
		}
}

int compare(const void *arg1, const void *arg2)
{
	wProduct *t1 = *(wProduct **)arg1;							// Инициализация t1 и t2, того же 
	wProduct *t2 = *(wProduct **)arg2;							// типа что и аргументы
	return _stricmp(t1->key.c_str(), t2->key.c_str());				// t1 больше чем t2, вернуть 1, 
}													// t1 = t2 – 0, иначе -1

//void printWork(const wTable &t, const string &s)
//{
//	ofstream out(s + ".txt");
//	out << "№\t" << "CIPHER\t\t" << "NAME\t" << "AMOUNT\n";
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
//	out << "№\t" << "CIPHER\t\t" << "NAME\t" << "AMOUNT\t" << "COST\n";
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

	for (int i = 0; wTbl.n < n && wTbl.n < Nmax; i++)    	// Генерация Work и Price-list
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
	//	if (pl.n < Nmax && pl.n)						// Генерируем и упоряд. бинарными включениям
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

	//for (int i = 0; sTbl.n < n && sTbl.n <= Nmax; i++)		// Генерация Stock
	//{										  	// Аналогично Wotk и Price-list
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
