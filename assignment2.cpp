#include <iostream>
#include <vector>

#define maxRows 30

using namespace std;

int majorityNum(const vector<int>& nums) {
    int max = 0;
    int count = 0;

    for (int num : nums) {
        if (count == 0) {
            max = num;
            count = 1;
        } else if (num == max) {
            count++;
        } else {
            count--;
        }
    }
    return max;
}

int main() {
    vector<int> nums = {2,2,1,1,1,2,2};
    cout << "Majority Element: " << majorityNum(nums) << endl;
    return 0;
}