#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <utility>

template <typename Key, typename Value>
class Map {
private:
    enum Color { RED, BLACK };

    struct Node {
        Key key;
        Value value;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Key& k, const Value& v, Color c, Node* p = nullptr)
            : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(p) {}
    };

    Node* root;

    void rotateLeft(Node*& node);
    void rotateRight(Node*& node);
    void insertFixup(Node*& node);
    void deleteFixup(Node*& node);
    Node* findNode(const Key& key) const;
    void clearTree(Node* node);

public:
    Map();
    ~Map();

    void insert(const Key& key, const Value& value);
    void remove(const Key& key);
    Value* find(const Key& key) const;
    void clear();

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        bool operator!=(const Iterator& other) const { return current != other.current; }
        std::pair<Key, Value> operator*() const { return {current->key, current->value}; }
        Iterator& operator++(); // Move to next element
    };

    Iterator begin() const;
    Iterator end() const;
};

#include "../src/Template/Map.tpp"
#endif
