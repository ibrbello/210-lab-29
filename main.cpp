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

    
    // --------------------------------------------------------
    // STEP 1: Declare the main data structure
    // A map where:
    //   Key   = department name (string)
    //   Value = array of 3 lists (Managers, Entry-Level, Interns)
    // --------------------------------------------------------
    map<string, array<list<string>, NUM_ROLES>> workforce;

    // --------------------------------------------------------
    // STEP 2: Read data from the file and populate the map
    // --------------------------------------------------------
    // This will provide BelloCorp's workforce at the beginning of the
    // 10-year period.

    // Temporary variables for each employee read from file
    string d; // temp department
    string r; // temp role
    string n; // temp name


    ifstream fin("employees.txt");
    if (fin.good()) {
        while (fin >> d) {
            fin >> r;
            fin >> n;
        int role = 0;
        // convert the role name in the file to an index
        if (r == "Manager") role = 0;
            workforce[d][role].push_back(n);
        }
        fin.close();
    }
    else
        cout << "Input file not found. Please try again." << endl;

    // --------------------------------------------------------
    // STEP 3: Display INITIAL STATE of BelloCorp
    // --------------------------------------------------------
    cout << "============================================" << endl;
    cout << "   BELLOCORP WORKFORCE - INITIAL STATE     " << endl;
    cout << "============================================" << endl;

    // // Iterate through each entry in the map
    // // For each department, call displayDepartment()

    for (auto it = workforce.begin(); it != workforce.end(); it++)
    {
        displayDepartment(it->first, it->second);
    }

    // --------------------------------------------------------
    // STEP 5: Run the discrete-event simulation (40 time periods)
    // --------------------------------------------------------
    // // For each time period from 1 to 40:
    // //   Print the current time period number
    // //   Randomly select a department from the map
    // //   Randomly decide which event occurs:
    // //     0 = No event (quiet period)
    // //     1 = Hiring Surge -> call hiringEvent()
    // //     2 = Layoff       -> call layoffEvent()

    cout << "\n============================================" << endl;
    cout << "       RUNNING SIMULATION (40 PERIODS)      " << endl;
    cout << "============================================" << endl;

    // --- WIREFRAME: run just 3 dummy periods to show simulation flow ---
    for (int period = 1; period <= 40; period++)
    {
        cout << "\n--- Quarter " << period << " ---" << endl;
        // // Pick random dept
        string chosen_dept = depts[rand() % NUM_DEPTS];
        // Randomly choose which event will occur in this period
        // 0 = nothing, 1 = hiring surge, 2 = layoff
        int event = rand() % 2;

        switch (event) {
            case 0:
                // Nothing happens
                cout << "[NO EVENT] Nothing happened this quarter." << endl;
                break;
            case 1: 
                // Hiring event
                hiringEvent(workforce, chosen_dept);
                break;
            case 2:
                // Layoff
                layoffEvent(workforce, chosen_dept);
                break;
            default:
                cout << "Something's off. Please try again." << endl;
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
    int hire_size = rand() % NUM_EMPS + 1;
    // For Loop num_emps times. For each run, pick random name and role, and add employee
    for (int i = 0; i < hire_size; i++) {
        // // Randomly determine which employee type to hire (0=Manager, 1=Entry-Level, 2=Intern)
        int role = roles[rand() % NUM_ROLES];
        string emp_name = names[rand() % NUM_NAMES];
        workforce[dept][role].push_back(emp_name);
    }
    // // Print a message announcing the hiring event
    cout << "[EVENT] Hiring Surge in " << dept << ": Added " << hire_size << " new employee(s)." << endl;
}

// FUNCTION: layoffEvent
// Purpose: Simulate a layoff by removing employees from a department
// Parameters: reference to the map, department name (string)

void layoffEvent(map<string, array<list<string>, NUM_ROLES>>& workforce, string dept) {
    // If department is empty, print message and don't layoff
    if (departmentSize(workforce[dept]) == 0) {
        cout << "[EVENT] Layoff in " << dept <<
         ": The department had no employees, so no one was laid off." << endl;
        return;
    }
    // Randomly determine how many employees to hire (1-10)
    int layoff_size = rand() % NUM_EMPS + 1;

    // If a layoff doesn't actually happen because there were no employees in that role,
    // this variable won't be incremented. That way, the outputted number of layoffs is accurate
    int layoffs_completed = 0;

    // For loop num_emps times. For each iteration, determine which role to fire from
    // and pick a random name from the list
    for (int i = 0; i < layoff_size; i++) {
        // Randomly determine which employee type category to lay off from
        int role = roles[rand() % NUM_ROLES];
        // Make sure that specific role is not empty
        auto & doomed_role = workforce[dept][role];
        int role_size = doomed_role.size();
        if (role_size == 0) {
            // Don't layoff, just move on
            continue;
        }
        else {
            // Pick a random person. Can't use [rand % ] bc lists don't have random
            // access, so use iterators
            auto it = doomed_role.begin();
            advance(it, rand() % role_size);
            // Now that the iterator is pointing to the right employee, fire them
            doomed_role.erase(it);
            // Successful layoff, so increment layoff counter
            layoffs_completed++;
        }
    }
    // Print a message announcing the layoff
    cout << "[EVENT] Layoff in " << dept << ": Fired " << layoffs_completed << " employees." << endl;

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
