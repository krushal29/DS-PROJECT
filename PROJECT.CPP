// Enhanced Hospital Management System;
// 1.Using a queue for appointment of patient.
#include <iostream>
using namespace std;
int front = -1;
int rear = -1;
#define max 3
int queue[max];

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

void remove_patient()
{
                      
} 



int main()
{
    cout << "                      |------------------------------------------------|\n";
    cout << "                      |                                                |\n";
    cout << "                      | Welcome to Enhanced Hospital Management System |\n";
    cout << "                      |                                                |\n";
    cout << "                      |------------------------------------------------|\n\n\n";

    cout << "ENTER 1 TO GET NORMAL APPOINTMET:";

    int option;
    cin >> option;
    while (option != 2)
    {

        int result= add_patient();
        if(result==1)
        break;

        cout << "ENTER 1 TO APPOINT ANOTHER PATIENT:\n";
        cout << "ENTER 2 TO END:\n";
        cin >> option;
    }
    return 0;
}
