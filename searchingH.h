#pragma once
/*测试记录元素顺序列表格式*/
struct records {
	records() {};
	records(char c, int n) :num(n), keyc(c) {};
	int num;
	char keyc;
};

typedef records LinearList[];
/*链表元素*/
struct celltype {
	records data;
	celltype* next;
};
typedef celltype* LinkedList;//LinkedList必须是指针
/*二叉查找树元素*/
struct treenode {
	records data;
	treenode* lchild, * rchild;
};
typedef treenode* BST;
/*AVL树结点*/
struct avlnode {
	/*初始化h为1、bf为0，很重要，在后续程序中认为空指针高度为0*/
	avlnode(records d) :
		data(d), h(1), bf(0), rchild(nullptr), lchild(nullptr) {};
	records data;
	int h;/*height*/
	int bf;/*balance factor*/
	avlnode* rchild, * lchild;
};
typedef avlnode* avlTree;
