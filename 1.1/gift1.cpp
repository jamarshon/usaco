/*
ID: jasonl91
PROG: gift1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");

    string person, giver, receiver;
    int NP, amount, N, i, dividedAmount;

    fin >> NP;

    int* walletArr = new int[NP]();
    string nameArr [NP];
    unordered_map<string, int> hashTable;

    for(i = 0; i < NP; i++) {
      fin >> person;
      hashTable[person] = i;
      nameArr[i] = person;
    }

    while(fin >> giver) {
      fin >> amount >> N;
      if(N > 0) {
        walletArr[hashTable[giver]] -= amount - (amount % N); // giver keeps remainder
        dividedAmount = amount / N; 
        for(i = 0; i < N; i++) {
          fin >> receiver;
          walletArr[hashTable[receiver]] += dividedAmount; // receiver gets divided amount
        }
      }
    }

    for(i = 0; i < NP; i++) {
      fout << nameArr[i] << " " << walletArr[i] << endl;
    }

    delete[] walletArr;
    return 0;
}