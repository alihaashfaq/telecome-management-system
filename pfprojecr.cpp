
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
const int MAX = 100;
int custID[MAX];
string custName[MAX];
string custPlan[MAX];
float prepaidBal[MAX];
float postpaidBill[MAX];
int total = 0;
int findCustomer(int id) {
    for (int i = 0; i < total; i++) {
        if (custID[i] == id)
            return i;
    }
    return -1;
}
void line() {
    cout<<endl<<"--------------------------------------------------"<<endl;
}
void customerMenu() {
    int choice;
    do {
        line();
        cout<<"CUSTOMER MANAGEMENT MENU"<<endl;
        cout<<"1. Add Customer"<<endl;
        cout<<"2. Update Customer"<<endl;
        cout<<"3. Delete Customer"<<endl;
        cout<<"4. View All Customers"<<endl;
        cout<<"5. Back to Main Menu"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        if (choice == 1) {
            int id;
            cout<<"Enter Customer ID: ";
            cin>>id;
            if (findCustomer(id) != -1) {
                cout<<"Customer already exists!"<<endl;
                continue;
            }
            custID[total] = id;
            cout<<"Enter Customer Name: ";
            cin>>custName[total];
            int planChoice;
            cout<<"Select Plan:"<<endl<<"1. Prepaid"<<endl<<"2. Postpaid"<<endl<<"Choice: ";
            cin>>planChoice;
            if (planChoice == 1) {
                custPlan[total] = "Prepaid";
                cout<<"Enter Initial Balance: ";
                cin>>prepaidBal[total];
                postpaidBill[total] = 0;
            } else {
                custPlan[total] = "Postpaid";
                prepaidBal[total] = 0;
                postpaidBill[total] = 0;
            }
            total++;
            cout<<"Customer added successfully!"<<endl;
        }
        else if (choice == 2) {
            int id;
            cout<<"Enter Customer ID to update: ";
            cin>>id;
            int index = findCustomer(id);
            if (index == -1) {
                cout<<"Customer not found!"<<endl;
            } else {
                cout<<"Enter new name: ";
                cin>>custName[index];
                cout<<"Customer updated successfully!"<<endl;
            }
        }
        else if (choice == 3) {
            int id;
            cout<<"Enter Customer ID to delete: ";
            cin>>id;
            int index = findCustomer(id);
            if (index == -1) {
                cout<<"Customer not found!"<<endl;
            } else {
                for (int i = index; i < total - 1; i++) {
                    custID[i] = custID[i + 1];
                    custName[i] = custName[i + 1];
                    custPlan[i] = custPlan[i + 1];
                    prepaidBal[i] = prepaidBal[i + 1];
                    postpaidBill[i] = postpaidBill[i + 1];
                }
                total--;
                cout<<"Customer deleted successfully!"<<endl;
            }
        }
        else if (choice == 4) {
            if (total == 0) {
                cout<<"No customers available."<<endl;
            } else {
                cout<<left<<setw(10)<<"ID"
                    <<setw(15)<<"Name"
                    <<setw(12)<<"Plan"
                    <<setw(10)<<"Balance"
                    <<setw(10)<<"Bill"<<endl;
                line();
                for (int i = 0; i < total; i++) {
                    cout<<left<<setw(10)<<custID[i]
                        <<setw(15)<<custName[i]
                        <<setw(12)<<custPlan[i]
                        <<setw(10)<<prepaidBal[i]
                        <<setw(10)<<postpaidBill[i]<<endl;
                }
            }
        }
    } while (choice != 5);
}
void usageMenu() {
    int choice;
    do {
        line();
        cout<<"USAGE & SERVICES MENU"<<endl;
        cout<<"1. Record Call"<<endl;
        cout<<"2. Recharge Prepaid Balance"<<endl;
        cout<<"3. Back to Main Menu"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        if (choice == 1) {
            int id;
            float minutes;
            cout<<"Enter Customer ID: ";
            cin>>id;
            int index = findCustomer(id);
            if (index == -1) {
                cout<<"Customer not found!"<<endl;
                continue;
            }
            cout<<"Enter Call Duration (minutes): ";
            cin>>minutes;
            float rate = 2.0;
            if (custPlan[index] == "Prepaid") {
                float cost = minutes * rate;
                if (prepaidBal[index] >= cost) {
                    prepaidBal[index] -= cost;
                    cout<<"Call recorded. Balance updated."<<endl;
                } else {
                    cout<<"Insufficient balance!"<<endl;
                }
            } else {
                postpaidBill[index] += minutes * rate;
                cout<<"Call recorded. Bill updated."<<endl;
            }
        }
        else if (choice == 2) {
            int id;
            float amount;
            cout<<"Enter Customer ID: ";
            cin>>id;
            int index = findCustomer(id);

            if (index == -1 || custPlan[index] != "Prepaid") {
                cout<<"Invalid prepaid customer!"<<endl;
                continue;
            }
            cout<<"Enter Recharge Amount: ";
            cin>>amount;
            prepaidBal[index] += amount;
            cout<<"Recharge successful!"<<endl;
        }
    } while (choice != 3);
}
void billingMenu() {
    int choice;
    do {
        line();
        cout<<"BILLING & PAYMENTS MENU"<<endl;
        cout<<"1. View Bill / Balance"<<endl;
        cout<<"2. Pay Postpaid Bill"<<endl;
        cout<<"3. Back to Main Menu"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        if (choice == 1) {
            int id;
            cout<<"Enter Customer ID: ";
            cin>>id;
            int index = findCustomer(id);
            if (index == -1) {
                cout<<"Customer not found!"<<endl;
            } else {
                if (custPlan[index] == "Prepaid")
                    cout<<"Remaining Balance: "<<prepaidBal[index]<<endl;
                else
                    cout<<"Total Bill: "<<postpaidBill[index]<<endl;
            }
        }
        else if (choice == 2) {
            int id;
            float amount;
            cout<<"Enter Customer ID: ";
            cin>>id;
            int index = findCustomer(id);
            if (index == -1 || custPlan[index] != "Postpaid") {
                cout<<"Invalid postpaid customer!"<<endl;
                continue;
            }
            cout<<"Current Bill: "<<postpaidBill[index]<<endl;
            cout<<"Enter Payment Amount: ";
            cin>>amount;
            if (amount <= postpaidBill[index]) {
                postpaidBill[index] -= amount;
                cout<<"Payment successful!"<<endl;
            } else {
                cout<<"Amount exceeds bill!"<<endl;
            }
        }
    } while (choice != 3);
}
void searchMenu() {
    int id;
    cout<<"Enter Customer ID to search: ";
    cin>>id;
    int index = findCustomer(id);

    if (index == -1) {
        cout<<"Customer not found!"<<endl;
    } else {
        cout<<"Name: "<<custName[index]<<endl;
        cout<<"Plan: "<<custPlan[index]<<endl;
    }
}
int main() {
    int choice;
    do {
        line();
        cout<<"TELECOM BILLING SYSTEM"<<endl;
        cout<<"1. Customer Management"<<endl;
        cout<<"2. Usage & Services"<<endl;
        cout<<"3. Billing & Payments"<<endl;
        cout<<"4. Search & Reports"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        if (choice == 1) customerMenu();
        else if (choice == 2) usageMenu();
        else if (choice == 3) billingMenu();
        else if (choice == 4) searchMenu();
        else if (choice == 5) cout<<"Exiting system..."<<endl;
        else cout<<"Invalid choice!"<<endl;
    } while (choice != 5);

    return 0;
}
