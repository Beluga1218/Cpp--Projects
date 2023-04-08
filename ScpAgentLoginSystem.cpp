#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>
using namespace std;

int UserID = -1;
string UserClass;
string UserName;
string UserPass;
string UserSiteID;
string UserNation;
string UserTeam;
int UserCnt = 0;

void Wait(int ms)
{
    Sleep(ms);
}

void GetTime()
{
    auto nowTime = chrono::system_clock::now();
    time_t Time = chrono::system_clock::to_time_t(nowTime);
    cout << ctime(&Time) << endl;
}

void Line()
{
    cout << endl;
    cout << "========================================" << endl;
    cout << endl;
}

void Clear()
{
    system("cls");
    Line();
    cout << "SCP Control Terminal v1.0" << endl;
    Line();
}

void MainMenu()
{
    Clear();
    cout << UserName << endl;
    cout << endl;
    cout << "ID: " << UserID << endl;
    cout << "Class: " << UserClass << endl;
    cout << "Team: " << UserTeam << endl;
    cout << "Nation: " << UserNation << endl;
    cout << "Site: " << UserSiteID << endl;
    Line();
}

class DataBase
{
public:
    int ID = -1;
    string Class;
    string Name;
    string Pass;
    string SiteID;
    string Nation;
    string Team;
    void Save(int _id, string _class, string _name, string _pass, string _siteId, string _nation, string _team)
    {
        ID = _id;
        Class = _class;
        Name = _name;
        Pass = _pass;
        SiteID = _siteId;
        Nation = _nation;
        Team = _team;
    }
};

DataBase DB[10005];

class LoginService
{
public:
    bool CheckID(int _id)
    {
        for (int i = 1; i <= UserCnt; i++)
        {
            if (DB[i].ID == _id)
            {
                UserID = DB[i].ID;
                UserClass = DB[i].Class;
                UserName = DB[i].Name;
                UserPass = DB[i].Pass;
                UserSiteID = DB[i].SiteID;
                UserNation = DB[i].Nation;
                UserTeam = DB[i].Team;
                return true;
            }
        }
        return false;
    }
    void Login()
    {
        Clear();
        cout << "Please enter your id: ";
        int id;
        cin >> id;
        if (CheckID(id))
        {
            cout << "Hello! " << UserTeam << " Member : " << UserName << ". Please enter your password: ";
            string pass;
            getline(cin, pass);
            getline(cin, pass);
            Clear();
            if (pass == UserPass)
            {
                cout << "Password correct, proceeding to main menu..." << endl;
                Wait(2000);
                MainMenu();
            }
            else
            {
                cout << "Wrong password, quitted." << endl;
            }
        }
        else
        {
            Line();
            cout << "Invalid ID or not signed up, quitted." << endl;
        }
    }
};

LoginService LS;

void AddUser(int _id, string _class, string _name, string _pass, string _siteId, string _nation, string _team)
{
    DB[++UserCnt].Save(_id, _class, _name, _pass, _siteId, _nation, _team);
}

void InitDataBase()
{
    AddUser(129001, "O5", "Yuchen Fan", "Password", "11", "China", "Alpha-1");
}

int main()
{
    InitDataBase();
    LS.Login();
    return 0;
}