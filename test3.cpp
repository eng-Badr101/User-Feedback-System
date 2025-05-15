#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;
#define size 10

struct user
{
    string username;
    string email;
    string address;
    string password;

    string feedback_message[size];
    string feedback_type[size];
    int priority[size];
    int feedback_count = 0;
};

const string admin_passkey = "admin";

user feedbacks[1000];
int feedback_index = 0;

void save_data_to_file()
{
    ofstream file("feedback_data.txt");
    if (!file)
    {
        cout << "Error opening file for saving.\n";
        return;
    }

    file << feedback_index << "\n";
    for (int i = 0; i < feedback_index; ++i)
    {
        file << feedbacks[i].username << "\n"
             << feedbacks[i].email << "\n"
             << feedbacks[i].address << "\n"
             << feedbacks[i].password << "\n"
             << feedbacks[i].feedback_count << "\n";

        for (int j = 0; j < feedbacks[i].feedback_count; ++j)
        {
            file << feedbacks[i].feedback_type[j] << "\n"
                 << feedbacks[i].feedback_message[j] << "\n"
                 << feedbacks[i].priority[j] << "\n";
        }
    }
    file.close();
}

void load_data_from_file()
{
    ifstream file("feedback_data.txt");
    if (!file)
    {
        cout << "No previous data found.\n";
        return;
    }

    file >> feedback_index;
    file.ignore();

    for (int i = 0; i < feedback_index; ++i)
    {
        getline(file, feedbacks[i].username);
        getline(file, feedbacks[i].email);
        getline(file, feedbacks[i].address);
        getline(file, feedbacks[i].password);
        file >> feedbacks[i].feedback_count;
        file.ignore();

        for (int j = 0; j < feedbacks[i].feedback_count; ++j)
        {
            getline(file, feedbacks[i].feedback_type[j]);
            getline(file, feedbacks[i].feedback_message[j]);
            file >> feedbacks[i].priority[j];
            file.ignore();
        }
    }
    file.close();
}

void menu();
void registration();
void login();
void feedback_form(user &fb);
void feedback_edit(int i);
void feedback_delete(int i);
void prioritization();
void admin_dashboard();
void view_by_type(string type);
void clearscreen();
void return_to_menu();

void clearscreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void return_to_menu()
{
    string back_bottom;
    cout << "\n\t\033[35mFor returning back to the menu press (M/m) for try agin press (any key)!! \n=>\033[0m";
    cin >> back_bottom;
    if (back_bottom == "M" || back_bottom == "m")
    {
        menu();
        return;
    }
}
void user_options(int feedback_index);
void show_feedbacks(int i, int j);

map<int, string> fb_type = {
    {1, "bug report"}, {2, "feature requests"}, {3, "general feedback"}};

int main()
{
    load_data_from_file(); // Load existing data at the start
    menu();
    save_data_to_file(); // Save data before exiting
    return 0;
}

void menu()
{
    int choice;
    int sec_choice;

    while (true)
    {
        clearscreen();
        cout << "\033[36m======Welcome in our user feedback project=====\033[0m\n\n ";

        cout << "1.Registeration\t2.Login\t\t";
        cout << "\033[31m3.Exit\033[0m\n\n";
        cout << "=> ";
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            registration();
            break;
        }
        else if (choice == 2)
        {
            cout << "\n\n===================================\n\n";
            cout << "Login as:\n\n [1] User\n [2] Admin\n\n=>";
            cin >> sec_choice;
            if (sec_choice == 1)
            {
                login();
            }
            else if (sec_choice == 2)
            {
                admin_dashboard();
            }
            else
            {
                cout << "\n\033[31minvalid\n\033[0m";
                system("pause");
                continue;
            }
            break;
        }

        else if (choice == 3)
        {
            cout << "Exiting the program...\n";
            return;
        }

        else
        {
            cout << "Invalid choice.\n\n\n";
            system("pause");
            continue;
        }
    }
}

void registration()
{
    bool found = false;
    user fb;
    do
    {
        found = false;
        clearscreen();
        cout << "\033[36m====== Feedback Regestration  =======\033[0m\n\n";

        cout << "Name: ";
        getline(cin, fb.username);
        cout << "\nSet your password: ";
        getline(cin, fb.password);
        cout << "\nEmail: ";
        getline(cin, fb.email);
        cout << "\nAddress: ";
        getline(cin, fb.address);
        for (int i = 0; i < feedback_index; i++)
        {

            if (fb.username == feedbacks[i].username)
            {
                found = true;
                cout << "\n\033[31m** This username already exists ,please try another one...\033[0m\n";
                system("pause");
            }
        }

    } while (found == true);

    cout << "\n\033[1;32mregistration has been approved <3\033[0m \n\n";
    system("pause");

    feedback_form(fb);
    save_data_to_file();
}

