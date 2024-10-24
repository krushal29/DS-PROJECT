#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <limits> // For numeric_limits to clear the input buffer
#include <fstream>

using namespace std;

// Define color codes
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET_TEXT "\033[0m"

// Structure for storing patient details
struct Details
{
    string P_name;
    int P_age;
    string p_gender;
    int P_id;
    string department; // NEW FIELD to store department name
    string time;
};

// Binary Search Tree node to store patient details
struct BSTNode
{
    Details patient;
    BSTNode *left;
    BSTNode *right;
};

// Linked list for normal appointments (General use for all departments)
struct node_
{
    int data;
    struct node_ *prev;
    struct node_ *next;
};

// For different department linked lists
struct node_ *head_cardio = NULL, *tail_cardio = NULL;
struct node_ *head_neuro = NULL, *tail_neuro = NULL;
struct node_ *head_ortho = NULL, *tail_ortho = NULL;
struct node_ *head_derma = NULL, *tail_derma = NULL;

// Priority queue for emergency cases (General use for all departments)
struct node
{
    int data;
    int priority;
    struct node *next;
};

// For different department priority queues
struct node *start_cardio = NULL;
struct node *start_neuro = NULL;
struct node *start_ortho = NULL;
struct node *start_derma = NULL;

// Function to create a new BST node
BSTNode *createBSTNode(Details d)
{
    BSTNode *newNode = new BSTNode();
    newNode->patient = d;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert patient details into BST
BSTNode *insertIntoBST(BSTNode *root, Details d)
{
    // Base case: if the tree is empty, create a new node
    if (root == NULL)
    {
        return createBSTNode(d);
    }

    // Otherwise, recur down the tree
    if (d.P_id < root->patient.P_id)
    {
        root->left = insertIntoBST(root->left, d);
    }
    else if (d.P_id > root->patient.P_id)
    {
        root->right = insertIntoBST(root->right, d);
    }

    return root;
}

// Function to search for patient by ID in the BST
BSTNode *searchBST(BSTNode *root, int P_id)
{
    // Base case: root is null or the ID matches
    if (root == NULL || root->patient.P_id == P_id)
    {
        return root;
    }

    // ID is smaller than root's ID
    if (P_id < root->patient.P_id)
    {
        return searchBST(root->left, P_id);
    }

    // ID is larger than root's ID
    return searchBST(root->right, P_id);
}

void displayBST(BSTNode *root)
{
    if (root == NULL)
        return;

    displayBST(root->left); // Visit left subtree

    // Print patient details
    cout << YELLOW << "ID: " << root->patient.P_id
         << ", Name: " << root->patient.P_name
         << ", Age: " << root->patient.P_age
         << ", Gender: " << root->patient.p_gender
         << ", Department: " << root->patient.department
         << ", Time: " << root->patient.time
         << RESET_TEXT << endl;

    displayBST(root->right); // Visit right subtree
}

// Generate a unique ID for each patient
int generate_unique_id(set<int> &generatedNumbers)
{
    int range = 100;
    int num;
    do
    {
        num = rand() % range;
    } while (generatedNumbers.find(num) != generatedNumbers.end());

    generatedNumbers.insert(num);
    return num;
}

// Function to get a valid integer input from the user
int get_valid_integer(const string &prompt)
{
    int value;
    while (true)
    {
        cout << BLUE << prompt << RESET_TEXT; // Changed to BLUE
        cin >> value;

        // Check if the input failed (non-numeric input)
        if (cin.fail())
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
            cout << RED << "Invalid input, please enter a number." << RESET_TEXT << endl;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer after valid input
            return value;                                        // Input is valid, return the integer
        }
    }
}

// Function to handle normal cases in any department
void normal_case(struct node_ *&head, struct node_ *&tail, int patientID)
{
    struct node_ *newnode = (struct node_ *)malloc(sizeof(struct node_));
    newnode->data = patientID;
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
    cout << GREEN << "PATIENT APPOINTED AS A NORMAL CASE" << RESET_TEXT << endl; // Changed to GREEN
}

// Function to handle emergency cases in any department
struct node *emergency_case(struct node *start, int patientID)
{
    struct node *ptr, *p;
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = patientID;

