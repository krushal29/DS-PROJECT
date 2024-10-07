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
        d[i].time=ctime(&currentTime);
        cout << "Do you want to add more patients? (y/n): ";
        cin >> ch;
        if (ch == 'n' || ch == 'N')
            break;
        else
        {
            i++;
            continue;
        }
    }

    int j = 0;
    while (j <= i)
    {
        cout << "Patient ID: " << d[j].P_id << " | Name: " << d[j].P_name << " | Age: " << d[j].P_age << " | Gender: " << d[j].p_gender << endl<<" | Time: "<<d[j].time<<endl;
        j++;
    }

    return 0;
}
