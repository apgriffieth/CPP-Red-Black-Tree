//************************************************************************
// ASU CSE310 Assignment #5
// Name of Author: Alan Griffieth
// ASU ID: 1212575453
// Description: Red black tree implementation. See RedBlackTree.h
//              for the tree definition. You need to add your own
//              code at //---- position
//************************************************************************

#include "RedBlackTree.h"

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
  root = NULL;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
  int nodeSize = deleteNode(root);
  cout << "The number of nodes deleted: " << nodeSize << endl;
}

//*******************************************************************
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This can be defined as a recursive function
int RedBlackTree::deleteNode(Node *node)
{
  int count = 0;
  if(node == NULL)
    return 0;
  count += this->deleteNode(node->leftChild);
  count += this->deleteNode(node->rightChild);
  delete(node);
  count++;
  return(count);
}

//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
void RedBlackTree::insertNode(Node *node)
{
  if(node == NULL)
    return;
  if(this->root == NULL) // if the tree is empty
    {
      //add your codes here
      this->root = node;
    }
  else
    { 
      //add your codes here
      string key = node->productID + node->name + node->supplierID + node->categoryID;
      Node* x = this->root;
      Node* y = x;

      while(x != NULL) {
	y = x;
	if(compareNodes(x, key) < 0) {//node should be a left child of x
	  x = x->leftChild;
	}
	else {//node should be a right child of x
	  x = x->rightChild;
	}	  
      }
  
      node->parent = y;

      if(compareNodes(y, key) < 0) {//node should be a left child of y
        y->leftChild = node;
      }
      else {//node should be a right child of y
        y->rightChild = node;
      }      
    }
  //At the end, need to call fixup() in case the newly
  //added node's parent is also RED
  this->fixUp(node);
}

//*******************************************************************
//At beginning, each newly added node will always be red,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.
void RedBlackTree::fixUp(Node *z)
{
  if(z == this->root)
    {
      z->color = "BLACK";
      return;
    }

  if(z->parent->color.compare("BLACK") == 0) {//if z's parent's color is black, we are done
    return;
  }
     
  //if z's color is 'RED' and its parent's color is also 'RED'
  while(z->color.compare("RED") == 0 &&
	z->parent != NULL &&
	z->parent->color.compare("RED") == 0)
    {
      //add your codes here
      if(z->parent == z->parent->parent->leftChild) {//z's parent is a left child
	if(z->parent->parent->rightChild != NULL && z->parent->parent->rightChild->color.compare("RED") == 0) {//z's uncle is red
	  z->parent->color = "BLACK";//change color of parent
	  if(z->parent->parent != this->root) {//only change the color if it's not the root
	    z->parent->parent->color = "RED";//change color of grandparent
	  }
	  z->parent->parent->rightChild->color = "BLACK";//change color of uncle
	  this->fixUp(z->parent->parent);//not a terminal case
	}

	else {//z's uncle is black
	  if(z->parent->rightChild == z) {//z is the right child of a left child
	    this->leftRotate(z->parent);
	    this->rightRotate(z->parent);//z's parent is now the original grandparent
	    z->color = "BLACK";
	    z->rightChild->color = "RED";//z's right child is now the original grandparent
	  }
	  
	  else {//z is the left child of a left child
	    this->rightRotate(z->parent->parent);
	    z->parent->color = "BLACK";
	    z->parent->rightChild->color = "RED";//This is the original grandparent
	    if(z->parent->rightChild->rightChild != NULL) {//Not a terminal case
	      this->fixUp(z->parent->rightChild->rightChild);
	    }
	  }
	}
      }
     
      else {//z's parent is a right child
	if(z->parent->parent->leftChild != NULL && z->parent->parent->leftChild->color.compare("RED") == 0) {//z's uncle is red
	  z->parent->color = "BLACK";//change color of parent
	  if(z->parent->parent != this->root) {//only change the color if it's not the root
	    z->parent->parent->color = "RED";//change color of grandparent
	  }
	  z->parent->parent->leftChild->color = "BLACK";//change color of uncle
	  this->fixUp(z->parent->parent); //Not a terminal case
	}
	else {//z's uncle is black
	  if(z->parent->leftChild == z) {//z is the left child of a right child
	    this->rightRotate(z->parent);
	    this->leftRotate(z->parent);//z's parent is now the original grandparent
	    z->color = "BLACK";
	    z->leftChild->color = "RED";//z's left child is now the original grandparent
	  }

	  else {//z is the right child of a right child
	    this->leftRotate(z->parent->parent);
	    z->parent->color = "BLACK";
	    z->parent->leftChild->color = "RED";//This is the original grandparent
	    if(z->parent->leftChild->leftChild != NULL) {
	      this->fixUp(z->parent->leftChild->leftChild);//not a terminal case
	    }
	  }
	}
      }
    }//end while
    //make sure the root is always 'BLACK'
    this->root->color = "BLACK";
}

