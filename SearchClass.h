#pragma once
#include "searchingH.h"
#include <iostream>
#include <algorithm>
using namespace std;
class SearchClass
{
public:
	SearchClass();
	~SearchClass();
	/*函数定义在LinearSearch.cpp中*/
	int Search(char k, int last, struct records L[]);
	/*********************
	*在F所指的链表中搜索包含关键字k的元素记录，并返回其指针
	**********************/
	LinkedList LinkedSearch(char k, LinkedList F) {
		while (F != NULL) {
			if (F->data.keyc == k) {
				return F;
			}
			else
				F = F->next;
		}
		return F;
	}
	/******************
	*折半排序
	*搜索有序排序的顺序表
	************************/
	int BinarySearch(char k, int last, LinearList F) {
		int low, up, mid;
		low = 0;
		up = last;
		while (low <= up) {
			mid = (low + up) / 2;
			if (F[mid].keyc > k) {
				up = mid - 1;
			}
			else if (F[mid].keyc < k) {
				low = mid + 1;
			}
			else
				return F[mid].num;
		}
		return 0;
		
	}
	/********************
	*线性分块搜索
	*blockL为每块长度，index数组元素为每组最大
	*********************/
	int LinearBlockedSearch(char k, int last, int blockL, char index[], LinearList F) {
		int i, j;//i是索引序号，j是组内序号
		i = 0;
		j = 1;
		while (index[i] < k) {
			i++;
			if (i == last) {
				return 0;
			}
		}
		while (j < blockL+1) {
			if (F[i * blockL + j].keyc == k) {
				return F[i * blockL + j].num;
			}
			else
				j++;
		}
		return 0;
	}

	/********************
	*在带索引的分块链表中搜索元素k
	*blocks是分块数
	*找到则返回其指针
	*/
	LinkedList linkedBlockedSearch(char k,int blocks,LinkedList LL[]) {
		int i=0;//索引序号
		while (LL[i]->data.keyc < k) {
			i++;
			if (i == blocks)
				return NULL;
		}
		LinkedList F = LL[i];
		while (F) {
			if (F->data.keyc == k) {
				return F;
			}
			else
				F = F->next;
		}
		return NULL;
	}
	/********************************
	*往带索引的链表中插入k、n
	*********************************/
	bool linkedBlockedInsert(char k,int n,int blocks,LinkedList LL[]) {
		int i = 0;
		while (LL[i]->data.keyc < k) {
			i++;
			if (i == blocks)
				return 0;
		}
		LinkedList F = LL[i];
		while (F) {
			if (F->data.keyc == k) {
				return 0;//不插入相同元素
			}
			else
				F = F->next;
		}
		LinkedList tempL = new celltype;
		tempL->data.keyc = k;
		tempL->data.num = n;
		tempL->next = LL[i]->next;
		LL[i]->next = tempL;
		return 1;
	}
	/**********************************
	*删除带索引分块链表中的关键字为k的元素
	***********************************/
	bool linkedBlockedDelete(char k, int blocks, LinkedList LL[]) {
		int i = 0;//索引序号
		while (LL[i]->data.keyc < k) {
			i++;
			if (i == blocks)
				return 0;
		}
		LinkedList B = LL[i],F = LL[i];//B为上一个，F为当前
		while (F) {
			if (F->data.keyc == k) {
				if (B == F) {
					return 0;//不删索引
				}
				else {
					B->next = F->next;
					delete LL[i];//从内存中删除
					return 1;
				}
			}
			else {
				B = F;
				F = F->next;
			}
		}
		return 0;
	}

	/*****************************
	*在二叉查找树中搜索
	******************************/
	BST bstSearch(char k, BST F) {
		if (F == NULL) {
			return NULL;
		}
		else if (k == (*F).data.keyc) {
			return F;
		}
		else if (k > F->data.keyc) {
			bstSearch(k, F->rchild);
		}
		else
			bstSearch(k, F->lchild);
	}
	/*****************************
	*在二叉查找树F中插入记录为R的元素
	*参数&F，在需要地址可变的时候，要用引用，
	******************************/
	void bstInsert(records R, BST& F) {
		if (!F) {
			F = new treenode;/**创建对象时会被赋予新地址***/
			F->data = R;
			F->lchild = NULL;
			F->rchild = NULL;
		}
		else if (R.keyc < F->data.keyc)
			bstInsert(R, F->lchild);
		else if (R.keyc > F->data.keyc)
			bstInsert(R, F->rchild);
	}

