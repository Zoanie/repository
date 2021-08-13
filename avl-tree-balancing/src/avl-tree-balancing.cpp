//============================================================================
// Name        : avl-tree-balancing.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
    Node* lchild;
    int data;
    Node* rchild;
    int height;
};

/*
 * Eclipse Generate getters and setters
 * http://www.eclipseonetips.com/2010/10/26/generate-rename-and-delete-getterssetters-in-eclipse
 *
 * To generate getters and setters, do the following:
 *
 * Create the fields you want in the class then press Alt+Shift+S, R.
 *     - A dialog will pop up allowing you to choose the fields you want to generate getters and setters.
 *
 * Click Select All to create getters/setters for all fields. Of course you can choose individual fields as required.
 *
 * Change Insertion point to Last Member.
 *     - This tells Eclipse that you want to put the methods at the bottom of the class.
 *       This is normally the best option for me as I want them out of the way.
 *
 * Click Ok. Eclipse will create the getters and setters for you.
 *
 * Eclipse Generate a constructor from fields
 * http://www.eclipseonetips.com/2010/03/08/generate-class-constructors-in-eclipse-based-on-fields-or-superclass-constructors/
 *
 *     - The fastest way to generate a constructor based on fields is to press Alt+Shift+S, O
 *       (alternatively select Source > Generate Constructor using Fields… from the application menu).
 *       This pops up a dialog where you can select the fields you want to include in the constructor arguments.
 *       Once you’ve selected the fields you want, just click Ok and you’re done.
 *
 *       BTW, Alt+Shif+S is the shortcut to display a shortened Source menu, allowing Java source editing commands.
 */
class AVL{
    Node* root;
    int currentBalanceFactor;
    int currentNodeHeight;
    int lastDeletedKey;
    int lastInsertedKey;

public:

	AVL() {
		root = nullptr;
		currentBalanceFactor = 0;
	    currentNodeHeight = 0;
	    lastDeletedKey = 0;
	    lastInsertedKey = 0;
	}

    // Helper methods for inserting
    int NodeHeight(Node* p);
    int BalanceFactor(Node* p);
    Node* LLRotation(Node* pA);
    Node* RRRotation(Node* pA);
    Node* LRRotation(Node* p);
    Node* RLRotation(Node* p);

    // Insert
    Node* rInsert(Node* p, int key);

    // Delete
    Node* Delete(Node* p, int key);
    Node* inorderPredecessor(Node *p);
    Node* inorderSuccessor(Node *p);

    // Traversal
    void Inorder(Node* p);
    void Inorder() { Inorder(root); }
    void Levelorder(Node *p);
    void Levelorder() { Levelorder(root); };

    Node* getRoot(){ return root; }

	void setRoot(const Node *&root) {
		this->root = root;
	}

	int getCurrentBalanceFactor() const {
		return currentBalanceFactor;
	}

	void setCurrentBalanceFactor(int currentBalanceFactor) {
		this->currentBalanceFactor = currentBalanceFactor;
	}

	int getCurrentNodeHeight() const {
		return currentNodeHeight;
	}

	void setCurrentNodeHeight(int currentNodeHeight) {
		this->currentNodeHeight = currentNodeHeight;
	}

	int getLastDeletedKey() const {
		return lastDeletedKey;
	}

	void setLastDeletedKey(int lastDeletedKey) {
		this->lastDeletedKey = lastDeletedKey;
	}

	int getLastInsertedKey() const {
		return lastInsertedKey;
	}

	void setLastInsertedKey(int lastInsertedKey) {
		this->lastInsertedKey = lastInsertedKey;
	}

};

int AVL::NodeHeight(Node *p) {
    int hl;
    int hr;

    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;

    return hl > hr ? hl + 1 : hr + 1;
}

int AVL::BalanceFactor(Node *p) {
    int hl;
    int hr;

    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;

    return hl - hr;
}

/*
 *      (A)          (B)
 *      / \          / \
 *    (B) (d)  =>  (C) (A)
 *    / \              / \
 *  (C) (e)          (e) (d)
 *
 *  For test case: A=30, B=20, C=10, d=null, d=null
 *
 *  Procedure:
 *  1. Replace B->rightchild = A
 *  2. Replace A->leftchild = B->rightchild
 *  3. Update heights for node A & B
 */
