# Double Linked List Implementation

## Overview
This project implements a **Double Linked List** in C++ with comprehensive functionality. A double linked list allows traversal in both directions, making it a versatile data structure for managing dynamic data. The program provides a menu-driven interface for operations like inserting, deleting, searching, and traversing elements, as well as conducting performance tests.

## Features

### Core Functionalities
1. **Search for an Element**: Locate an element by its key.
2. **Insert at Head**: Add a new element to the beginning of the list.
3. **Insert After an Element**: Insert a new element after a specific existing element.
4. **Insert at Tail**: Add a new element to the end of the list.
5. **Delete an Element**: Remove an element by its key.
6. **Traverse from Head to Tail**: Print all elements starting from the head.
7. **Traverse from Tail to Head**: Print all elements starting from the tail.
8. **Performance Testing**:
   - Measure the time to insert elements at the head of the list.
   - Measure the time to calculate the sum of all keys in the list.
   - Compare the performance of linked list operations with equivalent array operations.

### Additional Utilities
- **Dynamic Memory Management**: Automatically allocate and deallocate memory for list elements.
- **Array Simulation**: Compare list operations with array operations for better understanding of performance differences.

## Usage

### Menu Options
When you run the program, you will see the following menu:
```
Double Linked List - Choose an option:

1) Search for an element
2) Insert at head
3) Insert after an element
4) Insert at tail
5) Delete an element
6) Print from head to tail
7) Print from tail to head
8) Performance test
9) Exit
```

### Example Workflow
1. **Insert Elements**:
   - Choose option `2` to insert elements at the head.
   - Choose option `4` to insert elements at the tail.
   - Use option `3` to insert elements after a specific key.
2. **Search and Delete**:
   - Use option `1` to search for an element.
   - Use option `5` to delete an element by key.
3. **Traverse**:
   - Option `6` prints the list from head to tail.
   - Option `7` prints the list from tail to head.
4. **Performance Test**:
   - Select option `8` and input the number of elements for testing.
   - Compare insertion and summation operations between the linked list and arrays.
5. **Exit**:
   - Use option `9` to exit the program.

## Code Explanation

### Data Structure
```cpp
struct Element {
    int key;
    Element* prev, * next;
};
```
Each node contains:
- `key`: The value stored in the node.
- `prev`: Pointer to the previous node.
- `next`: Pointer to the next node.

### Core Functions

#### Search
```cpp
Element* search(int key) {
    Element* temp = head;
    while (temp != nullptr && temp->key != key) {
        temp = temp->next;
    }
    return temp;
}
```
Searches for an element by its key, returning a pointer to the node if found.

#### Insert
- **At Head**:
```cpp
void insertHead(int key) {
    Element* newElement = new Element{ key, nullptr, head };
    if (head != nullptr) {
        head->prev = newElement;
    } else {
        tail = newElement;
    }
    head = newElement;
}
```
Adds a new element to the beginning of the list.

- **At Tail**:
```cpp
void insertTail(int key) {
    Element* newElement = new Element{ key, tail, nullptr };
    if (tail != nullptr) {
        tail->next = newElement;
    } else {
        head = newElement;
    }
    tail = newElement;
}
```
Adds a new element to the end of the list.

#### Delete
```cpp
void deleteElement(int key) {
    Element* temp = search(key);
    if (temp == nullptr) {
        cout << "Error: Element not found!\n";
        return;
    }
    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;
    }
    delete temp;
}
```
Removes an element by updating pointers and freeing memory.

#### Traversal
- **From Head to Tail**:
```cpp
void printFromHead() {
    Element* temp = head;
    while (temp != nullptr) {
        cout << temp->key << " ";
        temp = temp->next;
    }
    cout << endl;
}
```
- **From Tail to Head**:
```cpp
void printFromTail() {
    Element* temp = tail;
    while (temp != nullptr) {
        cout << temp->key << " ";
        temp = temp->prev;
    }
    cout << endl;
}
```

### Performance Testing

#### Insert and Summation
- **Insert N Elements**:
```cpp
void insertNElementsAtHead(int N) {
    head = tail = nullptr;
    auto start = chrono::steady_clock::now();
    for (int i = 1; i <= N; i++) {
        insertHead(i);
    }
    auto end = chrono::steady_clock::now();
    cout << "Time to insert " << N << " elements at head: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << "µs.\n";
}
```
- **Sum Keys**:
```cpp
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
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << "µs.\n";
}
```

## Requirements
- **Compiler**: C++ compiler supporting C++11 or later.
- **Operating System**: Any OS capable of running compiled C++ programs.

## How to Run
1. Compile the program using a C++ compiler:
   ```bash
   g++ double_linked_list.cpp -o double_linked_list
   ```
2. Run the compiled executable:
   ```bash
   ./double_linked_list
   ```
3. Follow the menu options to perform operations on the double linked list.

## Conclusion
This double linked list implementation demonstrates the power and flexibility of linked data structures. By including features like bidirectional traversal and performance testing, this project serves as an educational and practical tool for understanding linked list operations.

