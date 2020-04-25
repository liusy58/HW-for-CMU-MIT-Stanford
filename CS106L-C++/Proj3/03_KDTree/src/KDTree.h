/**
 * File: KDTree.h
 * Author: (your name here)
 * ------------------------
 * An interface representing a kd-tree in some number of dimensions. The tree
 * can be constructed from a set of data and then queried for membership and
 * nearest neighbors.
 */

#ifndef KDTREE_INCLUDED
#define KDTREE_INCLUDED

#include "Point.h"
#include "BoundedPQueue.h"
#include <stdexcept>
#include <cmath>
#include <unordered_map>
#include <queue>
// "using namespace" in a header file is conventionally frowned upon, but I'm
// including it here so that you may use things like size_t without having to
// type std::size_t every time.
using namespace std;

template <size_t N, typename ElemType>
class KDTree {
public:
    // Constructor: KDTree();
    // Usage: KDTree<3, int> myTree;
    // ----------------------------------------------------
    // Constructs an empty KDTree.
    KDTree();

    // Destructor: ~KDTree()
    // Usage: (implicit)
    // ----------------------------------------------------
    // Cleans up all resources used by the KDTree.
    ~KDTree();

    // KDTree(const KDTree& rhs);
    // KDTree& operator=(const KDTree& rhs);
    // Usage: KDTree<3, int> one = two;
    // Usage: one = two;
    // -----------------------------------------------------
    // Deep-copies the contents of another KDTree into this one.
    KDTree(const KDTree& rhs);
    KDTree& operator=(const KDTree& rhs);

    // size_t dimension() const;
    // Usage: size_t dim = kd.dimension();
    // ----------------------------------------------------
    // Returns the dimension of the points stored in this KDTree.
    size_t dimension() const;

    // size_t size() const;
    // bool empty() const;
    // Usage: if (kd.empty())
    // ----------------------------------------------------
    // Returns the number of elements in the kd-tree and whether the tree is
    // empty.
    size_t size() const;
    bool empty() const;

    // bool contains(const Point<N>& pt) const;
    // Usage: if (kd.contains(pt))
    // ----------------------------------------------------
    // Returns whether the specified point is contained in the KDTree.
    bool contains(const Point<N>& pt) const;

    // void insert(const Point<N>& pt, const ElemType& value);
    // Usage: kd.insert(v, "This value is associated with v.");
    // ----------------------------------------------------
    // Inserts the point pt into the KDTree, associating it with the specified
    // value. If the element already existed in the tree, the new value will
    // overwrite the existing one.
    void insert(const Point<N>& pt, const ElemType& value);

    // ElemType& operator[](const Point<N>& pt);
    // Usage: kd[v] = "Some Value";
    // ----------------------------------------------------
    // Returns a reference to the value associated with point pt in the KDTree.
    // If the point does not exist, then it is added to the KDTree using the
    // default value of ElemType as its key.
    ElemType& operator[](const Point<N>& pt);

    // ElemType& at(const Point<N>& pt);
    // const ElemType& at(const Point<N>& pt) const;
    // Usage: cout << kd.at(v) << endl;
    // ----------------------------------------------------
    // Returns a reference to the key associated with the point pt. If the point
    // is not in the tree, this function throws an out_of_range exception.
    ElemType& at(const Point<N>& pt);
    const ElemType& at(const Point<N>& pt) const;

    // ElemType kNNValue(const Point<N>& key, size_t k) const
    // Usage: cout << kd.kNNValue(v, 3) << endl;
    // ----------------------------------------------------
    // Given a point v and an integer k, finds the k points in the KDTree
    // nearest to v and returns the most common value associated with those
    // points. In the event of a tie, one of the most frequent value will be
    // chosen.
    ElemType kNNValue(const Point<N>& key, size_t k) const;

private:
    size_t _dimension;
    struct Node{
        Point<N>point;
        ElemType element_value;
        Node* left;
        Node* right;
    };
    Node*root;
    size_t node_num;

