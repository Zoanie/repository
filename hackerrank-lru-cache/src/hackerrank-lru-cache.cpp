//============================================================================
// Name        : hackerrank-lru-cache.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.hackerrank.com/challenges/abstract-classes-polymorphism/problem
//============================================================================

#include <bits/stdc++.h>
#include <cassert>

/*
 * Abstract Classes - Polymorphism - LRU cache design
 *
Abstract base classes in C++ can only be used as base classes. Thus, they are allowed to have
virtual member functions without definitions.

A cache is a component that stores data so future requests for that data can be served faster.
The data stored in a cache might be the results of an earlier computation, or the duplicates
of data stored elsewhere. A cache hit occurs when the requested data can be found in a cache,
while a cache miss occurs when it cannot. Cache hits are served by reading data from the cache
which is faster than recomputing a result or reading from a slower data store. Thus, the more
requests that can be served from the cache, the faster the system performs.

One of the popular cache replacement policies is: "least recently used" (LRU). It discards the
least recently used items first.

For example, if a cache with a capacity to store 5 keys has the following state(arranged from
most recently used key to least recently used key) -
5 3 2 1 4

Now, If the next key comes as 1(which is a cache hit), then the cache state in the same order will be -
1 5 3 2 4

Now, If the next key comes as 6(which is a cache miss), then the cache state in the same order will be -
6 1 5 3 2

You can observe that 4 has been discarded because it was the least recently used key and since
the capacity of cache is 5, it could not be retained in the cache any longer.

Given an abstract base class Cache with member variables and functions:
mp - Map the key to the node in the linked list
cp - Capacity
tail - Double linked list tail pointer
head - Double linked list head pointer
set() - Set/insert the value of the key, if present, otherwise add the key as the most recently
used key. If the cache has reached its capacity, it should replace the least recently used key
with a new key.
get() - Get the value (will always be positive) of the key if the key exists in the cache,
otherwise return -1.

You have to write a class LRUCache which extends the class Cache and uses the member functions
and variables to implement an LRU cache.

Input Format:
First line of input will contain the N number of lines containing get or set commands followed
by the capacity  of the cache. The following N lines can either contain get or set commands.
An input line starting with get will be followed by a key to be found in the cache. An input
line starting with set will be followed by the key and value respectively to be inserted/replaced
in the cache.

Constraints:
1 <= N <= 500000        - number of commands
1 <= M <= 1000          - capacity of cache
1 <= key <= 20          - key range
1 <= value <= 2000      - value range

Output Format:
The code provided in the editor will use your derived class LRUCache to output the value whenever
a get command is encountered.

Sample Input:
3 1
set 1 2
get 1
get 2

Sample Output:
2
-1

Explanation:
Since, the capacity of the cache is 1, the first set results in setting up the key 1 with it's
value 2. The first get results in a cache hit of key 1, so 2 is printed as the value for the
first get. The second get is a cache miss, so -1 is printed.
 */


using namespace std;

struct Node {
   Node* prev;
   Node* next;
   int key;
   int value;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache {

protected:

    map<int,Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

    virtual ~Cache() {};

};

class LRUCache: public Cache {
    const int max_capacity = 100;
    const int max_unique_keys = 20;

    bool cachingNodes;
    vector<Node *> nodeCache;
    int cacheSize;
    int cacheHits;
    int cacheMisses;

public:
    LRUCache(int capacity) {
    	cp = capacity;
    	tail = nullptr;
    	head = nullptr;

    	/* */
    	cacheSize = 0;
    	cacheHits = 0;
    	cacheMisses = 0;
    	initNodeCache();
    	cachingNodes = true;
    }

    void initNodeCache() {
        // Init one more node than max for testing
        for(int key=0; key<=max_unique_keys; key++) {
            Node* node = new Node(key, 0);
            nodeCache.emplace_back(node);
            cacheSize++;
        }
    }

    Node* getNode(int key, int val) {
        Node* node = nullptr;
        if(cachingNodes && nodeCache.size() > 1) {
            node = nodeCache[key];
            // key should be the same. If not then something is wrong.
            assert((node->key == key) && "Error: cached key different than index!");
            node->value = val;
        }
        else {
            node = new Node(key, val);
        }
        return node;
    }

    void returnNode(Node *node) {
        if(cachingNodes) {
            if(node) {
                // clear node
                node->prev = nullptr;
                node->next = nullptr;
                node->value = 0;
                // keep the same key
                // node->key is also the vector element index;
            }
        }
        else {
            delete node;
        }
    }

    void update(Node* nextHead) {
        if(!nextHead) return;

        if(!head) {
            head = nextHead;
            tail = nextHead;
            return;
        }
        // skip update if nextHead is already the head
        if(head != nextHead) {
        	if(nextHead == tail) {
        	    // get a new tail
        		tail = nextHead->next;
        		tail->prev = nullptr;
        	}
        	else {
        	    // step 1: Get node pointers to both next and previous nodes of nextHead
        	    Node *prevNode = nextHead->prev;
        	    Node *nextNode = nextHead->next;
        	    // step 2: Remove and replace nextHead node from list.
        	    //         Inserted new nodes do not have prev or next pointers
        	    if(prevNode)
        	        prevNode->next = nextNode;
        	    if(nextNode)
        	        nextNode->prev = prevNode;
        	}
        	// Insert nextHead as head
        	nextHead->prev = head;	// point back to old head
        	head->next = nextHead;
        	nextHead->next = nullptr;

        	if(!tail) { assert(tail && "Tail is nullptr!"); }   // tail = nextHead; }  // might not be necessary
        	head = nextHead;
        }
    }

    void deleteTail() {
        tail = tail->next;
        if(cachingNodes) {
            returnNode(tail->next);
        }
        else {
            delete tail->prev;
        }
        tail->prev = nullptr;
    }

    // Set/insert the value of the key, if present, otherwise add the key as the most recently used key.
    void set(int key, int val) {

    	auto it = mp.find(key);
        if(it != mp.end()) {
            Node* node = mp[key];
            node->value = val;
            update(node);
        }
        else {
            // Using pre-allocated node design, this should never happen if the capacity is lte the number of unique keys.
            if((int) mp.size() >= cp) {
                // Make room for new key/node pair. Erase tail entry.
                mp.erase(tail->key);
                // delete list element at tail
                deleteTail();
            }

        	// key is not in the lookup table
            Node *node = getNode(key, val);
            update(node);
            mp.emplace(key, node);
        }
    }

    //  Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
    int get(int key) {
        // Which is more likely? Finding a key or not finding a key?
        // There are only 20 unique keys. Favor finding a key in the cache.
        if(mp.find(key) != mp.end()) {
            // update key to most used position at head of list
            Node* nextHead = mp[key];
            update(nextHead);
            cacheHits++;
            return mp[key]->value;
        }
        cacheMisses++;

        return -1; // key not found
    }

};

int main() {
    LRUCache testCache(10);
    int tenCount=0;
    for(int i=0; i < 10; i++) {
        int key = 1 + i;
        int value = 1000 + key;
        if(tenCount++ < 10 ) {
            testCache.set(key, value);
        }
    }
    for(int i=0; i < 10; i++) {
        int key = 1 + i;
        int value = 1000 + key;
        int testValue = testCache.get(key);
        if(value != testValue) {
            printf("Error on key %d, s/b %d, but is %d\n", key, value, testValue);
        }
        else {
            cout << ".";
        }
    }
    return 0;

    int n, capacity,i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for(i=0;i<n;i++) {
        string command;
        cin >> command;
        if(command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        }
        else if(command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key,value);
        }
    }
    return 0;
}
