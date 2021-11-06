#pragma once
#include"Node.h"
#include<stack>
#include<queue>
using std::cout;
using std::endl;
using std::stack;//使用栈代替了部分递归函数，事实证明可以全部换成迭代或全部换成递归
using std::queue;//层序遍历
using std::pair;
using std::make_pair;
using treeDepth = unsigned int;

template<typename T>
class AVLTree 
{
public:
	AVLTree();
	~AVLTree();//使用智能指针可以提升安全性

	const TreeNode<T>* is_exist(T data)const;
	bool insert(const T data);
	const TreeNode<T>* findMax()const;
	const TreeNode<T>* findMin()const;
	bool is_empty()const;
	bool remove(T data);
	void clear();
	void showInfo()const;//中序遍历
	void layer_show()const;//层序遍历
	treeDepth depth()const;

private:
	TreeNode<T>* createNode(const T data)const;
	void setFNode(TreeNode<T> *fNode, TreeNode<T> *cNode, const TreeNode<T> *pEq);
	const TreeNode<T>* data_find(const TreeNode<T> *pFind, bool max = N_MAX)const;
	TreeNode<T>* data_delete(stack<TreeNode<T>*> &sta, TreeNode<T> *pFind, T &data);
	void clear(TreeNode<T> *pNode);
	void data_show(const TreeNode<T> *pNode)const;
	TreeNode<T>* balanceRoot(TreeNode<T> *cNode);
	void insertBalance(stack<TreeNode<T>*> &sta, const T data);
	void removeBanlance(stack<TreeNode<T>*> &sta, T data);
	const treeDepth getDepth(const TreeNode<T> *header)const;
	TreeNode<T>* RR_Rotate(TreeNode<T> *cNode);
	TreeNode<T>* LR_Rotate(TreeNode<T> *cNode);
	TreeNode<T>* RL_Rotate(TreeNode<T> *cNode);
	TreeNode<T>* LL_Rotate(TreeNode<T> *cNode);
	static constexpr int LH = 1;
	static constexpr int EH = 0;
	static constexpr int RH = -1;
	static constexpr bool N_MAX = true;
	static constexpr bool N_MIN = false;
	TreeNode<T> *m_root;
};

template<typename T>
constexpr int AVLTree<T>::LH;

template<typename T>
constexpr int AVLTree<T>::EH;

template<typename T>
constexpr int AVLTree<T>::RH;

template<typename T>
constexpr bool AVLTree<T>::N_MAX;

template<typename T>
constexpr bool AVLTree<T>::N_MIN;

template<typename T>
AVLTree<T>::AVLTree()
{
	this->m_root = nullptr;
}

template<typename T>
const TreeNode<T>* AVLTree<T>::is_exist(T data)const
{
	TreeNode<T> *pTemp = this->m_root;

	if (pTemp!=nullptr) {
		while (pTemp != nullptr) {
			if (pTemp->tree_data > data) {
				pTemp = pTemp->lTree;
			}
			else if(pTemp->tree_data < data){
				pTemp = pTemp->rTree;
			}
			else {
				break;
			}
		}
	}
	return pTemp;
}

template<typename T>
inline TreeNode<T>* AVLTree<T>::createNode(const T data)const
{
	TreeNode<T> *newNode = new TreeNode<T>;
	newNode->tree_data = data;
	newNode->lTree = nullptr;
	newNode->rTree = nullptr;
	newNode->balance_factor = EH;
	return newNode;
}

template<typename T>
bool AVLTree<T>::insert(const T data)
{
	TreeNode<T> *tree_new = this->createNode(data);
	if (!this->m_root) {
		this->m_root = tree_new;
		return true;
	}
	else {
		TreeNode<T> *pTemp = this->m_root;
		stack<TreeNode<T>*> nodeSta;
		while (pTemp) {
			nodeSta.push(pTemp);
			if (pTemp->tree_data > data) {
				if (pTemp->lTree) {
					pTemp = pTemp->lTree;
				}
				else {
					pTemp->lTree = tree_new;
					this->insertBalance(nodeSta, data);
					return true;
				}
			}
			else if (pTemp->tree_data < data) {
				if (pTemp->rTree) {
					pTemp = pTemp->rTree;
				}
				else {
					pTemp->rTree = tree_new;
					this->insertBalance(nodeSta, data);
					return true;
				}
			}
			else {
				delete tree_new;
				tree_new = nullptr;
				return false;
			}
		}
	}
	return false;
}

template<typename T>
inline void  AVLTree<T>::setFNode(TreeNode<T> *fNode, TreeNode<T> *cNode, const TreeNode<T> *pEq)
{
	if (fNode->lTree == pEq) {
		fNode->lTree = cNode;
	}
	else {
		fNode->rTree = cNode;
	}
}

