// #include <Template/LinkedList.hpp>
// #include "../Library/Header.h"
#include <iostream>
#include <string>
using namespace std;

template<class T>
class Node
{
    public:
        T data;
        Node *next;
        Node *prev;

        Node(T val);
};

template<class T>
Node<T>::Node(T val) : data(val), next(NULL), prev(NULL) { }

template<class T>
class LinkedList
{
    protected:
        Node<T>* head;
        int count;
    public:
        LinkedList();
        ~LinkedList();

        // Kiểm tra danh sách rỗng
        bool isEmpty() const;

        // Thêm Node: đầu danh sách
        void prepend(T value);
        // Thêm Node: cuối danh sách
        void append(T value);
        // Thêm Node: tại vị trí pos
        void insertAt(T value, int position);

        // Xóa Node: đầu danh sách
        void removeFront();
        // Xóa Node: cuối danh sách
        void removeBack();
        // Xóa Node: tại vị trí pos
        void remove(int position);
        // Xóa toàn bộ danh sách
        void clear();

        // Tìm Node: trả về vị trí tìm thấy, ngược lại trả về -1
        int find(T value);

        // Lấy Node: lấy giá trị tại vị trí index
        T get(int index) const;
        T begin() const;
        T end() const;

        // Lấy kích thước
        int size() const;

        // Cập nhật Node
        void set(int index, T value);

        // In danh sách
        void display();
};

template<class T>
LinkedList<T>::LinkedList() : head(NULL), count(0) { }

template<class T>
LinkedList<T>::~LinkedList() { clear(); }

// Kiểm tra danh sách rỗng
template<class T>
bool LinkedList<T>::isEmpty() const {
    return head == NULL;
}

// Thêm Node: đầu danh sách
template<class T>
void LinkedList<T>::prepend(T value) { 
    Node<T>* newNode = new Node<T>(value);
    if(isEmpty()) {
        head = newNode;
        head->next = head;
        head->prev = head;
    }
    else {
        Node<T>* tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;
    }
    count++;
}

// Thêm Node: cuối danh sách
template<class T>
void LinkedList<T>::append(T value) { 
    Node<T>* newNode = new Node<T>(value);
    if(isEmpty()) {
        head = newNode;
        head->next = head;
        head->prev = head;
    }
    else{
        Node<T>* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
    count++;
}

// Thêm Node: tại vị trí pos
template<class T>
void LinkedList<T>::insertAt(T value, int position) { 
    if (position < 0 || position > count) return;

    if (position == 0) {
        prepend(value);
    } 
    else if (position == count) {
        append(value);
    }
    else {
        Node<T>* newNode = new Node<T>(value);
        Node<T>* current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        Node<T>* nextNode = current->next;
        current->next = newNode;
        newNode->prev = current;
        newNode->next = nextNode;
        nextNode->prev = newNode;
        count++;
    }
}

// Xóa Node: đầu danh sách
template<class T>
void LinkedList<T>::removeFront() { 
    if(isEmpty()) return;

    Node<T>* tail = head->prev;
    if(head == tail) {
        delete head;
        head = NULL;
    }
    else {
        Node<T>* temp = head;
        head = head->next;
        head->prev = tail;
        tail->next = head;
        delete temp;
    }
    count--;
}

// Xóa Node: cuối danh sách
template<class T>
void LinkedList<T>::removeBack() { 
    if(isEmpty()) return;

    Node<T>* tail = head->prev;
    if(head == tail) {
        delete head;
        head = NULL;
    }
    else {
        Node<T>* temp = tail;
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        delete temp;
    }
    count--;
}

// Xóa Node: tại vị trí pos
template<class T>
void LinkedList<T>::remove(int position) { 
    if (isEmpty() || position < 0 || position >= count) return;

    if(position == 0) {
        removeFront();
    }
    else if(position == count - 1) {
        removeBack();
    }
    else {
        Node<T>* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        count--;
    }
}

// Xóa toàn bộ danh sách
template<class T>
void LinkedList<T>::clear() { 
    while(!isEmpty()) {
        removeFront();
    }
}

// Tìm Node: trả về vị trí tìm thấy, ngược lại trả về -1
template<class T>
int LinkedList<T>::find(T value) { 
    if(isEmpty()) return -1;

    Node<T>* current = head;
    int index = 0;
    do
    {
        if(current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    } while (current != head);

    return -1;
}

// Lấy Node: lấy giá trị tại vị trí index
template<class T>
T LinkedList<T>::get(int index) const { 
    if (isEmpty() || index < 0 || index >= count) {
            throw out_of_range("Index out of range");
    }

    Node<T>* current = head;
    int idx = 0;
    do {
        if(idx == index) { return current->data; }
        current = current->next;
        idx++;
    } while(current != head);

    return T();
}

template<class T>
T LinkedList<T>::begin() const {
    return head->data;
}

template<class T>   
T LinkedList<T>::end() const {
    return head->prev->data;
}

template<class T>
void LinkedList<T>::set(int index, T value) {
    if (isEmpty() || index < 0 || index >= count) {
        throw out_of_range("Index out of range");
    }

    Node<T>* current = head;
    int idx = 0;
    do {
        if (idx == index) {
            current->data = value;
            return;
        }
        current = current->next;
        idx++;
    } while (current != head);
}

// Lấy kích thước
template<class T>
int LinkedList<T>::size() const { 
    return count;
}

// In danh sách
template<class T>
void LinkedList<T>::display() { 
    if(isEmpty()) {
        cout << "Danh sach rong!" << endl;
        return;
    }

    Node<T>* current = head;
    do
    {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}