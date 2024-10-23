#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Define color codes
#define BRIGHT_GREEN "\033[92m"
#define RED "\033[31m"
#define GREEN "\033[32m"
// #define BRIGHT_GREEN "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET_TEXT "\033[0m"

// Structure for storing patient details
struct Details
{
    string P_name;
    int P_age;
    string p_gender;
    int P_id;
    string department;
    string time;
    string case_type; // Added to store "Normal" or "Emergency"
};

// Binary Search Tree node to store patient details
struct BSTNode
{
    Details patient;
    BSTNode *left;
    BSTNode *right;
};

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
    if (root == NULL)
    {
        return createBSTNode(d);
    }

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
    if (root == NULL || root->patient.P_id == P_id)
    {
        return root;
    }

    if (P_id < root->patient.P_id)
    {
        return searchBST(root->left, P_id);
    }

    return searchBST(root->right, P_id);
}

// use inorder
void searchByCaseType(BSTNode *root, const string &case_type)
{
    if (root == NULL)
        return;

    searchByCaseType(root->left, case_type);

    if (root->patient.case_type == case_type)
    {
        cout << YELLOW
             << "Patient ID: " << root->patient.P_id << " || "
             << "Name: " << root->patient.P_name << " || "
             << "Age: " << root->patient.P_age << " || "
             << "Gender: " << root->patient.p_gender << " || "
             << "Department: " << root->patient.department << " || "
             << "Case Type: " << root->patient.case_type << " || "
             << "Time of entry: " << root->patient.time << RESET_TEXT << endl;
    }

    searchByCaseType(root->right, case_type);
}

// Function to display all patients in the hospital
//preoreder
void display_all_patients(BSTNode *root)
{
    if (root == NULL)
    {
        cout << RED << "No patients in the hospital." << RESET_TEXT << endl;
        return;
    }

    if (root->left)
        display_all_patients(root->left);

    cout << YELLOW
         << "Patient ID: " << root->patient.P_id << " || "
         << "Name: " << root->patient.P_name << " || "
         << "Age: " << root->patient.P_age << " || "
         << "Gender: " << root->patient.p_gender << " || "
         << "Department: " << root->patient.department << " || "
         << "Case Type: " << root->patient.case_type << " || "
         << "Time of entry: " << root->patient.time << RESET_TEXT << endl;

    if (root->right)
        display_all_patients(root->right);
}

