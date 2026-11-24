class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        const long long LIMIT = 25200; // max possible lcm * gcd

        for (int i = 0; i < n; i++) {
            long long prod = 1;
            long long g = 0;
            long long l = 1;

            for (int j = i; j < n; j++) {
                prod *= nums[j];
                if (prod > LIMIT) break;

                g = std::gcd(g, (long long)nums[j]);
                l = std::lcm(l, (long long)nums[j]);

                if (prod == g * l) {
                    ans = max(ans, j - i + 1);
                }
            }
        }
        return ans;
    }
};