
// Enhanced Hospital Management System;
// 1.Using a queue for appointment of patient.
#include <iostream>
using namespace std;
int front = -1;
int rear = -1;
#define max 3
int queue[max];
// PRIORITY QUEUE
struct node
{
    int data;
    int priority;
    struct node *next;
};
struct node *start = NULL;

struct node *emergency_insert(struct node *start)
{
    int val, pri;
    struct node *ptr, *p;
    ptr = (struct node *)malloc(sizeof(struct node));
    cout << "ENTER THE VALUE TO BE INSERTED:"; // IN PROJECT USE NAME INSTEAD OF VALUE
    cin >> val;
    cout << "\nENTER THE PRIORITY OF THE VALUE:\n";
    cin >> pri;
    ptr->data = val;
    ptr->priority = pri;

    if (start == NULL || pri < start->priority)
    {
        ptr->next = start;
        start = ptr;
    }
    else
    {
        p = start;
        while (p->next != NULL && p->next->priority <= pri)
        {
            p = p->next;
        }
        ptr->next = p->next;
        p->next = ptr;
        return start;
    }
}
void priority_display(struct node *start)
{
    struct node *ptr;
    ptr = start;
    if (start == NULL)
    {
        cout << "NO EMERGENCY CASES.\n";
    }
    else
    {
        cout << "PATIENTS ACCORDING TO PRIORITY ARE:\n";
        while (ptr != NULL)
        {
            cout << "DATA:" << ptr->data << "   " << "PRIORITY:" << ptr->priority << "\n"; // NAME INSTEAD OF DATA
            ptr = ptr->next;
        }
    }
}
// CIRCULAR QUEUE
int add_patient()
{

    if (front == 0 && rear == max - 1)
    {
        cout << "HOSPITAL CANNOT AFFORD MORE APPOINTMENTS , MAX PATIENTS APPOINTED FOR TODAY\n\n";
        return 1;
    }
    else if (front == -1 && rear == -1)
    {
        front++;
        rear++;
        cout << "PATIENT APPOINTED AS A NORMAL CASE \n\n";

        return 0;
    }

    else if (front != 0 && rear == max - 1)
    {
        rear = 0;

        return 0;
    }
    else
    {
        rear++;
        cout << " PATIENT APPOINTED AS A NORMAL CASE \n\n";

        return 0;
    }
}

int main()
{
    cout << "                      |------------------------------------------------|\n";
    cout << "                      |                                                |\n";
    cout << "                      | Welcome to Enhanced Hospital Management System |\n";
    cout << "                      |                                                |\n";
    cout << "                      |------------------------------------------------|\n\n\n";

    cout << "ENTER 1 TO GET NORMAL APPOINTMET:\n";
    cout << "ENTER 2 TO GET A EMERGENCY APPOINTMENT:\n";
    cout << "ENTER 3 TO EXIT\n";
    int option;
    cin >> option;
    while (option != -1)
    {
        if (option == 1)
        {

            int result = add_patient();
            if (result == 1)
                break;
        }
        else if(option==2)
        {
            start = emergency_insert(start);
        }
        else if(option==3)
        {
            priority_display(start);
        }

        cout << "ENTER 1 TO GET A NORMAL APPOINTMENT:\n";
        cout << "ENTER 2 TO GET A EMERGENCY APPOINTMENT:\n";
        cout << "ENTER 3 TO SHOW EMERGENCY CASES: \n";
        cout << "ENTER -1 TO END:\n";

        cin >> option;
    }
    return 0;
}
