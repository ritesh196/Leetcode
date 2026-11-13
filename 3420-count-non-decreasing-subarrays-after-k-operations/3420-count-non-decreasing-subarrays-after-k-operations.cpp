
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        long long ans = 0;
        long long cost = 0;

        deque<pair<int, int>> dq;

        int n = nums.size();
        int j = n - 1;

        for (int i = n - 1; i >= 0; i--) {
            int num = nums[i];
            int count = 1;

            while (!dq.empty() && dq.back().first < num) {
                int nextNum = dq.back().first;
                int nextCount = dq.back().second;

                dq.pop_back();

                count += nextCount;
                cost += 1LL * (num - nextNum) * nextCount;
            }

            dq.push_back({num, count});

            while (cost > k) {
                int rightmostNum = dq.front().first;
                int rightmostCount = dq.front().second;

                cost -= rightmostNum - nums[j];
                j--;

                dq.pop_front();

                if (rightmostCount > 1) {
                    dq.push_front({rightmostNum, rightmostCount - 1});
                }
            }

            ans += j - i + 1;
        }

        return ans;
    }
};