void feedback_form(user &fb)
{
    int choice;

    while (true)
    {
        if (fb.feedback_count >= 10)
        {
            cout << "\033[31mYou've reached the maximum of 10 feedbacks!\033[0m\n";
            break;
        }

        clearscreen();
        cout << "\033[36m====== Feedback Form =======\033[0m\n\n";
        cout << "Enter a number for feedback type:\n";
        cout << "1. bug report\n2. feature requests\n3. other feedbacks\n=> ";
        cin >> choice;

        if (choice < 1 || choice > 3)
        {
            cout << "\n\"Invalid choice\"\n";
            system("pause");
            continue;
        }

        fb.feedback_type[fb.feedback_count] = fb_type[choice];

        cout << "\n\033[34mType your feedback here: \033[0m";
        cin.ignore();
        getline(cin, fb.feedback_message[fb.feedback_count]);
        fb.priority[fb.feedback_count] = 1;

        cout << "\n\033[1;32mFeedback submitted successfully <3\033[0m\n";
        fb.feedback_count++;

        cout << "\nDo you want to submit another feedback? (y/n)\n=> ";
        char more;

        do
        {
            cin >> more;
            if (more != 'y' && more != 'Y' && more != 'n' && more != 'N')
            {
                cout << "\n\tinvalid, please try again...\n=>";
            }
            else
                break;
        } while (true);

        if (more == 'n' || more == 'N')
            break;
    }

    feedbacks[feedback_index++] = fb;

    user_options(feedback_index - 1);
}
void admin_dashboard()
{
    string back_bottom;
    bool admin_log = false;
    string passkey;
    string name;
    int view_option;
    clearscreen();
    cout << "========Register as Admin========";
    do
    {
        cout << "\n\nplease enter your name: ";
        cin >> name;
        cout << "Please enter the Admins passkey: ";
        cin >> passkey;

        if (passkey == admin_passkey)
        {
            
            admin_log = true;
            do
            {
                clearscreen();
                cout << "** Welcome Back Sir," << name << " **\n\n";

                cout << "\nChoose what you want to view:\n";
                cout << "1. Show only 'bug report' feedbacks\n";
                cout << "2. Show only 'feature requests' feedbacks\n";
                cout << "3. Show only 'general feedback' feedbacks\n";
                cout << "4. Show ALL feedbacks\n";
                cout << "=> ";
                cin >> view_option;
                clearscreen();
                if (view_option <= 3)
                    view_by_type(fb_type[view_option]);
                else if (view_option == 4)
                {
                    cout << "Here are all the feedbacks\n\n";
                    for (int i = 0; i < feedback_index; i++)
                    {
                        cout << "\n\n"
                             << i + 1 << ". Name: " << feedbacks[i].username;

                        for (int j = 0; j < feedbacks[i].feedback_count; j++)
                        {
                            show_feedbacks(i, j);
                        }
                        cout << "";
                    }
                }
                else
                {
                    cout << "\n\tinvalid, please try again...\n";
                    system("pause");
                    continue;
                }
                cout << "\n\n\tFor returning back to the menu press (M/m) and for return back press (any key)\n=> ";
                cin >> back_bottom;
                if (back_bottom == "M" || back_bottom == "m")
                {
                    menu();
                    return;
                }
                else
                {
                    continue;
                }
            } while (true);
        }
        else
        {
            cout << "\n\n\t\033[31mWrong admin passkey!!\033[0m";
            return_to_menu();
        }

    } while (!admin_log);
}

void login()
{
    string name, password;

    bool found = false;

    do
    {
        clearscreen();
        cout << "\033[36m====== login page =======\033[0m\n\n";
        cout << "Enter your username: ";
        cin.ignore();
        getline(cin, name);
        cout << "\nEnter your password: ";
        getline(cin, password);
        found = false;
        for (int i = 0; i < feedback_index; i++)
        {
            if (name == feedbacks[i].username && password == feedbacks[i].password)
            {
                found = true;
                clearscreen();

                cout << "** Welcome back Mr." << feedbacks[i].username << "<3 **\n\n";
                for (int j = 0; j < feedbacks[i].feedback_count; j++)
                {
                    show_feedbacks(i, j);
                }

                user_options(i);
            }
        }
        if (!found)
        {
            cout << "\n\033[31m** The username or password is incorrect **\033[0m\n";
            return_to_menu();
        }
    } while (found == false);
}

