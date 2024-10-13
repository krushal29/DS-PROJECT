#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;
#define size1 100

struct Details
{
    string P_name;
    int P_age;
    string p_gender;
    int P_id; // Add ID field to the struct
    string time;
};

struct node_
{
    int data;
    struct node_ *prev;
    struct node_ *next;
};

struct node_ *head = NULL, *tail = NULL;

void cardio_normal()
{
    int x;
    struct node_ *newnode = (struct node_ *)malloc(sizeof(struct node_));
    cout << endl
         << "ENTER ID: ";
    cin >> x;
    newnode->data = x;
    newnode->prev = NULL;
    newnode->next = NULL;

    if (head == NULL)
    {
        head = tail = newnode;
    }
    else
    {
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
        cout << "EXITING THE DEPARTMENT" << endl;
    }
}

int generate_unique_id(set<int> &generatedNumbers)
{
    int range = 100; // Set a larger range to avoid collisions
    int num;

    do
    {
        num = rand() % range; // Generate random number
    } while (generatedNumbers.find(num) != generatedNumbers.end()); // Check if it's unique

    generatedNumbers.insert(num); // Insert the number into the set
    return num;
}

int main()
{
    Details d[size1];
    char ch;

    srand(time(0));

    set<int> generatedNumbers;

    cout << "                      |------------------------------------------------|\n";
    cout << "                      |                                                |\n";
    cout << "                      | Welcome to Enhanced Hospital Management System |\n";
    cout << "                      |                                                |\n";
    cout << "                      |------------------------------------------------|\n\n\n";

    int i = 0;
    while (1)
    {
        cout << "Enter patient Name: ";
        cin >> d[i].P_name;
        cout << "Enter patient age: ";
        cin >> d[i].P_age;
        cout << "Enter patient Gender: ";
        cin >> d[i].p_gender;

        d[i].P_id = generate_unique_id(generatedNumbers);
        time_t currentTime = time(nullptr);
        d[i].time = ctime(&currentTime);

        cout << "This is your details\n";

        int j = 0;
        while (j <= i)
        {
            cout << "Patient ID: " << d[j].P_id << " | Name: " << d[j].P_name << " | Age: " << d[j].P_age << " | Gender: " << d[j].p_gender << endl
                 << " | Time: " << d[j].time << endl;
            j++;
        }

        cardio();

        cout << "\nDo you want to add more patients? (y/n): ";
        cin >> ch;
        if (ch == 'n' || ch == 'N')
            break;
        else
        {
            i++;
            continue;
        }
    }

    return 0;
}