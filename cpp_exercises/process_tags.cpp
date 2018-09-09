#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <string>
using namespace std;

struct Attribute {
    string attr_key;
    string attr_value;
};

struct Tag {
    string tag_name;
    vector<Tag> tags;
    vector<Attribute> attributes;
};

string getStr(string& line, char start_char, 
              char end_char, int& start_pos) {
    size_t index = line.find(start_char, start_pos);
    size_t index2 = line.find(end_char, index + 1);
    string sub = line.substr(index + 1, (index2 - index - 1));
    start_pos = index2;
    return sub;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int n;
    int q;
    cin >> n >> q;
    
    deque<string> active_tags;
    unordered_map<string, Tag> m; 
    vector<Tag> tag_vec;
    
    int i = 0;
    for (string line; getline(cin, line); )  {
        int pos = 0;
        size_t tag_end = line.find("</");
        
        if (tag_end != string::npos) {
            if (tag_end == 0) {
                active_tags.pop_front();
                continue;
            }
        }
        string tag_name = getStr(line, '<', ' ', pos);
        active_tags.push_front(tag_name);
        
        vector<Attribute> attr;
        size_t last_ind = line.find('>');
        
        while ((pos + 1) < last_ind) {
            string attr_name = getStr(line, ' ', ' ', pos);
            string eq_sign = getStr(line, ' ', ' ', pos);
            string attr_value = getStr(line, '\""', '\""', pos);
            
            Attribute curr_attribute = {attr_name, attr_value};
            attr.push_back(curr_attribute);
        }
        
        Tag new_tag;
        vector<Tag> included_tags;
        new_tag.tag_name = tag_name;
        new_tag.attributes = attr;
        new_tag.tags = included_tags;
        tag_vec.push_back(new_tag);
        m[tag_name] = new_tag;
        
        for (auto it = active_tags.begin(); 
             it != active_tags.end(); ++it) {
            string current_tag = *it;
            m[current_tag].tags.push_back(new_tag);
        }
        
        i += 1;
        if (i == n) {
            break;
        }
    }
    
    i = 0;
    for (string line; getline(cin, line); ) {
        
        string curr_string;
        Tag curr_tag;
        for (int j = 0; j < line.size(); ++j) {
            if (line[j] == '.') {
                if (m.find(curr_string) != m.end())
                    curr_tag = m[curr_string]; // tag name
                else {
                    cout << "Not Found!" << endl;
                    break;
                }
            }
            if (line[j] == '~') {
                
            }
            else {
                curr_string.push_back(line[i]);
            }
        }
        
        i += 1;
        if (i == q) {
            break;
        }
    }
    
    return 0;
}
