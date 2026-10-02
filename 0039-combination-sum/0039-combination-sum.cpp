class Solution {
public:
    vector<vector<int>> ans;

    void solve(vector<int>& candidates, int target, int index, vector<int>& temp) {
        if (target == 0) {
            ans.push_back(temp);
            return;
        }

        if (target < 0 || index == candidates.size())
            return;

        temp.push_back(candidates[index]);
        solve(candidates, target - candidates[index], index, temp);

        temp.pop_back();
        solve(candidates, target, index + 1, temp);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> temp;
        solve(candidates, target, 0, temp);
        return ans;
    }
};