    void copy_Subtree(Node**to,const Node*const from);//helper function to help construct the whole tree by recursion
    void delete_Subtree(const Node*const root);//helper function to help delete the whole tree by recursion
    Node const* const *findNode(const Point<N>& pt) const;
    void kNNValueHelper(BoundedPQueue<const Node*>&, const Point<N>& key,
                            const Node* const curr, const size_t pivotCoord) const;
    Node** findNode(const Point<N>& pt);

};

/** KDTree class implementation details */

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree() {
    _dimension=N;
    root=nullptr;
    node_num=0;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
    delete_Subtree(root);
    node_num=0;
    root=nullptr;
}

// KDTree(const KDTree& rhs);
// KDTree& operator=(const KDTree& rhs);
// Usage: KDTree<3, int> one = two;
// Usage: one = two;
// -----------------------------------------------------
// Deep-copies the contents of another KDTree into this one.
template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree& rhs)
{
    this->_dimension=rhs._dimension;
    this->node_num=rhs.node_num;
    copy_Subtree(&root,rhs.root);
}


template <size_t N, typename ElemType>
KDTree<N, ElemType>& KDTree<N, ElemType>::operator=(const KDTree& rhs)
{
    if(this!=&rhs)
    {
        delete_Subtree(root);
        _dimension=rhs.dimension();
        node_num=rhs.node_num;
        copy_Subtree(&(this->root),rhs.root);
    }
    return *this;
}

// size_t dimension() const;
// Usage: size_t dim = kd.dimension();
// ----------------------------------------------------
// Returns the dimension of the points stored in this KDTree.

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
    return _dimension;
}



template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const
{
    return node_num;
}


template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const
{
    return !node_num;
}

// bool contains(const Point<N>& pt) const;
// Usage: if (kd.contains(pt))
// ----------------------------------------------------
// Returns whether the specified point is contained in the KDTree.
template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N>& pt) const
{
    return *(findNode(pt))!=nullptr;
}



// void insert(const Point<N>& pt, const ElemType& value);
// Usage: kd.insert(v, "This value is associated with v.");
// ----------------------------------------------------
// Inserts the point pt into the KDTree, associating it with the specified
// value. If the element already existed in the tree, the new value will
// overwrite the existing one.
template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N>& pt, const ElemType& value)
{
    Node**res=findNode(pt);
    if(*res==nullptr)
    {
        *res = new Node{pt,value,nullptr,nullptr};
        ++node_num;
    }
    else
        (*res)->element_value=value;
}



// ElemType& operator[](const Point<N>& pt);
// Usage: kd[v] = "Some Value";
// ----------------------------------------------------
// Returns a reference to the value associated with point pt in the KDTree.
// If the point does not exist, then it is added to the KDTree using the
// default value of ElemType as its key.
template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt)
{
    Node ** res=findNode(pt);
    if(*res==nullptr)
    {
        *res = new Node{pt,ElemType(),nullptr,nullptr};
        ++node_num;
    }

    return (*res)->element_value;

}


// ElemType& at(const Point<N>& pt);
// const ElemType& at(const Point<N>& pt) const;
// Usage: cout << kd.at(v) << endl;
// ----------------------------------------------------
// Returns a reference to the key associated with the point pt. If the point
// is not in the tree, this function throws an out_of_range exception.
template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt)
{
    Node ** res=findNode(pt);
    if(*res==nullptr)
        throw std::out_of_range("Point is not in the tree or zero-dimension");
    return (*res)->element_value;
}

template <size_t N, typename ElemType>
const ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) const
{
    Node ** res=findNode(pt);
    if(*res==nullptr)
        throw std::out_of_range("Point is not in the tree or zero-dimension");
    return (*res)->element_value;
}


