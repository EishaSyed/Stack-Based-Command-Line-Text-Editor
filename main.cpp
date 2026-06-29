#include <iostream>
#include <stack>
#include <fstream>
#include <string>
using namespace std;

stack<string> undoStack;
stack<string> redoStack;

string currentText = "";

// Add text
void addText() {
    string text;

    cout << endl << "Enter text to add: ";
    cin.ignore();
    getline(cin, text);

    undoStack.push(currentText);
    currentText += text;

    while (!redoStack.empty())
        redoStack.pop();

    cout << "Text added successfully!" << endl;
}

// Delete last characters
void deleteText() {
    if (currentText.empty()) {
        cout << "Nothing to delete." << endl;
        return;
    }

    int n;

    cout << "How many characters to delete? ";
    cin >> n;

    if (n > currentText.length())
        n = currentText.length();

    undoStack.push(currentText);

    currentText.erase(currentText.length() - n);

    while (!redoStack.empty())
        redoStack.pop();

    cout << "Text deleted." << endl;
}

// Undo (shift text from current to redo and take text from undo to current)
void undo() {
    if (undoStack.empty()) {
        cout << "Nothing to undo." << endl;
        return;
    }

    redoStack.push(currentText);

    currentText = undoStack.top();
    undoStack.pop();

    cout << "Undo successful." << endl;
}

// Redo (shift text from current to undo and take text from redo to current)
void redo() {
    if (redoStack.empty()) {
        cout << "Nothing to redo." << endl;
        return;
    }

    undoStack.push(currentText);

    currentText = redoStack.top();
    redoStack.pop();

    cout << "Redo successful." << endl;
}

// Display text
void displayText() {
    cout << endl;
    cout << "Current Text:" << endl;
    cout << "------------------------" << endl;
    cout << currentText << endl;
    cout << "------------------------" << endl;
}

// Save file
void saveFile() {
    ofstream file("texteditor.txt");

    file << currentText;

    file.close();

    cout << "File saved successfully!" << endl;
}

// Load file
void loadFile() {
    ifstream file("texteditor.txt");

    if (!file) {
        cout << "File not found." << endl;
        return;
    }

    undoStack.push(currentText);

    getline(file, currentText, '\0');

    file.close();

    while (!redoStack.empty())
        redoStack.pop();

    cout << "File loaded successfully!" << endl;
}

// Clear text
void clearText() {
    undoStack.push(currentText);

    currentText = "";

    while (!redoStack.empty())
        redoStack.pop();

    cout << "Text cleared." << endl;
}

void searchAndReplace() {
    if (currentText.empty()) {
        cout << "No text available." << endl;
        return;
    }

    string searchWord, replaceWord;

    cout << endl << "Enter text to search: ";
    cin.ignore();
    getline(cin, searchWord);

    size_t position = currentText.find(searchWord);

    if (position == string::npos) {
        cout << "Text not found." << endl;
        return;
    }

    cout << "Enter replacement text: ";
    getline(cin, replaceWord);

    // Save current state for undo
    undoStack.push(currentText);

    while (!redoStack.empty())
        redoStack.pop();

    // Replace all occurrences
    while ((position = currentText.find(searchWord)) != string::npos) {
        currentText.replace(position,
                           searchWord.length(),
                           replaceWord);
    }

    cout << "Text replaced successfully!" << endl;
}


// Main
int main() {

    int choice;

    do {
        cout << endl;
        cout << "=================================" << endl;
        cout << "      STACK TEXT EDITOR" << endl;
        cout << "=================================" << endl;
        cout << "1. Add Text" << endl;
        cout << "2. Delete Last Characters" << endl;
        cout << "3. Undo" << endl;
        cout << "4. Redo" << endl;
        cout << "5. Display Text" << endl;
        cout << "6. Save File" << endl;
        cout << "7. Load File" << endl;
        cout << "8. Search and Replace" << endl;
        cout << "9. Clear Text" << endl;
        cout << "10. Exit" << endl;
        cout << "=================================" << endl;
        cout << "Enter Choice: ";

        cin >> choice;

        switch(choice) {

        case 1:
            addText();
            break;

        case 2:
            deleteText();
            break;

        case 3:
            undo();
            break;

        case 4:
            redo();
            break;

        case 5:
            displayText();
            break;

        case 6:
            saveFile();
            break;

        case 7:
            loadFile();
            break;

        case 8:
            searchAndReplace();
            break;

        case 9:
            clearText();
            break;

        case 10:
            cout << "Program ended." << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
        }

    } while(choice != 10);

    return 0;
}
