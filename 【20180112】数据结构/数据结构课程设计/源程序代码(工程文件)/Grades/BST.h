#ifndef BST_H
#define BST_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class BSTNode
{
public:
    BSTNode();
    BSTNode(int val);
    int value;
    int number;
    BSTNode *lchild;
    BSTNode *rchild;
};

class BST
{
    //为了数据结构私有化，不为外部访问，这里提供一些私有内部函数实现真正的操作以"__"开头。
    //对于public的接口来说，只需要直接调用内部函数即可
private:
    BSTNode * bstroot;//二叉排序树数据结构
    BSTNode * __search(BSTNode* root,const int& key);//查找关键字
    BSTNode * __treeMin(BSTNode*const root,BSTNode *&parent);//返回当前节点的最小孩子（一路向左）
    BSTNode * __treeMax(BSTNode*const root);//查找最大值（未实现）
    bool __Insert( const int &key);//插入节点
    bool __Delete(const int &key);//删除删除
    bool __isLeaf(BSTNode* const &);//判断是否是叶子节点
    bool __isNodeWithTwoChild(BSTNode * const &);//判断是否有两个孩子
    void __InorderTraversal(BSTNode *root,std::vector<int>&result,std::vector<int>&Num);//中序遍历
    void __DeleteAllNodes(BSTNode *root);//删除所有节点
public:
    //构造函数
    BST();//默认构造函数
    BST(std::vector<int>arr);
    BST(int *arr, int len);
    //析构函数
    ~BST();
    bool isEmpty() const;//判断树空
    bool search(const int &key);//查找关键字是否存在的对外接口
    bool Insert(const int &key);//插入节点的外部接口
    bool Delete(const int &key);//删除节点的外部接口
    void InorderTraversal(std::vector<int>&,std::vector<int>&Num);//中序遍历的外部接口
};

#endif // BST_H
