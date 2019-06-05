#include <iostream>
#include "table.h"

enum Commands
{
	CMD_QCK_LIB= 1,
	CMD_QCK,
	CMD_HEAP,
	CMD_SHL
};

int main()
{
	wTable work("work");
	sTable stock("Stock");
	priceList price_list("price-list");
	counts cnt = counts();
	bool inv = false;
	for (size_t i = 1; i < work.n && !inv; i++)
		inv = work.elem[i].key < work.elem[i - 1].key;
	if (inv)
	{
		cout << "1 Quick sort from Standard C Library\n"
			<< "2 Quick sort"
			<< "3 Heap sord\n"
			<< "4 Shellsort\n"
			<< "5 Exit\n"
			<< "Enter a kind of sort:";
		int n;
		cin >> n;
		switch (n)
		{
		case CMD_QCK_LIB: qsort(&work, work.n, sizeof(wProduct), compare);
			break;
		case CMD_QCK: QuickSort(work, 0, work.n - 1, cnt);
			break;
		case CMD_HEAP: HeapSort(work, cnt);
			break;
		case CMD_SHL: ShellSort(work, cnt);
			break;
		default:
			break;
		}
	}
	else
		cout << "Table 'Work' is already ordered\n";
	cout << "Views: " << cnt.views << endl
		<< "Compares: " << cnt.cmp << endl
		<< "Moves: " << cnt.mov << endl;
	printWork(work, "OrderedTable");
	Unite(stock, work, price_list);
	printStock(stock, "Result");
	system("PAUSE");
	return 0;
}