	/*****************************
	*在二叉查找树中删除某子树中关键字最小的结点（删除结点有两个非空子树时，右子树中最左边的结点代替被删的结点）
	*返回该结点数据，删除该结点并让其子树继承（最小结点只可能有右子树）
	******************************/
	records bstDeleteMin(BST &F) {
		records tmp;
		BST P;
		if (!F->lchild) {
			P = F;
			tmp = F->data;
			F = F->rchild;/**若参数中F不带引用&，则函数运行后该地址并不会改变**/
			delete P;/**若参数中F不带引用&，上句地址不改变，则树中的一个结点被破坏，后续操作会报错**/
			return tmp;
		}
		else
			return bstDeleteMin(F->lchild);
	}
	/*************************
	*删除树中结点
	**************************/
	void bstDelete(char k, BST& F) {
		if (F) {
			if (k < F->data.keyc)
				bstDelete(k, F->lchild);
			else if (k > F->data.keyc)
				bstDelete(k, F->rchild);
			else if (F->lchild == NULL)
				F = F->rchild;
			else if (F->rchild == NULL)
				F = F->lchild;
			else
				F->data = bstDeleteMin(F->rchild);
		}
	}
	/*************************
	*先根遍历
	***************************/
	void PreOrder(BST F) {
		if (F) {
			std::cout << F->data.keyc << std::endl;
			PreOrder(F->lchild);
			PreOrder(F->rchild);
		}
	}
	/*************************
	*中根遍历
	*中序遍历二叉查找树能按关键字大小顺序遍历
	***************************/
	void InOrder(BST F) {
		if (F) {
			InOrder(F->lchild);
			std::cout << F->data.keyc << std::endl;
			InOrder(F->rchild);
		}
	}

	
};
/********************
avltree方法比较多，且不仅仅是插入删除函数，所以用一个新类包装
*********************/
class AVLTree {
public:
	/**************************
	往avl树T中插入记录R
	***************************/
	void setBf_H(avlTree& T) {
		int lh, rh;
		if (T->lchild)
			lh = T->lchild->h;
		else
			lh = 0;
		if (T->rchild)
			rh = T->rchild->h;
		else
			rh = 0;
		T->h = std::max(lh, rh) + 1;
		T->bf = lh - rh;
	}

	void avlInsert(avlTree& T, records R) {
		if (!T) 
			T = new avlnode(R);
		else if (R.keyc < T->data.keyc) {
			avlInsert(T->lchild, R);
			/*插入后返回时，实时更新h和bf*/
			/*获取左右子树高度，处理nullptr的情况*/
			setBf_H(T);
			if (T->bf > 1) {/*在左子树插入，只需检验左子树是否过高*/
				leftRotation(T);
			}
		}
		else if (R.keyc > T->data.keyc) {
			avlInsert(T->rchild, R);
			setBf_H(T);
			if (T->bf <-1) {/*在右子树插入，只需检验右子树是否过高*/
				rightRotation(T);
			}
		}
	}

	void leftRotation(avlTree& Root) {
		avlTree newRoot,bRoot;
		/*LL型*/
		if (Root->lchild->bf == 1) {
			newRoot = Root->lchild;
			/*旋转*/
			Root->lchild = newRoot->rchild;
			newRoot->rchild = Root;
			/*更新属性,考虑到平衡二叉树的性质，新根的高度不变*/
			Root->h = Root->h - 2;
			Root->bf = 0;
			newRoot->bf = 0;
			/*更新指针*/
			Root = newRoot;
		}
		else {/*LR型*/
			bRoot = Root->lchild;
			newRoot = bRoot->rchild;
			/*旋转*/
			bRoot->rchild = newRoot->lchild;
			Root->lchild = newRoot->rchild;
			newRoot->lchild = bRoot;
			newRoot->rchild = Root;
			/*更新属性，分三种情况newRoot的bf分别为1，0，-1*/
			switch (newRoot->bf) {
			case 1:
				Root->bf = -1;
				bRoot->bf = 0;
			case 0:
				Root->bf = bRoot->bf = 0;
			case -1:
				Root->bf = 0;
				bRoot->bf = 1;
			}
			Root->h -= 2;
			bRoot->h -= 1;
			newRoot->h += 1;
			newRoot->bf = 0;
			/*更新指针*/
			Root = newRoot;
		}
	}
	