Node* AVL::LLRotation(Node *pA) {// (A)
    Node* pB = pA->lchild;		// (Al)->(B)
    Node* pBr = pB->rchild;		// (Br)->(E)
    cout << "LL-rotation:" << endl;

    pB->rchild = pA;			// (Br)->(A)  B->rightchild = (A)
    pA->lchild = pBr;			// (Al)->(E)  A->leftchild = (E)

    // Update height
    pA->height = NodeHeight(pA);
    pB->height = NodeHeight(pB);

    // Update root
    if (root == pA){
        root = pB;
    }
    cout << "root = (" << getRoot()->data << ")" << endl;
    return pB;
}

/*
 *    (A)          (B)
 *    / \          / \
 *  (d) (B)  =>  (A) (C)
 *      / \        \
 *    (e) (C)      (e)
 *
 *  For test case: A=10, B=20, C=30, d=null, e=null
 *
 *  Procedure:
 *  1. Replace B->leftchild = A
 *  2. Replace A->rightchild = B->leftchild
 *  3. Update heights for node A & B
 */
Node* AVL::RRRotation(Node *pA) {
    Node* pB = pA->rchild;		// (Ar)->(B)
    Node* pBl = pB->lchild;		// (Bl)->(e)
    cout << "RR-rotation:" << endl;

    pB->lchild = pA;			// (Bl)->(A)
    pA->rchild = pBl;			// (Ar)->(e)

    // Update height
    pA->height = NodeHeight(pA);
    pB->height = NodeHeight(pB);

    // Update root
    if (root == pA){
        root = pB;
    }
    cout << "root = (" << getRoot()->data << ")" << endl;
    return pB;
}

/*
 *     (A)            (C)
 *     / \          /     \
 *   (B) (d)  =>  (B)     (A)
 *   / \          / \     / \
 *     (C)         (cl) (cr)(d)
 *     / \
 *   (cl)(cr)
 *
 *  For test case: A=30, B=10, C=20, d=null
 *
 *  "The problem is with the children of C"
 *
 *  Procedure:
 *  1. Save C->leftchild & C->rightchild
 *  1. Replace C->leftchild = B
 *  2. Replace C->rightchild = A
 *  3. Replace B->rightchild = (cl)
 *  4. Replace A->leftchild = (cr)
 *  3. Update heights for node A & B
 */
Node* AVL::LRRotation(Node *pA) {
    Node* pB = pA->lchild;		// (Al)->(B)
    Node* pC = pB->rchild;		// (Br)->(C)
    Node* pCl = pC->lchild;
    Node* pCr = pC->rchild;
    cout << "LR-rotation:" << endl;

    pC->rchild = pA;			// (Cl)=(A)
    pC->lchild = pB;			// (Cr)=(B)
    pB->rchild = pCl;			// (Br)=(cl)
    pA->lchild = pCr;			// (Al)=(cr)

    // Update height
    pC->height = NodeHeight(pC);
    pA->height = NodeHeight(pA);

    // Update root
    if (root == pA){
        root = pC;
    }
    cout << "root = (" << getRoot()->data << ")" << endl;
    return pC;
}

/*
 *    (A)            (C)
 *    / \          /     \
 *  (d) (B)  =>  (A)     (B)
 *  /   /        / \     /
 *    (C)      (d)(cl) (cr)
 *    / \
 *  (cl)(cr)
 *  For test case: A=10, B=30, C=20, d=null
 *
 *  "The problem is with the children of C"
 *
 *  Procedure:
 *  1. Save C->leftchild & C->rightchild
 *  1. Replace C->leftchild = A
 *  2. Replace C->rightchild = B
 *  3. Replace A->rightchild = (cl)
 *  4. Replace B->leftchild = (cr)
 *  3. Update heights for node A & B
 */
