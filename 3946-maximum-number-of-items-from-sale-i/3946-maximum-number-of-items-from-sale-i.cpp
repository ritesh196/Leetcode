
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        int cheapest = INT_MAX;

        vector<int> freeCnt(n, 0);

        for (int i = 0; i < n; i++) {
            cheapest = min(cheapest, items[i][1]);

            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    freeCnt[i]++;
                }
            }
        }

        vector<int> dp(budget + 1, -1e9);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            int price = items[i][1];
            int gain = freeCnt[i] + 1;

            for (int j = budget; j >= price; j--) {
                dp[j] = max(dp[j], dp[j - price] + gain);
            }
        }

        int ans = 0;

        for (int j = 0; j <= budget; j++) {
            if (dp[j] != -1e9) {
                ans = max(ans, dp[j] + (budget - j) / cheapest);
            }
        }

        return ans;
    }
};
