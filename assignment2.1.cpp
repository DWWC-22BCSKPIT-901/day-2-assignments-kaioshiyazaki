#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> generate(int numRows) {
    vector<vector<int>> result;
    result.reserve(numRows); 
    for (int i = 0; i < numRows; ++i) {
        vector<int> row(i + 1, 1); // Initialize all to 1
        for (int j = 1; j < i; ++j) {
            row[j] = result[i-1][j-1] + result[i-1][j];
        }
        result.push_back(row);
    }
    return result;
}

int main() {
    int numRows = 5;
    vector<vector<int>> pascal = generate(numRows);

    cout << "[\n";
    for (const auto& row : pascal) {
        cout << "  [";
        for (int i = 0; i < (int)row.size(); ++i) {
            cout << row[i];
            if (i < (int)row.size() - 1) cout << ",";
        }
        cout << "]\n";
    }
    cout << "]" << endl;
 
    return 0;
}