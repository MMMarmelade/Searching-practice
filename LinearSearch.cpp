#include "SearchClass.h"


SearchClass::SearchClass()
{
}


SearchClass::~SearchClass()
{
}

/*************
*顺序列表搜索函数
*寻找关键字为k的记录元素
*last为数组最后一个元素序号
*记录数组L
*找到则返回记录元素的序号
*没找到则返回0
***********************/
int SearchClass::Search(char k,int last,struct records L[]) {
	int i = last;
	L[0].keyc = k;//搜索终点哨兵
	while (L[i].keyc != k) {
		i--;
	}
	return i;
}
