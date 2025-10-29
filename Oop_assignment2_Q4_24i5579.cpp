#include <iostream>
#include <string>
using namespace std;

class Customer 
{
public:
    int ID;
    string Name;
    int Number_of_tickets;
    Customer* next;

    Customer(int id, string name, int tickets)
    {ID = id;
    Name = name;
    Number_of_tickets = tickets;
    next = nullptr;}
};

class PriorityTicketQueue 
{
private:
    Customer* front;
    int size;

public:
    PriorityTicketQueue()
    {  front = nullptr;
        size = 0;
    }

    void enqueue(int id, string name, int tickets)
    {  Customer* new_customer = new Customer(id, name, tickets);
        
        if (front == nullptr || tickets > front->Number_of_tickets)
        {  new_customer->next = front;
            front = new_customer;
        }
        else
        {   Customer* current = front;
            while (current->next != nullptr && 
                   current->next->Number_of_tickets >= tickets)
            { current = current->next;}
            
            new_customer->next = current->next;
            current->next = new_customer;
        }
        size++;
        cout << "Customer " << name << " added to priority queue" << endl;
    }

    void dequeue()
    {   if (front == nullptr)
        { cout << "Queue empty" << endl;
            return;
        }

        Customer* temp = front;
        cout << "Issuing " << temp->Number_of_tickets << " tickets to " << temp->Name << endl;
        front = front->next;
        delete temp;
        size--;
    }

    void display()
    {   if (front == nullptr)
        { cout << "Queue empty" << endl;
          return;
        }

        cout << "Current Priority Queue Status:" << endl;
        Customer* temp = front;
        while (temp != nullptr)
        { cout << "ID: " << temp->ID 
          << ", Name: " << temp->Name 
          << ", Tickets: " << temp->Number_of_tickets << endl;
          temp = temp->next;
        }
        cout << "Total customers in queue: " << size << endl;
    }
};


int main()
{
    PriorityTicketQueue movieQueue;

    movieQueue.enqueue(1, "Noor", 2);
    movieQueue.enqueue(2, "Mashalle", 3);    
    movieQueue.enqueue(3, "Inayah", 1);  
    
    cout << endl;
    movieQueue.display();
    
    cout << endl;
    movieQueue.dequeue();  
    
    cout << endl;
    movieQueue.display();
    
    cout << endl;
    movieQueue.enqueue(4, "Mashalle", 4);   
    
    cout << endl;
    movieQueue.display();

    return 0; }
