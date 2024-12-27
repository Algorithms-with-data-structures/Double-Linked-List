// DOUBLE LINKED LIST

#include <iostream>
#include <chrono>
using namespace std;

struct Element {
	int key;
	Element* prev, * next;
};

Element* head = nullptr;
Element* tail = nullptr;

void showMenu() {
    cout << "\n";
    cout << "Double Linked List - Choose an option:\n\n";
    cout << "1) Search for an element\n";
    cout << "2) Insert at head\n";
    cout << "3) Insert after an element\n";
    cout << "4) Insert at tail\n";
    cout << "5) Delete an element\n";
    cout << "6) Print from head to tail\n";
    cout << "7) Print from tail to head\n";
    cout << "8) Performance test\n";
    cout << "9) Exit\n\n";
    cout << "Choose: ";
}

Element* search(int key) {
    Element* temp = head;
    while (temp != nullptr && temp->key != key) {
        temp = temp->next;
    }
    return temp;
}

void insertHead(int key) {
    Element* newElement = new Element{ key, nullptr, head };

    if (head != nullptr) {
        head->prev = newElement;
    }
    else {
        tail = newElement;
    }
    head = newElement;
}

void insertAfter(Element* existing, Element* newElement) {
    if (existing == nullptr) {
        cout << "Error: Existing element not found!\n";
        delete newElement;
        return;
    }

    newElement->prev = existing;
    newElement->next = existing->next;

    if (existing->next != nullptr) {
        existing->next->prev = newElement;
    }
    else {
        tail = newElement;
    }

    existing->next = newElement;
}

void insertAfterElement(int existingKey, int newKey) {
    Element* existing = search(existingKey);
    Element* newElement = new Element{ newKey, nullptr, nullptr };
    insertAfter(existing, newElement);
}

void insertTail(int key) {
    Element* newElement = new Element{ key, tail, nullptr };

    if (tail != nullptr) {
        tail->next = newElement;
    }
    else {
        head = newElement;
    }
    tail = newElement;
}

void deleteElement(int key) {
    Element* temp = search(key);
    if (temp == nullptr) {
        cout << "Error: Element not found!\n";
        return;
    }

    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    else {
        head = temp->next;
    }

    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    else {
        tail = temp->prev;
    }

    delete temp;
}

void printFromHead() {
    Element* temp = head;
    while (temp != nullptr) {
        cout << temp->key << " ";
        temp = temp->next;
    }
    cout << endl;
}

void printFromTail() {
    Element* temp = tail;
    while (temp != nullptr) {
        cout << temp->key << " ";
        temp = temp->prev;
    }
    cout << endl;
}

void insertNElementsAtHead(int N) {
    head = tail = nullptr;
    auto start = chrono::steady_clock::now();

    for (int i = 1; i <= N; i++) {
        insertHead(i);
    }

    auto end = chrono::steady_clock::now();
    cout << "Time to insert " << N << " elements at head: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count() << "μs.\n";
}

void sumKeysInList(int N) {
    Element* temp = head;
    long long sum = 0;

    auto start = chrono::steady_clock::now();
    while (temp != nullptr) {
        sum += temp->key;
        temp = temp->next;
    }
    auto end = chrono::steady_clock::now();

    cout << "Time to calculate sum of " << N << " elements in list: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count() << "μs.\n";
}

void shiftArrayRight(int* arr, int size) {
    for (int i = size - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
}

int* createArrayWithHeadInsert(int size) {
    int* arr = new int[size]();

    auto start = chrono::steady_clock::now();
    for (int i = 1; i < size; i++) {
        shiftArrayRight(arr, size);
        arr[0] = i;
    }
    auto end = chrono::steady_clock::now();

    cout << "Time to insert " << size << " values at the head of the array: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count() << "μs.\n";

    return arr;
}

void sumKeysInArray(int* arr, int size) {
    long long sum = 0;

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    auto end = chrono::steady_clock::now();

    cout << "Time to calculate sum of " << size << " values in array: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count() << "μs.\n";

    delete[] arr;
}

void createArrayWithTailInsert(int size) {
    int* arr = new int[size];

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    auto end = chrono::steady_clock::now();

    cout << "Time to insert " << size << " values at the tail of the array: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count() << "μs.\n";

    delete[] arr;
}

void testPerformance(int size) {
    insertNElementsAtHead(size);
    sumKeysInList(size);

    int* arr = createArrayWithHeadInsert(size);
    sumKeysInArray(arr, size);

    createArrayWithTailInsert(size);
}

int main() {
    bool running = true;

    while (running) {
        int choice, key, existingKey, size;
        showMenu();
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            cout << "Enter key to search: ";
            cin >> key;
            if (search(key)) {
                cout << "Element exists in the list.\n";
            }
            else {
                cout << "Element does not exist in the list.\n";
            }
            break;
        case 2:
            cout << "Enter key to insert at head: ";
            cin >> key;
            insertHead(key);
            break;
        case 3:
            cout << "Enter key to insert after: ";
            cin >> existingKey;
            if (!search(existingKey)) {
                cout << "Element does not exist. Try again.\n";
                break;
            }
            cout << "Enter new key: ";
            cin >> key;
            insertAfterElement(existingKey, key);
            break;
        case 4:
            cout << "Enter key to insert at tail: ";
            cin >> key;
            insertTail(key);
            break;
        case 5:
            cout << "Enter key to delete: ";
            cin >> key;
            deleteElement(key);
            break;
        case 6:
            printFromHead();
            break;
        case 7:
            printFromTail();
            break;
        case 8:
            cout << "Enter number of elements for performance test: ";
            cin >> size;
            testPerformance(size);
            break;
        case 9:
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}