template<typename T>
const TreeNode<T>* AVLTree<T>::data_find(const TreeNode<T> *pFind,bool max)const
{
	if (pFind) {
		if (max == N_MAX) {
			while (pFind->rTree) {
				pFind = pFind->rTree;
			}
		}
		else {
			while (pFind->lTree) {
				pFind = pFind->lTree;
			}
		}
	}
	return pFind;
}

template<typename T>
const TreeNode<T>* AVLTree<T>::findMax()const
{
	return this->data_find(this->m_root, N_MAX);
}

template<typename T>
const TreeNode<T>* AVLTree<T>::findMin()const
{
	return this->data_find(this->m_root, N_MIN);
}

template<typename T>
bool AVLTree<T>::is_empty()const
{
	return this->m_root==nullptr ? true : false;
}

template<typename T>
TreeNode<T>* AVLTree<T>::data_delete(stack<TreeNode<T>*> &sta, TreeNode<T> *pFind, T &data)
{
	if (pFind->lTree) {
		TreeNode<T> *pMax = pFind->lTree;
		sta.push(pFind);
		while (pMax->rTree) {
			sta.push(pMax);
			pMax = pMax->rTree;
		}
		TreeNode<T> *fNode = sta.top();
		pFind->tree_data = pMax->tree_data;

		if (fNode->lTree == pMax) {
			fNode->lTree = pMax->lTree;
			data = pMax->tree_data - 1;//非常重要的条件，当T无法作算数运算时报错
		}
		else {
			fNode->rTree = pMax->lTree;
			data = pMax->tree_data + 1;//非常重要的条件，当T无法作算数运算时报错
		}
		delete pMax;
		pMax = nullptr;
	}
	else if (!pFind->lTree && !pFind->rTree) {
		delete pFind;
		pFind = nullptr;
	}
	else{
		TreeNode<T> *pMin = pFind->rTree;
		sta.push(pFind);
		while (pMin->lTree) {
			sta.push(pMin);
			pMin = pMin->lTree;
		}
		TreeNode<T> *fNode = sta.top();
		pFind->tree_data = pMin->tree_data;

		if (fNode->lTree == pMin) {
			fNode->lTree = pMin->rTree;
			data = pMin->tree_data - 1;
		}
		else {
			fNode->rTree = pMin->rTree;
			data = pMin->tree_data + 1;
		}
		delete pMin;
		pMin = nullptr;
	}
	return pFind;
}

template<typename T>
bool AVLTree<T>::remove(T data)
{
	int m_data = data;
	TreeNode<T> *pFind = this->m_root;
	stack<TreeNode<T>*> sta;
	while (pFind) {
		if (pFind->tree_data > data) {
			sta.push(pFind);
			pFind = pFind->lTree;
		}
		else if (pFind->tree_data < data) {
			sta.push(pFind);
			pFind = pFind->rTree;
		}
		else {
			if (!sta.empty()) {
				TreeNode<T> *fNode = sta.top();
				TreeNode<T> *ret = this->data_delete(sta, pFind, data);
				this->setFNode(fNode, ret, pFind);
			}
			else {
				this->m_root = this->data_delete(sta, pFind, data);
			}
			this->removeBanlance(sta, data);
			return true;
		}
	}
	return false;
}

template<typename T>
void AVLTree<T>::data_show(const TreeNode<T> *pNode)const
{
	if (pNode) {
		data_show(pNode->lTree);
		cout << pNode->tree_data << " ";
		data_show(pNode->rTree);
	}
}

template<typename T>
void AVLTree<T>::showInfo()const
{
	if (this->m_root != nullptr) {
		data_show(this->m_root);
		cout << endl;
	}
}

template<typename T>
void AVLTree<T>::layer_show()const
{
	if (this->m_root != nullptr) {
		queue<const TreeNode<T>*> que;
		que.push(this->m_root);
		while (!que.empty()) {
			const TreeNode<T> *pTemp = que.front();
			if (pTemp->lTree != nullptr) {
				que.push(pTemp->lTree);
			}

			if (pTemp->rTree != nullptr) {
				que.push(pTemp->rTree);
			}
			cout << pTemp->tree_data << " ";
			que.pop();
		}
		cout << endl;
	}
}

template<typename T>
TreeNode<T>* AVLTree<T>::balanceRoot(TreeNode<T> *cNode)
{
	if (cNode->balance_factor == LH) {
		if (cNode->lTree->balance_factor == LH) {
			return this->RR_Rotate(cNode);
		}
		else {
			return this->RL_Rotate(cNode);
		}
	}
	else if (cNode->balance_factor == RH) {
		if (cNode->rTree->balance_factor == LH) {
			return this->LR_Rotate(cNode);
		}
		else {
			return this->LL_Rotate(cNode);
		}
	}
	return cNode;
}

