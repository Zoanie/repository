//============================================================================
// Name        : binaryTreePractice.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Tree
{
public:
	Tree *left;
	Tree *right;
	int value;
	Tree() {
	    left = nullptr;
	    right = nullptr;
	    value = 0;
	}
};

class Node
{
public:
	Node *leftNode;
	Node *rightNode;
	int nodeValue;

  Node(int initValue){
    leftNode = nullptr;
    rightNode = nullptr;
    nodeValue = initValue;
  }
};

class BinarySearchTree
{
private:
	Node *rootNode;

public:
	BinarySearchTree(){
		rootNode = nullptr;
	}

	bool removeNode(int removeValue);
	Node *insertNode(int newNodeValue);
	Node *lookup(int lookupValue);


};

Node * BinarySearchTree::lookup(int lookupValue)
{
	if (!rootNode) {
		return nullptr;
	}
	Node *currentNode = rootNode;
	while(currentNode){
		if(lookupValue < currentNode->nodeValue){
			currentNode = currentNode->leftNode;
		} else if(lookupValue > currentNode->nodeValue){
			currentNode = currentNode->rightNode;
		} else if (currentNode->nodeValue == lookupValue) {
			return currentNode;
		}
	}
	return nullptr;
}

 bool BinarySearchTree::removeNode(int removeValue)
 {
	if (!rootNode) {
		return false;
	}
	Node *currentNode = rootNode;
	Node *parentNode = nullptr;
	while (currentNode) {
		if (removeValue < currentNode->nodeValue) {
			//Continue looking for matching value, move to the left
			parentNode = currentNode;
			currentNode = currentNode->leftNode;
		} else if (removeValue > currentNode->nodeValue) {
			//Continue looking for matching value, move to the right
			parentNode = currentNode;
			currentNode = currentNode->rightNode;
		} else if (currentNode->nodeValue == removeValue) {
			//We have a match, get to work! 3 options to decision:
			//  o No right child:

			//Option 1: No right child:
			if (currentNode->rightNode == nullptr) {
				// If the parent node is null, then we are being asked to replace the root node
				if (parentNode == nullptr) {
					rootNode = currentNode->leftNode;
				} else {

					//if parent > current value, make current left child a child of parent
					if (currentNode->nodeValue < parentNode->nodeValue) {
						parentNode->leftNode = currentNode->leftNode;

						//if parent < current value, make left child a right child of parent
					} else if (currentNode->nodeValue > parentNode->nodeValue) {
						parentNode->rightNode = currentNode->leftNode;
					}
				}

			//Option 2: Right child which doesn't have a left child
			} else if (currentNode->rightNode->leftNode == nullptr) {
				currentNode->rightNode->leftNode = currentNode->leftNode;
				if (parentNode == nullptr) {
					rootNode = currentNode->rightNode;
				} else {

					//if parent > current, make right child of the left the parent
					if (currentNode->nodeValue < parentNode->nodeValue) {
						parentNode->leftNode = currentNode->rightNode;

						//if parent < current, make right child a right child of the parent
					} else if (currentNode->nodeValue > parentNode->nodeValue) {
						parentNode->rightNode = currentNode->rightNode;
					}
				}

			//Option 3: Right child that has a left child
			} else {

				//find the Right child's left most child
				Node *leftmost = currentNode->rightNode->leftNode;
				Node *leftmostParent = currentNode->rightNode;
				while (leftmost->leftNode != nullptr) {
					leftmostParent = leftmost;
					leftmost = leftmost->leftNode;
				}

				//Parent's left subtree is now leftmost's right subtree
				leftmostParent->leftNode = leftmost->rightNode;
				leftmost->leftNode = currentNode->leftNode;
				leftmost->rightNode = currentNode->rightNode;

				if (parentNode == nullptr) {
					rootNode = leftmost;
				} else {
					if (currentNode->nodeValue < parentNode->nodeValue) {
						parentNode->leftNode = leftmost;
					} else if (currentNode->nodeValue > parentNode->nodeValue) {
						parentNode->rightNode = leftmost;
					}
				}
			}
			return true;
		}
	}
	return false;
}

Node *BinarySearchTree::insertNode(int newNodeValue)
{
	if (rootNode == nullptr) {
		Node *newNode = new Node(newNodeValue);
		rootNode = newNode;
		return newNode;
	} else {
		Node *currentNode = rootNode;
		while (true) {
			if (newNodeValue < currentNode->nodeValue) {
				//Left
				if (!currentNode->leftNode) {
					Node *newNode = new Node(newNodeValue);
					currentNode->leftNode = newNode;
					return newNode;
				}
				currentNode = currentNode->leftNode;
			} else if (newNodeValue > currentNode->nodeValue) {
				//Right
				if (!currentNode->rightNode) {
					Node *newNode = new Node(newNodeValue);
					currentNode->rightNode = newNode;
					return newNode;
				}
				currentNode = currentNode->rightNode;
			} else {
				// Neither - an invalid duplicate
				return nullptr;
			}
		}
	}
}

/*
Node *traverse(Node *node) {
  Tree *treeBranch = new Tree;
  //cout << "[" << node->nodeValue << ", ", <<
  treeBranch->value = node->nodeValue;
  treeBranch->left =  (node->leftNode == nullptr) ? nullptr : traverse(node->leftNode);
  treeBranch->right = (node->rightNode) == nullptr ? nullptr : traverse(node->rightNode);
  return treeBranch;
}
*/

 int main() {
 	cout << "https://repl.it/@aneagoie/Data-Structures-Trees#main.js" << endl;
 	BinarySearchTree* binaryTree = new BinarySearchTree();

 	binaryTree->insertNode(9);
 	binaryTree->insertNode(4);
 	binaryTree->insertNode(6);
 	binaryTree->insertNode(20);
 	binaryTree->insertNode(170);
 	binaryTree->insertNode(15);
 	binaryTree->insertNode(1);

 	// testing vector & list integration: Bo Qian, Vector vs Deque -part II
 	//
 	list<int> mylist = {2,4,6,8};

 	vector<int> vec(mylist.begin(), mylist.end());

 	for(auto elem : vec)
 		cout << elem << ", ";

 }


