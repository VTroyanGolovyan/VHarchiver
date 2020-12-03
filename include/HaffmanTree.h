#include <vector>
#include <queue>
#include <cstdint>


class HaffmanTree {
private:

    class Node {
    public:
        int byteValue;
        size_t priority;
        Node* left;
        Node* right;

        Node(
            int byteValue,
            size_t priority,
            Node* left,
            Node* right
        );

        Node(
            int byteValue,
            size_t priority
        );

    };

    class NodesComparator {
    public:
        bool operator () (Node*& a, Node*& b) {
            return a->priority > b->priority;
        }
    };

public:
  
    HaffmanTree();

    void buildTree(std::vector<size_t>& statistic);

private:
    Node* root;
};
