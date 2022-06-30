#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

void repayDebt(double** edges, int n, unordered_map<string, int>& userMap, string group)
{
    double amount;
    cout << "Enter -1, when there is no one left for pay debt." << endl;
    cout << "\nHow much amount debt completes : ";
    cin >> amount;

    while(amount != -1)
    {
        if(amount <= 0)
        {
            cout << "\nWrong amount !!" << endl;
            return;
        }

        string nameWhoPaid, nameWhoReceived;
        cout << "Who Paid : ";
        cin >> nameWhoPaid;
        cout << "Who received : ";
        cin >> nameWhoReceived;

        if(userMap.count(nameWhoPaid) == 0)
        {
            cout << "Person " << nameWhoPaid << " doesn't exist in group " << group  << " !!"<< endl;
            return;
        }

        if(userMap.count(nameWhoReceived) == 0)
        {
            cout << "Person " << nameWhoReceived << " doesn't exist in group " << group  << " !!"<< endl;
            return;
        }

        int personWhoPaid = userMap[nameWhoPaid];
        int personWhoReceived = userMap[nameWhoReceived];

        edges[personWhoReceived][personWhoPaid] = edges[personWhoReceived][personWhoPaid] + amount;

        if(edges[personWhoReceived][personWhoPaid] > edges[personWhoPaid][personWhoReceived])
        {
            edges[personWhoReceived][personWhoPaid] = edges[personWhoReceived][personWhoPaid] - edges[personWhoPaid][personWhoReceived];
            edges[personWhoPaid][personWhoReceived] = 0;
        }
        else if(edges[personWhoReceived][personWhoPaid] == edges[personWhoPaid][personWhoReceived])
        {
            edges[personWhoReceived][personWhoPaid] = 0;
            edges[personWhoPaid][personWhoReceived] = 0;
        }
        else
        {
            edges[personWhoPaid][personWhoReceived] = edges[personWhoPaid][personWhoReceived] - edges[personWhoReceived][personWhoPaid];
            edges[personWhoReceived][personWhoPaid] = 0;
        }

        cout << "\nHow much amount debt completes : ";
        cin >> amount;
    }
}

void addExpense(double** edges, int n, unordered_map<string, int>& userMap, string group)
{
    double expense;
    cout << "Enter -1, if there is no more expenses." << endl;
    cout << "\nEnter the Expenses to group " << group << " : ";
    cin >> expense;

    while(expense != -1)
    {
        if(expense <= 0)
        {
            cout << "Wrong Expense !!" << endl;
            return;
        }

        string nameWhoPaid;
        cout << "Who Paid : ";
        cin >> nameWhoPaid;

        if(userMap.count(nameWhoPaid) == 0)
        {
            cout << "Person " << nameWhoPaid << " doesn't exist in group " << group  << " !!"<< endl;
            return;
        }

        int personWhoPaid = userMap[nameWhoPaid];

        int option;
        cout << "Enter 1, for add expense to whole group " << group << endl;
        cout << "Enter 2, for add expense to some people of " << group << endl;
        cin >> option;

        if(option == 1)
        {
            for(int i=0; i<n; i++)
            {
                if(i == personWhoPaid)
                {
                    continue;
                }

                double expensePerPerson = expense/n;
                edges[i][personWhoPaid] = edges[i][personWhoPaid] + expensePerPerson;

                if(edges[i][personWhoPaid] > edges[personWhoPaid][i])
                {
                    edges[i][personWhoPaid] = edges[i][personWhoPaid] - edges[personWhoPaid][i];
                    edges[personWhoPaid][i] = 0;
                }
                else if(edges[i][personWhoPaid] == edges[personWhoPaid][i])
                {
                    edges[i][personWhoPaid] = 0;
                    edges[personWhoPaid][i] = 0;
                }
                else
                {
                    edges[personWhoPaid][i] = edges[personWhoPaid][i] - edges[i][personWhoPaid];
                    edges[i][personWhoPaid] = 0;
                }
            }
        }
        else if(option == 2)
        {
            int i;
            cout << "Enter number of peoples involved in expense : ";
            cin >> i;

            if(i>n-1 || i<1)
            {
                cout << "Entered number of peoples are not possible." << endl;
                return;
            }

            for(int j=1; j<i; j++)
            {
                string includedName;
                cout << "Enter " << j << "th person : ";
                cin >> includedName;

                if(userMap.count(includedName) == 0)
                {
                    cout << "Person " << includedName << " doesn't exist in group " << group  << " !!"<< endl;
                    return;
                }

                int includedPerson = userMap[includedName];

                if(includedPerson == personWhoPaid)
                {
                    j--;
                    continue;
                }

                double expensePerPerson = expense/i;
                edges[includedPerson][personWhoPaid] = edges[includedPerson][personWhoPaid] + expensePerPerson;

                if(edges[includedPerson][personWhoPaid] > edges[personWhoPaid][includedPerson])
                {
                    edges[includedPerson][personWhoPaid] = edges[includedPerson][personWhoPaid] - edges[personWhoPaid][includedPerson];
                    edges[personWhoPaid][includedPerson] = 0;
                }
                else if(edges[includedPerson][personWhoPaid] == edges[personWhoPaid][includedPerson])
                {
                    edges[includedPerson][personWhoPaid] = 0;
                    edges[personWhoPaid][includedPerson] = 0;
                }
                else
                {
                    edges[personWhoPaid][includedPerson] = edges[personWhoPaid][includedPerson] - edges[includedPerson][personWhoPaid];
                    edges[includedPerson][personWhoPaid] = 0;
                }
            }
        }
        else
        {
            cout << "Option doesn't exist!" << endl;
            return;
        }

        cout << "\nEnter the Expenses to group " << group << " : ";
        cin >> expense;
    }
}

