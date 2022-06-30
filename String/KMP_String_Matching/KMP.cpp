#include <iostream>
#include <string>
#include <vector>
#include <list>

#define DEBUG 1
using namespace std;

void ConstructPiTable(string& pattern, vector<int> & piTable)

{
    for (int i = 0; i < pattern.length(); ++i)
    {
        int length = i;
        string currString = pattern.substr(0, i + 1);

        while(length)
        {
            auto prefix = currString.substr(0, length);
            auto suffix = currString.substr(currString.length() - length, length);
            bool match =  suffix == prefix;
            if(match)
            {
                break;
            }
            --length;
        }

        piTable[i] = length;
    }
}

int MatchString(string  pattern, string text)
{
    int i = 0;

    while(i < pattern.size())
    {
        if(pattern[i] != text[i])
        {
            break;
        }
        ++i;
    }

    return i;
}

void KMPPatternMatcher(string  text, string pattern, vector<int> & indexes)
{
    int index = 0;
    int length = text.length();
    int patternLength = pattern.length();
    vector<int> piTable(patternLength);
    ConstructPiTable(pattern, piTable);

    while (index < length)
    {
        
        int misMatch = MatchString(pattern, text.substr(index, patternLength));
        
        if (DEBUG)
        {
            cout << "index: " << index << " length: " << length << " string: " << text.substr(index, patternLength) << " mismatch: " << misMatch << endl;
        }

        if (misMatch == patternLength)
        {
            indexes.push_back(index);
        }

        if (misMatch == 0)
        {
            ++index;
            continue;
        }
        index += misMatch - piTable[misMatch - 1];

    }
}

int main()
{
    string text = "ABC ABCDAB ABCDABCDABDE";
    string pattern = "ABCDABD";

    /////       Test ConstructPiTable method ////
    vector<int> pi(pattern.size());
    ConstructPiTable(pattern, pi);

    for (int &k : pi)
    {
        cout << k << " ";
    }
    cout << endl;
    ////////////////////////////////////////////
    vector<int> indexes;
    KMPPatternMatcher(text, pattern, indexes);

    for (int &index : indexes)
    {
        cout << index << " ";
    }
    cout << endl;
}