//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::preOrderTraversal(Node *node)
{
  if(node == NULL)
    {
      return;
    }
  else
    {
      //add your codes here
      this->print(node);
      this->preOrderTraversal(node->leftChild);
      this->preOrderTraversal(node->rightChild);
    }
}

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::inorderTraversal(Node *node)
{
  if(node == NULL)
    {
      return;
    }
  else
    {
      //add your codes here
      this->inorderTraversal(node->leftChild);
      this->print(node);
      this->inorderTraversal(node->rightChild);
    }
}

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::postOrderTraversal(Node *node)
{
  if(node == NULL)
    {
      return;
    }
  else
    {
      //add your codes here
      this->postOrderTraversal(node->leftChild);
      this->postOrderTraversal(node->rightChild);
      this->print(node);
    }
}

//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It's a recursive function
Node* RedBlackTree::findMinimumNode(Node *node)
{
  if (node == NULL)
    {
      cout << "Tree is empty, no MINIMUM." << endl;
      return node;
    }
  else
    {
      //add your codes here
      while(node->leftChild != NULL) {
	node = node->leftChild;
      }
      return node;
    }
}

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It's a recursive function
Node* RedBlackTree::findMaximumNode(Node *node)
{
  if (node == NULL)
    {
      cout << "Tree is empty, no MAXIMUM." << endl;
      return node;
    }
  else
    {
      //add your codes here
      while(node->rightChild != NULL) {
	node = node->rightChild;
      }
      return node;
    }
}

//**************************************************************
//This function search the tree for a given key of a Product
//Note: key is the combination of productID, name, supplierID
//and categoryID. It returns a pointer points to the node if founded
//otherwise return NULL
Node* RedBlackTree::treeSearch(string productID, string name, string supplierID, string categoryID)
{
  string key1 = productID + name + supplierID + categoryID;
  Node *node = root;
  bool found = false;
  while(node != NULL)
    {
      string key2 = node->productID + node->name + node->supplierID + node->categoryID;
      if(key1.compare(key2) == 0) {//the node is found
	found = true;
	break;//exit while loop
      }

      else if(this->compareNodes(node, key1) < 0) {//key1 < node
	node = node->leftChild;	
      }

      else {//key1 > node
	node = node->rightChild;
      }
    }//end while
      
  if(found)
    {
      cout << left;
      cout << setw(5) << productID
	   << setw(35) << name
	   << setw(15) << supplierID
	   << setw(15) << categoryID
	   << " is FOUND." << endl;
      return node;
    }
  else
    {
      cout << left;
      cout << setw(5) << productID
	   << setw(35) << name
	   << setw(15) << supplierID
	   << setw(15) << categoryID
	   << " is NOT FOUND." << endl;
      return NULL;
    }
}


