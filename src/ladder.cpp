#include "ladder.h"
#include <queue>
#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
#include <fstream>
using namespace std;

void error(string word1, string word2, string msg) {
    cout << "Error: " << word1 << " " << word2 << " " << msg << endl;
}


// Source : https://www.geeksforgeeks.org/introduction-to-levenshtein-distance/

// Recursive -- resulted in infinite loop
// int levenshteinDistances(const string& str1, const string& str2, int m, int n) {
//     // Base cases
//     if (m == 0)
//         return n; 
//     if (n == 0)
//         return m; 

//     // If matches, continue
//     if (str1[m - 1] == str2[n - 1]) {
//         return levenshteinDistances(str1, str2, m - 1, n - 1);
//     }

//     return 1 + min(
//         levenshteinDistances(str1, str2, m, n - 1),    
//         min(
//             levenshteinDistances(str1, str2, m - 1, n), 
//             levenshteinDistances(str1, str2, m - 1, n - 1)
//         )
//     );
// }

// Iterative
// apple -> apples
// apple -> ample
// apple -> sapple
// apples -> apple
// appsle -> apple --- sle, le
// apple -> aple
// Idea -- Past leetcode question 
// Initial attempt -- inifnite loop
// bool edit_distance_within(const string& str1, const string& str2, int d) {
//     int len1 = str1.length();
//     int len2 = str2.length();
//     int diffLen = len2 - len1;

//     // Edge case
//     if (abs(diffLen) > d){
//         return false;
//     }

//     int count = 0;
//     string s1 = str1;
//     string s2 = str2;
//     while (!s1.empty() && !s2.empty()) { 
//         int len1 = s1.length();
//         int len2 = s2.length();
        
//         if (s1[0] == s2[0]) {
//             s1 = s1.substr(1); 
//             s2 = s2.substr(1); 
//         } else {
//             count++;
//             if (len1 < len2) {
//                 s2 = s2.substr(1);
//             }
//             else if (len1 > len2) {
//                 s1 = s1.substr(1);
//             }
//             else {
//                 s1 = s1.substr(1);
//                 s2 = s2.substr(1);
//             }
//         }
//     }

//     if(!s1.empty()) {
//         count += s1.length();
//     }
//     else {
//         count += s2.length();
//     }

//     return count <= d;  
// }

// apple -> apples --- _, s 
// apple -> sapple --- apple, apple

// apples -> apple -- s, _
// sapple -> apple --- apple, apple

// apple -> ample
// appsle -> apple --- sle, le --- le, le
// apple -> aple --- ple, le --- le, le
// Tested for when d == 1, may be incorrect for other values of d
bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    int i = 0;
    int j = 0;
    int count = 0;

    while(i < len1 && j < len2) {
        if(str1[i] == str2[j]) {
            i++;
            j++;
        }
        else{
            count++;
            if(len1 < len2)
                j++; 
            else if(len1 > len2)
                i++;
            else {
                i++;
                j++;
            }
        }
    }

    count += len1 - i;
    count += len2 - j;
    return count <= d;
}

// Checks if it is one step away from the original word
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        // Find any adjacent words from the word list
        for (string word : word_list) {
            // If it is adjacent word and if it is not yet in the ladder add it
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    // add a list of new possible ladders
                    ladder_queue.push(new_ladder); 
                }
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    if(in.is_open()) {
        string word;
        while(in >> word) {
            word_list.insert(word);
        }
    }
    else {
        cout << "Unable to open file" << endl;
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    for(size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}

// void verify_word_ladder() {
// }