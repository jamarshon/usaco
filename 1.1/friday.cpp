/*
ID: jasonl91
PROG: friday
LANG: C++11
*/
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");

    int N;
    int daysInAWeek = 7;
    int* outputArr = new int[daysInAWeek]();

    fin >> N;
    // January 1, 1900 to December 31, 1900+N-1
    int currentFriThirteen = (2 + 12) % 7; // January 1, 1900 was a Monday
    int endYear = 1900 + N - 1;
    int monthOffsets[] = {0,31,28,31,30,31,30,31,31,30,31,30}; 

    for(int year = 1900; year <= endYear; year++) {
      bool isLeapYear = (year % 100 == 0 && year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);

      for(int i = 0; i < 12; i++) {
        int dayOffset = (i == 2 && isLeapYear) ? 1 : 0; // add one day to offset for leap years
        currentFriThirteen = (currentFriThirteen + monthOffsets[i] + dayOffset) % 7;
        outputArr[currentFriThirteen]++;
      }

      currentFriThirteen = (currentFriThirteen + 31) % 7; // December
    }

    for(int i = 0; i < daysInAWeek - 1; i++) {
      fout << outputArr[i] << " ";
    }

    fout << outputArr[daysInAWeek - 1] << endl;
    delete[] outputArr;

    return 0;
}