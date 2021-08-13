//============================================================================
// Name        : lru-cache.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

/*
 * LRU Cache
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

	o LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
	o int get(int key) Return the value of the key if the key exists, otherwise return -1.
	o void put(int key, int value) Update the value of the key if the key exists.

Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity
from this operation, evict the least recently used key.

Follow up:
Could you do get and put in O(1) time complexity?

Example 1:
Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4


Constraints:

1 <= capacity <= 3000
0 <= key <= 3000
0 <= value <= 104
At most 3 * 104 calls will be made to get and put.
 */

/*
 * Notes:
 *
 * https://leetcode.com/problems/lru-cache/discuss/316389/Simple-Solution-using-list-hash-map-and-splice-with-Explanation
 * list.splice operation is explained here:
 *     https://www.geeksforgeeks.org/list-splice-function-in-c-stl/
 *     https://howardhinnant.github.io/On_list_size.html
 *
 * https://leetcode.com/problems/lru-cache/discuss/45976/C%2B%2B11-code-74ms-Hash-table-%2B-List
 *     The good thing about lists is that iterators are never invalidated by modifiers
 *     (unless erasing the element itself). This way, we can store the iterator to the
 *     corresponding LRU queue in the values of the hash map. Since using erase on a list
 *     with an iterator takes constant time, all operations of the LRU cache run in
 *     constant time.
 */
/*
 * Solution: https://leetcode.com/problems/lru-cache/discuss/891408/Easy-and-Well-Explained
 */
class LRUCache {
// linked list that contains values of keys and their pairs
list<pair<int, int>> keys;

// contains keys and their pointer to the linked list
unordered_map<int, list<pair<int, int>>::iterator> key_address;
int cache_size = 0;
const int not_found = -1;

public:
    LRUCache(int capacity) {
        cache_size = capacity;
    }

    int get(int key){

        auto find_key = key_address.find(key);

        // if it is not in the cache
        if(find_key == key_address.end())
            return not_found;

        // splice is used to move the elements
        // >move to keys.begin, as this is key used most recently
        // >from keys and iterator is find-key, which will now
        // >point to keys.begin
        keys.splice(keys.begin(), keys, find_key->second);

        // return the value of the key in the linked list.
        return find_key->second->second;
    }

    void put(int key, int value) {

        // if key found
        if(key_address.find(key) != key_address.end())
        {
           // change the value of last
            keys.splice(keys.begin(), keys, key_address[key]);
            key_address[key]->second = value;
            return;
        }

        int list_size = keys.size();
        if(list_size >= cache_size)
        {
        	// !!! Probably should be int to_delete = keys.back().first; Since the end() of std::list is a dummy tail
            int to_delete = keys.end()->first;
            key_address.erase(to_delete);
            // Removes the last element in the list container, effectively reducing the container size by one.
            keys.pop_back();
        }

        keys.push_front({key, value});
        key_address[key] = keys.begin();

        return;
    }
};

class LRUCacheV2 {
public:

    int cap;
    unordered_map<int,int> hashMap;
    list<int> lst;
    const int not_found = -1;

    LRUCacheV2(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        if (hashMap.find(key) != hashMap.end()) {
            auto it = hashMap.find(key);
            int ans = it->second;
            // Update key to front of recently used list
            // - We could check if it is already at the front and skip the remove & push
            lst.remove(key);
            lst.push_front(key);
            return ans;
        }
        else return not_found;

    }

    void put(int key, int value) {
        if (hashMap.find(key) != hashMap.end()) {
            hashMap[key] = value;
            lst.remove(key);
        }
        else {
            hashMap[key] = value;
        }

        lst.push_front(key);
        if (lst.size() > cap) {
            hashMap.erase(lst.back());
            lst.pop_back();
        }
    }
};

// These two solutions use the same design
// https://leetcode.com/problems/lru-cache/discuss/46223/O(1)-unordered_map-%2B-list-%2B-splice
// https://leetcode.com/problems/lru-cache/discuss/316389/Simple-Solution-using-list-hash-map-and-splice-with-Explanation
class LRUCacheV3 {
private:
	// This is an ordered list of the '_most_ recently used' key/value pairs.
	// The least recently used pairs are removed from the list.
	// The number of keys in the map is equal to number of list elements
    list<pair<int, int>>mru_list;

    // map (key & list iterator)
    unordered_map<int, list<pair<int,int>>::iterator> cache;
    int capacity;	// cache capacity

public:
    LRUCacheV3(int capacity): capacity(capacity) {}

    // Return the value of the key if the key exists, otherwise return -1
    int get(int key) {
        if(cache.find(key) == cache.end())
            return -1; // key not found
        // Move the element to beginning of the list
        // The cache value for each key is an iterator into the 'most recently used list'
        mru_list.splice(mru_list.begin(), mru_list, cache[key]);
        return cache[key]->second;
    }

    // Update the value of the key if the key exists.
    void put(int key, int value) {
        // Test if key is cached,
        if(cache.find(key) == cache.end())
        {
        	// key is not in the hash table
            // if hash table size equal to capacity then remove the least recently used (LRU) element, which is at end of the list
            if(cache.size() == capacity)
            {
            	// map.erase arg is a key, hash table delete is O(1) constant time
                cache.erase(mru_list.back().first); // mru_list.back().first is the key
                mru_list.pop_back(); // remove from list is O(1) constant time
            }
            // list and map each contain the same number of elements
            mru_list.push_front(make_pair(key, value)); // key/value moved to the most recently used position
            cache[key] = mru_list.begin(); // hash table values are list iterators
        }
        else // key is found in the hash table
        {
            // Update the value associated with the key
            cache[key]->second = value;

            // Move a single list element to beginning of the list
            //   - void splice (const_iterator position, list& x, const_iterator i);
            mru_list.splice(mru_list.begin(), mru_list, cache[key]);
        }
    }
};
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
	cout << "https://leetcode.com/problems/lru-cache/" << endl; // prints https://leetcode.com/problems/lru-cache/
	return 0;
}
