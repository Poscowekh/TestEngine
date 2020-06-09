#pragma once
#include <time.h>
#include "TestsArray.hpp"
#include "TestsList.hpp"
#include "TestsSequence.hpp"
#include "TestsDeque.hpp"

using namespace std;

class Test
{
    private:
        void Realloc(int new_size)
        {
            TestFunction<Check>* tmp = (TestFunction<Check>*)malloc(new_size * el_size);
            memcpy(tmp, functions, count * el_size);
            free(functions);
            functions = tmp;
        };
        int el_size;
        int errors;
        string name;
        TestFunction<Check>* functions;
        int count;
    public:
        Test(string test_name)
        {
            name = test_name;
            count = 0;
            functions = 0;
            errors = 0;
            el_size = sizeof(TestFunction<Check>);
        };
        void AddTest(string func_name, Check(*const func)())
        {
            TestFunction<Check>* new_func = new TestFunction<Check>(func_name, func);
            Realloc(count + 1);
            memcpy(functions + count, new_func, el_size);
            count++;
        };
        void RunTests()
        {
            Check check;
            TestFunction<Check>* tmp;
            cout << endl << "Testing " << name << "..." << endl;
            for(int i = 0; i < count; i++)
            {
                tmp = functions + i;
                check = tmp->function();
                cout << "   " << "test " << i + 1 << ": " << tmp->function_name << " - ";
                if(check == ERROR)
                {
                    errors++;
                    overall_errors++;
                    cout << "error" << endl;
                }
                else
                    cout << "no errors" << endl;
            };
            cout << "Errors found: " << errors << endl << "Test Finished." << endl << endl;
        };
};

//Array
void TestArray()
{
    Test* array_test = new Test("array");
    array_test->AddTest("Create Array", TestArrayCreate);
    array_test->AddTest("Set/Get Array", TestArraySetGet);
    array_test->AddTest("Push/Pop Array", TestArrayPushPop);
    array_test->AddTest("InsertAt/RemoveAt Array", TestArrayInsertRemove);
    array_test->AddTest("SubArray", TestArraySubArray);
    array_test->AddTest("Concate Arrays", TestArrayConcate);
    array_test->RunTests();
    delete array_test;
};

//List
void TestList()
{
    Test* list_test = new Test("list");
    list_test->AddTest("Create List", TestListCreate);
    list_test->AddTest("Set/Get List", TestListSetGet);
    list_test->AddTest("Push/Pop List", TestListPushPop);
    list_test->AddTest("InsertAt/RemoveAt List", TestListInsertRemove);
    list_test->AddTest("SubList", TestListSublist);
    list_test->AddTest("Concate Lists", TestListConcate);
    list_test->RunTests();
    delete list_test;
};

/*
int seed = time(NULL);

//COMPLEX

Complex<int, int> complex1(1,2);
Complex<int, int> complex2(2,4);
Complex<int, int> complex3(3,8);
Complex<int, int> complex4(4,16);
Complex<int, int> complex5 = ++complex2.GetConjugate();
/*
complex1 *= complex1;
cout << "First complex:  ";
complex1.PrintComplex();
complex2 *= complex3;
cout << "Second complex: ";
complex2.PrintComplex();
complex3.Conjugate();
cout << "Third complex:  ";
complex3.PrintComplex();
++complex4;
cout << "Fourth complex: ";
complex4.PrintComplex();
*/

//LINKEDLIST
/*
LinkedList< Complex<int, int> >* list = new LinkedList< Complex<int, int> >();
list->PushFront(&complex4);
list->PushFront(&complex1);
list->PushBack(&complex3);
list->PushBack(&complex2);
cout << "List:" << endl;
for(int i = 0; i < list->GetLength(); i++)
    list->Get(i).PrintComplex();
cout << endl;
LinkedList< Complex<int, int> >* list_copy = new LinkedList< Complex<int, int> >(*list);
list_copy->InsertAt(&complex5, 2);
cout << "List copy:" << endl;
for(int i = 0; i < list_copy->GetLength(); i++)
    list_copy->Get(i).PrintComplex();
cout << endl;
list_copy->Sort();
cout << "Sorted list if possible:" << endl;
for(int i = 0; i < list_copy->GetLength(); i++)
    list_copy->Get(i).PrintComplex();
cout << endl;
list_copy = list_copy->GetSubList(1, 3);
cout << "Sublist from 1 to 3 from list copy:" << endl;
for(int i = 0; i < list_copy->GetLength(); i++)
    list_copy->Get(i).PrintComplex();
cout << endl;
list_copy->Clear();
cout << "Cleared list:" << endl;
for(int i = 0; i < list_copy->GetLength(); i++)
    list_copy->Get(i).PrintComplex();
cout << endl;
delete list_copy;
delete list;
*/

//ARRAY
/*
DynamicArray< Complex<int, int> > array = DynamicArray< Complex<int, int> >();
array.PushFront(complex2);
array.PushFront(complex1);
array.PushBack(complex3);
array.PushBack(complex4);
for(int i = 0; i < array.GetLength(); i++)
    array[i].PrintComplex();
cout << endl;
DynamicArray< Complex<int, int> > array_copy = DynamicArray< Complex<int, int> >(array);
array_copy.RemoveAt(array_copy.GetLength() - 1);
array_copy.PopFront();
array_copy.PopBack();
array_copy.InsertAt(&complex4, 0);
array_copy.InsertAt(&complex1, 0);
array_copy.InsertAt(&complex5, 2);
array_copy.InsertAt(&complex3, array_copy.GetLength() - 1);
for(int i = 0; i < array_copy.GetLength(); i++)
    array_copy[i].PrintComplex();
cout << endl;
*/

//SEQUENCE
/*
DynamicArray< Complex<float, float> >* arr = FloatComplexArray(seed, 5);
LinkedListSequence< Complex<float, float> > list_sequence = LinkedListSequence< Complex<float, float> >();
LinkedListSequence< Complex<float, float> >* list_subsequence;
seed += RandomInt(seed);
seed -= RandomInt(seed);
cout << "List sequence:" << endl;
for(int i = 0; i < arr->GetLength(); i++)
    list_sequence.Prepend(arr->GetPointer(i));
for(int i = 0; i < list_sequence.GetLength(); i++)
    cout << list_sequence.Get(i).StringComplex() << endl;
list_subsequence = list_sequence.GetSubsequence(1,3);
cout << endl << "List subsequence" << endl;
for(int i = 0; i < list_subsequence->GetLength(); i++)
    (*list_subsequence)[i].PrintComplex();
cout << endl;
delete arr;
*/

//DEQUE
/*
Deque< Complex<int, int> > deque = Deque< Complex<int, int> >();
if(deque.Empty())
    cout << "EMPTY" << endl;
DynamicArray< Complex<int, int> >* arr = IntComplexArray(seed, rand() % 4 + 2);
cout << "Some array:" << endl;
for(int i = 0; i < arr->GetLength(); i++)
    cout << arr->Get(i).ComplexToString() << endl;
cout << endl << "Deque:" << endl;
for(int i = 0; i < arr->GetLength(); i++)
    deque.PushFront(arr->GetPointer(i));
for(int i = 0; i < deque.GetLength(); i++)
    deque[i].PrintComplex();
seed++;
*/

void Tests()
{
    cout << endl << "RUNNING TESTS" << endl;
    //TestArray();
    TestList();
    cout << "All tests finished";
    if(overall_errors > 0)
        cout << ", found " << overall_errors << " errors." << endl;
    else
        cout << " successfully." << endl;
    getchar();
};
