#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void print(vector<T> v) { for(auto e: v) cout << e << ' '; cout << endl; }

template <typename T> 
void print2(vector<vector<T>> v) { for(auto v2: v) print(v2); }


int magic(int N, int Q, string arr[], int score[]) {
    string mine = arr[0];
    int correct = score[0];
    int same = 0;
    for(int i = 0; i < Q; i++) {
        if(mine[i] == arr[1][i]) {
            same++;
        }
    }

    int wrong = Q - correct;
    int different = Q - same;
    return min(same, correct) + Q - max(same, correct);
}

int main() {
    int T, N, Q;
    cin >> T; 
    for (int i = 1; i <= T; i++) {
        cin >> N >> Q;
        string arr[N + 1];
        int score[N];
        for(int j = 0; j <= N; j++) {
            cin >> arr[j];
            // cout << arr[j] << endl;
        }
        for(int j = 0; j < N; j++) {
            cin >> score[j];
            // cout << score[j] << endl;
        }
        cout << "Case #" << i << ": " << magic(N, Q, arr, score) << endl;
    }
    return 0;
}