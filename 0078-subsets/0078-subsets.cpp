
class Solution {
public:
    vector<vector<int>> ans;

    void solve(vector<int>& nums, int index, vector<int>& temp) {
        if (index == nums.size()) {
            ans.push_back(temp);
            return;
        }

        // Include current element
        temp.push_back(nums[index]);
        solve(nums, index + 1, temp);

        // Exclude current element
        temp.pop_back();
        solve(nums, index + 1, temp);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> temp;
        solve(nums, 0, temp);
        return ans;
    }
};
