#include <bits/stdc++.h>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

long get(const unordered_map<long, unordered_map<long, long>>& dp,
         const long& key1, const long& key2) {
  if (!dp.count(key1)) return 0;
  const auto& inner_map = dp.find(key1)->second;
  if (!inner_map.count(key2)) return 0;
  return inner_map.find(key2)->second;
}

// Complete the countTriplets function below.
// https://www.hackerrank.com/challenges/count-triplets-1/problem
long countTriplets(vector<long> arr, long r) {
  if (arr.empty()) return 0;
  long count = 0;
  unordered_map<long, unordered_map<long, long>> dp;
  for (int i = arr.size() - 1; i >= 0; --i) {
    if (arr[i] > LONG_MAX / r) {
      dp[arr[i]][1]++;
      continue;
    }

    const long& target = arr[i] * r;
    const long& chain1 = get(dp, target, 1);
    const long& chain2 = get(dp, target, 2);
    /*
    dp[e][1] is the number of times e appears so far
    dp[e][2] is the unique number of times a chain of two that begins with this
    e

    triplet is increased by number of chain of two for arr[i] * r since this e
    completes it
    chain of two is increased by number of chain of one for arr[i] * r since
    this e completes it
    */
    count += chain2;
    dp[arr[i]][1]++;
    dp[arr[i]][2] += chain1;
  }

  return count;
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string nr_temp;
  getline(cin, nr_temp);

  vector<string> nr = split(rtrim(nr_temp));

  int n = stoi(nr[0]);

  long r = stol(nr[1]);

  string arr_temp_temp;
  getline(cin, arr_temp_temp);

  vector<string> arr_temp = split(rtrim(arr_temp_temp));

  vector<long> arr(n);

  for (int i = 0; i < n; i++) {
    long arr_item = stol(arr_temp[i]);

    arr[i] = arr_item;
  }

  long ans = countTriplets(arr, r);

  fout << ans << "\n";

  fout.close();

  return 0;
}

string ltrim(const string& str) {
  string s(str);

  s.erase(s.begin(),
          find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

  return s;
}

string rtrim(const string& str) {
  string s(str);

  s.erase(
      find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
      s.end());

  return s;
}

vector<string> split(const string& str) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(" ", start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}
