#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = (int)height.size() - 1;
        int max_water = 0;

        while (left < right) {
            int current_height = min(height[left], height[right]);
            int current_width = right - left;
            int current_area = current_height * current_width;

            max_water = max(max_water, current_area);

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return max_water;
    }
};

int main() {
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    Solution sol;
    cout << "Maximum Area: " << sol.maxArea(height) << endl;
    return 0;
}
