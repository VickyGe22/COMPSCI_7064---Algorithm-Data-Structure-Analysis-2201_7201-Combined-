#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <cstddef>
#include <sstream>

// Initialize the hash table
enum SlotStatus
{
    Never_used,
    Tombstone,
    occupied
};

struct Slot
{
    std::string key;
    SlotStatus status;

    Slot() : status(Never_used) {}
};

// Hash table with linear probing
class HashTable
{
private:
    std::vector<Slot> table;

    int hash(const std::string &key)
    {
        return key.back() - 'a';
    }

public:
    HashTable() : table(26) {}

    int search(const std::string &key)
    {
        int hash_index = hash(key);
        while (table[hash_index].status != Never_used){
            if (table[hash_index].status == occupied && table[hash_index].key == key){
                return hash_index;
            }
            hash_index = (hash_index + 1) % 26;
        }
        return -1;
    }


    void insert(const std::string& key){
        if (search(key) != -1){
            return;
        }
        int hash_index = hash(key);
        while (table[hash_index].status == occupied){
            hash_index = (hash_index + 1) % 26;
        }
        table[hash_index].key = key;
        table[hash_index].status = occupied;
    }

    void remove(const std::string& key){
        int hash_index = search(key);
        if (hash_index != -1){
            table[hash_index].status = Tombstone;
        }
    }

    void program(const std::vector<std::string>& inputs){
        for (size_t i = 0; i < inputs.size(); ++i){
            char action = inputs[i].at(0);
            std::string key = inputs[i].substr(1);

            if (action == 'A'){
                insert(key);
            }
            else if (action == 'D'){
                remove(key);
            }
        }
    }

    void print(){
        for (size_t i = 0; i < table.size(); ++i){
            if (table[i].status == occupied){
                std::cout << table[i].key << " ";
            }
        }
        std::cout << "\n";
    }

};

int main(){
    HashTable hs_table;
    std::string input;
    std::getline(std::cin, input);

    // Splitting the input string based on spaces
    std::istringstream iss(input);
    std::vector<std::string> inputs;
    std::string temp;
    while (iss >> temp){
        inputs.push_back(temp);
    }
    hs_table.program(inputs);
    hs_table.print();
}



// Hash table with linear probing

// You are asked to implement a very specific hash table.
//  The keys are lower-case English words (e.g., apple,pear).
//  The length of a key is at most 10.

// The hash function is “simply using the last character”.
// That is, the hash value of apple should be e, and the hash value of pear should be r.

// Your hash table contains exactly 26 slots (hash value a to hash value z).

// The total number of English words/keys you need to deal with is at most 26, so the table is never too small.

// A table slot has three different statuses:
// “never used”, “tombstone”, and “occupied”.
// Table starts with 26 “never used” slots.

// 哈希表内容总共26个a-z，Key全称-hash value是Key的最后字符 - 最后的字符取决于把这个key插到第几个slot里
// 结构：Statuses:Key
// 总共26个，Key最长10个字符

// 搜索工作，给定一个key，取它的最后一个字符作为哈希值
//  Searching works as follows: given a key, take its last character as the hash value.

// First try the corresponding table slot, if the objective key is there, then you have found it.
// 如果目标Key在哈希表就找到它

// If the corresponding slot is never used, terminate because we are certain that the objective is not in the table.
// 如果对应的value状态是never used，那么就是说这个key不在哈希表里，直接终止程序

// If the slot is occupied but it’s not the objective, or the slot is a “tombstone”, then we move on to the next slot (may need to wrap around the table if the current slot is the last one). We keep trying until we either find the key or are certain that the key does not exist in the table.
// 如果这个slot是occupied或者是tombstone，但是不是目标key，那么就继续往下一个slot找，直到找到目标key或者确定这个key不在哈希表里

// 插入工作
//  Insertion works as follows:
//  First perform searching to ensure that the key does not exist.
// 先查找，如果不存在在插入
//  If it already exists, then do nothing.
// 如果存在就什么都不做

// If it does not, take the last character of a key as the hash value.

// If the corresponding table slot is not occupied (either “never used” or “tombstone”), put the key there (the slot is now occupied).
// 如果对应的slot是never used或者tombstone，就把key放进去，这个slot就变成occupied了

// If the corresponding slot is already occupied, try the next slot. Repeat trying until you find an unoccupied slot.
// 如果对应的slot是occupied，就往下一个slot找，直到找到一个unoccupied的slot

// 删除工作
//  Deletion works as follows:
//  given a key, use the searching process to locate its slot. (If the key is not in the table, then do nothing.)
// 如果key不在哈希表里，就什么都不做
//  Once you find the key, change the slot status to “tombstone”.
// 如果key在哈希表里，就把这个slot的状态改成tombstone

// You should start your program by initializing an empty hash table.
// 创建空的哈希表

// Your program takes one line as input.
// The input line contains n “modification moves” separated by spaces (1 ≤ n ≤ 26).
// The available modification moves are

// • AWord (Character A followed by a lower-case English word of length at most 10):
// Aapple means insert key apple into the hash table. If apple is already in the table, do nothing.

// • DWord (Character D followed by a lower-case English word of length at most 10):
// Dapple means delete key apple from the hash table. If apple is not in the tree, do nothing.

// At the end, you need to go through the slots from a to z, and output all the keys separated by space. You don’t need to worry about invalid inputs.
// Sample input 1: Aaaa Accc Abbb
// Sample output 1: aaa bbb ccc
// Sample input 2: Abba Aaaa Acca
// Sample output 2: bba aaa cca
// Sample input 3: Abba Aaaa Acca Daaa
// Sample output 3: bba cca

// Basics of the Hash Function:

// A hash function takes an input (or 'message') and returns a fixed-size string of bytes.
// For our purpose, our hash function is going to return an index in the range [0, 25].
// In this problem, our hash function will simply use the last character of a word.
// So, if the last character is 'a', it points to slot 0, if it's 'b', it points to slot 1, and so on up to 'z', which points to slot 25.
// If two words have the same last letter, they will point to the same slot.
// In that case, we use a technique called "linear probing" to find the next available slot.

// How the Hash Function Works:

// For the word "apple", our hash function uses the last character 'e', so it will point to the slot for 'e' which is 4 (assuming a=0, b=1, ..., e=4, ... z=25).

// Searching Logic:

// Compute the hash value (i.e., find which slot it should ideally be in) using the last character of the key.
// Check if the key exists in that slot:
// If the slot status is "never used", the key doesn't exist in the table.
// If the slot status is "occupied" and the key matches the key we are looking for, we found it.
// If the slot status is "occupied" but the key doesn't match or if the slot status is "tombstone", check the next slot (wrap around to the start if needed).
// Repeat until you either find the key or you're sure it doesn't exist.

// Insertion Logic:

// Compute the hash value.
// Check if the key already exists using the searching logic. If it does, don't insert.
// If it doesn't exist, find where to insert:
// If the computed slot is "never used" or "tombstone", insert there.
// If the slot is "occupied", check the next slot.
// Repeat until you find a slot to insert.

// Deletion Logic:

// Use the searching logic to find the key.
// If the key is found, change its status to "tombstone". If it's not found, do nothing.
// The key (pun intended!) to understanding this is realizing how the hash function uses the last character to decide the initial slot, and then how linear probing (checking subsequent slots) is used when there are collisions (when multiple keys hash to the same slot).