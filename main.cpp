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
#include <fstream>
#include <algorithm>
using namespace std;

vector<int> frequencyCounter(vector<char> total, int pos) {
    // frequency vectors are [0,a,..,z]
    vector<int> frequency(27);
    int ascii;
    for (int j = pos; j < (pos+500); j++) {
        ascii = int(total[j]);
        //cout << total[j];
        if (total[j] == ' ') {
            frequency[0]++;
        }
        else {
            frequency[ascii - 96]++;
        }
    }
    //cout << '\n';
    return frequency;
}

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
    
    for (char& a : vectAlph){
        freqsum += freq[a] * (freq[a]-1);
    }
    IC=freqsum/((N*(N-1))/vectAlph.size());
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
    //    int count = 1;
    //    for( vector<vector<vector<char>>>::const_iterator i = manyKeys.begin(); i != manyKeys.end(); ++i)
    //    {
    //        cout << "Key Length: " << count<<endl;
    //        for( vector<vector<char>>::const_iterator j = i->begin(); j != i->end(); ++j)
    //        {
    //            cout<<"\t";
    //            for( vector<char>::const_iterator k = j->begin(); k != j->end(); ++k)
    //            {
    //                cout<<*k << ' ';
    //            }
    //            cout <<endl;
    //        }
    //        count++;
    //    }
    /////////////////////////////////////////////
    
    //    for (auto a:avgIC){
    //        cout <<a <<endl;
    //    }
    return max_element(avgIC.begin(),avgIC.end()) - avgIC.begin()+1;
}

//string decryptCipher(string cipherText, vector<int> key, int keyLength) {
//    string plainText = "";
//    //string helper
//    int posInKey = 0;
//    for (int i =0; i < cipherText.length(); i++) {
//        int x = int(cipherText[i]);
//        if (posInKey > keyLength-1) {
//            posInKey = 0;
//        }
//        for (int j = 0; j <keyLength; j++) {
//            if ( char(x) == 'a') {
//                x = int('z');
//            } else {
//                x--;
//            }
//        }
//        char c = char(x);
//        plainText += c;
//        posInKey++;
//    }
//    return plainText;
//}



