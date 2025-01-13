// Problem Statement:
// Implement a hash table using linear probing for collision resolution.
// The hash table should support the following operations:
// 1. Insert a key-value pair.
// 2. Search for a value by its key.
// 3. Remove a key-value pair.
// 4. Display the contents of the hash table.
// 
// Key Features:
// - Use a simple hash function (key % capacity).
// - Handle collisions using linear probing.
// - Ensure the hash table supports basic operations efficiently.

#include <iostream>
#include <string>

class HashTable {
private:
    struct Entry {
        int key;
        std::string value;
        bool isOccupied;

        Entry() : key(0), value(""), isOccupied(false) {}
    };

    Entry* table;
    int capacity;
    int size;

    int hashFunction(int key) {
        return key % capacity;
    }

public:
    HashTable(int capacity) : capacity(capacity), size(0) {
        table = new Entry[capacity];
    }

    ~HashTable() {
        delete[] table;
    }

    bool insert(int key, const std::string &value) {
        if (size == capacity) {
            std::cout << "Hash table is full!\n";
            return false;
        }

        int index = hashFunction(key);
        int originalIndex = index;
        
        while (table[index].isOccupied && table[index].key != key) {
            index = (index + 1) % capacity;
            if (index == originalIndex) { // Full cycle
                std::cout << "No available slots!\n";
                return false;
            }
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        size++;
        return true;
    }

    bool search(int key, std::string &value) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                value = table[index].value;
                return true;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                break;
            }
        }
        return false;
    }

    bool remove(int key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                table[index].isOccupied = false;
                size--;
                return true;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                break;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < capacity; ++i) {
            if (table[i].isOccupied) {
                std::cout << "Index " << i << ": Key=" << table[i].key << ", Value=" << table[i].value << "\n";
            } else {
                std::cout << "Index " << i << ": Empty\n";
            }
        }
    }
};

int main() {
    HashTable hashTable(10);

    hashTable.insert(1, "Value1");
    hashTable.insert(12, "Value12"); // Collision with key 1
    hashTable.insert(23, "Value23"); // Collision with keys 1 and 12

    hashTable.display();

    std::string value;
    if (hashTable.search(12, value)) {
        std::cout << "Found key 12: " << value << "\n";
    } else {
        std::cout << "Key 12 not found!\n";
    }

    hashTable.remove(12);
    hashTable.display();

    if (hashTable.search(12, value)) {
        std::cout << "Found key 12: " << value << "\n";
    } else {
        std::cout << "Key 12 not found!\n";
    }

    return 0;
}
