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

// Checks if words differ by an insertion or deltion
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    // Check if it differs by one letter
    int len1 = str1.length();
    int len2 = str2.length();
    int diffLen = len2 - len1;
    if (abs(diffLen) > d){
        return false;
    }

    int count = 0;
    int i = 0;
    int j = 0;

    while (i < len1 && j < len2) {
        // Matching characters
        if (str1[i] == str2[j]) {
            i++;
            j++;
        }
        else {
            count++;
            // insert
            if (len1 < len2)     
                j++;
            // deletion
            else if (len1 > len2)
                i++;
            else {
                i++;
                j++;
            }

            if (count > d)
                return false;
        }
        
    }

    // Remaining either str1 or str2
    count += (len1 - i) + (len2 - j);
    return count <= d; // at most d!
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