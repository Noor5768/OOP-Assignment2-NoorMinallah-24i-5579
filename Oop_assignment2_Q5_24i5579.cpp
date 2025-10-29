#include <iostream>
using namespace std;

class Node 
{
public:
    char data;
    Node* next;
    Node(char c) 
    {   data = c; 
        next = nullptr; 
    }
};

class node 
{
private:
    Node* top;

public:
    node() 
    {  top = nullptr; }
    
    
    void push(char c) 
    {   Node* node = new Node(c);
        node->next = top;
        top = node;
    }

    char pop() 
    {   if (top == nullptr) 
            return '\0';
        char c = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return c;
    }
};

class ArrayStack 
{
private:
    char* array;
    int SIZE;
    int TOP;

public:
    ArrayStack() 
    {   SIZE = 10;
        array = new char[SIZE];
        TOP = -1;
    }

    void push(char c) 
    {
        if (TOP == SIZE - 1) 
        { char* temp = new char[SIZE * 2];
            for (int i = 0; i < SIZE; i++) 
                temp[i] = array[i];
            delete[] array;
            array = temp;
            SIZE *= 2;}
        
        array[++TOP] = c;
    }

    char pop() 
    {     if (TOP < 0) 
          return '\0';
        return array[TOP--];
    }
};


void ChangeLocationArray(char* Array, int b1, int b2) 
{   ArrayStack stack;
    for (int i = b1 - 1; i < b2; i++) 
        stack.push(Array[i]);
    for (int i = b1 - 1; i < b2; i++) 
        Array[i] = stack.pop();
}

void ChangeLocationList(char* Array, int b1, int b2) 
{   node stack;
    for (int i = b1 - 1; i < b2; i++) 
        stack.push(Array[i]);
    for (int i = b1 - 1; i < b2; i++) 
        Array[i] = stack.pop();
}


void PrintPatternArray(int n) 
{
    ArrayStack stack;
    for (int i = n; i > 0; i--) 
    {   int rem = i;
        while (rem > 0) 
        {
            if (rem >= 2) 
            { stack.push('2'); 
                rem -= 2; }
            else 
            { stack.push('1'); 
                rem--; }  
        }
        
        char c;
        while ((c = stack.pop()) != '\0') 
            cout << c << " ";
        cout << endl;
    }
}

void PrintPatternList(int n) 
{   node stack;
    for (int i = n; i > 0; i--) 
    {   int rem = i;
        while (rem > 0) 
        {
            if (rem >= 2) 
            {  stack.push('2'); 
                rem -= 2; }
            else 
            {  stack.push('1'); 
                rem--; }    
        }
        char c;
        while ((c = stack.pop()) != '\0') 
            cout << c << " ";
        cout << endl;
    }
}

int main() 
{
   
    char arr1[] = "COMPUTER";
    char arr2[] = "COMPUTER";
    
    cout << "Original: " << arr1 << endl;
    
    cout << "Array-based implementation:" << endl;
    ChangeLocationArray(arr1, 3, 7);
    cout << "Changed: " << arr1 << endl;
    
    cout << "List-based implementation:" << endl;
    ChangeLocationList(arr2, 3, 7);
    cout << "Changed: " << arr2 << endl;

    cout << "Pattern for n=4 (Array-based):" << endl;
    PrintPatternArray(4);
    
    cout << "Pattern for n=4 (List-based):" << endl;
    PrintPatternList(4);
    
    return 0;
}