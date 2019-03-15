//
//  main.cpp
//  Cryptography
//
//  Created by Joshua Yam on 3/15/19.
//  Copyright © 2019 Joshua Yam. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
using namespace std;

float getIC(vector<char>& seq){
    int N = seq.size(); //Size of Alphabet
    map<char, int> freq; //Frequency of each letter in a sequence
    static const char* alph = " abcdefghijklmnopqrstuvwxyz";
    vector<char> vectAlph(alph, alph+27);
    float freqsum = 0.0;
    float IC;
    for ( int i = 0; i < vectAlph.size(); i++ ){
        freq[ vectAlph[i]]=0;
    }
    for ( int i = 0; i < seq.size(); i++ ){
        freq[ seq[i] ] ++;
    }
    for(auto elem : freq)
    {
        std::cout << elem.first << " " <<elem.second<< "\n";
    }
    for (char& a : vectAlph){
        freqsum += freq[a] * (freq[a]-1);
    }
    IC=freqsum/(N*(N-1));
    return IC;
}


int getKeyLength(const string& cipherText){
    vector<vector<vector<char>>> manyKeys; //3-D Vector stroring all possible key lengths and their sequences
    vector<vector<char>> aKey; //2-D Vector storing a key length and its sequences
    vector<char> seq; //One Sequence
    vector<float> avgIC; //Avg Index of Coincidence for each possible Key Length
    vector<float> individualIC; //Index of Coincidence for each Sequence
    int counter=26;
    
    for (int i =1; i<=counter;i++){
        for (int j =0; j<i;j++){
            for(int k=0; k<cipherText.length();k+=i){
                seq.push_back(cipherText[k+j]);
            }
            aKey.push_back(seq);
            individualIC.push_back(getIC(seq));
            seq.clear();
        }
        manyKeys.push_back(aKey);
        float avg = accumulate( individualIC.begin(), individualIC.end(), 0.0)/individualIC.size();
        avgIC.push_back(avg);
        aKey.clear();
    }
    //////////////////////////////////////////////////TEST
    int count = 1;
    for( vector<vector<vector<char>>>::const_iterator i = manyKeys.begin(); i != manyKeys.end(); ++i)
    {
        cout << "Key Length: " << count<<endl;
        for( vector<vector<char>>::const_iterator j = i->begin(); j != i->end(); ++j)
        {
            cout<<"\t";
            for( vector<char>::const_iterator k = j->begin(); k != j->end(); ++k)
            {
                cout<<*k << ' ';
            }
            cout <<endl;
        }
        count++;
    }
    /////////////////////////////////////////////
    
    for (auto a:avgIC){
        cout <<a <<endl;
    }
    return 0;
}
int main(int argc, const char * argv[]) {
    cout << "Cyphertext: ";//Prompts user for the ciphertext to be decrpyted
    string input;
    getline(cin,input);
    cout <<input<<endl;
    int keyLength=getKeyLength(input);
    
    return 0;
}
