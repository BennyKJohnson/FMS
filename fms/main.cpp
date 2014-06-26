//
//  main.cpp
//  fms
//
//  Created by Ben Johnson on 26/06/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//
// Algorithm that detects if difference in word

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iomanip>

using namespace std;

vector<string> tokenizeString(string s)
{
    vector<string> tokens;
    istringstream iss(s);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter<vector<string> >(tokens));
    return tokens;
    
}
float edit_distance(string s,string t)
{
    float m = (int)s.size();
    int n = (int)t.size();
    vector<vector<int>> d(m+ 1,vector<int>(n+1));
    
    for (int i = 0; i <= m; i++) {
        d[i][0] = i;
    }
    for (int i =1; i<= n; i++) {
        d[0][i] = i;
    }
    
    for (int j =1; j <= n; j++) {
        for (int i =1; i<=m; i++) {
            //  cout << token1[i-1] << " " << token2[j-1] << endl;
            if (s[i-1] == t[j-1]) {
                d[i][j] = d[i-1][j-1];
            }
            else
            {
                int min1 = d[i-1][j] + 1; // A deletion
                int min2 = d[i][j-1] + 1; // A insertion
                int min3 = d[i-1][j-1] + 2;
                d[i][j] = min(min1,min(min2, min3));
                
            }
        }
    }

    return d[m][n];
}
int main(int argc, const char * argv[])
{
    string s = "5 pack bonds hipster briefs";
    string t = "bonds 5 pack hipster briefs";
    
    vector<string> token1 = tokenizeString(s);
    vector<string> token2 = tokenizeString(t);
    int m = (int)token1.size();
    int n = (int)token2.size();
    vector<vector<float>> d(m+ 1,vector<float>(n+1));
    
    for (int i = 0; i <= m; i++) {
        d[i][0] = i;
    }
    for (int i =1; i<= n; i++) {
        d[0][i] = i;
    }
    
    for (int j =1; j <= n; j++) {
        for (int i =1; i<=m; i++) {
          //  cout << token1[i-1] << " " << token2[j-1] << endl;
            if (token1[i-1] == token2[j-1]) {
                d[i][j] = d[i-1][j-1];
            }
            else
            {
                float min1 = d[i-1][j] + 1; // A deletion
                float min2 = d[i][j-1] + 0.1; // A insertion
                float min3 = d[i-1][j-1] + edit_distance(token1[i-1], token2[j-1]);
                d[i][j] = min(min1,min(min2, min3));
                
            }
        }
    }
    
    for (int i = 0; i < d.size(); i++) {
        for (int j =0; j < d[i].size(); j++) {
            cout << setprecision(2) <<  d[i][j] << " ";
        }
        cout << endl;
    }
    
    
    std::cout << "ED: " << edit_distance("sitten", "kitten") << endl;
    std::cout << "FMS: " <<1 - d[m][n] / m << endl;

    return 0;
}

