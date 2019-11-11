// Project:  Xref
// Name: Tyler Randolph
// Submitted: 11/11/2019
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student,
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class.

/*
 Reflection (1-2 paragraphs):  I really enjoyed writing this program, but had trouble with the regex. It took a little bit of work to remember how it works, but once I got my head wrapped around it again, it started coming back to me and I was able to get it figured out.
 */

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <regex>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// Forward Declarations
static std::vector<std::string> findAll (std::string, std::string);
static void search(std::string);

struct compare {
    bool operator()(const string &s1, const string &s2) const{
        
        string one = s1;
        string two = s2;
        
        transform( one.begin(), one.end(), one.begin(), ::tolower );
        transform( two.begin(), two.end(), two.begin(), ::tolower );

        if (one==two)
             return s1 < s2;
        else
            return one < two;
        
    }
};

int main(int argc, const char * argv[]) {
    
    string file;
    
    try {
        
        if (argc != 2) {
            search("No file given, search standard input");
        } else {
            file = argv[1];
            search(file);
        }
        
    } catch (exception& x) {
        cerr << x.what() << '\n';
    }

}

vector<string> findAll(string s, string pat) {
    vector<string> v;
    regex r{pat};
    transform(sregex_iterator(begin(s),end(s),r),sregex_iterator(),back_inserter(v),
              [](smatch p){return p.str();});
    return v;
}

void search(string file) {
    map<string, map<int,int>, compare> wordCountMap;
    const int MAX_LINE_NUMBERS = 9;
    string line;
    string match = "[-a-zA-Z](?:[-'a-zA-Z]?[a-zA-Z])*";
    int lineNumber = 1;
    int largestWord = 1;
    int wordLength;
    
    
    if (file == "No file given, search standard input") {
        
        while(getline(cin, line)) {
            auto results = findAll(line, match);
            line = "";
            for (auto word : results) {
                wordLength = (int) word.length();
                if (wordLength > largestWord) {
                    largestWord = (int) word.size();
                }
                if (word == " ") {
                    continue;
                } else {
                    wordCountMap[word][lineNumber]++;
                }
            }
            lineNumber++;
            //getline(cin, line);
        }
    } else {
        ifstream in(file);
                
        if (!in) {
            throw invalid_argument("File does not exist");
        }
        
        while (getline(in, line)) {
            auto results = findAll(line, match);
            string line = "";
            for (auto word : results) {
                wordLength = (int) word.length();
                if (wordLength > largestWord) {
                    largestWord = (int) word.size();
                }
                if (word == " ") {
                    continue;
                } else {
                    wordCountMap[word][lineNumber]++;
                }
            }
            lineNumber++;
        }
    }

    
    largestWord += 3;
    int sizeOfSecond;
    
    for(auto elem : wordCountMap)
    {
        int spacer = (int) elem.first.size();
        int counter = 0;
        cout << elem.first << setw(largestWord-spacer) << " : ";
        int lineLength = 0;
        for(auto elem2 : elem.second) {
            sizeOfSecond = (int) elem.second.size();
            counter++;
            if (sizeOfSecond > 1 && counter != sizeOfSecond)
                cout << elem2.first << ":" << elem2.second << ", ";
            else
                cout << elem2.first << ":" << elem2.second;
            lineLength++;
            if (lineLength == MAX_LINE_NUMBERS && counter != sizeOfSecond) {
                cout << endl << setw(largestWord) << " : ";
                lineLength = 0;
            }
        }
        cout << endl;
    }
}
