#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

vector<string> MatchStr(const string &str_in, ifstream &fin);
void Write_to_File(const vector<string> &result, ofstream &fout);

int main() {
    ifstream fin("string.in");
    ofstream fout("string.out");
    vector<string> result;
    string str_in;
    cin >> str_in;

    if (fin && fout) {
        result = MatchStr(str_in, fin);
        Write_to_File(result, fout);
    }
    else {
        cout << "file open error" << endl;
        system("pause");
        return 1;
    }

    system("pause");
    return 0;
}



vector<string> MatchStr(const string &str_in, ifstream &fin) {
    vector<string> wait_for_match;
    vector<char> elements = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
    'r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','A','B','C','D',
    'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    vector<string> matched;
    string str_line;
    int p_brackets_f = -1, p_brackets_b = -1, p_asterisk = -1, p_involution = -1;
    int line = 0;

    while (!fin.eof()) {
        if (getline(fin, str_line)) {
            line++;
            string str_line_backup = str_line;
            string str_in_lower = str_in;

            transform(str_line.begin(), str_line.end(), str_line.begin(), [](unsigned char c) { return tolower(c); });
            transform(str_in_lower.begin(), str_in_lower.end(), str_in_lower.begin(), [](unsigned char c) { return tolower(c); });

            matched.push_back(to_string(line));

            p_brackets_f = str_in.find('[');
            p_asterisk = str_in.find('*');

            if (p_brackets_f != string::npos) {
                p_brackets_b = str_in.find(']');
                if (str_in[p_brackets_f + 1] == '^') {
                    for (size_t i = p_brackets_f + 2; i < p_brackets_b; i++) {
                        for (char element : elements) {
                            if (element == str_in_lower[i] || element == str_in_lower[i] - 32)
                                continue;
                            else
                                wait_for_match.push_back(str_in.substr(0, p_brackets_f) + element + str_in.substr(p_brackets_b + 1));
                        }
                    }

                    for (size_t i = 0; i < str_line.length(); i++) {
                        if (str_line[i] == ' ')
                            continue;
                        for (string str : wait_for_match) {
                            if (str_line_backup.find(str, i) != string::npos) {
                                matched.push_back(str);
                            }
                        }
                    }
                    //wait_for_match.clear();
                }
                else {
                    for (size_t i = p_brackets_f + 1; i < p_brackets_b; i++) {
                        wait_for_match.push_back(str_in.substr(0, p_brackets_f) + str_in_lower[i] + str_in.substr(p_brackets_b + 1));
                        wait_for_match.push_back(str_in.substr(0, p_brackets_f) + to_string(str_in_lower[i] - 32) + str_in.substr(p_brackets_b + 1));
                    }

                    for (size_t i = 0; i < str_line.length(); i++) {
                        if (str_line[i] == ' ')
                            continue;
                        for (string str : wait_for_match) {
                            if (str_line_backup.find(str, i) != string::npos) {
                                matched.push_back(str);
                            }
                        }
                    }
                }
            }
            else if (p_asterisk != string::npos) {
                //vector<string> temp;
                string front = str_in_lower.substr(0, p_asterisk);
                string back = str_in_lower.substr(p_asterisk + 1);
                for (size_t i = 0; i < str_line.length(); i++) {
                    if (str_line[i] == ' ')
                        continue;
                    int temp_fpos = str_line.find(front, i);
                    int temp_bpos = str_line.find(back, i);
                    matched.push_back(str_line_backup.substr(temp_fpos + front.length(), temp_bpos - temp_fpos - front.length()));
                }
            }
        }
        else {
            cout << "read error" << endl;
            system("pause");
            exit(1);
        }
        wait_for_match.clear();
    }
    return matched;
}

void Write_to_File(const vector<string> &result, ofstream &fout) {
    for (size_t i = 0; i < result.size(); i++) {
        if (isdigit(result[i][0])) {
            fout << result[i] << ":";
        }
        else {
            fout << result[i];
            if (i == result.size() - 1)
                ;
            else if (isdigit(result[i + 1][0]))
                fout << endl;
            else if (!isdigit(result[i + 1][0]))
                fout << ",";
        }
    }
}