template<typename T>
void AVLTree<T>::insertBalance(stack<TreeNode<T>*> &sta, const T data)
{
	while (!sta.empty()) {
		TreeNode<T> *pTemp = sta.top();
		sta.pop();
		TreeNode<T> *fNode = nullptr;
		if (pTemp->tree_data > data) {
			switch (pTemp->balance_factor) {
			case LH:
			{
				if (!sta.empty()) {
					fNode = sta.top();
					this->setFNode(fNode, this->balanceRoot(pTemp), pTemp);
				}
				else {
					this->m_root = this->balanceRoot(pTemp);
				}
				return;
			}
			case EH:
				pTemp->balance_factor = LH;
				break;
			case RH:
				pTemp->balance_factor = EH;
				return;
			}
		}
		else {
			switch (pTemp->balance_factor) {
			case RH:
			{
				if (!sta.empty()) {
					fNode = sta.top();
					this->setFNode(fNode, this->balanceRoot(pTemp), pTemp);
				}
				else {
					this->m_root = this->balanceRoot(pTemp);
				}
				return;
			}
			case EH:
				pTemp->balance_factor = RH;
				break;
			case LH:
				pTemp->balance_factor = EH;
				return;//超重要的退出条件
			}
		}
	}
}


template<typename T>
void AVLTree<T>::removeBanlance(stack<TreeNode<T>*> &sta, T data)
{
	while (!sta.empty()) {
		TreeNode<T> *pTemp = sta.top();
		sta.pop();
		TreeNode<T> *fNode = nullptr;
		if (pTemp->tree_data > data) {
			switch (pTemp->balance_factor)
			{
			case RH:
			{
				if (!sta.empty()) {
					fNode = sta.top();
					switch (pTemp->rTree->balance_factor)
					{
					case LH:
						this->setFNode(fNode, this->LR_Rotate(pTemp), pTemp);
						break;
					case RH:
						this->setFNode(fNode, this->LL_Rotate(pTemp), pTemp);
						break;
					case EH:
						this->setFNode(fNode, this->LL_Rotate(pTemp), pTemp);
						return;
					}
				}
				else {
					switch (pTemp->rTree->balance_factor)
					{
					case LH:
						this->m_root = this->LR_Rotate(pTemp);
						break;
					case RH:
						this->m_root = this->LL_Rotate(pTemp);
						break;
					case EH:
						this->m_root = this->LL_Rotate(pTemp);
						return;
					}
				}
				break;
			}
			case LH:
				pTemp->balance_factor = EH;
				break;
			case EH:
				pTemp->balance_factor = RH;
				return;
			}
		}
		else {
			switch (pTemp->balance_factor)
			{
			case LH:
			{
				if (!sta.empty()) {
					fNode = sta.top();
					switch (pTemp->lTree->balance_factor)
					{
					case LH:
						this->setFNode(fNode, this->RR_Rotate(pTemp), pTemp);
						break;
					case RH:
						this->setFNode(fNode, this->RL_Rotate(pTemp), pTemp);
						break;
					case EH:
						this->setFNode(fNode, this->RR_Rotate(pTemp), pTemp);
						return;
					}
				}
				else {
					switch (pTemp->lTree->balance_factor)
					{
					case LH:
						this->m_root = this->RR_Rotate(pTemp);
						break;
					case RH:
						this->m_root = this->RL_Rotate(pTemp);
						break;
					case EH:
						this->m_root = this->RR_Rotate(pTemp);
						return;
					}
				}
			}
			case RH:
				pTemp->balance_factor = EH;
				break;
			case EH:
				pTemp->balance_factor = LH;
				return;
			}
		}
		data = pTemp->tree_data;
	}
}


template<typename T>
const treeDepth AVLTree<T>::getDepth(const TreeNode<T> *header)const
{
	treeDepth depth = 0;
	if (header) {
		stack < pair<const treeDepth, const TreeNode<T>*>> sta;
		sta.push(make_pair(depth + 1, header));
		while (!sta.empty()) {
			pair<const treeDepth, const TreeNode<T>*> pTemp = sta.top();
			sta.pop();
			if (depth < pTemp.first) {
				depth = pTemp.first;
			}

			if (pTemp.second->lTree) {
				sta.push(make_pair(pTemp.first + 1, pTemp.second->lTree));
			}

			if (pTemp.second->rTree) {
				sta.push(make_pair(pTemp.first + 1, pTemp.second->rTree));
			}
		}
	}
	return depth;

	/*if (header) {
		treeDepth lv1 = this->getDepth(header->lTree);
		treeDepth lv2 = this->getDepth(header->rTree);
		return ((lv1 > lv2) ? (lv1 + 1) : (lv2 + 1));
	}
	else {
		return 0;
	}*/
}

