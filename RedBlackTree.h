//************************************************************************
// ASU CSE310 Assignment #5
// productID of Author: Alan Griffieth
// ASU ID: 1212575453
// Description: Red black tree header file. It defines the node and the
// red black tree functionalities.
//************************************************************************
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

struct Node
{
  string productID, name, supplierID, categoryID, unit;
  double price;
  Node *parent;
  Node *leftChild;
  Node *rightChild;
  string color;
};

class RedBlackTree
{
 private:
  Node *root;

 public:
  RedBlackTree();
  ~RedBlackTree();
  int deleteNode(Node *node);
  void insertNode(Node *node);
  void fixUp(Node *node);

  void preOrderTraversal(Node *node);
  void inorderTraversal(Node *node);
  void postOrderTraversal(Node *node);

  Node* findMinimumNode(Node *node);
  Node* findMaximumNode(Node *node);
  Node* treeSearch(string productID, string name, string supplierID, string categoryID);
  void leftRotate(Node *node);
  void rightRotate(Node *node);
  Node* findPredecessorNode(Node *node);
  Node* findSuccessorNode(Node *node);

  void treeMinimum();
  void treeMaximum();
  void preorder();
  void inorder();
  void postorder();
  void treePredecessor(string productID, string name, string supplierID, string categoryID);
  void treeSucessor(string productID, string name, string supplierID, string categoryID);
  void treeInsert(string productID, string name, string supplierID,
		  string categoryID, string unit, double price);

  void print(Node *node);
  int compareNodes(Node *node, string key);
  Node* getRoot();
};

#endif
