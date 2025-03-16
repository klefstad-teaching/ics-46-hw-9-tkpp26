#include <vector>
#include <cassert>
#include "ladder.h"
using namespace std;

void test_edit_distance() {
    cout << "Testing edit_distance()..." << endl;
    
    assert(edit_distance_within("apple", "apple", 1) == true);
    assert(edit_distance_within("apple", "apples", 1) == true);
    assert(edit_distance_within("apple", "sapple", 1) == true);
    assert(edit_distance_within("apple", "appe", 1) == true);
}

void test_generate_word_ladder() {
    cout << "Testing for generate_word_ladder()..";
    set<string> word_list = {"hit", "hot", "dot", "dog", "cog", "log", "lot"};
    vector<string> ladder = generate_word_ladder("hit", "cog", word_list);
    print_word_ladder(ladder);
}

void test_load_words() {
    cout << "Testing load_words()..." << endl;
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    assert(word_list.find("abandon") != word_list.end());
    assert(word_list.find("abasement") != word_list.end());
    assert(word_list.find("Aaron") != word_list.end());
}

void test_load_generate() {
    cout << "Testing words.txt..." << endl;
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    vector<string> ladder = generate_word_ladder("awake", "sleep", word_list);
    print_word_ladder(ladder);
}

void test_potential_infinite_loop() {
    cout << "Testing potential infinite loop case..." << endl;
    
    set<string> word_list;
    load_words(word_list, "src/words.txt"); 
    vector<string> ladder = generate_word_ladder("abandon", "absorption", word_list);
    print_word_ladder(ladder);
}


int main() {
    test_edit_distance();
    test_generate_word_ladder();
    test_load_words();
    test_load_generate();
    test_potential_infinite_loop();
}
