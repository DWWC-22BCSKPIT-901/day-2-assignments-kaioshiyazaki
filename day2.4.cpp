#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <functional>
using namespace std;

class Solution {
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        int ans = 0;
        vector<int> cnt(batchSize, 0);
        for (int g : groups) {
            int r = g % batchSize;
            if (r == 0) ans++;
            else cnt[r]++;
        }
        vector<int> freq;
        for (int i = 1; i < batchSize; i++) {
            for (int j = 0; j < cnt[i]; j++)
                freq.push_back(i);
        }
        if (freq.empty()) return ans;
        int n = (int)freq.size();
        vector<vector<int>> memo(1 << n, vector<int>(batchSize, -1));
        function<int(int,int)> dfs = [&](int mask, int r) -> int {
            if (mask == (1 << n) - 1) return 0;
            if (memo[mask][r] != -1) return memo[mask][r];
            int res = 0;
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) {
                    int nr = (r + freq[i]) % batchSize;
                    res = max(res, (nr == 0 ? 1 : 0) + dfs(mask | (1 << i), nr));
                }
            }
            memo[mask][r] = res;
            return res;
        };
        ans += dfs(0, 0);
        return ans;
    }
};

class Solution2 {
public:
    int res;
    void backtrack(vector<int>& jobs, vector<int>& workerTime, int idx, int k, int curMax) {
        if (idx == (int)jobs.size()) {
            res = min(res, curMax);
            return;
        }
        if (curMax >= res) return;
        unordered_set<int> seen;
        for (int i = 0; i < k; i++) {
            if (seen.count(workerTime[i])) continue;
            seen.insert(workerTime[i]);
            workerTime[i] += jobs[idx];
            backtrack(jobs, workerTime, idx + 1, k, max(curMax, workerTime[i]));
            workerTime[i] -= jobs[idx];
            if (workerTime[i] == 0) break;
        }
    }
    int minimumTimeRequired(vector<int>& jobs, int k) {
        sort(jobs.begin(), jobs.end(), greater<int>());
        int sum = 0;
        for (auto j : jobs) sum += j;
        res = sum;
        vector<int> workerTime(k, 0);
        backtrack(jobs, workerTime, 0, k, 0);
        return res;
    }
};

int main() {
    {
        Solution sol;
        int batchSize = 3;
        vector<int> groups = {1,2,3,4,5,6};
        cout << sol.maxHappyGroups(batchSize, groups) << endl;
    }
    {
        Solution sol;
        int batchSize = 4;
        vector<int> groups = {1,3,2,5,2,2,1,6};
        cout << sol.maxHappyGroups(batchSize, groups) << endl;
    }
    {
        Solution2 sol2;
        vector<int> jobs = {3,2,3};
        int k = 3;
        cout << sol2.minimumTimeRequired(jobs, k) << endl;
    }
    {
        Solution2 sol2;
        vector<int> jobs = {1,2,4,7,8};
        int k = 2;
        cout << sol2.minimumTimeRequired(jobs, k) << endl;
    }
    return 0;
}
