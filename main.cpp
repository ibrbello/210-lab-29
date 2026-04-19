// COMSC-210 || Lab 29 | Ibrahim Bello
// BelloCorp Workforce Simulation

#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <ctime>

using namespace std;

const int NUM_EMPS = 10; // number of employees added or removed per quarter
const int NUM_ROLES = 3, NUM_NAMES = 50, NUM_DEPTS = 4;
const string depts[NUM_DEPTS] = {"Product","Finance","Marketing", "HR"};
// Because the roles are represented by lists and not maps, I'll just
// refer to each role by its index within the code. In the output it'll be clear
// which employees are represented by which roles
const int roles[NUM_ROLES] = {0,1,2}; // 0 = Manager,  1 = Entry-Level,  2 = Intern
const string names[NUM_NAMES] = {
    "Alice", "Brandon", "Carmen", "Derek", "Elena",
    "Felix", "Grace", "Henry", "Isla", "Jordan",
    "Kara", "Liam", "Maya", "Noah", "Olivia",
    "Pedro", "Quinn", "Rachel", "Samuel", "Tara",
    "Ursula", "Victor", "Wendy", "Xavier", "Yara",
    "Zane", "Abby", "Blake", "Chloe", "Dylan",
    "Eva", "Finn", "Gina", "Hunter", "Ivy",
    "Jake", "Kira", "Logan", "Mia", "Nathan",
    "Opal", "Preston", "Rosa", "Scott", "Tina",
    "Uma", "Vince", "Willa", "Xander", "Yusuf"
};

void displayDepartment(const string , const array<list<string>, NUM_ROLES> & );
void hiringEvent(map<string, array<list<string>, NUM_ROLES>>& , string );
void layoffEvent(map<string, array<list<string>, NUM_ROLES>>& , string );
int departmentSize( const array<list<string>, NUM_ROLES> &);


int main()
{
    srand(time(0));


  // Write tests for displayDepartment
    // create test container
    cout << "Testing display department function..." << endl;

    map<string, array<list<string>, NUM_ROLES>> testWorkforce;
    testWorkforce["Finance"][0].push_back("Alice");
    testWorkforce["HR"][0].push_back("Ibrahim");
    testWorkforce["HR"][1].push_back("Bob");
    // ensure correct output
    for (auto it = testWorkforce.begin(); it != testWorkforce.end(); it++)
    {
        displayDepartment(it->first, it->second);
    }
    // Should cout  error message
    cout << "Testing display department function on empty department..." << endl;
    map<string, array<list<string>, NUM_ROLES>> emptyWorkforce;
    for (auto it = emptyWorkforce.begin(); it != emptyWorkforce.end(); it++)
    {
        cout << "Within the loop..." << endl;
        displayDepartment(it->first, it->second);
    }
    
    /*
    // Test for departmentSize()
    array<list<string>, NUM_ROLES> testDept;
      // Populate the department with workers from each role 
      for (int i = 0; i < 10; i++) {
        testDept[0].push_back("Alice");
        testDept[1].push_back("Bob");
        testDept[2].push_back("John");
    } 
    cout << "The size of the first department should be 30 people." << endl;
    cout << "The size of the first department is: " << departmentSize(testDept) << endl;

    // Test with different number of employees in each role
    array<list<string>, NUM_ROLES> testDept2;
    for (int j = 0; j < 10; j++) {
        testDept2[0].push_back("Alice");
        if (j % 2 == 0) {
            testDept2[1].push_back("Bob");
        }
        if (j % 3 == 0) {
            testDept2[2].push_back("John");
        }
    }
    cout << "The size of the second department is: " << departmentSize(testDept2) << endl;

    // Test with empty department
    array<list<string>, NUM_ROLES> emptyDept;
    cout << "The size of the empty department is: " << departmentSize(emptyDept) << endl;
    */

    /*
    // --------------------------------------------------------
    // STEP 1: Declare the main data structure
    // A map where:
    //   Key   = department name (string)
    //   Value = array of 3 lists (Managers, Entry-Level, Interns)
    // --------------------------------------------------------
    map<string, array<list<string>, NUM_ROLES>> workforce;

    // --------------------------------------------------------
    // STEP 2: Open the external data file
    // --------------------------------------------------------
    // // Open the file (e.g., "employees.txt") using ifstream
    // // If the file does not open successfully, print an error and exit

    // --- WIREFRAME: simulate file reading with one dummy entry ---
    ifstream fin("employees.txt");
    if (!fin)
    {
        cout << "[WARNING] Could not open employees.txt. Running with dummy data." << endl;

        // Dummy data: one department entry to prove the data structure works
        workforce["Sales"][0].push_back("Alice_Manager");      // Manager
        workforce["Sales"][1].push_back("Bob_EntryLevel");     // Entry-Level
        workforce["Sales"][2].push_back("Carol_Intern");       // Intern
    }

    // --------------------------------------------------------
    // STEP 3: Read data from file and populate the map
    // --------------------------------------------------------
    // // While there are still lines to read from the file:
    // //   Read: department name, employee type (0/1/2), employee name
    // //   Insert the employee name into workforce[dept][type]
    // // Close the file after reading

    // --------------------------------------------------------
    // STEP 4: Display INITIAL STATE of BelloCorp
    // --------------------------------------------------------
    cout << "============================================" << endl;
    cout << "   BELLOCORP WORKFORCE - INITIAL STATE     " << endl;
    cout << "============================================" << endl;

    // // Iterate through each entry in the map
    // // For each department, call displayDepartment()

    // --- WIREFRAME ---
    for (auto it = workforce.begin(); it != workforce.end(); it++)
    {
        displayDepartment(it->first, it->second);
    }

    // --------------------------------------------------------
    // STEP 5: Run the discrete-event simulation (25 time periods)
    // --------------------------------------------------------
    // // For each time period from 1 to 25:
    // //   Print the current time period number
    // //   Randomly select a department from the map
    // //   Randomly decide which event occurs:
    // //     0 = No event (quiet period)
    // //     1 = Hiring Surge -> call hiringEvent()
    // //     2 = Layoff       -> call layoffEvent()

    cout << "\n============================================" << endl;
    cout << "       RUNNING SIMULATION (25 PERIODS)      " << endl;
    cout << "============================================" << endl;

    // --- WIREFRAME: run just 3 dummy periods to show simulation flow ---
    for (int period = 1; period <= 3; period++)
    {
        cout << "\n--- Time Period " << period << " ---" << endl;

        // // [In full implementation] pick random dept & random event
        // Dummy: alternate between hiring and layoff on "Sales"
        if (period % 2 == 1)
        {
            hiringEvent(workforce, "Sales");
        }
        else
        {
            layoffEvent(workforce, "Sales");
        }
    }

    


    // --------------------------------------------------------
    // STEP 6: Display FINAL STATE of BelloCorp after simulation
    // --------------------------------------------------------
    cout << "\n============================================" << endl;
    cout << "    BELLOCORP WORKFORCE - FINAL STATE       " << endl;
    cout << "============================================" << endl;

    // // Iterate through the map again and call displayDepartment() for each

    // --- WIREFRAME ---
    for (auto it = workforce.begin(); it != workforce.end(); it++)
    {
        displayDepartment(it->first, it->second);
    }
    */
    return 0;
}

