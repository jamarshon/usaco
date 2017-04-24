#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream fin1 ("output.txt");
    ifstream fin2 ("output3.txt");

    int T = 99;
    string a, b;
    int correct = 0;
    for(int i = 1; i <= T; i++) {
        fin1 >> a;
        fin2 >> b;
        fin1 >> a;
        fin2 >> b;
        fin1 >> a;
        fin2 >> b;
        if(a != b) {
            cout << "Case #" << i << " " << a << " " << b << endl;
        } else {
            correct++;
        }
    }
    cout << correct << " / " << T << endl;
    return 0;
}