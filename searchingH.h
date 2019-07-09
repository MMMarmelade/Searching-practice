#pragma once
/*测试记录元素顺序列表格式*/
struct records {
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
