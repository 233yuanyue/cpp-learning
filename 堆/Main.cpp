#include<iostream>
#include"Heap.hpp"
using namespace std;

/* 堆：一个完全二叉树
		特点：1、父结点的值大于等于(或小于等于）子结点的值
			  2、子结点的大小无明显要求

这里我们用数组实现堆，这也是常用的实现方法
设计要求：Heap<Ty,_Pr=less>
	1、Heap(int capacity)                          //创建一个容量为capacity的堆
	2、bool val_cmp(int i,int j)                   //比较i和j索引处值的大小
	3、void exch(int i,int j)                      //交换i和j索引处的值
	4、Ty pop()                                    //删除并返回堆中最大元素或最小元素(默认最大元素）
	6、int insert(Ty ty)                           //向堆中插入ty元素，并返回其索引，索引为-1时插入失败
	7、void swim(int k)                            //使用上浮算法，使k索引处元素在堆中处于正确位置
	8、void sink(int k)                            //使用下沉算法，使k索引处元素在堆中处于正确位置

最终用自建堆实现堆排序
*/

void test()
{
	initializer_list<int> lst{ 1,3,5,7,9,10,8,6,4,2 };
	Heap<int> heap(lst);

	for (int i = 0; i < 10; ++i) {
		cout << heap.pop() << " ";
	}
	cout << endl;

	Heap<int,less<int>> demo(16);
	for (int i = 21; i >=4; i -= 2) {
		demo.insert(i);
	}

	demo.insert(lst);
	for (int i = 0; i < 16; ++i) {
		cout << demo.pop() << " ";
	}
	cout << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}