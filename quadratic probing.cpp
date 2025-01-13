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

    bool insert(int key, const std::string& value) {
        if (size == capacity) {
            std::cout << "Hash table is full!\n";
            return false;
        }

        int index = hashFunction(key);
        int i = 0;

        while (table[(index + i * i) % capacity].isOccupied) {
            if (table[(index + i * i) % capacity].key == key) {
                std::cout << "Key already exists!\n";
                return false;
            }
            i++;
            if (i == capacity) { // Full cycle
                std::cout << "No available slots!\n";
                return false;
            }
        }

        table[(index + i * i) % capacity].key = key;
        table[(index + i * i) % capacity].value = value;
        table[(index + i * i) % capacity].isOccupied = true;
        size++;
        return true;
    }

    bool search(int key, std::string& value) {
        int index = hashFunction(key);
        int i = 0;

        while (table[(index + i * i) % capacity].isOccupied) {
            if (table[(index + i * i) % capacity].key == key) {
                value = table[(index + i * i) % capacity].value;
                return true;
            }
            i++;
            if (i == capacity) {
                break;
            }
        }
        return false;
    }

    bool remove(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (table[(index + i * i) % capacity].isOccupied) {
            if (table[(index + i * i) % capacity].key == key) {
                table[(index + i * i) % capacity].isOccupied = false;
                size--;
                return true;
            }
            i++;
            if (i == capacity) {
                break;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < capacity; ++i) {
            if (table[i].isOccupied) {
                std::cout << "Index " << i << ": Key=" << table[i].key
                          << ", Value=" << table[i].value << "\n";
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