    // Use get_valid_integer for priority input
    int pri = get_valid_integer("ENTER THE PRIORITY OF PATIENT (1-3): ");
    ptr->priority = pri;

    if (start == NULL || pri < start->priority)
    {
        ptr->next = start;
        start = ptr;
        cout << MAGENTA << "PATIENT-" << patientID << " IS APPOINTED AS AN EMERGENCY CASE" << RESET_TEXT << endl; // Changed to MAGENTA
    }
    else
    {
        p = start;
        while (p->next != NULL && p->next->priority <= pri)
            p = p->next;
        ptr->next = p->next;
        p->next = ptr;
    }
    return start;
}

// General function for department handling
void department_handler(int patientID, struct node_ *&head, struct node_ *&tail, struct node *&start)
{
    int option1 = get_valid_integer("ENTER 1 FOR EMERGENCY CASES.\nENTER 2 FOR NORMAL APPOINTMENT.\nENTER HERE: ");

    switch (option1)
    {
    case 1:
        start = emergency_case(start, patientID);
        break;

    case 2:
        normal_case(head, tail, patientID);
        break;

    default:
        cout << RED << "EXITING THE DEPARTMENT" << RESET_TEXT << endl;
    }
}

// Cardiology department handling
void cardio(int patientID)
{
    cout << GREEN << "                                WELCOME TO THE CARDIOLOGY DEPARTMENT." << RESET_TEXT << endl; // Changed to GREEN
    department_handler(patientID, head_cardio, tail_cardio, start_cardio);
}

// Neurology department handling
void neuro(int patientID)
{
    cout << GREEN << "                                WELCOME TO THE NEUROLOGY DEPARTMENT." << RESET_TEXT << endl; // Changed to GREEN
    department_handler(patientID, head_neuro, tail_neuro, start_neuro);
}

// Orthopedics department handling
void ortho(int patientID)
{
    cout << GREEN << "                                WELCOME TO THE ORTHOPEDICS DEPARTMENT." << RESET_TEXT << endl; // Changed to GREEN
    department_handler(patientID, head_ortho, tail_ortho, start_ortho);
}

// Dermatology department handling
void derma(int patientID)
{
    cout << GREEN << "                                WELCOME TO THE DERMATOLOGY DEPARTMENT." << RESET_TEXT << endl; // Changed to GREEN
    department_handler(patientID, head_derma, tail_derma, start_derma);
}

void displayDepartmentPatients(BSTNode *root, const string &department)
{
    if (root == NULL)
        return;

    // Recursively traverse the left subtree
    displayDepartmentPatients(root->left, department);

    // Check if the patient's department matches
    if (root->patient.department == department)
    {
        cout << YELLOW << "ID: " << root->patient.P_id
             << ", Name: " << root->patient.P_name
             << ", Age: " << root->patient.P_age
             << ", Gender: " << root->patient.p_gender
             << ", Department: " << root->patient.department
             << ", Time: " << root->patient.time
             << RESET_TEXT << endl;
    }
}

