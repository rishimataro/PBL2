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