	void rightRotation(avlTree& Root) {
		avlTree newRoot, bRoot;
		/*RR*/
		if (Root->rchild->bf == -1) {
			newRoot = Root->rchild;
			/*rotation*/
			Root->rchild = newRoot->lchild;
			newRoot->lchild = Root;
			/*update configurations:h and bf*/
			Root->h -= 2;
			Root->bf = 0;
			newRoot->bf = 0;
			/*update pointer*/
			Root = newRoot;
		}
		/*RL*/
		else {
			bRoot = Root->rchild;
			newRoot = bRoot->lchild;
			/*rotation*/
			Root->rchild = newRoot->lchild;
			bRoot->lchild = newRoot->rchild;
			newRoot->lchild = Root;
			newRoot->rchild = bRoot;
			/*update h & bf, given the bf of newRoot:1,0,-1*/
			switch (newRoot->bf) {
			case 1:
				Root->bf = 0;
				bRoot->bf = -1;
			case 0:
				Root->bf = bRoot->bf = 0;
			case -1:
				Root->bf = 1;
				bRoot->bf = 0;
			}
			newRoot->bf = 0;
			Root->h -= 2;
			bRoot->h -= 1;
			newRoot->h += 1;
			/*update pointer*/
			Root = newRoot;
		}
	}

	/**********************
	delete a record in a avlTree T
	***********************/
	void avlDelete(avlTree& T, records R) {
		if (T) {
			avlTree P;
			if (R.keyc == T->data.keyc) {
				if (!T->rchild) {
					P = T;
					T = T->lchild;
					delete P;
				}
				else if (!T->lchild) {
					P = T;
					T = T->rchild;
					delete P;
				}
				else
					T->data = avlDeleteMin(T);/*put the minium record of the right child-tree into the node*/
			}
			else if (R.keyc < T->data.keyc) {
				avlDelete(T->lchild, R);
				if (T) {
					setBf_H(T);/*update the bf&h*/
					/*re-balance*/
					/*come back form the left, means that left might become shorter*/
					if (T->bf < -1) {
						rightRotation(T);
						//cout <<"1"<< T->bf << "right_rotation" << endl;
					}
					//cout << "2" << T->bf << endl;
				}

			}
			else if (R.keyc > T->data.keyc) {
				avlDelete(T->rchild, R);
				if (T) {
					setBf_H(T);/*update the bf&h*/
					/*come back form the right, means that right might become shorter*/
					if (T->bf > 1) {
						leftRotation(T);
						//cout << "3" << T->bf << "left_rotation" << endl;
					}
					//cout << "4" << T->bf << endl;
				}
			}
		}
	}

	records avlDeleteMin(avlTree& T) {
		records trandata;
		avlTree P;
		if (!T->lchild) {
			trandata = T->data;/*get the record data*/
			T = T->rchild;/*rchild attaches to the parentnode*/
			P = T;
			delete P;
			return trandata;
		}
		else
			return avlDeleteMin(T->lchild);
	}

	/**********************
	search function is similar to the search-function of BST
	***********************/
	avlTree avlSearch(avlTree T, records R) {

	}

	/************************
	traversal functions
	*************************/
	void avlTraversalPre(avlTree T) {
		if (!T)
			return;
		else {
			cout << T->data.keyc << T->h << endl;
			avlTraversalPre(T->lchild);
			avlTraversalPre(T->rchild);
		}
	}
	void avlTraversalIn(avlTree T) {
		if (!T)
			return;
		else {
			avlTraversalIn(T->lchild);
			cout << T->data.keyc <<T->h<< endl;
			avlTraversalIn(T->rchild);
		}
	}
	void avlTraversalPost(avlTree T) {
		if (!T)
			return;
		else {
			avlTraversalPost(T->lchild);
			avlTraversalPost(T->rchild);
			cout << T->data.keyc << T->h << endl;
		}
	}
};
