#include <queue>
#include <cstdint>
#include <iostream>
#include "HaffmanTree.h"

HaffmanTree::Node::Node(
    int byteValue,
    size_t priority,
    Node* left,
    Node* right
) : byteValue(byteValue),
    priority(priority),
    left(left),
    right(right) { }

HaffmanTree::Node::Node(
    int byteValue,
    size_t priority
) : Node(byteValue, priority, nullptr, nullptr) {}

HaffmanTree::HaffmanTree() : root(nullptr) {  }

void HaffmanTree::buildTree(std::vector<size_t>& statistic) {

    std::priority_queue<
        Node*,
        std::vector<Node*>,
        NodesComparator
    > pq((NodesComparator()));

    for (size_t i = 0; i < statistic.size(); ++i) {
        if (statistic[i] != 0) {
            pq.push(new Node(i, statistic[i], nullptr, nullptr));
        }
    }

    while (pq.size() != 1) {
        Node* firstMin = pq.top();
        pq.pop();
        Node* secondMin = pq.top();
        pq.pop();
        Node* newNode = new Node(-1, firstMin->priority + secondMin->priority, firstMin, secondMin);
        pq.push(newNode);
    }

    root = pq.top();
    pq.pop();

}

std::map<unsigned char, std::string> HaffmanTree::getDict() {
    std::map<unsigned char, std::string> dictionary;
    getDict(root, "1", dictionary);
    return dictionary;
}

void HaffmanTree::getDict(
    Node* now,
    const std::string& code,
    std::map<unsigned char, std::string>& dictionary
) {
    if (now == nullptr) {
        return;
    }
    if (now->byteValue != -1) {
        dictionary[static_cast<unsigned char>(now->byteValue)] = code;
    } else {
        getDict(now->left, code + "0", dictionary);
        getDict(now->right, code + "1", dictionary);
    }
}

unsigned char HaffmanTree::iterateSymbol(
    const std::vector<unsigned char> &bytes,
    size_t& i_bit
) {
    ++i_bit;
    return iterateSymbol(root, bytes, i_bit);
}

unsigned char HaffmanTree::iterateSymbol(
    const Node* now,
    const std::vector<unsigned char> &bytes,
    size_t& i_bit
) {
    size_t i = i_bit / (sizeof(unsigned char) * 8);
    size_t j = i_bit % (sizeof(unsigned char) * 8);
    size_t mask = 1 << (7 - j);

    if (now->byteValue != -1) {
        return now->byteValue;
    }
    ++i_bit;
    if ((bytes[i] & mask) != mask) {
        return iterateSymbol(now->left, bytes, i_bit);
    } else {
        return iterateSymbol(now->right, bytes, i_bit);
    }
}
