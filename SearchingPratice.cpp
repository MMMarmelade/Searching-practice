//main programm

#include "searchingH.h"
#include "SearchClass.h"
#include <iostream>
using namespace std;

const int maxsize = 10;
char List_c[maxsize] = { 'a','c','e','g','i','k','m','o','q','r' };
struct records List[maxsize];
char index[3] = { 'c','f','i' };//顺序表有a~i共9个元素，分块时分3组，每组3个

/******************
*顺序列表测试
********************/
void test1() {
	/*****创建一个临时顺序表，第0位为空*****/
	List[0].num = 0;
	List[0].keyc = NULL;
	for (int i = 1;i != maxsize;i++) {
		List[i].num = i;
		List[i].keyc = List_c[i - 1];//disorder
	}
	//std::cout << List[8].num << List[8].keyc << std::endl;
	SearchClass LS;// = new LinearSearch;
	int result = LS.Search('v', maxsize - 1, List);
	std::cout << result << std::endl;
}

/***********************
*链表测试
************************/
void testLinkedList() {
	int i = 0;
	/****临时创建一个链表******/
	LinkedList linkedlist = new celltype;//必须初始化
	linkedlist->data.keyc= NULL;
	linkedlist->data.num = NULL;
	linkedlist->next = NULL;//链头初始化
	while (i != maxsize) {
		LinkedList tempcell = new celltype;//必须初始化
		tempcell->data.keyc = List_c[i];
		tempcell->data.num = i + 1;
		tempcell->next = linkedlist->next;
		linkedlist->next = tempcell;
		i++;
	}
	SearchClass LS;
	LinkedList result = LS.LinkedSearch('v', linkedlist);
	if (result)
		cout << result->data.keyc << result->data.num << endl;
	else
		cout << "no result" << endl;
}

void binaryTest() {
	/*****创建一个临时顺序表，第0位为空*****/
	List[0].num = 0;
	List[0].keyc = NULL;
	for (int i = 1;i != maxsize;i++) {
		List[i].num = i;
		List[i].keyc = List_c[i - 1];//disorder
	}
	SearchClass LS;// = new LinearSearch;
	int result = LS.BinarySearch('i', maxsize - 1, List);
	std::cout << result << std::endl;
}

void linearblockTest() {
	/*****创建一个临时顺序表，第0位为空*****/
	List[0].num = 0;
	List[0].keyc = NULL;
	for (int i = 1;i != maxsize;i++) {
		List[i].num = i;
		List[i].keyc = List_c[i - 1];//disorder
	}
	SearchClass LS;// = new LinearSearch;
	int result = LS.LinearBlockedSearch('j', maxsize - 1,3, index, List);
	std::cout << result << std::endl;
}

void linkedblockedTest() {
	/*****创建一个临时带索引的链表*****/
	LinkedList ll[3];
	for (int i = 0;i != 3;i++) {
		int cn = 3 * i + 2;
		ll[i] = new celltype;
		ll[i]->data.keyc = List_c[cn];
		ll[i]->data.num = cn;
		ll[i]->next = NULL;
		for (int j = 1;j != 3;j++) {
			LinkedList childLL = new celltype;
			childLL->data.num = cn-j;
			childLL->data.keyc = List_c[cn - j];
			childLL->next = ll[i]->next;
			ll[i]->next = childLL;
		}
	}
	/**临时打印**/
	LinkedList templl = ll[0];
	while (templl) {
		cout << templl->data.keyc << templl->data.num << endl;
		templl = templl->next;
	}
	/**测试**/
	SearchClass LS;
	bool inResult = LS.linkedBlockedInsert('a',10,3,ll);
	bool deResult = LS.linkedBlockedDelete('b', 3, ll);
	cout << inResult << deResult << endl;
	LinkedList result = LS.linkedBlockedSearch('a',3, ll);
	if (result)
		cout << result->data.num << result->data.keyc << endl;
	else
		cout << "no result" << endl;
}

void bstTest() {
	/**建立一个二叉查找树F**/
	BST F = new treenode;
	F = NULL;//必须初始化为空
	char c[maxsize] = { 'i','e','m','c','g','k','r','a','o','q' };
	struct records R;
	SearchClass* sc = new SearchClass;
	for (int i = 0;i != maxsize;i++) {
		R.keyc = c[i];R.num = i;
		sc->bstInsert(R, F);
	}
	/**遍历F**/
	if (F)
		sc->InOrder(F);
	else
		cout << "F为空" << endl;
	/**删除一个元素**/
	sc->bstDelete('m', F);
	/**遍历F**/
	if (F)
		sc->InOrder(F);
	else
		cout << "F为空" << endl;

}


void avlTest() {
	/*constructe a testing avlTree*/
	avlTree T=NULL;
	AVLTree* at = new AVLTree();
	char c[maxsize] = { 'i','e','m','c','g','k','r','a','o','q' };
	struct records R;
	for (int i = 0;i != maxsize;i++) {
		R.keyc = c[i];R.num = i;
		at->avlInsert(T, R);
	}

	at->avlDelete(T, records('g',0));/*a record node to test avlDelete(), num is useless here*/
	at->avlDelete(T, records('a', 0));
	at->avlDelete(T, records('e', 0));

	/*print the avlTree*/
	at->avlTraversalPre(T);
	at->avlTraversalIn(T);
}

int main()
{
	/*测试函数*/
	avlTest();
}