template<typename T>
treeDepth AVLTree<T>::depth()const
{
	return this->getDepth(this->m_root);
}

//template<typename T>
//TreeNode<T>*  AVLTree<T>::setBF(TreeNode<T> *rNode)
//{
//	/*插入的时候不用修正，删除的时候会出现旋转后根节点仍然为LH或RH的情况，使用该函数处理删除会比较慢，getDepth会比较耗时*/
//	int dif = this->getDepth(rNode->lTree) - this->getDepth(rNode->rTree);
//	if (dif == LH) {
//		rNode->balance_factor = LH;
//	}
//	else if (dif == RH) {
//		rNode->balance_factor = RH;
//	}
//	else {
//		rNode->balance_factor = EH;
//	}
//	return rNode;
//}

template<typename T>
TreeNode<T>* AVLTree<T>::RR_Rotate(TreeNode<T> *cNode)
{
	TreeNode<T> *rc = cNode->lTree->rTree, *temp = cNode->lTree;
	cNode->lTree = rc;
	//temp->balance_factor = EH;删除时temp可能不平衡,同时应先平衡左右子树;
	/*if (INSERT) {
		temp->rTree = this->setBF(cNode);
		return this->setBF(temp);
	}*/

	if (temp->balance_factor == EH) {
		temp->balance_factor = RH;
		cNode->balance_factor = LH;
	}
	else {
		temp->balance_factor = EH;
		cNode->balance_factor = EH;
	}
	temp->rTree = cNode;
	return temp;
}

template<typename T>
TreeNode<T>* AVLTree<T>::LR_Rotate(TreeNode<T> *cNode)
{
	TreeNode<T> *temp = cNode->rTree->lTree;
	TreeNode<T> *lc = temp->lTree, *rc = temp->rTree;
	cNode->rTree->lTree = rc;
	TreeNode<T> *fTemp = cNode->rTree;
	cNode->rTree = lc;
	/*if (INSERT) {
		temp->rTree = this->setBF(fTemp);
		temp->lTree = this->setBF(cNode);
		return this->setBF(temp);
	}*/

	if (temp->balance_factor == EH) {
		cNode->balance_factor = EH;
		fTemp->balance_factor = EH;
		temp->balance_factor = EH;
	}
	else if (temp->balance_factor == LH) {
		cNode->balance_factor = EH;
		fTemp->balance_factor = RH;
		temp->balance_factor = EH;
	}
	else {
		cNode->balance_factor = LH;
		fTemp->balance_factor = EH;
		temp->balance_factor = EH;
	}
	temp->rTree = fTemp;
	temp->lTree = cNode;
	return temp;
}

template<typename T>
TreeNode<T>* AVLTree<T>::RL_Rotate(TreeNode<T> *cNode)
{
	TreeNode<T> *temp = cNode->lTree->rTree;
	TreeNode<T> *lc = temp->lTree, *rc = temp->rTree;
	cNode->lTree->rTree = lc;
	TreeNode<T> *fTemp = cNode->lTree;
	cNode->lTree = rc;
	/*if (INSERT) {
		temp->lTree = this->setBF(fTemp);
		temp->rTree = this->setBF(cNode);
		return this->setBF(temp);
	}*/

	if (temp->balance_factor == EH) {
		temp->balance_factor = EH;
		fTemp->balance_factor = EH;
		cNode->balance_factor = EH;
	}
	else if (temp->balance_factor == LH) {
		fTemp->balance_factor = EH;
		cNode->balance_factor = RH;
		temp->balance_factor = EH;
	}
	else {
		fTemp->balance_factor = LH;
		cNode->balance_factor = EH;
		temp->balance_factor = EH;
	}
	temp->lTree = fTemp;
	temp->rTree = cNode;
	return temp;
}

template<typename T>
TreeNode<T>* AVLTree<T>::LL_Rotate(TreeNode<T> *cNode)
{
	TreeNode<T> *lc = cNode->rTree->lTree, *temp = cNode->rTree;
	cNode->rTree = lc;
	/*if (INSERT) {
		temp->lTree = this->setBF(cNode);
		return this->setBF(temp);
	}*/

	if (temp->balance_factor == EH) {
		temp->balance_factor = LH;
		cNode->balance_factor = RH;
	}
	else {
		temp->balance_factor = EH;
		cNode->balance_factor = EH;
	}
	temp->lTree = cNode;
	return temp;
}

template<typename T>
void AVLTree<T>::clear(TreeNode<T> *pNode)
{
	if (pNode) {
		this->clear(pNode->lTree);
		this->clear(pNode->rTree);
		delete pNode;
		pNode = nullptr;
		this->m_root = nullptr;
	}
}

template<typename T>
void AVLTree<T>::clear()
{
	TreeNode<T> *pTemp = this->m_root;
	this->clear(pTemp);
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	this->clear();
}