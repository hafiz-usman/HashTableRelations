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
    HashTable(int initialSlots, int maxCollisionsAllowedPerSlot, double growFactor) :
        _size(0),
        _initialSlots(initialSlots),
        _currentSlots(initialSlots),
        _maxCollisionsAllowedPerSlot(maxCollisionsAllowedPerSlot),
        _growFactor(growFactor)
    {
        _table = new vector<list<Node>>(_initialSlots);
    }

    ~HashTable()
    {
        delete _table;
    }

    bool insert(int key, Value& value)
    {
        int slot = _hashFunction(key);
        if (slot < 0 || slot >= _table->size())
        {
            return false;
        }

        int numSlotCollisions = _table->at(slot).size();
        // if any slot has reached the _maxCollisionResizeThreshold, grow the table
        if (numSlotCollisions >= _maxCollisionsAllowedPerSlot)
        {
            _growTable();
            // IMP!! Since we recreated the table with more slots, the slot needs to be recomputed also!!!
            slot = _hashFunction(key);
        }

        _table->at(slot).push_back(Node(key, value));
        _size++;
    }

    bool find(int key, Value& retVal)
    {
        int slot = _hashFunction(key);
        if (slot < 0 || slot >= _table->size())
        {
            return false;
        }

        for (auto iter = _table->at(slot).begin(); iter != _table->at(slot).end(); ++iter)
        {
            if (iter->key == key)
            {
                retVal = iter->val;
                return true;
            }
        }
        return false;
    }

    bool remove(int key)
    {
        int slot = _hashFunction(key);

        if (slot < 0 || slot >= _table->size())
        {
            return false;
        }

        bool found = false;
        for (auto iter = _table->at(slot).begin(); iter != _table->at(slot).end(); ++iter)
        {
            if (iter->key == key)
            {
                found = true;
                _table->at(slot).erase(iter);
                _size--;
                break;
            }
        }
        return found;
    }

    int size()
    {
        return _size;
    }

    void dump()
    {
        cout << "HashTable Dump:" << endl;
        for (int i = 0; i < _table->size(); i++)
        {
            cout << "[" << i << "]: " << endl;
            for (auto b : _table->at(i))
            {
                cout << "  ";
                cout << "key=" << b.key << ", val=" << b.val.str.c_str() << endl;
            }
        }
    }

private:
    vector<list<Node>>* _table;
    int _size;
    int _initialSlots;
    int _currentSlots;
    int _maxCollisionsAllowedPerSlot;
    int _growFactor;

    int _hashFunction(int key)
    {
        int maxSlots = _table->size();
        int slot = key % maxSlots;
        return slot;
    }

    void _growTable()
    {
        vector<list<Node>>* oldTable = _table;
        _table = new vector<list<Node>>();

        int temp = _currentSlots * _growFactor;
        assert(temp > _currentSlots); // check for overflow
        _table->resize(temp);
        _currentSlots = temp;

        // MAKE SURE TO RESET SIZE since we're not deleting key's from the original table, the size is continuously going up
        int oldSize = _size;
        _size = 0;

        for (int i = 0; i < oldTable->size(); i++)
        {
            for (auto iter = oldTable->at(i).begin(); iter != oldTable->at(i).end(); ++iter)
            {
                insert(iter->key, iter->val);
            }
        }

        cout << "==========     GROW TABLE (old=" << oldTable->size() << ",new=" << _table->size() << ")    ==========" << endl;

        delete oldTable;
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

    HashTable ht(2, 1, 2);
    int flag = false;

    for (int i = 0; i < input.size(); i++)
    {
        cout << "Inserting: [" << i << "] = " << input[i].c_str() << endl;
        flag = ht.insert(i, Value(input[i]));
        assert(flag != false);
        ht.dump();
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

    int size = 0;
    k = -1;
    assert(ht.remove(k) == false && ht.size() == input.size());
    k = 0;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 1;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 2;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 3;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 4;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 5;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 6;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 7;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 8;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 9;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 10;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 11;
    assert(ht.remove(k) == true && (size = ht.size()) == (input.size() - (k + 1)) && (flag = ht.find(k, v)) == false);
    k = 12;
    assert(ht.remove(k) == false && ht.size() == 0);
    k = input.size() + 1;
    assert(ht.remove(k) == false && ht.size() == 0);

    return 0;
}

