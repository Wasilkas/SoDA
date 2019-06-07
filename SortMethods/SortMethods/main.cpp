#include <iostream>
#include <ctime>
#include "table.h"

enum Commands
{
	CMD_QCK_LIB = 1,
	CMD_QCK,
	CMD_HEAP,
	CMD_SHL
};

int main()
{
	wTable work /*("work")*/;
	sTable stock/*("Stock")*/ = {};
	priceList price_list/*("price-list")*/ = {};
	counts cnt = counts();
	generator(work, price_list, stock);
	bool inv = false;
	for (size_t i = 1; i < work.n && !inv; i++)      // ≈сли таблица изначально упор€дочена по возр.,
		inv = work.elem[i]->key < work.elem[i - 1]->key;   // то нет смысла обращатьс€ к опци€м сортировки 
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
		double t = clock();
		switch (n)
		{
		case CMD_QCK_LIB: qsort((&work)->elem, work.n, sizeof(wProduct*), compare);
			break;
		case CMD_QCK: QuickSort(&work, 0, work.n - 1);
			break;
		case CMD_HEAP: HeapSort(work, cnt);
			break;
		case CMD_SHL: ShellSort(work, cnt);
			break;
		default:
			break;
		}
		t = (clock() - t) / CLOCKS_PER_SEC;
		cout << "time: " << t << endl;
	}
	else
		cout << "Table 'Work' is already ordered\n";
	cout << "Views: " << cnt.views << endl
		<< "Compares: " << cnt.cmp << endl
		<< "Moves: " << cnt.mov << endl;
	/*printWork(work, "OrderedTable");*/
	/*Unite(stock, work, price_list);*/
	/*printStock(stock, "Result");*/
	system("PAUSE");
	return 0;
}