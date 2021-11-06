#pragma once
#include<iostream>

template<typename T>
struct TreeNode {
	int balance_factor;
	TreeNode *rTree, *lTree;
	T tree_data;
};