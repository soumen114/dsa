#include <iostream>
#include <string>

class HashTable {
private:
    struct Entry {
        int key;
        std::string value;
        bool isOccupied;
        bool isDeleted;

        Entry() : key(0), value(""), isOccupied(false), isDeleted(false) {}
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

        while (i < capacity) {
            int newIndex = (index + i * i) % capacity;
            if (!table[newIndex].isOccupied || table[newIndex].isDeleted) {
                table[newIndex].key = key;
                table[newIndex].value = value;
                table[newIndex].isOccupied = true;
                table[newIndex].isDeleted = false;
                size++;
                return true;
            } else if (table[newIndex].key == key) {
                std::cout << "Key already exists!\n";
                return false;
            }
            i++;
        }

        std::cout << "No available slots!\n";
        return false;
    }

    bool search(int key, std::string& value) {
        int index = hashFunction(key);
        int i = 0;

        while (i < capacity) {
            int newIndex = (index + i * i) % capacity;
            if (!table[newIndex].isOccupied && !table[newIndex].isDeleted) {
                break;
            }
            if (table[newIndex].isOccupied && table[newIndex].key == key) {
                value = table[newIndex].value;
                return true;
            }
            i++;
        }
        return false;
    }

    bool remove(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (i < capacity) {
            int newIndex = (index + i * i) % capacity;
            if (!table[newIndex].isOccupied && !table[newIndex].isDeleted) {
                break;
            }
            if (table[newIndex].isOccupied && table[newIndex].key == key) {
                table[newIndex].isOccupied = false;
                table[newIndex].isDeleted = true;
                size--;
                return true;
            }
            i++;
        }
        return false;
    }

    void display() {
        std::cout << "\nHash Table:\n";
        for (int i = 0; i < capacity; ++i) {
            if (table[i].isOccupied) {
                std::cout << "Index " << i << ": Key=" << table[i].key
                          << ", Value=" << table[i].value << "\n";
            } else if (table[i].isDeleted) {
                std::cout << "Index " << i << ": Deleted\n";
            } else {
                std::cout << "Index " << i << ": Empty\n";
            }
        }
    }
};

int main() {
    int capacity;
    std::cout << "Enter the capacity of the hash table: ";
    std::cin >> capacity;

    HashTable hashTable(capacity);

    while (true) {
        std::cout << "\nChoose an operation:\n";
        std::cout << "1. Insert\n2. Search\n3. Remove\n4. Display\n5. Exit\n";
        std::cout << "Enter your choice: ";
        
        int choice, key;
        std::string value;
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter key and value: ";
                std::cin >> key >> value;
                if (hashTable.insert(key, value)) {
                    std::cout << "Inserted successfully!\n";
                }
                break;

            case 2:
                std::cout << "Enter key to search: ";
                std::cin >> key;
                if (hashTable.search(key, value)) {
                    std::cout << "Found key " << key << ": " << value << "\n";
                } else {
                    std::cout << "Key not found!\n";
                }
                break;

            case 3:
                std::cout << "Enter key to remove: ";
                std::cin >> key;
                if (hashTable.remove(key)) {
                    std::cout << "Key removed successfully!\n";
                } else {
                    std::cout << "Key not found!\n";
                }
                break;

            case 4:
                hashTable.display();
                break;

            case 5:
                std::cout << "Exiting program.\n";
                return 0;

            default:
                std::cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