Node* AVL::RLRotation(Node *pA) {
    Node* pB = pA->rchild;		// (Al)->(B)
    Node* pC = pB->lchild;		// (Br)->(C)
    Node* pCl = pC->lchild;
    Node* pCr = pC->rchild;
    cout << "RL-rotation:" << endl;

    pC->lchild = pA;			// (Cl)=(B)
    pC->rchild = pB;			// (Cr)=(A)
    pB->lchild = pCr;			// (Bl)=(cr)
    pA->rchild = pCl;			// (Ar)=(cl)

    // Update height
    pC->height = NodeHeight(pC);
    pA->height = NodeHeight(pA);

    // Update root
    if (root == pA){
        root = pC;
    }
    cout << "root = (" << getRoot()->data << ")" << endl;
    return pC;
}

Node* AVL::rInsert(Node *p, int key) {
    Node* t;
    if (p == nullptr){
        t = new Node;
        t->data = key;
        t->lchild = nullptr;
        t->rchild = nullptr;
        t->height = 1;  // Starting height from 1 onwards instead of 0
        return t;
    }

    if (key < p->data){
        p->lchild = rInsert(p->lchild, key);
    } else if (key > p->data){
        p->rchild = rInsert(p->rchild, key);
    }

    // Update height
    p->height = NodeHeight(p);

    // Balance Factor and Rotation
    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {
        return LLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1){
        return LRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1){
        return RRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1){
        return RLRotation(p);
    }

    return p;
}

/*
 * 	Find right-most child of the left subtree.
 * 	This node has the next lower value from the specified input node
 */
Node* AVL::inorderPredecessor(Node *p) {
    while (p && p->rchild != nullptr){
        p = p->rchild;
    }
    return p;
}

/*
 * 	Find left-most child of the right subtree.
 * 	This node has the next higher value from the specified input node
 */
Node* AVL::inorderSuccessor(Node *p) {
	// find left-most child
    while (p && p->lchild != nullptr){
        p = p->lchild;
    }
    return p;
}

Node* AVL::Delete(Node *p, int key) {
    if (p == nullptr){
        return nullptr;
    }

    if (p->lchild == nullptr && p->rchild == nullptr){
        if (p == root){
        	cout << "Deleting root node (" << root->data << ")" << endl;
            root = nullptr;
        }
    	cout << "Deleting node (" << p->data << ")" << endl;
        delete p;
        return nullptr;
    }

    if (key < p->data){
        p->lchild = Delete(p->lchild, key);
    } else if (key > p->data){
        p->rchild = Delete(p->rchild, key);
    } else {
        Node* q;
        /*
    	 * Key match for node to-be-deleted is found. Delete procedure follows:
    	 *
         * 1. First choose which child node will take deleted nodes place based on which child node height is greater. This will maintain balance.
         * 2. Choice is either inorder predecessor from left child, or inorder successor from right child.
         * 3. Replace data element with selected child node data element.
         * 4. Actual node delete operation is completed on the selected replacement node. The target node of this function is actually just replaced.
         */
        if (NodeHeight(p->lchild) > NodeHeight(p->rchild)){
        	/*
        	 * Left subtree has greater height. Selecting a replacement node from this side will maintain balance.
        	 * This side contains the inorder predecessor, which is the next lower value.
        	 * After finding the predecessor node, use its data element to replace the target node of this function
        	 * and then delete the node in the predecessor subtree with the .
        	 */
            q = inorderPredecessor(p->lchild);
            cout << "Selected inorder predecessor node (" << q->data << ") to replace node (" << p->data << ")"<< endl;
            p->data = q->data;
            p->lchild = Delete(p->lchild, q->data);
        } else {
        	/*
        	 * Right subtree has greater or equal height. Selecting a replacement node from this side will maintain balance or is the default.
        	 * This side contains the inorder successor, which is the next higher value.
        	 * After finding the successor node, use its data element to replace the target node of this function
        	 * and then delete the predecessor node.
        	 */
        	q = inorderSuccessor(p->rchild);
            cout << "Selected inorder successor node (" << q->data << ") to replace node (" << p->data << ")"<< endl;
            p->data = q->data;
            p->rchild = Delete(p->rchild, q->data);
        }
    }

    // Update height
    p->height = NodeHeight(p);

    // Balance Factor and Rotation
    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {  // L1 Rotation
        return LLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1){  // L-1 Rotation
        return LRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1){  // R-1 Rotation
        return RRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1){  // R1 Rotation
        return RLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 0){  // L0 Rotation
        return LLRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 0){  // R0 Rotation
        return RRRotation(p);
    }

    return p;
}

