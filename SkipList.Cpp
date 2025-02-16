#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

class Node {
public:
    int key;
    Node** forward;
    Node(int key, int level);
};

Node::Node(int key, int level) {
    this->key = key;
    forward = new Node*[level + 1];
    for (int i = 0; i <= level; i++) {
        forward[i] = nullptr;
    }
}

class SkipList {
    int maxLevel;
    float p;
    int level;
    Node* header;

public:
    SkipList(int maxLevel, float p);
    int randomLevel();
    void insert(int key);
    void erase(int key);
    bool search(int key);
    void display();
};

SkipList::SkipList(int maxLevel, float p) {
    this->maxLevel = maxLevel;
    this->p = p;
    level = 0;
    header = new Node(-1, maxLevel);
}

int SkipList::randomLevel() {
    int lvl = 0;
    while (((float)rand() / RAND_MAX) < p && lvl < maxLevel) {
        lvl++;
    }
    return lvl;
}

void SkipList::insert(int key) {
    Node* update[maxLevel + 1];
    Node* current = header;
    
    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    if (current == nullptr || current->key != key) {
        int randLvl = randomLevel();
        if (randLvl > level) {
            for (int i = level + 1; i <= randLvl; i++) {
                update[i] = header;
            }
            level = randLvl;
        }
        
        Node* newNode = new Node(key, randLvl);
        for (int i = 0; i <= randLvl; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

void SkipList::erase(int key) {
    Node* update[maxLevel + 1];
    Node* current = header;
    
    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    if (current != nullptr && current->key == key) {
        for (int i = 0; i <= level; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }
        delete current;
        while (level > 0 && header->forward[level] == nullptr) {
            level--;
        }
    }
}

bool SkipList::search(int key) {
    Node* current = header;
    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    return (current != nullptr && current->key == key);
}

void SkipList::display() {
    for (int i = 0; i <= level; i++) {
        Node* node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != nullptr) {
            cout << node->key << " ";
            node = node->forward[i];
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    SkipList skipList(4, 0.5);
    int choice, key;
    
    do {
        cout << "\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                skipList.insert(key);
                break;
            case 2:
                cout << "Enter key to search: ";
                cin >> key;
                cout << (skipList.search(key) ? "Found" : "Not Found") << endl;
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                skipList.erase(key);
                break;
            case 4:
                skipList.display();
                break;
        }
    } while (choice != 5);
    
    return 0;
}