//****************************************************
//This function left-rotate the BST at 'node'
void RedBlackTree::leftRotate(Node *node)
{
  if(node == NULL || node->rightChild == NULL) {
    return;
  }
  //add your codes here
  else {
    Node* y = node->rightChild;
    node->rightChild = y->leftChild;
    if(y->leftChild != NULL) {
      y->leftChild->parent = node;
    }

    y->parent = node->parent;
    
    if(node->parent == NULL) {//It is the root node
      this->root = y;
    }
    
    else if (node == node->parent->leftChild) {//It is the left child
      node->parent->leftChild = y;
    }
    
    else {//It is the right child
      node->parent->rightChild = y;
    }
    
    y->leftChild = node;
    node->parent = y;
  }
}

//***************************************************
//This function right-rotate the BST at 'node'
void RedBlackTree::rightRotate(Node *node)
{
  if(node == NULL || node->leftChild == NULL) {
    return;
  }
  //add your codes here
  else {
    Node* y = node->leftChild;
    node->leftChild = y->rightChild;
    if(y->rightChild != NULL) {
      y->rightChild->parent = node;
    }
    
    y->parent = node->parent;
    
    if(node->parent == NULL) {//It is the root node
      this->root = y;
    }

    else if (node == node->parent->leftChild) {//It is the left child
      node->parent->leftChild = y;
    }

    else {//It is the right child
      node->parent->rightChild = y;
    }

    y->rightChild = node;
    node->parent = y;
  }
}


      //**************************************************************
      //This function finds the predecessor of the given 'node'
      //it prints the relevant predecessor info. on screen.
      Node* RedBlackTree::findPredecessorNode(Node *node)
      {
	Node* predn = NULL;
	if(node->leftChild != NULL) {
	  predn = this->findMaximumNode(node->leftChild);
	}

	else if (node->parent != NULL) {
	  predn = node->parent;
	  while(predn != NULL && node == predn->leftChild) {
	    node = predn;
	    predn = predn->parent;
	  }
	}
	if(predn != NULL)//----found
	  {
	    //add your codes here
	    cout << left;
	    cout << "Its Predecessor is: " << endl;
	    print(predn);
	    return predn;
	  }
	else  //not found
	  {
	    //add your codes here
	    //----
	    cout << left;
	    cout << "Its Predecessor does NOT EXIST"<< endl;
	    return predn;
	  }
      }
	//**************************************************************
	//This function finds the successor of the given 'node'
	//it prints the relevant successor info. on screen.
	Node* RedBlackTree::findSuccessorNode(Node *node)
	{
	  Node* sn;
	  if(node->rightChild != NULL) {
	    sn = this->findMinimumNode(node->rightChild);
	  }

	  else if (node->parent != NULL) {
	    sn = node->parent;
	    while(sn != NULL && node == sn->rightChild) {
	      node = sn;
	      sn = sn->parent;
	    }
	  }
	  if(sn != NULL)//----found
	    {
	      //add your codes here
	      cout << left;
	      cout << "Its Successor is: " << endl;
	      print(sn);
	      return sn;
	    }
	  else  //not found
	    {
	      cout << left;
	      cout << "Its Successor does NOT EXIST"<< endl;
	      return NULL;
	    }
	}
      

	  //**************************************************************
	  //This function find the minimum node of the entire red-black tree
	  //It print out the minimum node info. on screen if tree is not empty
	  //or print 'Tree is empty' message on screen.
	  void RedBlackTree::treeMinimum()
	  {
	    if (root == NULL)
	      {
		cout << "Tree is empty. No Minimum." << endl;
		return;
	      }

	    //add your codes here
	    else {
	      Node* min = this->findMinimumNode(this->root);
	      cout << "The MINIMUM is:" << endl;
	      this->print(min);
	    }
	  }

	  //**************************************************************
	  //This function find the maximum node of the entire red-black tree
	  //It print out the maximum node info. on screen if tree is not empty
	  //or print 'Tree is empty' message on screen.
	  void RedBlackTree::treeMaximum()
	  {
	    if (root == NULL)
	      {
		cout << "Tree is empty. No Maximum." << endl;
		return;
	      }

	    //add your codes here
	    else {
	      Node* max = this->findMaximumNode(this->root);
	      cout << "The MAXIMUM is:" << endl;
	      this->print(max);
	    }
	  }

	  //******************************************************************
	  //This function print out the pre-order traversal of the entire tree
	  void RedBlackTree::preorder()
	  {
	    //add your codes here
	    this->preOrderTraversal(this->root);
	  }

	  //******************************************************************
	  //This function print out the in-order traversal of the entire tree
	  void RedBlackTree::inorder()
	  {
	    //add your codes here
	    this->inorderTraversal(this->root);
	  }

	  //******************************************************************
	  //This function print out the post-order traversal of the entire tree
	  void RedBlackTree::postorder()
	  {
	    //add your codes here
	    this->postOrderTraversal(this->root);
	  }

	  //******************************************************************
	  //Given a product's key, this function first check whether the
	  //product is inside the tree or not, if it is inside, it will print
	  //its predecessor info. on screen, if not, it print an error message
	  void RedBlackTree::treePredecessor(string productID, string name,
					     string supplierID,string categoryID)
	  {
	    if (root == NULL)
	      cout << "Tree is empty. No Predecessor." << endl;
	    else
	      {
		Node* node = this->treeSearch(productID, name, supplierID, categoryID);
		//add your codes here
		if (node != NULL) {//the product is inside the tree
		  this->findPredecessorNode(node);
		}
	      }
	  }

	  //******************************************************************
	  //Given a product's key, this function first check whether the
	  //product is inside the tree or not, if it is inside, it will print
	  //its successor info. on screen, if not, it print an error message
	  void RedBlackTree::treeSucessor(string productID, string name,
					  string supplierID, string categoryID)
	  {
	    if (root == NULL)
	      cout << "Tree is empty. No Successor." << endl;
	    else
	      {
		//add your codes here
		Node* node = this->treeSearch(productID, name, supplierID, categoryID);
		if (node != NULL) {//the product is not inside the tree
		  this->findSuccessorNode(node);
		}
	      }
	  }

	  //**************************************************************
	  //This function create a node from the given info., then insert
	  //the node inside the red-black tree. Note: at beginning, the newly
	  //added node should always be 'RED'
	  void RedBlackTree::treeInsert(string productID, string name, string supplierID,
					string categoryID, string unit, double price)
	  {
	    //add your codes here
	    Node* newNode = new Node;//initialize the new node
	    newNode->productID = productID;
	    newNode->name = name;
	    newNode->supplierID = supplierID;
	    newNode->categoryID = categoryID;
	    newNode->unit = unit;
	    newNode->price = price;
	    newNode->color = "RED";
	    newNode->leftChild = NULL;
	    newNode->rightChild = NULL;
	    newNode->parent = NULL;
	    this->insertNode(newNode);
	  }
	  //******************************************************************
	  //Given a 'node', this function prints all its information on screen
	  void RedBlackTree::print(Node *node)
	  {
	    cout << left;
	    cout<< setw(5) << node->productID
		<< setw(35) << node->name
		<< setw(15) << node->supplierID
		<< setw(15) << node->categoryID
		<< setw(25) << node->unit
		<< setw(7) << node->price
		<< setw(7) << node->color << endl;
	  }

	  //**************************************************************
	  //Given a Node 'node1', this function compares it with another
	  //node's key.
	  //key is a string combination of productID + name + supplierID + categoryID
	  //It returns a negative number if in alphabetical order, key2 is
	  //in front of 'node1'; otherwise it returns a positive number
	  int RedBlackTree::compareNodes(Node *node1, string key2)
	  {
	    //add your codes here
	    string key1 = node1->productID + node1->name + node1->supplierID + node1->categoryID;
	    if(key1.compare(key2) < 0) {//key2 goes after key1
	      return(1);
	    }

	    else {//key2 goes before key1
	      return(-1);
	    }
	  }

	  //**************************************************************
	  //This function return the root of the red-black tree
	  Node* RedBlackTree::getRoot()
	  {
	    return this->root;
	  }
