#pragma once
#include "../Structures/DynamicArray.hpp"
#include "../Utility/RandomGen.hpp"
#include "../Utility/Function.hpp"
#include "Check.h"
#include <time.h>

using namespace std;

Check TestArrayCreate()
{
    srand(time(NULL));
    DynamicArray<int>* array;
    int size = rand() % 1000 + 1;
    array = new DynamicArray<int>();
    if(array->GetLength() != 0)
        return ERROR;
    array = new DynamicArray<int>(size);
    if(array->GetLength() != size)
        return ERROR;
    int* data = (int*)malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++)
        memcpy(data + i, &size, sizeof(int));
    array = new DynamicArray<int>(data, size);
    if(array->GetLength() != size)
        return ERROR;
    for(int i = 0; i < array->GetLength(); i++)
        if(array->Get(i) != size)
            return ERROR;
    DynamicArray<int>* array_copy = new DynamicArray<int>(*array);
    if(array_copy->GetLength() != size)
        return ERROR;
    for(int i = 0; i < array_copy->GetLength(); i++)
        if(array_copy->Get(i) != size)
            return ERROR;
    delete array;
    delete array_copy;
    return NO_ERROR;
};

Check TestArraySetGet()
{
    int seed = time(NULL);
    srand(seed);
    int size = rand() % 1000 + 1;
    seed++;
    DynamicArray<int>* array = new DynamicArray<int>(size);
    int tmp = RandomInt(seed);
    seed++;
    for(int i = 0; i < size; i++)
    {
        array->Set(i, tmp);
    };
    for(int i = 0; i < size; i++)
        if(array->Get(i) != tmp)
            return ERROR;
    delete array;
    return NO_ERROR;
};

Check TestArrayPushPop()
{
    int seed = time(NULL);
    srand(seed);
    DynamicArray<int>* array = new DynamicArray<int>();
    int r_size = rand() % 1000 + 1;
    int a = RandomInt(seed);
    seed++;
    for(int i = 0; i < r_size; i++)
        array->PushFront(a);
    if(array->GetLength() != r_size)
        return ERROR;
    for(int i = 0; i < array->GetLength(); i++)
        if(array->Get(i) != a)
            return ERROR;
    srand(seed);
    int tmp = rand() % r_size;
    seed++;
    for(int i = 0; i < tmp; i++)
        array->PopFront();
    if(array->GetLength() != r_size - tmp)
        return ERROR;
    array->Clear();
    srand(seed);
    r_size = rand() % 1000 + 1;
    a = RandomInt(seed);
    seed++;
    for(int i = 0; i < r_size; i++)
        array->PushBack(a);
    if(array->GetLength() != r_size)
        return ERROR;
    for(int i = 0; i < array->GetLength(); i++)
        if(array->Get(i) != a)
            return ERROR;
    srand(seed);
    tmp = rand() % r_size;
    seed++;
    for(int i = 0; i < tmp; i++)
        array->PopBack();
    if(array->GetLength() != r_size - tmp)
        return ERROR;
    delete array;
    return NO_ERROR;
};

Check TestArrayInsertRemove()
{
    int seed = time(NULL);
    srand(seed);
    int r_size = rand() % 10 + 1;//% 1000 + 1;
    seed++;
    DynamicArray<int>* array = IntArray(seed, r_size);
    DynamicArray<int>* array_copy = new DynamicArray<int>(*array);
    srand(seed);
    int at = rand() % (array->GetLength() - 1);
    seed++;
    int r_int = RandomInt(seed);
    seed++;
    array->InsertAt(r_int, at);
    if(array->GetLength() - 1 != array_copy->GetLength())
        return ERROR;
    if(at > 0)
        if(array->Get(at - 1) != array_copy->Get(at - 1))
            return ERROR;
    if(array->Get(at) != r_int)
        return ERROR;
    if(array->Get(at + 1) != array_copy->Get(at))
        return ERROR;
    array->RemoveAt(at);
    if(array->GetLength() != array_copy->GetLength())
        return ERROR;
    for(int i = 0; i < array->GetLength(); i++)
        if(array->Get(i) != array_copy->Get(i))
            return ERROR;
    delete array;
    delete array_copy;
    return NO_ERROR;
};

Check TestArraySubArray()
{
    int seed = time(NULL);
    srand(seed);
    seed++;
    int r_size = rand() % 1000 + 1;
    DynamicArray<int>* array = new DynamicArray<int>();
    int a = RandomInt(seed);
    for(int i = 0; i < r_size; i++)
        array->PushBack(a);
    int from = rand() % (array->GetLength() / 4);
    int to = rand() % (array->GetLength() / 4) + array->GetLength() / 2;
    DynamicArray<int>* subarray = array->GetSubArray(from, to);
    if(subarray->GetLength() != to - from + 1)
        return ERROR;
    for(int i = 0; i < subarray->GetLength(); i++)
        if(subarray->Get(i) != a)
            return ERROR;
    delete array;
    delete subarray;
    return NO_ERROR;
};

Check TestArrayConcate()
{
    int seed = time(NULL);
    srand(seed);
    DynamicArray<int>* array1 = new DynamicArray<int>();
    DynamicArray<int>* array2 = new DynamicArray<int>();
    DynamicArray<int>* array3 = new DynamicArray<int>();
    int r_size1 = 5;//rand() % 1000 + 1;
    int a = RandomInt(seed);
    seed++;
    srand(seed);
    int r_size2 = 6;//rand() % 1000 + 1;
    int b = RandomInt(seed);
    for(int i = 0; i < r_size1; i++)
        array1->PushBack(a);
    for(int i = 0; i < r_size2; i++)
        array2->PushBack(b);
    array3 = new DynamicArray<int>(*array1);
    array3->Concate(*array2);
    if(array3->GetLength() != array1->GetLength() + array2->GetLength())
        return ERROR;
    for(int i = 0; i < array1->GetLength(); i++)
        if(array3->Get(i) != array1->Get(i))
            return ERROR;
    for(int i = 0; i < array2->GetLength(); i++)
        if(array3->Get(i + array1->GetLength()) != array2->Get(i))
            return ERROR;
    delete array1;
    delete array2;
    delete array3;
    return NO_ERROR;
};
