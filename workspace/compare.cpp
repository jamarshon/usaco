#include <iostream>
#include <fstream>
 
using namespace std;
 
int main() {
    int T;
    ifstream file1("d.out");
    ifstream file2("f.out");
 
    do {
        string line1, line2;
        getline(file1, line1);
        getline(file2, line2);
        if(file1 || file2) {
            bool print_line1 = false;
            bool print_line2 = false;
            if(file1 && file2) {
                if(line1 != line2) {
                    print_line1 = true;
                    print_line2 = true;
                }
            } else if(file1) {
                print_line1 = true;
            } else {
                print_line2 = true;
            }
 
            if(print_line1) cout << line1 << endl;
            if(print_line2) cout << line2 << endl;
            if(print_line1 || print_line2) cout << endl;
        }
    } while (file1 || file2);
 
    return 0;
}