void currentPosition(double** edges, int n, unordered_map<int, string>& ourMap)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(edges[i][j] != 0)
            {
                cout << ourMap[j] << " wants " << edges[i][j] << " rupees from " << ourMap[i] << endl;
            }
        }
    }
}

int main()
{
    string group;
    cout << "Enter the group name : ";
    cin >> group;

    int n;
    cout << "Enter number of people in group " << group << " : ";
    cin >> n;

    if(n < 1)
    {
        cout << "Invalid person in group " << group << endl;
        return 0;
    }

    unordered_map<int, string> ourMap;
    unordered_map<string, int> userMap;

    cout << "Enter the names of people in group " << group << " :-" << endl;
    for(int i=0; i<n; i++)
    {
        string name;
        cin >> name;

        ourMap[i] = name;
        userMap[name] = i;
    }

    double** edges = new double*[n];
    for(int i=0; i<n; i++)
    {
        edges[i] = new double[n];
        for(int j=0; j<n; j++)
        {
            edges[i][j] = 0;
        }
    }

    cout << "\n************ MAIN MENU *************" << endl << endl;
    cout << "Enter  1 : For add expense to group " << group << endl;
    cout << "Enter  2 : If anyone wants to repay his/her debt." << endl;
    cout << "Enter  3 : For check current position of debt of group " << group << endl;
    cout << "Enter -1 : For exit." << endl;

    int i;
    cout << "\nEnter function that you want to perform : ";
    cin >> i;

    while(i != -1)
    {
        switch(i)
        {
            case 1 : addExpense(edges, n, userMap, group);
            break;

            case 2 : repayDebt(edges, n, userMap, group);
            break;

            case 3 : currentPosition(edges, n, ourMap);
            break;

            default : cout << "Wrong Input!" << endl;
        }

        cout << "***********************************" << endl << endl;
        cout << "\n************ MAIN MENU *************" << endl << endl;
        cout << "Enter  1 : For add expense to group " << group << endl;
        cout << "Enter  2 : If anyone wants to repay his/her debt." << endl;
        cout << "Enter  3 : For check current position of debt of group " << group << endl;
        cout << "Enter -1 : For exit." << endl;
        cout << "\nEnter function that you want to perform : ";
        cin >> i;
    }
    cout << "You are Exit." << endl;

    for(int i=0; i<n; i++)
    {
        delete [] edges[i];
    }
    delete [] edges;

    return 0;
}
