#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <string>
#define SIZE 10010
using namespace std;

typedef struct Node {
	int value;
	int cursor;
} StaticLinkedList, List[SIZE];


void init(StaticLinkedList *list)
{
	for (int i = 0; i < SIZE - 1; i++)
		list[i].cursor = i + 1;
	list[SIZE - 1].cursor = 0;  // Head node.
}

int alloc(StaticLinkedList *list)
{
	int cntPt = list[0].cursor;
	if (cntPt > 0)
		list[0].cursor = list[cntPt].cursor;  // cntPt == 0 means the list is full.
	return cntPt;
}

void free(StaticLinkedList *list, int pt)
{
	list[pt].cursor = list[0].cursor;
	list[0].cursor = pt;  // Mark it as free.
}

bool isLast(StaticLinkedList *list, int pt)
{
	return list[pt].cursor == 0;
}

bool isEmpty(StaticLinkedList *list)
{
	return list[SIZE - 1].cursor == 0;
}

int getLength(StaticLinkedList *list)
{
	int pt = SIZE - 1, length = 0;
	while (list[pt].cursor > 0)
	{
		length++;
		pt = list[pt].cursor;
	}
	return length;
}

int getPt(StaticLinkedList *list, int position)
{
	// Note that we should initialize pt = SIZE - 1 instead of pt = list[SIZE - 1].cursor.
	// Because for position 1, when getting its previous node it should be guided to SIZE - 1 instead of 0.
	int pt = SIZE - 1;
	for (int i = 1; i <= position; i++)
		pt = list[pt].cursor;
	return pt;
}

void insertNode(StaticLinkedList *list, int value, int position)
{
	int prevPt = getPt(list, position - 1);
	int nextPt = list[prevPt].cursor;
	int cntPt = alloc(list);

	list[cntPt].value = value;
	list[cntPt].cursor = nextPt;
	list[prevPt].cursor = cntPt;
}

void deleteNode(StaticLinkedList *list, int position)
{
	int prevPt = getPt(list, position - 1);
	int cntPt = list[prevPt].cursor;
	int nextPt = list[cntPt].cursor;

	list[prevPt].cursor = nextPt;
	free(list, cntPt);
}

void printList(StaticLinkedList *list)
{
	int pt = SIZE - 1;
	cout << "startPt: " << list[SIZE - 1].cursor << " nextPt: " << list[0].cursor << endl;
	while (list[pt].cursor > 0)
	{
		pt = list[pt].cursor;
		cout << "pt: " << pt << " value: " << list[pt].value << " cursor: "<< list[pt].cursor << endl;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	List arr;
	init(arr);
	string opr;
	while(cin >> opr)
	{
		if (opr == "INSERT")
		{
			int value, position;
			cin >> value >> position;
			insertNode(arr, value, position);
		}
		else if (opr == "DELETE")
		{
			int position;
			cin >> position;
			deleteNode(arr, position);
		}
		else if (opr == "LENGTH")
			cout << getLength(arr) << endl;
		else if (opr == "PRINT")
			printList(arr);
		else if (opr == "EXIT")
			break;
	}
	return 0;
}
