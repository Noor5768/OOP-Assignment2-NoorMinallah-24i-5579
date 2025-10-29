#include <iostream>
#include <string>

using namespace std;

class Feature 
{
public:
    string Name;
    Feature(const string& name)
    {
        Name = name;
    }
    virtual ~Feature()
    {
        
    }
    virtual void analyze() const = 0;
};

class LandFeature : public Feature 
{
public:
    LandFeature(const string& name) : Feature(name)
    {
        
    }
    void analyze() const override
    {
        cout << "LandFeature \"" << Name << "\": land area detected." << endl;
    }
};

class WaterFeature : public Feature 
{
public:
    WaterFeature(const string& name) : Feature(name)
    {
        
    }
    void analyze() const override
    {
        cout << "WaterFeature \"" << Name << "\": water body detected." << endl;
    }
};


class Node
{
public:
    int FeatureID;
    Feature* feature;
    Node* next;

    Node(int id, Feature* f)
        : FeatureID(id), feature(f), next(nullptr)
    {
    }
};

class SinglyLinkedList 
{
    Node* head;

public:
    SinglyLinkedList()
    {
        head = nullptr;
    }

    ~SinglyLinkedList()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* tmp = current->next;
            if (current->feature != nullptr)
            {
                delete current->feature;
                current->feature = nullptr;
            }
            delete current;
            current = tmp;
        }
        head = nullptr;
    }

    void insertAtEnd(int featureID, Feature* f)
    {
        if (f == nullptr)
        {
            return;
        }
        Node* node = new Node(featureID, f);
        if (head == nullptr)
        {
            head = node;
            return;
        }
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = node;
    }

    bool deleteByID(int featureID)
    {
        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr && current->FeatureID != featureID)
        {
            previous = current;
            current = current->next;
        }
        if (current == nullptr)
        {
            return false;
        }
        if (previous == nullptr)
        {
            head = current->next;
        }
        else
        {
            previous->next = current->next;
        }
        if (current->feature != nullptr)
        {
            delete current->feature;
            current->feature = nullptr;
        }
        delete current;
        return true;
    }

    void displayAll() const
    {
        if (head == nullptr)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node* current = head;
        while (current != nullptr)
        {
            cout << "FeatureID " << current->FeatureID << " -> ";
            if (current->feature != nullptr)
            {
                current->feature->analyze();
            }
            else
            {
                cout << "(no feature)" << endl;
            }
            current = current->next;
        }
    }

    void reverseList()
    {
        Node* previous = nullptr;
        Node* current = head;
        while (current != nullptr)
        {
            Node* nxt = current->next;
            current->next = previous;
            previous = current;
            current = nxt;
        }
        head = previous;
    }
};

int main()
{
    SinglyLinkedList list;

    list.insertAtEnd(101, new LandFeature(string("Dense Grasslands")));
    list.insertAtEnd(102, new WaterFeature(string("River")));
    list.insertAtEnd(103, new LandFeature(string("Sandy Desert")));
    list.insertAtEnd(104, new WaterFeature(string("Saltwater Lake")));

    cout << "Initial list:" << endl;
    list.displayAll();

    cout << endl;
    cout << "Deleting FeatureID 102..." << endl;
    bool deleted = list.deleteByID(102);
    if (deleted == true)
    {
        cout << "Deleted 102" << endl;
    }
    else
    {
        cout << "102 not found" << endl;
    }

    cout << "After deletion:" << endl;
    list.displayAll();

    cout << endl;
    cout << "Reversing list..." << endl;
    list.reverseList();
    cout << "After reversing:" << endl;
    list.displayAll();

    return 0;
}