// Helper function to find the minimum value node in the right subtree
BSTNode *findMin(BSTNode *node)
{
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to delete a patient from the BST using their ID
//preorder
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

// Function to traverse and count patients in a specific department
// inorder
void traverse_and_count(BSTNode *node, const string &department, bool &found)
{
    if (node == NULL)
        return;

    traverse_and_count(node->left, department, found); // Traverse left

    // Check if the current patient's department matches the chosen department
    if (node->patient.department == department)
    {
        found = true; // Mark as found
        cout << YELLOW
             << "Patient ID: " << node->patient.P_id << " || "
             << "Name: " << node->patient.P_name << " || "
             << "Age: " << node->patient.P_age << " || "
             << "Gender: " << node->patient.p_gender << " || "
             << "Case Type: " << node->patient.case_type << " || "
             << "Time of entry: " << node->patient.time << RESET_TEXT << endl;
    }

    traverse_and_count(node->right, department, found); // Traverse right
}

// Function to display patients by department and handle no patients found case
void display_department_patients(BSTNode *root, const string &department)
{
    bool found = false; // Track if any patient was found

    // Traverse the BST and display patients
    traverse_and_count(root, department, found);

    // If no patients were found, display a message
    if (!found)
    {
        cout << RED << "No patients found in " << department << " department." << RESET_TEXT << endl;
    }
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
        cout << BRIGHT_GREEN << prompt << RESET_TEXT;
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input, please enter a number." << RESET_TEXT << endl;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Function to handle normal cases in any department
void normal_case(Details &d)
{
    d.case_type = "Normal";
    cout << YELLOW << "Patient appointed as a normal case." << RESET_TEXT << endl;
}

// Function to handle emergency cases in any department
void emergency_case(Details &d)
{
    d.case_type = "Emergency";
    int priority = get_valid_integer("Enter the priority of the patient (1-3): ");
    cout << YELLOW << "Patient assigned as an emergency case with priority: " << priority << RESET_TEXT << endl;
}

// Function to choose case type (Normal or Emergency)
void choose_case_type(Details &d)
{
    int case_type = get_valid_integer("Enter 1 for Emergency case\nEnter 2 for Normal appointment\nEnter choice: ");
    if (case_type == 1)
    {
        emergency_case(d);
    }
    else if (case_type == 2)
    {
        normal_case(d);
    }
    else
    {
        cout << RED << "Invalid choice. Defaulting to normal case." << RESET_TEXT << endl;
        normal_case(d);
    }
}

int main()
{
    Details d[100];
    set<int> generatedNumbers;
    BSTNode *root = NULL; // Initialize the root of the BST
    srand(time(0));       // Seed for random number generation
    char ch;

    cout << RED << "                      |------------------------------------------------|\n";
    cout << "                      |                                                |\n";
    cout << "                      | Welcome to Enhanced Hospital Management System |\n";
    cout << "                      |                                                |\n";
    cout << "                      |------------------------------------------------|\n\n\n"
         << RESET_TEXT;

    do
    {
        int option;
        cout << BRIGHT_GREEN << "MENU OPTIONS:\n"
             << RESET_TEXT;
        cout << BLUE << "1. Register a New Patient\n";
        cout << "2. Search a Patient by ID\n";
        cout << "3. View All Patients\n";
        cout << "4. View Patients by Department\n";
        cout << "5. Delete Patient from Hospital\n";
        cout << "6.Display by cases like normal and emergency\n"
             << RESET_TEXT;
        cout << BRIGHT_GREEN << "Choose an option (1-6): " << RESET_TEXT;

        cin >> option;

        switch (option)
        {
        case 1:
        {
            int number = generate_unique_id(generatedNumbers); // Unique ID generation

            // Taking patient details
            cout << BLUE << "ENTER PATIENT NAME: " << RESET_TEXT;
            getline(cin >> ws, d[number].P_name);
            d[number].P_age = get_valid_integer("ENTER AGE: ");
            cout << BLUE << "ENTER GENDER (male/female): " << RESET_TEXT;
            getline(cin >> ws, d[number].p_gender);
            d[number].P_id = number;

            time_t now = time(0);         // Get current time
            d[number].time = ctime(&now); // Convert to string

            // Display the generated Patient ID
            cout << YELLOW << "Patient ID: " << RESET_TEXT << d[number].P_id << YELLOW << " has been generated successfully!" << RESET_TEXT << endl;

            // Department selection
            int department_choice = get_valid_integer("ENTER DEPARTMENT:\n1 FOR CARDIOLOGY\n2 FOR NEUROLOGY\n3 FOR ORTHOPEDICS\n4 FOR DERMATOLOGY\nENTER HERE: ");

            switch (department_choice)
            {
            case 1:
                d[number].department = "Cardiology";
                break;
            case 2:
                d[number].department = "Neurology";
                break;
            case 3:
                d[number].department = "Orthopedics";
                break;
            case 4:
                d[number].department = "Dermatology";
                break;
            default:
                cout << RED << "DEPARTMENT DOES NOT EXIST" << RESET_TEXT << endl;
                continue;
            }

            // Choose case type (Normal or Emergency)
            choose_case_type(d[number]);

            // Insert patient details into the BST
            root = insertIntoBST(root, d[number]);
        }
        break;

        case 2:
        {
            int patientID = get_valid_integer("ENTER PATIENT ID: ");
            BSTNode *result = searchBST(root, patientID);

            if (result != NULL)
            {
                cout << YELLOW << "Patient found! Details are as follows:\n";
                cout << "Name: " << result->patient.P_name << "\n";
                cout << "Age: " << result->patient.P_age << "\n";
                cout << "Gender: " << result->patient.p_gender << "\n";
                cout << "ID: " << result->patient.P_id << "\n";
                cout << "Department: " << result->patient.department << "\n";
                cout << "Case Type: " << result->patient.case_type << "\n"; // Display case type (Normal or Emergency)
                cout << "Time of entry: " << result->patient.time << RESET_TEXT << endl;
            }
            else
            {
                cout << RED << "PATIENT NOT FOUND" << RESET_TEXT << endl;
            }
        }
        break;

        case 3:
            display_all_patients(root); // Display all patients
            break;

        case 4:
        {
            int department_choice = get_valid_integer("ENTER DEPARTMENT TO VIEW:\n1 FOR CARDIOLOGY\n2 FOR NEUROLOGY\n3 FOR ORTHOPEDICS\n4 FOR DERMATOLOGY\nENTER HERE: ");
            string department;

            switch (department_choice)
            {
            case 1:
                department = "Cardiology";
                break;
            case 2:
                department = "Neurology";
                break;
            case 3:
                department = "Orthopedics";
                break;
            case 4:
                department = "Dermatology";
                break;
            default:
                cout << RED << "DEPARTMENT DOES NOT EXIST" << RESET_TEXT << endl;
                continue;
            }

            cout << GREEN << "Displaying patients in department: " << department << RESET_TEXT << endl;
            display_department_patients(root, department); // Display patients by selected department
        }
        break;

        case 5:
        {
            int delete_id = get_valid_integer("Enter Patient ID to delete: ");
            root = deleteFromBST(root, delete_id);
            cout << GREEN << "Patient with ID " << delete_id << " has been deleted." << RESET_TEXT << endl;
        }
        break;

        case 6:
        {
            int caseOption = get_valid_integer("ENTER 1 TO DISPLAY ALL NORMAL CASES\nENTER 2 TO DISPLAY ALL EMERGENCY CASES\n");
            string caseType;

            // Set case type based on user input
            if (caseOption == 1)
                caseType = "Normal";
            else if (caseOption == 2)
                caseType = "Emergency";
            else
            {
                cout << RED << "Invalid option." << RESET_TEXT << endl;
                break;
            }

            searchByCaseType(root, caseType);
        }
        break;

        default:
            cout << RED << "INVALID OPTION" << RESET_TEXT << endl;
            break;
        }

        cout << BRIGHT_GREEN << "Do you want to continue (y/n)? " << RESET_TEXT;
        cin >> ch;

    } while (ch == 'y' || ch == 'Y');

    return 0;
}
