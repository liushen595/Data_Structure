#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct temp_data {
    string operate;
    long long username;
    string password;
    temp_data(string s = "0", long long uname = 0, string pw = "0") :operate(s), username(uname), password(pw) {}
};

void Handle(const vector<temp_data> &submitted, unordered_map<long long, string> &Users);

int main() {
    unordered_map<long long, string> Users;
    int n;
    long long username;
    string password;
    cin >> n;
    string operate;
    vector<temp_data> submitted;

    for (int i = 0; i < n; i++) {
        cin >> operate >> username >> password;
        submitted.push_back(temp_data(operate, username, password));
    }

    Handle(submitted, Users);


    return 0;
    system("pause");
}

void create_new_user(long long username, const string &password, unordered_map <long long, string> &Users) {
    if (username <= 1000 || username > 9999999999)
        return;
    auto it = Users.find(username);
    if (it != Users.end()) {
        cout << "ERROR: Exist" << endl;
        return;
    }
    else {
        if (password.length() < 6 || password.length() > 16 || password.find(' ') != string::npos) {
            cout << "ERROR: Wrong PW" << endl;
            return;
        }
        else {
            Users[username] = password;
            cout << "New: OK" << endl;
            return;
        }
    }
}

void user_login(long long username, const string &password, const unordered_map <long long, string> &Users) {
    if (username <= 1000 || username > 9999999999)
        return;
    auto it = Users.find(username);
    if (it == Users.end()) {
        cout << "ERROR: Not Exist" << endl;
        return;
    }
    else {
        if (it->second != password) {
            cout << "ERROR: Wrong PW" << endl;
            return;
        }
        else {
            cout << "Login: OK" << endl;
            return;
        }
    }
}

void Handle(const vector<temp_data> &submitted, unordered_map<long long, string> &Users) {
    for (size_t i = 0; i < submitted.size(); i++) {
        if (submitted[i].operate == "N")
            create_new_user(submitted[i].username, submitted[i].password, Users);
        else
            user_login(submitted[i].username, submitted[i].password, Users);
    }
}