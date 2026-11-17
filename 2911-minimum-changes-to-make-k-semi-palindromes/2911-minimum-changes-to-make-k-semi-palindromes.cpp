
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();

        vector<vector<int>> cost(n, vector<int>(n, 0));

        // Calculate minimum changes for every substring
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int len = j - i + 1;
                int best = n;

                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;

                    int cnt = 0;

                    for (int offset = 0; offset < d; offset++) {
                        int l = i + offset;
                        int r = j - d + 1 + offset;

                        while (l < r) {
                            if (s[l] != s[r]) {
                                cnt++;
                            }
                            l += d;
                            r -= d;
                        }
                    }

                    best = min(best, cnt);
                }

                cost[i][j] = best;
            }
        }

        // DP: minimum changes to split suffix into k parts
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, n));

        dp[n][0] = 0;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = 1; j <= k; j++) {
                for (int l = i + 1; l < n; l++) {
                    dp[i][j] = min(
                        dp[i][j],
                        dp[l + 1][j - 1] + cost[i][l]
                    );
                }
            }
        }

        return dp[0][k];
    }
};
