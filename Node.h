#ifndef TRIES_NODE_H
#define TRIES_NODE_H
#include <map>
class Node{
private:
    std::map<std::string,Node*> next;
    bool visited;
    bool encontrar;
public:
    Node() {
        visited = false;
        encontrar = false;
    }
    friend class Tries;
};
#endif