void AVL::Inorder(Node *p) {
    if (p){
        Inorder(p->lchild);
        cout << p->data << ", " << flush;
        Inorder(p->rchild);
    }
}

void AVL::Levelorder(Node *p) {

	if(p == nullptr)
		return;

    queue<Node*> q;
    // queue node, get/pop/remove node, if left:output data & queue node, if right:output data & queue node...repeat
    cout << root->data << ", " << flush;

    /*
     * Good opportunity to examine STL queue lib function emplace() vs push() / push_back().
     *
     * STL queue class is a container adapter. The class template acts as a wrapper to the underlying container.
     * push() effectively calls the member function push_back of the underlying container object.
     *
     * push() adds a copy of an already constructed object into the queue as a parameter, it takes an object of the queue's element type.
	 *
	 * emplace() constructs a new object in-place at the end of the queue. It takes as parameters the parameters that the queue's element
	 * types constructor takes. If your usage pattern is one where you create a new object and add it to the container, you shortcut a
	 * few steps (creation of a temporary object and copying it) by using emplace().
     */
    q.emplace(root);

    while (! q.empty()){
    	// Thread safety requires STL queue to use 2 functions to pull an item from a queue
        p = q.front();
        q.pop();

        if (p->lchild){
            cout << p->lchild->data << ", " << flush;
            q.emplace(p->lchild);
        }

        if (p->rchild){
            cout << p->rchild->data << ", " << flush;
            q.emplace(p->rchild);
        }
    }
}



int main() {
	//cout << "https://www.udemy.com/course/datastructurescncpp/learn/lecture/13190664#questions/12081676" << endl; // prints https://www.udemy.com/course/datastructurescncpp/learn/lecture/13190664#questions/12081676
	cout << "AVL tree balancing during insertion" << endl;
    // LL Rotation
    AVL tll;
    tll.root = tll.rInsert(tll.root, 30);
    tll.root = tll.rInsert(tll.root, 20);
    //tll.root = tll.rInsert(tll.root, 25);
    tll.root = tll.rInsert(tll.root, 10);

    tll.Inorder();
    cout << endl;

    // RR Rotation
    AVL trr;
    trr.root = trr.rInsert(trr.root, 10);
    trr.root = trr.rInsert(trr.root, 20);
    trr.root = trr.rInsert(trr.root, 30);

    trr.Inorder();
    cout << endl;

    // LR Rotation
    AVL tlr;
    tlr.root = tlr.rInsert(tlr.root, 30);
    tlr.root = tlr.rInsert(tlr.root, 10);
    tlr.root = tlr.rInsert(tlr.root, 20);

    tlr.Inorder();
    cout << endl;

    // LR Rotation
    AVL trl;
    trl.root = trl.rInsert(trl.root, 10);
    trl.root = trl.rInsert(trl.root, 30);
    trl.root = trl.rInsert(trl.root, 20);

    trl.Inorder();
    cout << endl;

    cout << "AVL tree balancing after node delete - first create tree" << endl;
    AVL tree;
    // 2 ways to initialize a vector from an array:
    int array[] = {10, 20, 30, 25, 28, 27, 5};
    int num_elements = sizeof(array) / sizeof(int);

    // 1: Initialize same as an array is initialized
    vector<int> A{10, 20, 30, 25, 28, 27, 5};

    // 2: Initialize using array pointer and number of elements
    vector<int> B(array, array + num_elements);

    // C++11 method
    for (auto element : A) {
        tree.root = tree.rInsert(tree.root, element);
    }

    cout << "AVL tree, level order before node delete:" << endl;
    tree.Levelorder();
    cout << endl;

    int node_to_delete = 28;
    cout << "Delete node " << node_to_delete << endl;
    tree.Delete(tree.root, node_to_delete);

    cout << "AVL tree, level order after node delete:" << endl;
    tree.Levelorder();
    cout << endl;

    return 0;
}

