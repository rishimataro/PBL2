#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <memory>
using namespace std;

template <class T>
class Node
{
public:
    T* data;
    unique_ptr<Node> next;
    Node* prev;

    Node(T* val);
    ~Node();
};

template <class T>
::Node<T>::Node(T* val) : data(val), next(nullptr), prev(nullptr) {}

template <class T>
::Node<T>::~Node()
{
    delete data; // Giải phóng bộ nhớ của data
}

template <class T>
class LinkedList
{
protected:
    unique_ptr<Node<T>> head;
    Node<T>* tail;
    int count;

public:
    LinkedList();
    LinkedList(const LinkedList<T>& other);
    ~LinkedList();

    bool isEmpty() const;
    void prepend(T* value);
    void append(T* value);
    void insertAt(T* value, int position);
    void removeFront();
    void removeBack();
    void remove(int position);
    void clear();
    void removeIf(const function<bool(const T&)>& predicate);
    T* find(const function<bool(const T&)>& predicate);
    T* get(int index) const;
    T* begin() const;
    T* end() const;
    int size() const;
    void set(int index, T* value);
    void display();
    void forEach(void (*func)(T*));
    bool operator==(const LinkedList<T>& other) const;
    void operator=(const LinkedList<T>& other);
};

template <class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), count(0)
{
    Node<T>* current = other.head.get();
    while (current)
    {
        append(new T(*current->data)); // Sao chép từng phần tử
        current = current->next.get();
    }
}


template <class T>
LinkedList<T>::~LinkedList() { clear(); }

template <class T>
bool LinkedList<T>::isEmpty() const
{
    return head == nullptr;
}

template <class T>
void LinkedList<T>::prepend(T* value)
{
    auto newNode = make_unique<Node<T>>(value);
    if (isEmpty())
    {
        head = move(newNode);
        head->next = nullptr;
        head->prev = nullptr;
        tail = head.get();
    }
    else
    {
        newNode->next = move(head);
        newNode->prev = nullptr;
        head->prev = newNode.get();
        head = move(newNode);
    }
    count++;
}

template <class T>
void LinkedList<T>::append(T* value)
{
    auto newNode = make_unique<Node<T>>(value);
    if (isEmpty())
    {
        head = move(newNode);
        head->next = nullptr;
        head->prev = nullptr;
        tail = head.get();
    }
    else
    {
        tail->next = move(newNode);
        tail->next->prev = tail;
        tail = tail->next.get();
    }
    count++;
}

template <class T>
void LinkedList<T>::insertAt(T* value, int position)
{
    if (position < 0 || position > count)
        return;

    if (position == 0)
    {
        prepend(value);
    }
    else if (position == count)
    {
        append(value);
    }
    else
    {
        Node<T>* current = head.get();
        for (int i = 0; i < position - 1; i++)
        {
            current = current->next.get();
        }

        auto newNode = make_unique<Node<T>>(value);
        Node<T>* nextNode = current->next.get();
        current->next = move(newNode);
        current->next->prev = current;
        current->next->next = move(nextNode->prev->next);
        count++;
    }
}

template <class T>
void LinkedList<T>::removeFront()
{
    if (isEmpty())
        return;

    if (head.get() == tail)
    {
        head.reset();
        tail = nullptr;
    }
    else
    {
        head = move(head->next);
        head->prev = nullptr;
    }
    count--;
}

template <class T>
void LinkedList<T>::removeBack()
{
    if (isEmpty())
        return;

    if (head.get() == tail)
    {
        head.reset();
        tail = nullptr;
    }
    else
    {
        Node<T>* temp = tail;
        tail = tail->prev;
        tail->next.reset();  // Sử dụng unique_ptr để tự động giải phóng bộ nhớ của tail->next
        // Không cần gọi delete temp nữa vì unique_ptr đã tự xử lý việc giải phóng
    }
    count--;
}