void feedback_delete(int i)
{
    string back_bottom;
    if (i < 0 || i >= feedback_index)
        return;
    int index;
    cout << "Enter the feedback number to delete (1 to " << feedbacks[i].feedback_count << "): ";
    cin >> index;
    index--;
    if (index < 0 || index >= feedbacks[i].feedback_count)
    {
        cout << "Invalid feedback number.\n";
        return;
    }

    for (int j = index; j < feedbacks[i].feedback_count - 1; j++)
    {
        feedbacks[i].feedback_type[j] = feedbacks[i].feedback_type[j + 1];
        feedbacks[i].feedback_message[j] = feedbacks[i].feedback_message[j + 1];
        feedbacks[i].priority[j] = feedbacks[i].priority[j + 1];
    }
    feedbacks[i].feedback_count--;
    cout << "\033[1;32mFeedback deleted successfully!\033[0m\n";
    system("pause");
    clearscreen();
    for(int j=0;j<feedbacks[i].feedback_count;j++)
    show_feedbacks(i,j);
}
void feedback_edit(int i)
{

    char choise;
    do
    {
        int edit_opt;
        clearscreen();
        cout << "====================EDITTING PAGE==========================\n\n";
        cout << "press:\n1.edit name\n2.edit password\n3.edit email\n4.edit address\n5.edit type and messege\n";
        cout << "for return back to the menu press(6)\n\n=>";

        cin >> edit_opt;
        cin.ignore();
        cout << "Enter your edit: ";

        if (edit_opt == 1)
            getline(cin, feedbacks[i].username);
        else if (edit_opt == 2)
            getline(cin, feedbacks[i].password);
        else if (edit_opt == 3)
            getline(cin, feedbacks[i].email);
        else if (edit_opt == 4)
            getline(cin, feedbacks[i].address);
        else if (edit_opt == 5)
        {
            if (i < 0 || i >= feedback_index)
                return;
            int index;
            cout << "Enter the feedback number to edit (1 to " << feedbacks[i].feedback_count << "): ";
            cin >> index;
            index--;
            if (index < 0 || index >= feedbacks[i].feedback_count)
            {
                cout << "Invalid feedback number.\n";
                return;
            }
            cin.ignore();

            cout << "Editing feedback type (current: " << feedbacks[i].feedback_type[index] << "): ";
            getline(cin, feedbacks[i].feedback_type[index]);

            cout << "Editing feedback message (current: " << feedbacks[i].feedback_message[index] << "): ";
            getline(cin, feedbacks[i].feedback_message[index]);

            cout << "\033[1;32mFeedback updated successfully!\033[0m\n";
        }
        
        else
        {
            cout << "Invalid option! Returning to menu...\n";
            system("pause");
            menu();
            return;
        }
      
        cout << "\npress (y) for another edit and press (b) for return back\n=>";
 
        cin>>choise;
        cin.ignore();
        if(choise=='b'){
            clearscreen();
            cout<<"===============\n\n";
            for(int j=0;j<feedbacks[i].feedback_count;j++) {
            show_feedbacks(i,j);
        
        }}
       
    } while (choise=='y');
}
void user_options(int i)
{
    int choice_form;
    int typechoice;
    do
    {
        
    cout << "\n\n_";
    cout << "\n*To delete a specific feedback press (1).";
    cout << "\n*To edit a specific feedback press (2).";
    cout << "\n*to ADD a new feedback press(3)";
    cout << "\n*To return to menu press (4).\n=> ";
        cin >> choice_form;

        if (choice_form == 1)
            feedback_delete(i);
        else if (choice_form == 2)
            feedback_edit(i);


        else if (choice_form == 3)
        {
            clearscreen();
           int  j= feedbacks[i].feedback_count;
           cout << "\n\nChoose your feedback type :\n 1. bug report\n2. feature requests\n3. other feedbacks\n=> ";
           cin>>typechoice;
           feedbacks[i].feedback_type[j]= fb_type[typechoice];;
           
           cout << "\nType your feedback message ): ";
           
           cin.ignore();
            getline(cin, feedbacks[i].feedback_message[j]);
            feedbacks[i].feedback_count++;

            cout << "\033[1;32mFeedback has been Add successfully!\033[0m\n";
            system("pause");
            clearscreen();
            for(int j=0;j<feedbacks[i].feedback_count;j++)
            show_feedbacks(i,j);
            
        }
        
        
        
        
        else if (choice_form == 4)
        {
            menu();
            return;
        }
        else
        {
            cout << "\ninvalid, please try again...\n=>\n";
            system("pause");
        }
        cout<<"\n\n";
       
    } while (true);
}
void prioritization()
{

    for (int i = 0; i < feedback_index; i++)
    {
        for (int j = 0; j < feedbacks[i].feedback_count; j++)
        {
            int count = 1;

            for (int k = 0; k < feedback_index; k++)
            {
                for (int l = 0; l < feedbacks[k].feedback_count; l++)
                {
                    if (i == k && j == l)
                    {
                        continue;
                    }

                    if (feedbacks[i].feedback_message[j] == feedbacks[k].feedback_message[l])
                    {
                        count++;
                    }
                }
            }

            feedbacks[i].priority[j] = count;
        }
    }
}
void show_feedbacks(int i, int j)
{
    prioritization();
    if (j == 0)
    {
        cout << " \t| Email: " << feedbacks[i].email;
        cout << " \t| Address: " << feedbacks[i].address << "\n";
    }
    cout << "\n  Feedback #" << (j + 1);
    cout << " | Type: " << feedbacks[i].feedback_type[j];
    cout << " | Priority: " << feedbacks[i].priority[j];
    cout << "\n  Message: " << feedbacks[i].feedback_message[j] << "\n";
    cout <<feedbacks[i].password<<"\n\n";
}
void view_by_type(string type)
{

    for (int i = 0; i < feedback_index; i++)
    {
        for (int j = 0; j < feedbacks[i].feedback_count; j++)
        {
            if (feedbacks[i].feedback_type[j] == type)
            {
                if (j == 0)
                {
                    cout << "\n\n"
                         << i + 1 << ". Name: " << feedbacks[i].username;
                }
                show_feedbacks(i, j);
            }
        }
    }
}