#include <stdexcept>
#include "Template/Map.hpp"
template <typename Key, typename Value>
Map<Key, Value>::Map() : root(nullptr) {}

template <typename Key, typename Value>
Map<Key, Value>::~Map() {
    clear();
}

template <typename Key, typename Value>
void Map<Key, Value>::rotateLeft(Node*& node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left) rightChild->left->parent = node;
    rightChild->parent = node->parent;
    if (!node->parent)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;
    rightChild->left = node;
    node->parent = rightChild;
}

template <typename Key, typename Value>
void Map<Key, Value>::rotateRight(Node*& node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right) leftChild->right->parent = node;
    leftChild->parent = node->parent;
    if (!node->parent)
        root = leftChild;
    else if (node == node->parent->right)
        node->parent->right = leftChild;
    else
        node->parent->left = leftChild;
    leftChild->right = node;
    node->parent = leftChild;
}

template <typename Key, typename Value>
void Map<Key, Value>::insert(const Key& key, const Value& value) {
    Node* newNode = new Node(key, value, RED);
    Node* parent = nullptr;
    Node* current = root;

    while (current) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else {
            current->value = value;
            delete newNode;
            return;
        }
    }

    newNode->parent = parent;
    if (!parent)
        root = newNode;
    else if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    insertFixup(newNode);
}

template <typename Key, typename Value>
void Map<Key, Value>::insertFixup(Node*& node) {
    while (node->parent && node->parent->color == RED) {
        Node* grandparent = node->parent->parent;
        if (node->parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }
                node->parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(grandparent);
            }
        } else {
            Node* uncle = grandparent->left;
            if (uncle && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(grandparent);
            }
        }
    }
    root->color = BLACK;
}

template <typename Key, typename Value>
Value* Map<Key, Value>::find(const Key& key) const {
    Node* node = findNode(key);
    if (node)
        return &node->value;
    return nullptr;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Node* Map<Key, Value>::findNode(const Key& key) const {
    Node* current = root;
    while (current) {
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return current;
    }
    return nullptr;
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::begin() const {
    Node* current = root;
    while (current && current->left)
        current = current->left;
    return Iterator(current);
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::end() const {
    return Iterator(nullptr);
}

template <typename Key, typename Value>
typename Map<Key, Value>::Iterator& Map<Key, Value>::Iterator::operator++() {
    if (current->right) {
        current = current->right;
        while (current->left)
            current = current->left;
    } else {
        Node* parent = current->parent;
        while (parent && current == parent->right) {
            current = parent;
            parent = parent->parent;
        }
        current = parent;
    }
    return *this;
}

template <typename Key, typename Value>
void Map<Key, Value>::clear() {
    clearTree(root);
    root = nullptr;
}

template <typename Key, typename Value>
void Map<Key, Value>::clearTree(Node* node) {
    if (node) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}