template <class T>
void LinkedList<T>::remove(int position)
{
    if (isEmpty() || position < 0 || position >= count)
        return;

    if (position == 0)
    {
        removeFront();
    }
    else if (position == count - 1)
    {
        removeBack();
    }
    else
    {
        Node<T>* current = head.get();
        for (int i = 0; i < position; i++)
        {
            current = current->next.get();
        }

        Node<T>* nextNode = current->next.get();
        Node<T>* prevNode = current->prev;

        prevNode->next = move(current->next);
        if (nextNode)
        {
            nextNode->prev = prevNode;
        }
        count--;
    }
}

template <class T>
void LinkedList<T>::clear()
{
    while (!isEmpty())
    {
        removeFront();
    }
}

template <class T>
void LinkedList<T>::removeIf(const function<bool(const T&)>& predicate)
{
    Node<T>* current = head.get();
    while (current)
    {
        if (predicate(*current->data))
        {
            Node<T>* toRemove = current;
            if (toRemove->prev)
            {
                toRemove->prev->next = move(toRemove->next);
                if (toRemove->prev->next)
                {
                    toRemove->prev->next->prev = toRemove->prev;
                }
            }
            else
            {
                head = move(toRemove->next);
                if (head)
                    head->prev = nullptr;
            }
            current = toRemove->next.get();
            if (toRemove == tail)
            {
                tail = toRemove->prev;
            }
            continue;
        }
        current = current->next.get();
    }
}

template <class T>
T* LinkedList<T>::find(const function<bool(const T&)>& predicate)
{
    Node<T>* current = head.get();
    while (current)
    {
        if (predicate(*current->data))
        {
            return current->data;
        }
        current = current->next.get();
    }
    return nullptr;
}

template <class T>
T* LinkedList<T>::get(int index) const
{
    if (isEmpty() || index < 0 || index >= count)
    {
        throw out_of_range("Index out of range");
    }

    Node<T>* current = head.get();
    for (int i = 0; i < index; i++)
    {
        current = current->next.get();
    }

    return current->data;
}

template <class T>
T* LinkedList<T>::begin() const
{
    return head ? head->data : nullptr;
}

template <class T>
T* LinkedList<T>::end() const
{
    return tail ? tail->data : nullptr;
}

template <class T>
void LinkedList<T>::set(int index, T* value)
{
    if (isEmpty() || index < 0 || index >= count)
    {
        throw out_of_range("Index out of range");
    }

    Node<T>* current = head.get();
    for (int i = 0; i < index; i++)
    {
        current = current->next.get();
    }

    delete current->data; // Giải phóng bộ nhớ trước đó
    current->data = value;
}

template <class T>
int LinkedList<T>::size() const
{
    return count;
}

template <class T>
void LinkedList<T>::display()
{
    if (isEmpty())
    {
        cout << "Danh sach rong!" << endl;
        return;
    }

    Node<T>* current = head.get();
    while (current)
    {
        cout << *current->data << " ";
        current = current->next.get();
    }
    cout << endl;
}

template <class T>
void LinkedList<T>::forEach(void (*func)(T*))
{
    if (isEmpty())
        return;

    Node<T>* current = head.get();
    while (current)
    {
        func(current->data);
        current = current->next.get();
    }
}
template <class T>
bool LinkedList<T>::operator==(const LinkedList<T>& other) const
{
    // Kiểm tra xem cả hai danh sách có cùng kích thước không
    if (count != other.count)
        return false;

    Node<T>* current1 = head.get();
    Node<T>* current2 = other.head.get();

    // So sánh từng phần tử trong danh sách
    while (current1 && current2)
    {
        if (*current1->data != *current2->data) // So sánh dữ liệu
            return false;

        current1 = current1->next.get();
        current2 = current2->next.get();
    }

    return true; // Nếu tất cả các phần tử đều giống nhau
}

template <class T>
void LinkedList<T>::operator=(const LinkedList<T>& other)
{
    if (this == &other) // Kiểm tra xem có phải là gán cho chính nó không
        return;

    clear(); // Xóa sạch danh sách hiện tại

    Node<T>* current = other.head.get(); // Bắt đầu từ đầu danh sách khác
    while (current)
    {
        // Sao chép từng giá trị từ danh sách khác và thêm vào danh sách này
        append(new T(*current->data));
        current = current->next.get(); // Di chuyển đến nút tiếp theo
    }
}
