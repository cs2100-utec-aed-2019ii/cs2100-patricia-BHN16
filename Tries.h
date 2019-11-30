#ifndef TRIES_TRIES_H
#define TRIES_TRIES_H
#include "Node.h"
#include <map>
#include <iostream>
#include <utility>
#include <vector>
class Tries {
private:
    Node* root;

public:
    Tries() {
        root = new Node();
    }

    void insert(std::string insert) {
        Node** temp = &root;
        std::string s;
        for(char i : insert) {
            s = i;
            temp = &(*temp)->next[s];
            if(!(*temp)) {
                (*temp) = new Node;
            }
        }
        (*temp)->visited = true;
    }

    void insert_patricia(std::string s, Node** temp) {
        temp = &(*temp)->next[s];
    }

    bool search_by_prefix(std::string search) {
        return !search_by_complete(search);
    }

    bool search_by_complete(std::string search) {
        Node* temp = root;
        std::string s;
        for(char i : search) {
            s = i;
            if(!temp->next[s]) {
                auto it = temp->next.find(s);
                temp->next.erase(it);
                return false;
            }
            temp = temp->next[s];
        }
        return temp->visited;
    }

    void erase(std::string del) {
        Node** borrar = &root;
        int indice = 0;
        erase_helper(del,indice,borrar);
        if(!(*borrar)) {
            (*borrar) = new Node;
        }
    }

    void print() {
        Node* imprimir = root;
        std::string pal;
        for(auto & it : imprimir->next) {
            pal.push_back(it.first[0]);
            print_helper(pal, it.second);
            pal.clear();
        }
    }

    /*void corregir(std::string s) {
        Node* com = root;
        std::string help;
        char c;
        for(auto it = com->next.begin(); it != com->next.end(); ++it) {
            help = s[0];
            c = s[0];
            if(it->first == help) {
                s.erase(s.begin());
                corregir_helper(s,it->second);
                s.push_back(c);
            } else {
                corregir_helper(s,it->second);
            }
        }
        std::cout << "Los valores que se aproximan son : \n";
        print_corregir();
    }*/

    /*void print_corregir() {
        Node* imprimir = root;
        std::string pal;
        for(auto it = imprimir->next.begin(); it != imprimir->next.end(); ++it) {
            pal.push_back(it->first[0]);
            print_corregir_helper(pal, it->second);
            pal.clear();
        }
    }*/

    void to_Patricia() {
        for(auto it = root->next.begin(); it != root->next.end(); ++it) {
            if(it->second->next.size() == 1) {
                std::string i = it->first;
                Node* p = Patricia_convert(i);
                root->next.erase(it);
                root->next[i] = p;
            }
            else if(it->second->next.empty()) {

            }
            else {

            }
        }
    }
private:
    Node* Patricia_convert(std::string &s) {
        for(auto it = root->next.begin(); it != root->next.end(); ++it) {
            if(it->second->next.size() == 1 && it->second->visited) {
                return it->second;
            }
            if(it->second->next.size() == 1) {
                s.push_back(it->first[0]);
                return Patricia_convert(s);
            }
        }
    }

    void Patricia_iterate(Node** p) {
        for(auto it = root->next.begin(); it != root->next.end(); ++it) {
            if(it->second->next.size() == 1) {

            }
            else if(it->second->next.empty()) {

            }
            else {
                Patricia_iterate(&it->second);
            }
        }
    }

    static void erase_helper(std::string del, int indice, Node** borrar) {
        if(indice == del.size()) {
            if((*borrar)->visited && (*borrar)->next.empty())  {
                delete (*borrar);
                (*borrar) = nullptr;
                return;
            } else if((*borrar)->visited && !(*borrar)->next.empty()) {
                (*borrar)->visited = false;
                return;
            }
        } else {
            std::string s;
            s = del[indice];
            erase_helper(del, indice + 1, &(*borrar)->next[s]);
            if (!(*borrar)->next[s]) {
                auto it = (*borrar)->next.find(s);
                (*borrar)->next.erase(it);
            }
            if (!(*borrar)->visited && (*borrar)->next.empty()) {
                delete (*borrar);
                (*borrar) = nullptr;
            }
        }
    }

    static void print_helper(std::string p, Node* r) {
        if(r->visited && r->next.empty()) {
            std::cout << p << std::endl;
            return;
        }
        if(r->visited) {
            std::cout << p << std::endl;
        }
        for(auto & it : r->next) {
            p.push_back(it.first[0]);
            print_helper(p, it.second);
            p.pop_back();
        }
    }

    /*void print_corregir_helper(std::string p, Node* r) {
        if(r->encontrar && r->next.empty()) {
            std::cout << p << std::endl;
            return;
        }
        if(r->encontrar) {
            std::cout << p << std::endl;
        }
        for(auto it = r->next.begin(); it != r->next.end(); ++it) {
            p.push_back(it->first[0]);
            print_corregir_helper(p, it->second);
            p.pop_back();
        }
    }*/

    /*void corregir_helper(std::string k, Node* p) {
        std::string help;
        char c;
        if(k == "") {
            if(p->visited) {
                p->encontrar = true;
            }
            for(auto it = p->next.begin(); it != p->next.end(); ++it) {
                corregir_helper(k,it->second);
            }
        } else {
            help = k[0];
            c = k[0];
            for (auto it = p->next.begin(); it != p->next.end(); ++it) {
                if (it->first == help) {
                    k.erase(k.begin());
                    std::cout << k << std::endl;
                    corregir_helper(k, it->second);
                    k = c + k;
                    std::cout << k << std::endl;
                } else {
                    corregir_helper(k, it->second);
                }
            }
        }
    }*/
};
#endif