#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_set>
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

// Function to match strings from input with the file content
vector<string> MatchStr(const string &str_in, ifstream &fin) {
    vector<string> matched;
    string str_line;
    int p_brackets_f = -1, p_brackets_b = -1, p_asterisk = -1;
    int line = 0;

    while (getline(fin, str_line)) {
        line++;
        string str_line_lower = str_line;
        string str_in_lower = str_in;

        // Convert both the input and line to lowercase for case-insensitive matching
        transform(str_line.begin(), str_line.end(), str_line_lower.begin(), [](unsigned char c) { return tolower(c); });
        transform(str_in.begin(), str_in.end(), str_in_lower.begin(), [](unsigned char c) { return tolower(c); });

        unordered_set<string> found_matches;

        p_brackets_f = str_in_lower.find('[');
        p_asterisk = str_in_lower.find('*');

        if (p_brackets_f != string::npos) {
            // Handle logic for matching when brackets are present
            p_brackets_b = str_in_lower.find(']');
            string before_bracket = str_in_lower.substr(0, p_brackets_f);
            string after_bracket = str_in_lower.substr(p_brackets_b + 1);
            string options = str_in_lower.substr(p_brackets_f + 1, p_brackets_b - p_brackets_f - 1);

            // Determine if the bracket contains exclusion (using '^')
            bool exclude = options[0] == '^';
            unordered_set<char> option_chars;

            // Collect characters inside the brackets (excluding '^' if present)
            for (size_t i = exclude ? 1 : 0; i < options.size(); ++i) {
                option_chars.insert(options[i]);
            }

            // Iterate through the line to find matches
            for (size_t i = 0; i <= str_line_lower.size() - str_in_lower.size() + (p_brackets_b - p_brackets_f); ++i) {
                if (str_line_lower.substr(i, before_bracket.size()) == before_bracket &&
                    str_line_lower.substr(i + before_bracket.size() + 1, after_bracket.size()) == after_bracket) {
                    char bracket_char = str_line_lower[i + before_bracket.size()];
                    bool match = exclude ? (option_chars.find(bracket_char) == option_chars.end()) : (option_chars.find(bracket_char) != option_chars.end());
                    if (match) {
                        found_matches.insert(str_line.substr(i, before_bracket.size() + 1 + after_bracket.size()));
                    }
                }
            }
        }
        else if (p_asterisk != string::npos) {
            // Handle logic for matching when asterisk is present
            string front = str_in_lower.substr(0, p_asterisk);
            string back = str_in_lower.substr(p_asterisk + 1);

            size_t start_pos = 0;
            while ((start_pos = str_line_lower.find(front, start_pos)) != string::npos) {
                size_t back_pos = str_line_lower.find(back, start_pos + front.size());
                if (back_pos != string::npos) {
                    // Extract the matched substring and add to the result set
                    found_matches.insert(str_line.substr(start_pos, back_pos + back.size() - start_pos));
                    start_pos = back_pos + back.size();
                }
                else {
                    break;
                }
            }
        }
        else {
            // Handle simple string matching without brackets or asterisk
            size_t pos = 0;
            while ((pos = str_line_lower.find(str_in_lower, pos)) != string::npos) {
                found_matches.insert(str_line.substr(pos, str_in_lower.size()));
                pos += str_in_lower.size();
            }
        }

        // If matches are found, format the result for this line
        if (!found_matches.empty()) {
            string result_line = to_string(line) + ":";
            bool first = true;
            for (const auto &match : found_matches) {
                if (!first) {
                    result_line += ",";
                }
                result_line += match;
                first = false;
            }
            matched.push_back(result_line);
        }
    }

    return matched;
}

// Function to write the matching results to the output file
void Write_to_File(const vector<string> &result, ofstream &fout) {
    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];
        if (i != result.size() - 1) {
            fout << endl;
        }
    }
}
