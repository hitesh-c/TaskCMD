/*
Usage :-·
    $ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list·
    $ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order·
    $ ./task del INDEX            # Delete the incomplete item with the given index·
    $ ./task done INDEX           # Mark the incomplete item with the given index as complete·
    $ ./task help                 # Show usage·
    $ ./task report               # Statistics·
    
                                                                                                    
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

void sort_file(string f)                    //Function to sort tasks in txt files
{
    //cout << "sortcalled";
    ifstream is(f);
    string line;
    vector<string> text;
    while (getline(is, line))
    {
        text.push_back(line);
    }
    is.close();
    sort(text.begin(), text.end()); 
    ofstream fout("task.txt", ios::out);
    for (auto i : text)
    {
        fout << i << endl;
    }
    fout.close();
}

int count_file(string f)                //Function to count tasks in txt file
{
    ifstream is(f);
    string line;

    int index = 0;
    while (getline(is, line))
    {
        index++;
    }
    is.close();
    return index;
}

void done(string i)                              //Function to mark tasks done in txt file
{

    stringstream index(i);
    int x = 0;
    index >> x;
    int limit = count_file("task.txt");
    if (x > limit || x < 1)
    {
        cout << "Error: no incomplete item with index #" << x << " exists.";
        return;
    }

    int check = 1;
    ifstream is("task.txt");
    string line;
    vector<string> text;
    vector<string> text1;
    while (getline(is, line))
    {
        if (check == x)
        {
            check++;
            text.push_back(line);
        }
        else
        {
            check++;
            text1.push_back(line);
        }
    }
    is.close();
    //  sort(text.begin(), text.end()); //sortin
    ofstream fouc("cmpltd.txt", ios::app);

    for (auto i : text)
    {

        fouc << i << endl;

        //cout << i <<endl;
    }
    fouc.close();

    ofstream task_fout("task.txt", ios::out);
    for (auto i : text1)
    {
        task_fout << i << endl;
        //cout << i <<endl;
    }
    task_fout.close();

    cout << "Marked item as done." << '\n';
}

void del(string i)                   //Function to del tasks in txt file
{
    stringstream index(i);
    int x = 0;
    index >> x;
    int limit = count_file("task.txt");
    if (x > limit || x < 1)
    {
        cout << "Error: task with index #" << x << " does not exist. Nothing deleted.";
        return;
    }
    int check = 1;
    ifstream is("task.txt");
    string line;
    vector<string> text;
    while (getline(is, line))
    {
        if (check == x)
        {
            check++;
            continue;
        }
        text.push_back(line);
        check++;
    }
    is.close();
    sort(text.begin(), text.end()); //sortin
    ofstream fout("task.txt", ios::out);
    for (auto i : text)
    {
        fout << i << endl;
        //cout << i <<endl;
    }
    fout.close();
    cout << "Deleted task #" << i << '\n';
}

void add_task(int n, char *text[])               //Function to ADD tasks in txt file
{ //add task function
    if (n == 2)
    {
        cout << "Error: Missing tasks string. Nothing added!";
        return;
    }

    ofstream fout("task.txt", ios::app);

    for (int i = 2; i < n; i++)
    {
        fout << text[i];
        if (n - i != 1)
            fout << " ";
    }
    fout << endl;
    fout.close();

    sort_file("task.txt"); //sorting in task.txt

    cout << "Added task: \"";
    for (int i = 3; i < n; i++)
    {
        cout << text[i];
        if (n - i != 1)
            cout << " ";
    }
    cout << "\" with priority " << text[2] << "." << '\n';
};

int list_file(string f)                          //Function to list tasks from txt file
{
    ifstream is(f);
    string line;

    int index = 1;
    while (getline(is, line, '\n'))
    {
        cout << index << ".";
        cout << " " << line.substr(2) << " [" << line[0] << "]" << '\n';
        index++;
    }
    return index;
    is.close();
}

void help()                          //Function to display help.txt
{

    ifstream is("help.txt");
    string line;
    string msg;
    while (getline(is, line))
    {
        msg = msg + line + '\n';
    }
    cout << msg;
    is.close();
};

//function to identify task

void identify_task(string task, char *text[], int n)
{
    if (task == "add")
    {
        add_task(n, text);
    }
    else if (task == "ls")
    {
        int cnt = count_file("task.txt");
        if (cnt == 0)
        {
            cout << "There are no pending tasks!";
        }
        else
            list_file("task.txt");
    }
    else if (task == "del")
    {
        if (n == 2)
        {
            cout << "Error: Missing NUMBER for deleting tasks.";
            return;
        }
        del(text[2]);
    }
    else if (task == "done")
    {
        if (n == 2)
        {
            cout << "Error: Missing NUMBER for marking tasks as done.";
            return;
        }
        done(text[2]);
    }
    else if (task == "help")
    {
        help();
    }
    else if (task == "report")
    {
        cout << "Pending :" << count_file("task.txt") << '\n';
        int cnt = count_file("task.txt");
        if (cnt != 0)
        {
            list_file("task.txt");
        }
        cout << "Completed :" << count_file("cmpltd.txt") << '\n';
        cnt = count_file("cmpltd.txt");
        if (cnt != 0)
        {
            ifstream is("cmpltd.txt");
            string line;
            int index = 1;
            while (getline(is, line))
            {
                cout << index << ".";
                cout << " " << line.substr(2) << '\n';
                index++;
            }

            is.close();
        }
    }
    else
    {
        help();
    }
}

//DRIVER CODE

int main(int n, char *args[])
{
    // std::cout << "Hello, world!";

    if (n == 1)
    {   help();
        return 0; }

    string task = args[1];
    identify_task(task, args, n);
    return 0;
}