// FUNCTION: displayDepartment
// Purpose: Neatly print all employees in a given department,
//          organized by their type (Manager, Entry-Level, Intern)
// Parameters: department name (string), array of three lists (employees by type)

void displayDepartment(string deptName, const array<list<string>, NUM_ROLES> & department_emps) {
    // // Print the department name as a header
    cout << "=== Department: " << deptName << " ===" << endl;

    // Print message if department is empty
    int deptSize = departmentSize(department_emps);
    if (deptSize == 0) {
        cout << "The department is empty." << endl;
        return;
    }

    // Trying to print using a nested loop, instead of 3 separate loops for each role
    string role_names[NUM_ROLES] = {"Managers", "Entry-Level Associates", "Interns"};
    // // For each role category, iterate through the list and print each employee name
    for (int i = 0; i <= 2; i++) {
        cout << role_names[i] << ": {";
        // Loop through each role within the department and print out the name of each employee
        // The employe variable should be the value within the list, which is a string
        for (auto employee : department_emps[i]) {
            cout << employee << ", ";
        }
        cout << "}" << endl;
    }
  
}

// FUNCTION: hiringEvent
// Purpose: Simulate a hiring surge by adding employees to a department
// Parameters: reference to the map (so changes persist), department name (string)

void hiringEvent(map<string, array<list<string>, NUM_ROLES>>& workforce, string dept) {
    // Randomly determine how many employees to hire (1-10)
    int num_emps = rand() % 10 + 1;
    // // Randomly determine which employee type to hire (0=Manager, 1=Entry-Level, 2=Intern)
    int role = roles[rand() % NUM_ROLES];
    // // For Loop num_emps times. For each run, pick random name and add it to the correct list
    for (int i = 0; i < num_emps; i++) {
        string emp_name = names[rand() % NUM_NAMES];
        workforce[dept][role].push_back(emp_name);
    }
    // // Print a message announcing the hiring event, e.g.:
    cout << "[EVENT] Hiring Surge in " << dept << ": Added " << num_emps << " new employee(s)." << endl;
}

// FUNCTION: layoffEvent
// Purpose: Simulate a layoff by removing employees from a department
// Parameters: reference to the map, department name (string)

void layoffEvent(map<string, array<list<string>, NUM_ROLES>>& workforce, string dept) {
    // Randomly determine which employee type category to lay off from

    // Make sure the chosen list is not empty before removing

    // Randomly determine how many employees to remove (cannot exceed list size)

    // Remove that many employees from the list

    // Print a message announcing the layoff, e.g.:
    // "LAYOFF in [dept]: Removed [n] [type] employee(s)."

    // --- WIREFRAME (dummy output to demonstrate function works) ---
    cout << "[EVENT] Layoff in " << dept << ": Removed 1 Intern(s)." << endl;
    if (!workforce[dept][2].empty())
    {
        workforce[dept][2].pop_front();  // dummy: remove first intern
    }
}

// FUNCTION: departmentSize
// Purpose: Find the number of employees in a department across all roles
// Since I need to find the size of a department several times in the program
// (testing whether hiring/layoff worked, determining whether a department is empty)
// I've decided to add this function
// Parameters: reference to the map, department name (string)
int departmentSize(const array<list<string>, NUM_ROLES> & department_emps) {
    int deptSize = 0;
    // Iterate over the array, summing the size of each list
    for (int i = 0; i < NUM_ROLES; i++) {
        deptSize += department_emps[i].size();
    }
    return deptSize;
}
