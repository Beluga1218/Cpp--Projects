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
int LogCnt = 0;

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

class LogBase
{
public:
    string AuthorName;
    int AuthorID;
    string AuthorClass;
    string AuthorNation;
    string AuthorTeam;
    string AuthorSiteID;
    string Title;
    string Content;
    void Save(string _name, int _id, string _class, string _nation, string _team, string _siteId, string _title, string _content)
    {
        AuthorName = _name;
        AuthorClass = _class;
        AuthorNation = _nation;
        AuthorTeam = _team;
        AuthorSiteID = _siteId;
        Title = _title;
        Content = _content;
    }
};

LogBase LB[100005];

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
    /*
    129XXX : O5
    128XXX : A - 1
    127XXX : A - 2
    126XXX : B - 1
    125XXX : B - 2
    124XXX : C - 1
    123XXX : C - 2
    122XXX : D - 1
    121XXX : D - 2
    */
    AddUser(12900001, "O5", "Yuchen Fan", "Password", "T-11", "China", "Alpha-1");
    AddUser(12900002, "O5", "Yichen Wang", "Password", "T-11", "China", "Epsilon-11");
    AddUser(12800001, "A-1", "Isabella He", "Password", "N-15", "China", "Nu-7");
    AddUser(12700001, "A-2", "Alan Chen", "Password", "N-15", "China", "Beta-12");
}

void AddLog(string _name, int _id, string _class, string _nation, string _team, string _siteId, string _title, string _content)
{
    LB[++LogCnt].Save(_name, _id, _class, _nation, _team, _siteId, _title, _content);
}

void ShowLog(int _id)
{
    Line();
    cout << LB[_id].Title << endl
         << endl;
    cout << LB[_id].AuthorName << " | " << LB[_id].AuthorClass << endl
         << endl;
    cout << LB[_id].Content << endl;
    Line();
}

void StartTerminal()
{
    string OpCode = "";
    while (OpCode != "Quit")
    {
        cin >> OpCode;
        if (OpCode == "Time")
        {
            GetTime();
            Line();
        }
        else if (OpCode == "Clear")
        {
            Clear();
        }
        else if (OpCode == "WriteLog")
        {
            Line();
            string Title;
            cout << "Title: ";
            getline(cin, Title);
            getline(cin, Title);
            string Content;
            cout << "Content: ";
            getline(cin, Content);
            AddLog(UserName, UserID, UserClass, UserNation, UserTeam, UserSiteID, Title, Content);
            Line();
        }
        else if (OpCode == "DispLog")
        {
            int ID;
            cout << "LogID: ";
            cin >> ID;
            ShowLog(ID);
        }
    }
}

int main()
{
    InitDataBase();
    LS.Login();
    StartTerminal();
    return 0;
}