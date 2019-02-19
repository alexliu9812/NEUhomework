#include"BST.h"

BSTNode::BSTNode()
{
    value = 0;
    lchild = NULL;
    rchild = NULL;
}

BSTNode::BSTNode(int val)
{
    value = val;
    lchild = NULL;
    rchild = NULL;
}

//判断树空
bool BST::isEmpty() const
{
    return bstroot == NULL;
}

//判断是否是叶子节点（删除部分用到）
bool BST::__isLeaf(BSTNode*const & root)
{
    if ((root->lchild == NULL) && (root->rchild == NULL))
        return true;
    else
        return false;
}

//判断节点是否有两个孩子（删除部分用到）
bool BST::__isNodeWithTwoChild(BSTNode * const & root)
{
    if (root->lchild != NULL &&root->rchild != NULL)
        return true;
    else
        return false;
}

//找到当前节点为根的子树中的最小值（删除部分用到，因此返回其父节点和当前节点）
BSTNode * BST::__treeMin(BSTNode*const root,BSTNode *&parent)
{
    BSTNode * curr = root;
    while (curr->lchild != NULL)
    {
        parent = curr;
        curr = curr->lchild;
    }
    return curr;
}

//删除节点内部实现
bool BST::__Delete(const int &key)
{
    bool found = false;//找到待删除的元素
    if (isEmpty())
    {
        //std::cerr << "Binary Search Tree Is Empty" << std::endl;//BST为空
        return false;
    }
    BSTNode * curr = bstroot;
    BSTNode *parent = NULL;
    while (curr != NULL)//查找待删除节点
    {

        if (key == curr->value)
        {
            found = true;
            break;
        }
        else
        {
            parent = curr;
            if (key < curr->value)
                curr = curr->lchild;
            else
                curr = curr->rchild;
        }
    }
    if (!found)
    {
        //std::cerr << "KeyValue Not Found" << std::endl;
        return false;
    }
    if (NULL == parent)//删除最后一个节点(根节点需要特殊处理)
    {
        bstroot = NULL;
        delete curr;
        return true;
    }
    //对于待删除的节点有三种可能：
    //1.叶子节点
    //2.只包含左子树或者右子树（单个孩子）
    //3.既包含左子树又包含右子树
    //删除节点的时候需要分3种情况进行考虑

    if (__isLeaf(curr))//叶子节点
    {
        if (parent->lchild == curr)
            parent->lchild = NULL;
        else
            parent->rchild = NULL;
        delete curr;
        return true;
    }//end if
    else if (__isNodeWithTwoChild(curr))//有两个孩子的节点
    {
        //以当前节点的右子树中的最小值取代它
        BSTNode*parent=curr;
        BSTNode *tmp = __treeMin(curr->rchild,parent);
        curr->value = tmp->value;
        if (parent->rchild == tmp)
            parent->rchild = NULL;
        else
            parent->lchild = NULL;
        delete tmp;
        return true;
    }//end else-if
    else//只有一个孩子的节点
    {
        if (curr->lchild != NULL)//只有左孩子
        {
            if (parent->lchild == curr)
            {
                parent->lchild = curr->lchild;
                delete curr;
                return true;
            }
            else
            {
                parent->rchild = curr->lchild;
                delete  curr;
                return true;
            }
        }
        if (curr->rchild != NULL)//只有右孩子
        {
            if (parent->lchild == curr)
            {
                parent->lchild = curr->rchild;
                delete curr;
                return true;
            }
            else
            {
                parent->rchild = curr->rchild;
                delete  curr;
                return true;
            }
        }
    }//end else
    return false;
}

//删除操作的外部接口
bool BST::Delete(const int &key)
{
    return __Delete(key);
}

//插入函数
//插入节点的内部实现，插入操作一定都在叶子节点处。
bool BST::__Insert(const int & key)
{
    BSTNode* t = new BSTNode(key);//临时节点
    t->number = 1;
    BSTNode*parent = NULL;
    if (isEmpty())//新树
    {
        bstroot = t;
        return true;
    }
    else
    {
        BSTNode* curr;
        curr = bstroot;
        while (curr)
        {
            //插入位置都位于叶子节点处
            parent = curr;
            if (t->value > curr->value)
                curr = curr->rchild;
            else if (t->value < curr->value)
                curr = curr->lchild;
            else {curr->number++;break;}
        }
        if (t->value < parent->value)
        {
            parent->lchild = t;
            return true;
        }
        else if(t->value > parent->value)
        {
            parent->rchild = t;
            return true;
        }
        //else ;
    }
    return false;
}

//插入节点的外部接口
bool BST::Insert(const int &key)
{
    return __Insert(key);
}

//构造函数
BST::BST()//默认构造函数
{
    bstroot = NULL;
}

BST::BST(int*arr, int len)//数组构造
{
    bstroot = NULL;
    for (int i = 0; i < len; i++)
    {
        __Insert(*(arr + i));
    }
}

BST::BST(std::vector<int>arr)//容器构造
{
    bstroot = NULL;
    for (int i = 0; i < (int)arr.size(); i++)
    {
        __Insert(arr[i]);
    }
}

//内部查找函数
//递归调用
BSTNode* BST::__search(BSTNode*root,const int& key)
{
    if (NULL == root)
        return NULL;
    if (key == root->value)
        return root;
    else if (key < root->value)
        return __search(root->lchild, key);
    else
        return __search(root->rchild, key);
}

//查找函数接口
bool BST::search(const int& key)
{
    BSTNode*t = __search(bstroot, key);
    return t == NULL ? false : true;
}

//中序遍历内部实现
void BST::__InorderTraversal(BSTNode *root,std::vector<int>&result,std::vector<int>&Num)
{
    if (NULL == root)
        return;
    __InorderTraversal(root->lchild, result, Num);
    //std::cout << root->value <<"->"<<root->number<< " ";
    result.push_back(root->value);
    Num.push_back(root->number);
    __InorderTraversal(root->rchild, result, Num);
}

//中序遍历接口，vector保存遍历结果
void BST::InorderTraversal(std::vector<int>&result,std::vector<int>&Num)
{
    __InorderTraversal(bstroot, result, Num);
}

//删除所有节点（析构用）
void BST::__DeleteAllNodes(BSTNode *root)
{
    if (root == NULL)
    {
        return;
    }
    __DeleteAllNodes(root->lchild);
    __DeleteAllNodes(root->rchild);
    __Delete(root->value);
}

//析构函数
BST::~BST()
{
    BSTNode*curr = bstroot;
    __DeleteAllNodes(curr);
}
