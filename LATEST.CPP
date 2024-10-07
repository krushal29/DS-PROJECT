// DEPARTMENTS:-     1> Cardiology
//                   2> Neurology
//                   3>Orthopedics
//                   4>Dermatology
#include <iostream>
using namespace std;
struct node_ {
    int data;
    struct node_ *prev;
    struct node_ *next;
};

struct node_ *head = NULL, *tail = NULL;

void cardio_normal() {
    int x;
    struct node_ *newnode = (struct node_ *)malloc(sizeof(struct node_));
    cout<<endl<<"ENTER ID: ";
    cin>>x;
    newnode->data = x; 
    newnode->prev = NULL;
    newnode->next = NULL;

    if (head == NULL) {
        head = tail = newnode;
    } else {
        tail->next = newnode;
        newnode->prev = tail;
        tail = newnode;
    }
    cout << "PATIENT APPOINTED AS A NORMAL CASE";
}

struct node
{
    int data;
    int priority;
    struct node *next;
};
struct node *start = NULL;
struct node *cardio_emergency()
{

    int val, pri;
    cout << "ENTER THE PATIENT ID :";
    cin >> val;
    struct node *ptr, *p;
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = val;
    cout << "ENTER THE PRIORITY OF PATEINT OUT OF 3:";
    cin >> pri;
    ptr->priority = pri;

    if (start == NULL || pri < start->priority)
    {
        ptr->next = start;
        start = ptr;
        cout << "PATIENT-" << val << " IS APPOINTED AS EMEGENCY CASE";
    }
    else
    {
        p = start;
        while (p->next != NULL && p->next->priority <= pri)
            p = p->next;
        ptr->next = ptr->next;
        p->next = ptr;
    }
    return start;
}



void cardio()
{
    cout << "                                WELCOME TO THE CARIOLOGY DEPARTMENT." << endl
         << endl;

    cout << "ENTER 1 FOR EMERGENCY CASES." << endl;
    cout << "ENTER 2 FOR NORMAL APPOINTMENT." << endl;
    cout << "ENTER HERE:";
    int option1;
    cin >> option1;

    switch (option1)
    {
    case 1:
        cardio_emergency();
        break;

    case 2:
        cardio_normal();
        break;

    default:
    cout<<"EXITING THE DEPARTMENT"<<endl;
    }
}
int main()
{
    cardio();
    return 0;
}
