#pragma once
#include "../Structures/DynamicArray.hpp"
#include "../Structures/LinkedList.hpp"
#include "../Utility/RandomGen.hpp"
#include "../Utility/Function.hpp"
#include "Check.h"
#include <time.h>

using namespace std;

Check TestListCreate()
{
    srand(time(NULL));
    LinkedList<int>* list;
    int size = rand() % 1000 + 1;
    list = new LinkedList<int>();
    if(list->GetLength() != 0)
        return ERROR;
    int* data = (int*)malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++)
        memcpy(data + i, &size, sizeof(int));
    list = new LinkedList<int>(data, size);
    if(list->GetLength() != size)
        return ERROR;
    for(int i = 0; i < list->GetLength(); i++)
        if(list->Get(i) != size)
            return ERROR;
    LinkedList<int>* list_copy = new LinkedList<int>(*list);
    if(list_copy->GetLength() != size)
        return ERROR;
    for(int i = 0; i < list_copy->GetLength(); i++)
        if(list_copy->Get(i) != size)
            return ERROR;
    delete list;
    delete list_copy;
    return NO_ERROR;
};

Check TestListSetGet()
{
    int seed = time(NULL);
    srand(seed);
    int size = rand() % 1000 + 1;
    seed++;
    LinkedList<int>* list = new LinkedList<int>();
    for(int i = 0; i < size; i++)
        list->PushBack(0);
    int tmp = RandomInt(seed);
    for(int i = 0; i < size; i++)
    {
        list->Set(i, tmp);
    };
    if(list->GetLength() != size)
        return ERROR;
    for(int i = 0; i < size; i++)
        if(list->Get(i) != tmp)
            return ERROR;
    delete list;
    return NO_ERROR;
};

Check TestListPushPop()
{
    int seed = time(NULL);
    srand(seed);
    LinkedList<int>* list = new LinkedList<int>();
    int r_size = rand() % 1000 + 1;
    int a = RandomInt(seed);
    seed++;
    for(int i = 0; i < r_size; i++)
        list->PushFront(a);
    if(list->GetLength() != r_size)
        return ERROR;
    for(int i = 0; i < list->GetLength(); i++)
        if(list->Get(i) != a)
            return ERROR;
    srand(seed);
    int tmp = rand() % r_size;
    seed++;
    for(int i = 0; i < tmp; i++)
        list->PopFront();
    if(list->GetLength() != r_size - tmp)
        return ERROR;
    list->Clear();
    srand(seed);
    r_size = rand() % 1000 + 1;
    a = RandomInt(seed);
    seed++;
    for(int i = 0; i < r_size; i++)
        list->PushBack(a);
    if(list->GetLength() != r_size)
        return ERROR;
    for(int i = 0; i < list->GetLength(); i++)
        if(list->Get(i) != a)
            return ERROR;
    srand(seed);
    tmp = rand() % r_size;
    seed++;
    for(int i = 0; i < tmp; i++)
        list->PopBack();
    if(list->GetLength() != r_size - tmp)
        return ERROR;
    delete list;
    return NO_ERROR;
};

Check TestListInsertRemove()
{
    int seed = time(NULL);
    srand(seed);
    int r_size = rand() % 1000 + 1;
    seed++;
    DynamicArray<int>* array = IntArray(seed, r_size);
    LinkedList<int>* list = new LinkedList<int>(array->DataPointer(), array->GetLength());
    LinkedList<int>* list_copy = new LinkedList<int>(*list);
    srand(seed);
    int at = rand() % (list->GetLength() - 1);
    seed++;
    int r_int = RandomInt(seed);
    seed++;
    list->InsertAt(r_int, at);
    if(list->GetLength() - 1 != list_copy->GetLength())
        return ERROR;
    if(at > 0)
        if(list->Get(at - 1) != list_copy->Get(at - 1))
            return ERROR;
    if(list->Get(at) != r_int)
        return ERROR;
    if(list->Get(at + 1) != list_copy->Get(at))
        return ERROR;
    list->RemoveAt(at);
    if(list->GetLength() != list_copy->GetLength())
        return ERROR;
    for(int i = 0; i < list->GetLength(); i++)
        if(list->Get(i) != list_copy->Get(i))
            return ERROR;
    delete list;
    delete list_copy;
    return NO_ERROR;
};

Check TestListSublist()
{
    int seed = time(NULL);
    srand(seed);
    seed++;
    int r_size = rand() % 1000 + 1;
    LinkedList<int>* list = new LinkedList<int>();
    int a = RandomInt(seed);
    for(int i = 0; i < r_size; i++)
        list->PushBack(a);
    int from = rand() % (list->GetLength() / 4);
    int to = rand() % (list->GetLength() / 4) + list->GetLength() / 2;
    LinkedList<int>* sublist = list->GetSublist(from, to);
    if(sublist->GetLength() != to - from + 1)
        return ERROR;
    for(int i = 0; i < sublist->GetLength(); i++)
        if(sublist->Get(i) != a)
            return ERROR;
    delete list;
    delete sublist;
    return NO_ERROR;
};

Check TestListConcate()
{
    int seed = time(NULL);
    srand(seed);
    LinkedList<int>* list1 = new LinkedList<int>();
    LinkedList<int>* list2 = new LinkedList<int>();
    LinkedList<int>* list3 = new LinkedList<int>();
    int r_size1 = 5;//rand() % 1000 + 1;
    int a = RandomInt(seed);
    seed++;
    srand(seed);
    int r_size2 = 6;//rand() % 1000 + 1;
    int b = RandomInt(seed);
    for(int i = 0; i < r_size1; i++)
        list1->PushBack(a);
    for(int i = 0; i < r_size2; i++)
        list2->PushBack(b);
    list3 = new LinkedList<int>(*list1);
    list3->Concate(list2);
    if(list3->GetLength() != list1->GetLength() + list2->GetLength())
        return ERROR;
    for(int i = 0; i < list1->GetLength(); i++)
        if(list3->Get(i) != list1->Get(i))
            return ERROR;
    for(int i = 0; i < list2->GetLength(); i++)
        if(list3->Get(i + list1->GetLength()) != list2->Get(i))
            return ERROR;
    delete list1;
    delete list2;
    delete list3;
    return NO_ERROR;
};
