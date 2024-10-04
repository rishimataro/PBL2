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
    private:
        Node<T>* head;
        int count; // caching the size of the list
    public:
        LinkedList();
        ~LinkedList();

        // Kiểm tra danh sách rỗng
        bool isEmpty();

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
        T get(int index);
        // Lấy kích thước
        int size();

        // In danh sách
        void display();
};

template<class T>
LinkedList<T>::LinkedList() : head(NULL), count(0) { }

template<class T>
LinkedList<T>::~LinkedList() { clear(); }

// Kiểm tra danh sách rỗng
template<class T>
bool LinkedList<T>::isEmpty() {
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
T LinkedList<T>::get(int index) { 
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

// Lấy kích thước
template<class T>
int LinkedList<T>::size() { 
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

/* int main() {
    LinkedList<string> list;

    // Thêm các chuỗi vào danh sách
    list.append("apple");
    list.display();  // Output: apple

    list.prepend("orange");
    list.display();  // Output: orange apple

    list.append("banana");
    list.display();  // Output: orange apple banana

    // Thêm "grape" vào vị trí thứ 2 (giữa "orange" và "apple")
    list.insertAt("grape", 2);
    list.display();  // Output: orange apple grape banana

    // Xóa phần tử ở vị trí thứ 2 (giá trị "grape")
    list.remove(2);
    list.display();  // Output: orange apple banana

    // Tìm vị trí của "apple"
    int pos = list.find("apple");
    cout << "Vi tri cua 'apple': " << pos << endl;  // Output: 1

    // Lấy giá trị tại vị trí thứ 0 (giá trị "orange")
    cout << "Gia tri tai vi tri 0: " << list.get(0) << endl;  // Output: orange

    string str;
    cout << "Nhap chuoi: "; getline(cin, str);
    list.append(str);
    list.display();

    LinkedList<int> list;

    list.append(10); 
    list.display();

    list.prepend(5); 
    list.display();

    list.append(15); 
    list.display();

    list.insertAt(12, 1); 
    list.display();

    int n;
    cout << "Nhap n: "; cin >> n;
    if(list.find(n) == -1) cout << "Khong co!" << endl;
    else cout << list.find(n) << endl; 

    list.prepend(74); 
    list.prepend(-8); 
    list.prepend(0); 
    list.prepend(54); 
    list.prepend(17); 
    
    list.display();
    list.removeFront();
    list.display();

    list.removeBack();
    list.display();

    cout << list.get(1) << ", " << list.get(2) << endl;
    list.remove(1); 
    list.display();

    cout << list.get(1) << ", " << list.get(2) << endl;

    list.clear(); 
    list.display();

    return 0;
} */