int main(int argc, const char * argv[]) {
//    vector<int> testVec = {1,2,3,4,5,6,7,8,9};
//    rotate(testVec.begin(),testVec.end()-1,testVec.end());
//    for (int i = 0; i < testVec.size(); i++){ cout << "rotate" << testVec[i] << '\n';}
    ifstream ifs("dictionary.txt");
    if (!ifs) {
        cerr << "Couldn't open 'dictionary.txt'\n";
        exit(1);
    }
    
    vector<char> temp;
    char x;
    while (ifs >> noskipws >> x) {
        temp.push_back(x);
    }
    cout << endl;
    
    // each vector contains the frequency of each char
    vector<int> plainText1 = frequencyCounter(temp, 0);
    vector<int> plainText2 = frequencyCounter(temp, 501);
    vector<int> plainText3 = frequencyCounter(temp, 1002);
    vector<int> plainText4 = frequencyCounter(temp, 1503);
    vector<int> plainText5 = frequencyCounter(temp, 2004);
    
    string plainText1_string = "surrenderee document spunkiest coquetted abatis leasehold nuclei fogginess genoa traitors blockbuster superpositions flams surprized honcho cetera to transmit psychol wintered gruntingly cheapness translation laborer lissomeness caravansaries reflexes overextends bitter uplift strate filler cupolaed automatic machree nonparasitic unashamed braggy typier potencies greyness gulped masonwork blandisher disks fadeaway origamis manurer olives engine looted whitehall imperils shadowbox jabbing exports";
    string plainText2_string = "tumble cooked twirled absinths ceca cheatery raters redeploy niacinamide offeree preventively tangibleness beamy oligarchical microbus intends galvanize indelible tubings overcools rollover maladroit logways frilling skinks affirmatively flatfoots oversleeps consignors completes espadrille booms repaved ofays keens dinosaurs rerouted consignments victimless psychophysical chuckle admissibility muleteer deescalating ovary bowwow assisi fore tubbiest vocatively filially preestablish lacquerers spr";
    string plainText3_string = "harmonizations pratique defoliated brashly elegancy henpeck ecumenicism valuta lingers acrobatic mismarriage fruitlessness pattering enables travois nymphs fratricides awakener ordure tribulation elicit nonviable guiles raucously euclidean evangelist preoperative pathogeny frames medium inviabilities retrains crankcase awkwarder stopwatch subclinical irrigators lettuce skidooed fonder teem funguses purviews longshot affaires wearing judo resettle antedate inoperable pinworm pumper annul anteposi";
    string plainText4_string = "hark reascended recedes inebriate flowery awkwarder waterbed complacency sikh compartmented dependably alliterations headache basketfuls malocclusions cubistic hint headdresses unfrocks keloidal translucent fidelities instructional graphed baker superb spectroscopies bismark uncanniest detachability letdown querulously unstack curdling chained pointy drippers larch spermicide inextricability anteed improvising jape imponderably lithographic winglets advents triplicating growling fescue salabilit";
    string plainText5_string = "enrollee pins datively armiger bisect installs taffeta compliances governorship laceworks preciousness bedizens immaculately disinfect nucleonics biremes mailbags behaves enhance floppiest brutisms registered silenced tuques oryxes coddler undersigned mackintosh misemployment peacemakers pleadings dandification platypuses swig doer reshowed quadrangles locutory encapsules bawdies woolpack valuated malodorously shill cryogenies known distr bonsai morale mirage skit aquacades pi overcommon flippan";
    
    
    
    cout << "Cyphertext: ";//Prompts user for the ciphertext to be decrpyted
    string input;
    getline(cin,input);
    int keyLength=getKeyLength(input);
    cout <<"Key Length is: " <<keyLength <<endl;
    
    // real frequencies of <space, a, ..., z>
    vector<double> alphabetFreq = {18.28846265, 6.53216702, 1.25888074, 2.23367596, 3.28292310, 10.26665037, 1.98306716, 1.62490441, 4.97856396, 5.66844326, 0.09752181, 0.56096272, 3.31754796, 2.02656783, 5.71201113, 6.15957725, 1.50432428, 0.08367550, 4.98790855, 5.31700534, 7.51699827, 2.27579536, 0.79611644, 1.70389377, 0.14092016,     1.42766662, 0.05128469 }; //space to Z
    
    //convert cipherText string to vector<char> (frequencyCounter takes vector<char> as parameter)
    vector<char> cipherText;
    for (int i = 0; i < input.length(); i++){
        cipherText.push_back(input[i]);
    }
    
    // frequencies for the ciphertext
    vector<int> cipherTextFrequencies = frequencyCounter(cipherText,0);
//    for (int i = 0; i < cipherTextFrequencies.size(); i++) {
//        cout << char(i+96) << ' ' << cipherTextFrequencies[i] << ' ';
//    }
    
    vector<int> keyValues;
    int pointer = 0;
    
    // finding each value in the key
    for (int j = 0; j < keyLength; j++) {
        // double = frequency (for cipherText), int = ascii
        vector<tuple<double, int>> thisShift;
        // double = sum, int = position in vector
        vector<tuple<double, int>> sumsForThisShift;
        int jump = pointer;
        int ascii = 0;
        double freq = 0;
        // calculating this rows/shifts frequencies
        for (int k = pointer; k <= (500/keyLength); k++) {
            char thisChar = cipherText[jump];
            if (thisChar == ' ') {
                ascii = 0;
                freq = cipherTextFrequencies[0];
                
            } else {
                ascii = int(thisChar)-96;
                freq = cipherTextFrequencies[ascii];            }
            thisShift.push_back(make_tuple(freq, ascii));
            //thisShift.push_back(tuple<double, int>(freq, ascii));
            jump += keyLength;
        }
//        for (int i = 0; i < thisShift.size(); i++){
//            cout << "HELLO " << get<0>(thisShift[i]) << '\n';
//        }
        
        //shifting thisShift over and calculating sums
        for (int p = 0; p <thisShift.size(); p++) {
            double sum = 0;
            //cout << "thisShift[" << p << "] " << get<0>(thisShift[p]) << '\n';
            for (int l = 0; l < thisShift.size(); l++){
                tuple<double, int> tempTuple = thisShift[l];
                //cout << "ascii " << ascii << '\n';
                int ascii = get<1>(tempTuple);
                sum += (get<0>(tempTuple) * alphabetFreq[ascii]);
                cout << get<0>(tempTuple) << " x " << alphabetFreq[ascii] << " = " << sum << '\n';
            }
            cout << "done" << '\n';
            cout << "final sum " << sum << '\n';
            sumsForThisShift.push_back(make_tuple(sum, p));
            rotate(thisShift.begin(),thisShift.end()-1,thisShift.end());
//            for (int i = 0; i < thisShift.size(); i++){ cout << "rotate" << get<0>(thisShift[i]) << '\n';}
        }
        
        tuple<double, int> maxAndPos = sumsForThisShift[0];
        
        for (int q = 1; q < sumsForThisShift.size(); q++){
            //cout << "sums[q] " << q << get<0>(sumsForThisShift[q]) << '\n';
            if (get<0>(sumsForThisShift[q]) >= get<0>(maxAndPos) ) {
                maxAndPos = sumsForThisShift[q];
            }
            //cout << "maxPos " << get<0>(maxAndPos) << '\n';
        }
        
        cout << "done" << '\n';
        //cout << "lastMaxPos " << get<1>(maxAndPos) << '\n';
        
        keyValues.push_back(get<1>(maxAndPos));
        pointer++;
    }
    
    for (int i = 0; i < keyValues.size(); i++ ) { cout << keyValues[i] << ' ';}
    
//    string possiblePlainText = decryptCipher(input, keyValues, keyLength);
//    cout << possiblePlainText;
    return 0;
}
