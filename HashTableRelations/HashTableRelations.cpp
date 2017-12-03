// HashTableRelations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <assert.h>

using namespace std;

struct Value
{
    string str;
    Value()
    {}
    Value(string s) :
        str(s)
    {}
};
class HashTable
{
    struct Node
    {
        int key;
        Value val;
        Node() :
            key(-1)
        {}
        Node(int k, Value v) :
            key(k),
            val(v)
        {}
    };

public:
    HashTable(int size)
    {
        _table.resize(size);
    }

    bool insert(int key, Value& value)
    {
        int slot = _hashFunction(key);
        if (slot < 0 || slot >= _table.size())
        {
            return false;
        }
        _table[slot].push_back(Node(key, value));
    }

    bool find(int key, Value& retVal)
    {
        int slot = _hashFunction(key);
        if (slot < 0 || slot >= _table.size())
        {
            return false;
        }

        for (auto iter = _table[slot].begin(); iter != _table[slot].end(); ++iter)
        {
            if (iter->key == key)
            {
                retVal = iter->val;
                return true;
            }
        }
        return false;
    }

    void dump()
    {
        cout << "HashTable Dump:" << endl;
        for (int i = 0; i < _table.size(); i++)
        {
            cout << "[" << i << "]: " << endl;
            for (auto b : _table[i])
            {
                cout << "  ";
                cout << "key=" << b.key << ", val=" << b.val.str.c_str() << endl;
            }
        }
    }

private:
    vector<list<Node>> _table;

    int _hashFunction(int key)
    {
        int size = _table.size();
        int slot = key % size;
        return slot;
    }
};

int main()
{
    vector<string> input{
        "file",
        "edit",
        "view",
        "project", 
        "build",
        "debug",
        "team",
        "tools",
        "test",
        "analyze",
        "window",
        "help",
    };

    HashTable ht(3);

    for (int i = 0; i < input.size(); i++)
    {
        cout << "Inserting: [" << i << "] = " << input[i].c_str() << endl;
        ht.insert(i, Value(input[i]));
        //ht.dump();
    }

    int k;
    Value v;

    k = -1;
    assert(ht.find(k, v) == false);
    k = 0;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 1;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 2;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 3;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 4;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 5;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 6;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 7;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 8;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 9;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 10;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 11;
    assert(ht.find(k, v) != false && v.str == input[k]);
    k = 12;
    assert(ht.find(k, v) == false);
    k = input.size() + 1;
    assert(ht.find(k, v) == false);

    return 0;
}

