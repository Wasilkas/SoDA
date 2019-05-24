#include <iostream>
#include "table.h"

enum Commands
{
	CMD_QCK = 1,
	CMD_HEAP,
	CMD_SHL
};

int main()
{
	table work = {};
	table store = {};
	priceList price_list = {};
	inputTable(work);
	inputPriceList(price_list);
	inputStoreList(store);
	counts cnt = counts();
	cout << "1 Quick sort\n"
		<< "2 Heap sord\n"
		<< "3 Shellsort\n"
		<< "4 Exit\n"
		<< "Enter a kind of sort:";
	int n;
	cin >> n;
	switch (n)
	{
	case CMD_QCK:
		QuickSort(work, 0, work.n - 1, cnt);
		cout << "Views: " << cnt.views << endl
			<< "Compares: " << cnt.cmp << endl
			<< "Moves: " << cnt.mov << endl;
		break;
	case CMD_HEAP:
		HeapSort(work, cnt);
		cout << "Views: " << cnt.views << endl
			<< "Compares: " << cnt.cmp << endl
			<< "Moves: " << cnt.mov << endl;
		break;
	case CMD_SHL:
		ShellSort(work, cnt);
		cout << "Views: " << cnt.views << endl
			<< "Compares: " << cnt.cmp << endl
			<< "Moves: " << cnt.mov << endl;
		break;
	default:
		break;
	}
	print(work, "OrderedTable");
	Unite(store, work, price_list);
	print(store, "STORE");
	system("PAUSE");
	return 0;
}