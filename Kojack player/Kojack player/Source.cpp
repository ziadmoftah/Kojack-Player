#include <bits/stdc++.h>

using namespace std;

int numUser=0;
vector<string>songs;

struct user
{
	int order;
	string name, password;
	map<string, int>rate;
};
user user_data[9];
struct song
{
	string name;
	string genre;
	string album;
	string artist;
	int year;
	int rating =0;
	bool display = true;
}song_data[10000];


void users_login();
void create_user();
void save_users();
void read_users();
void Authenticate();
void read_data();
void save_data();

fstream fs;
ofstream ofs;
ifstream ifs;

int main()
{
    songs.push_back("abc");
    songs.push_back("klm");
    songs.push_back("xyz");
    users_login();
    cout<<song_data[2].rating<<endl;



    return 0;
}

void users_login()
{
    read_users();
    read_data();
    cout<<"Press\n1 to create\n2 to login\n";
    int x;cin>>x;
    if(x==1)
    {
        create_user();
        save_users();
        save_data();
    }
    else if(x==2)
    {
        Authenticate();
    }
}

void read_users()
{
	ifs.open("Users.txt", ios::in);
	ifs >> numUser;
	for (int i = 1; i <= numUser; i++)
	{
		ifs >> user_data[i].order >> user_data[i].name >> user_data[i].password;
	}
	ifs.close();
}
void create_user()
{
    cin.ignore();
	numUser++;
	cout<<"*Create User*\n";
	user_data[numUser].order = numUser;
	cout<<"Enter your name:\n";
	getline(cin,user_data[numUser].name);
	cout<<"Enter your password:\n";
	 getline(cin,user_data[numUser].password);


}
void save_users()
{
	fs.open("Users.txt", ios::out | ios::trunc);
	fs << numUser<<endl;
	for (int i = 1; i <= numUser; i++)
	{
		fs << user_data[i].order << "\n" << user_data[i].name << "\n" << user_data[i].password << endl;
	}
	fs.close();
}
void Authenticate()
{
    cout<<"*Authenticate*\n";
	cout << "Enter User Name: " << endl;
	bool f = false;
	string n, p; cin >> n;
	for (int i = 0; i <= numUser; i++)
	{
		if (user_data[i].name == n)
		{
			f = true;
			cout << "Enter your password: " << endl;
			cin >> p;

			for(int j=0;j<songs.size();j++)
            {
                song_data[j].rating=user_data[i].rate[songs[j]];
            }

			/*if (p == user_data[i].password)
			{
				cout << "WELCOME " << user_data[i].name<<endl;
			}*/
		}
	}
	if(f==false)
        cout<<"NOTFOUND!";
}
void read_data()
{
    ifs.open("UsersData.txt", ios::in);
    string s;int x,n;
    ifs>>numUser;
    for(int i=1;i<=numUser;i++)
    {
        ifs>>user_data[i].order;
        for(int j=0;j<songs.size();j++)
        {
            ifs>>s;ifs>>x;
            user_data[i].rate[s]=x;
        }
    }
    ifs.close();
}
void save_data()
{

	ofs.open("UsersData.txt", ios::out | ios::trunc);
	ofs<<numUser<<endl;
	for (int j = 1; j <= numUser; j++)
	{
		ofs << j << endl;
		for (int i = 0; i < songs.size(); i++)
		{
			ofs << songs[i] << " " << user_data[j].rate[songs[i]] << endl;
		}
		ofs << endl;
	}
	ofs.close();
}
