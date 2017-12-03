// HashTableRelations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    string value;
};

class HashTable
{
public:
    HashTable(int size)
    {
        _table.resize(size);
    }

    void create(int size)
    {}
    void insert(int key, Node* value)
    {}
    Node* find(int key)
    {}

private:
    vector<vector<Node>> _table;

    int _hashFunction(int key)
    {
        int size = _table.size();
        int slot = key % size;
        return slot;
    }
};

int main()
{
    return 0;
}