// Helper function to find the minimum value node in the right subtree
BSTNode *findMin(BSTNode *node)
{
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to delete a patient from the BST using their ID
BSTNode *deleteFromBST(BSTNode *root, int P_id)
{
    // Base case: if the tree is empty
    if (root == NULL)
        return root;

    // If the ID to be deleted is smaller, recur down the left subtree
    if (P_id < root->patient.P_id)
        root->left = deleteFromBST(root->left, P_id);

    // If the ID to be deleted is greater, recur down the right subtree
    else if (P_id > root->patient.P_id)
        root->right = deleteFromBST(root->right, P_id);

    // If the ID is found, delete this node
    else
    {
        // Node with only one child or no child
        if (root->left == NULL)
        {
            BSTNode *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            BSTNode *temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        BSTNode *temp = findMin(root->right);

        // Copy the inorder successor's content to this node
        root->patient = temp->patient;

        // Delete the inorder successor
        root->right = deleteFromBST(root->right, temp->patient.P_id);
    }

    return root;
}

int main()
{
    Details d[100]; // Size of details array
    char ch;
    srand(time(0));
    set<int> generatedNumbers;

    BSTNode *root = NULL; // Initialize the root of the BST

    cout << BLUE << "                      |------------------------------------------------|\n";
    cout << "                      |                                                |\n";
    cout << "                      | Welcome to Enhanced Hospital Management System |\n";
    cout << "                      |                                                |\n";
    cout << "                      |------------------------------------------------|\n\n\n"
         << RESET_TEXT;

    while (true)
    {
        // Ask the user if they want to enter details or search history
        int main_choice = get_valid_integer("Enter 1 to search for a patient's history \nEnter 2 to enter new patient details\nEnter 3 Delete patient\nEnter 4 for display all detail: ");

        if (main_choice == 1) // Search for patient history
        {
            int search_id = get_valid_integer("Enter Patient ID to search for patient history: ");
            BSTNode *result = searchBST(root, search_id);
            if (result != NULL)
            {
                ofstream my_file("data.txt");
                cout << YELLOW << "Patient Found!" << RESET_TEXT << endl; // Changed to YELLOW
                cout << YELLOW << "ID: " << result->patient.P_id << " | Name: " << result->patient.P_name << " | Age: " << result->patient.P_age
                     << " | Gender: " << result->patient.p_gender << " | Department: " << result->patient.department
                     << " | Time: " << result->patient.time << RESET_TEXT << endl; // NEW: Department displayed
                my_file.close();
            }
            else
            {
                cout << RED << "Patient with ID " << search_id << " not found." << RESET_TEXT << endl;
            }
        }
        else if (main_choice == 2) // Enter new patient details
        {
            static int i = 0;
            cout << BLUE << "Enter patient Name: " << RESET_TEXT; // Changed to BLUE
            getline(cin, d[i].P_name);                            // Use getline to allow full names with spaces
            d[i].P_age = get_valid_integer("Enter patient age: ");
            cout << BLUE << "Enter patient Gender: " << RESET_TEXT; // Changed to BLUE
            cin >> d[i].p_gender;

            // Generate a unique ID for the patient
            d[i].P_id = generate_unique_id(generatedNumbers);
            time_t currentTime = time(nullptr);
            d[i].time = ctime(&currentTime);

            // Output the patient ID
            cout << GREEN << "Patient ID: " << RESET_TEXT << d[i].P_id << GREEN << " assigned successfully!" << RESET_TEXT << endl;

            // Use get_valid_integer for department choice
            int dept_choice = get_valid_integer("Choose Department:\n1. Cardiology\n2. Neurology\n3. Orthopedics\n4. Dermatology\n");

            switch (dept_choice)
            {
            case 1:
                cardio(d[i].P_id);
                d[i].department = "Cardiology"; // Store department
                break;
            case 2:
                neuro(d[i].P_id);
                d[i].department = "Neurology"; // Store department
                break;
            case 3:
                ortho(d[i].P_id);
                d[i].department = "Orthopedics"; // Store department
                break;
            case 4:
                derma(d[i].P_id);
                d[i].department = "Dermatology"; // Store department
                break;
            default:
                cout << RED << "Invalid Department Choice!" << RESET_TEXT << endl;
            }

            // Insert patient details into the BST
            root = insertIntoBST(root, d[i]);

            i++;
        }
        else if (main_choice == 3)
        {
            int delete_id = get_valid_integer("Enter Patient ID to delete: ");
           root= deleteFromBST(root, delete_id);
            cout << GREEN << "Patient with ID " << delete_id << " has been deleted." << RESET_TEXT << endl;
        }
        else if (main_choice == 4)
        {
            displayBST(root);
        }

        // nisarg can you change it where we will put this condition
        //  else if (main_choice == 5)
        //  {
        //      displayDepartmentPatients(root, "Cardiology");
        //  }

        else
        {
            cout << RED << "Invalid choice. Please try again." << RESET_TEXT << endl;
        }

        // Ask if the user wants to continue
        cout << BLUE << "Do you want to continue? (y/n): " << RESET_TEXT; // Changed to BLUE
        cin >> ch;
        if (ch == 'n' || ch == 'N')
            break;
    }

    return 0;
}
