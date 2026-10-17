
class Solution {
public:
    string getPermutation(int n, int k) {
        string nums = "";
        vector<int> fact(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            nums += char('0' + i);
            fact[i] = fact[i - 1] * i;
        }

        k--;

        string ans = "";

        for (int i = n; i >= 1; i--) {
            int index = k / fact[i - 1];

            ans += nums[index];
            nums.erase(index, 1);

            k %= fact[i - 1];
        }

        return ans;
    }
};
