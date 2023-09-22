#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Person {
    string name;
    double amountPaid;
    double amountOwed;

    Person(string n, double paid) : name(n), amountPaid(paid), amountOwed(0) {}
};

struct Node {
    Person data;
    Node* next;

    Node(Person p) : data(p), next(nullptr) {}
};

class reimburseCalc {
private:
    Node* head;

public:
    reimburseCalc() : head(nullptr) {}

    void addPerson(Person p) {
        Node* newNode = new Node(p);
        newNode->next = head;
        head = newNode;
    }

    void readFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            size_t spacePos = line.find(' ');

            if (spacePos != string::npos) {
                double amountPaid = stod(line.substr(0, spacePos));
                string name = line.substr(spacePos + 1);

                Person p(name, amountPaid);
                addPerson(p);
            }
        }

        file.close();
    }

    void interpretDebt() {
        double totalAmountPaid = 0;
        int numPeople = 0;
        Node* current = head;

        while (current != nullptr) {
            totalAmountPaid += current->data.amountPaid;
            numPeople++;
            current = current->next;
        }

        double equalShare = totalAmountPaid / numPeople;

        current = head;
        while (current != nullptr) {
            current->data.amountOwed = equalShare - current->data.amountPaid;
            cout << current->data.name << " should ";
            if (current->data.amountOwed < 0) {
                cout << "do nothing";
            } else if (current->data.amountOwed > 0) {
                cout << "pay $" << current->data.amountOwed;
            } else {
                cout << "do nothing";
            }
            cout << endl;
            current = current->next;
        }
    }

    ~reimburseCalc() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;

    reimburseCalc splitter;
    splitter.readFile(filename);
    splitter.interpretDebt();

    return 0;
}
