#include <iostream>
#include <string>
#include <map>
#include <cstdlib>  // For system("cls") to clear the screen
#include <windows.h> // For changing text color on Windows
using namespace std;

map<string, string> variables;

// Function to declare a variable
void declareVariable(const string& name, const string& value) {
    variables[name] = value;
}

// Function to get the value of a variable
string getVariable(const string& name) {
    return variables[name];
}

// Function to evaluate conditions
bool evaluateCondition(const string& condition) {
    size_t eq_pos = condition.find(" == ");
    if (eq_pos != string::npos) {
        string var_name = condition.substr(0, eq_pos);
        string value = condition.substr(eq_pos + 4);
        return getVariable(var_name) == value;
    }
    return false;  // Return false if the condition doesn't match
}

// Function to change text color in the console
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to process the input code
void processCode(string code) {
    if (code.find("if") == 0) {  // If it's an "if" statement
        size_t open_brace = code.find("{");
        size_t close_brace = code.find("}");
        string condition = code.substr(3, open_brace - 3); // Extract condition

        // Handle AND conditions with "ndnd"
        size_t and_pos = condition.find("ndnd");
        if (and_pos != string::npos) {
            string left_condition = condition.substr(0, and_pos);
            string right_condition = condition.substr(and_pos + 4);

            if (evaluateCondition(left_condition) && evaluateCondition(right_condition)) {
                setColor(10); // Green for success
                cout << "Condition met!" << endl;
                setColor(7);  // Reset to normal text color
            } else {
                setColor(12); // Red for failure
                cout << "Condition not met." << endl;
                setColor(7);  // Reset to normal text color
            }
        } else {
            // Single condition check
            if (evaluateCondition(condition)) {
                setColor(10); // Green for success
                cout << "Condition met!" << endl;
                setColor(7);  // Reset to normal text color
            } else {
                setColor(12); // Red for failure
                cout << "Condition not met." << endl;
                setColor(7);  // Reset to normal text color
            }
        }
    } else if (code.find("output.print:") == 0) {  // Output print statement
        string message = code.substr(14);  // Extract message after "output.print:"
        setColor(14); // Yellow for output
        cout << message << endl;
        setColor(7);  // Reset to normal text color
    } else if (code.find("var") == 0) {  // Variable assignment
        size_t eq_pos = code.find(" = ");
        if (eq_pos != string::npos) {
            string var_name = code.substr(4, eq_pos - 4);
            string var_value = code.substr(eq_pos + 3);
            declareVariable(var_name, var_value);
            setColor(9); // Blue for variable assignment
            cout << "Variable " << var_name << " set to " << var_value << endl;
            setColor(7);  // Reset to normal text color
        } else {
            setColor(12); // Red for error
            cout << "Error: Invalid variable assignment." << endl;
            setColor(7);  // Reset to normal text color
        }
    } else {
        setColor(12); // Red for error
        cout << "Your code has errors. :(" << endl;
        setColor(7);  // Reset to normal text color
    }
}

int main() {
    system("color 1E");
    string code;
    string input;
    setColor(11); // Cyan for the IDE welcome message
    cout << "Welcome to i-sharp (i#) IDE (Terminal-based)" << endl;
    setColor(7);  // Reset to normal text color

    // Declare some sample variables
    declareVariable("y", "mafaka");
    declareVariable("x", "yo yo");

    cout << "Enter i# code below (type 'exit' to quit):" << endl;

    // Interactive loop for continuous input
    while (true) {
        cout << "> ";  // Prompt user for input
        getline(cin, code);  // Read full line of input

        if (code == "exit") {
            setColor(13); // Magenta for exit message
            cout << "Exiting i-sharp IDE." << endl;
            setColor(7);  // Reset to normal text color
            break;  // Exit the loop and the program
        }

        // Process the code entered
        processCode(code);
    }

    return 0;
}
