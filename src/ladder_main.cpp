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

int main() {
    test_edit_distance();
    test_generate_word_ladder();
}
