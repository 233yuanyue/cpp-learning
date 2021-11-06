#include<iostream>	
#include"BalancedBinaryTree.hpp"
using namespace std;

//Balanced Binary Tree(AVL树)：BF不超过1的二叉树
/*相关名词：Balance Factor(平衡因子):左右子树的高度差
BF(T)=hl-hr*/

void demo1()
{
	AVLTree<int> tree;
	for (int i = 0; i < 50; ++i) {
		tree.insert(i * 2 + 1);
		tree.insert((49 - i) * 2);
	}
	tree.layer_show();
	tree.showInfo();
	cout << "depth=" << tree.depth() << endl;

	for (int i = 0; i < 50; ++i) {
		tree.remove(i * 2 + 1);
		tree.remove((49 - i) * 2);
	}
}

void demo2()
{
	AVLTree<int> tree;
	for (int i = 0; i < 4000; ++i) {
		tree.insert(i);
	}
	tree.showInfo();
	cout << "======================================================" << endl;
	tree.layer_show();
	cout << "depth=" << tree.depth() << endl;
	for (int i = 3999; i >= 0; --i) {
		tree.remove(i);
	}
}

void test()
{
	AVLTree<int> t;
	t.remove(1);

	t.insert(7);
	t.insert(8);
	t.insert(9);
	t.insert(20);
	t.insert(11);
	t.insert(3);
	t.insert(15);
	t.insert(100);
	t.insert(66);
	t.insert(4);
	t.insert(33);
	t.insert(44);
	t.insert(10);
	t.insert(77);
	t.insert(88);
	t.insert(17);
	t.insert(23);
	t.insert(1);
	t.insert(122);
	t.insert(133);
	t.insert(0);
	t.showInfo();
	t.layer_show();
	cout << "depth=" << t.depth() << endl;
	t.remove(77);
	t.remove(7);
	t.remove(8);
	t.remove(133);
	t.remove(0);
	t.remove(3);
	t.remove(15);
	t.remove(77);
	t.remove(20);
	t.remove(44);
	t.remove(33);
	t.remove(122);
	t.remove(23);
	t.remove(88);
	t.remove(100);
	t.remove(10);
	t.remove(15);
	t.remove(17);
	t.remove(66);
	cout << "depth=" << t.depth() << endl;
	t.showInfo();
	t.layer_show();
	t.insert(133);
	auto f = t.is_exist(8);
	if (f!=nullptr) {
		cout << "存在元素："<<f->tree_data << endl;
	}

	t.showInfo();
	
	auto a = t.findMax();
	if (a != nullptr) {
		cout << "Max=" << a->tree_data << endl;
	}
	t.clear();
}

int main()
{
	//demo1();
	//demo2();
	//test();
	
	system("pause");
	return 0;
}