// ElemType kNNValue(const Point<N>& key, size_t k) const
// Usage: cout << kd.kNNValue(v, 3) << endl;
// ----------------------------------------------------
// Given a point v and an integer k, finds the k points in the KDTree
// nearest to v and returns the most common value associated with those
// points. In the event of a tie, one of the most frequent value will be
// chosen.
template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::kNNValue(const Point<N>& key, size_t k) const
{
    if(!k)
       throw std::out_of_range("0-nearest neighbors search");
     BoundedPQueue<const Node*> bpq(k);
     kNNValueHelper(bpq, key, root, 0);

     if(bpq.empty()) throw std::out_of_range("Empty KDTree kNN search");

     unordered_map<ElemType, size_t> frequencyCounter;
     while(!bpq.empty()) ++frequencyCounter[bpq.dequeueMin()->image];

     auto cmp = [](pair<ElemType, size_t> p1, pair<ElemType, size_t> p2)
     { return p1.second < p2.second; };

     priority_queue<pair<ElemType, size_t>, vector< pair<ElemType, size_t> >,
             decltype(cmp)> imageCounterPQueue(cmp);

     for(auto item : frequencyCounter) imageCounterPQueue.push(item);

     return imageCounterPQueue.top().first;
}






//helper function to help construct the whole tree by recursion
template <size_t N, typename ElemType>
void KDTree<N, ElemType>::copy_Subtree(Node**to,const Node*const from)
{
    if(from==nullptr)
        return;
    *to=new Node{from->point,from->element_value,nullptr,nullptr};
    copy_Subtree(&((*to)->left),from->left);
    copy_Subtree(&((*to)->right),from->right);
}


//helper function to help delete the whole tree by recursion
template <size_t N, typename ElemType>
void KDTree<N, ElemType>::delete_Subtree(const Node*const root)
{
    if(root==nullptr)
        return;
    delete_Subtree(root->left);
    delete_Subtree(root->right);
    delete(root);
}
// TODO: finish the implementation of the rest of the KDTree class

template <size_t N, typename ElemType>
typename KDTree<N, ElemType>::Node const* const *KDTree<N, ElemType>::findNode(const Point<N>& pt) const
{
   Node const * const *res=&root;
   size_t level=0;
   while(*res!=nullptr&&((*res)->point!=pt))
   {
       if((*res)->point[level%N]>pt[level%N])
           res=&((*res)->left);
       else
           res=&((*res)->right);
   }
   return res;
}

template <size_t N, typename ElemType>
typename KDTree<N, ElemType>::Node** KDTree<N, ElemType>::findNode(const Point<N>& pt)
{
    Node **res=&root;
    size_t level=0;
    while(*res!=nullptr&&((*res)->point!=pt))
    {
        if((*res)->point[level%N]>pt[level%N])
            res=&((*res)->left);
        else
            res=&((*res)->right);
    }
    return res;
}
template <size_t N, typename ElemType>
void KDTree<N, ElemType>::kNNValueHelper(BoundedPQueue<const Node*>& bpq, const Point<N>& key,
                                         const Node* const curr, const size_t pivotCoord) const {
    if(curr == nullptr) return;
    double distance = Distance(curr->point, key);
    if(distance < bpq.worst() || bpq.size() < bpq.maxSize()) bpq.enqueue(curr, distance);

    const double distanceToPivot = key[pivotCoord % N] - curr->point[pivotCoord % N];

    (distanceToPivot < 0) ? kNNValueHelper(bpq, key, curr->left, pivotCoord + 1) :
                            kNNValueHelper(bpq, key, curr->right, pivotCoord + 1);

    if(bpq.size() < bpq.maxSize() || fabs(distanceToPivot) < bpq.worst()) {

        (distanceToPivot < 0) ? kNNValueHelper(bpq, key, curr->right, pivotCoord + 1) :
                                kNNValueHelper(bpq, key, curr->left, pivotCoord + 1);
    }
}
#endif // KDTREE_INCLUDED
