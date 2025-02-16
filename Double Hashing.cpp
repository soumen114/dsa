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

    int hash1(int key) {
        return key % capacity;
    }

    int hash2(int key) {
        return 1 + (key % (capacity - 1)); // Secondary hash function
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

        int index = hash1(key);
        int stepSize = hash2(key);
        int i = 0;

        while (table[(index + i * stepSize) % capacity].isOccupied) {
            if (table[(index + i * stepSize) % capacity].key == key) {
                std::cout << "Key already exists!\n";
                return false;
            }
            i++;
            if (i == capacity) { // Full cycle
                std::cout << "No available slots!\n";
                return false;
            }
        }

        table[(index + i * stepSize) % capacity].key = key;
        table[(index + i * stepSize) % capacity].value = value;
        table[(index + i * stepSize) % capacity].isOccupied = true;
        size++;
        return true;
    }

    bool search(int key, std::string& value) {
        int index = hash1(key);
        int stepSize = hash2(key);
        int i = 0;

        while (table[(index + i * stepSize) % capacity].isOccupied) {
            if (table[(index + i * stepSize) % capacity].key == key) {
                value = table[(index + i * stepSize) % capacity].value;
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
        int index = hash1(key);
        int stepSize = hash2(key);
        int i = 0;

        while (table[(index + i * stepSize) % capacity].isOccupied) {
            if (table[(index + i * stepSize) % capacity].key == key) {
                table[(index + i * stepSize) % capacity].isOccupied = false;
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
    int capacity;
    std::cout << "Enter hash table capacity: ";
    std::cin >> capacity;
    HashTable hashTable(capacity);

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Search\n";
        std::cout << "3. Remove\n";
        std::cout << "4. Display\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) { // Insert
            int key;
            std::string value;
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cout << "Enter value: ";
            std::cin.ignore();
            std::getline(std::cin, value);
            hashTable.insert(key, value);

        } else if (choice == 2) { // Search
            int key;
            std::string value;
            std::cout << "Enter key to search: ";
            std::cin >> key;
            if (hashTable.search(key, value)) {
                std::cout << "Found key " << key << ": " << value << "\n";
            } else {
                std::cout << "Key " << key << " not found!\n";
            }

        } else if (choice == 3) { // Remove
            int key;
            std::cout << "Enter key to remove: ";
            std::cin >> key;
            if (hashTable.remove(key)) {
                std::cout << "Key " << key << " removed successfully.\n";
            } else {
                std::cout << "Key " << key << " not found!\n";
            }

        } else if (choice == 4) { // Display
            hashTable.display();

        } else if (choice == 5) { // Exit
            break;

        } else {
            std::cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
