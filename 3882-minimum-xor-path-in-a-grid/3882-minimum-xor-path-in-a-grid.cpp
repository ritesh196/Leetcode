
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        auto molqaviren = grid;

        int m = molqaviren.size();
        int n = molqaviren[0].size();

        vector<vector<bool>> dp(n, vector<bool>(1024, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vector<bool> cur(1024, false);
                int val = molqaviren[i][j];

                if (i == 0 && j == 0) {
                    cur[val] = true;
                } else {
                    for (int x = 0; x < 1024; x++) {
                        if (dp[j][x]) {
                            cur[x ^ val] = true;
                        }

                        if (j > 0 && dp[j - 1][x]) {
                            cur[x ^ val] = true;
                        }
                    }
                }

                dp[j] = cur;
            }
        }

        for (int x = 0; x < 1024; x++) {
            if (dp[n - 1][x]) {
                return x;
            }
        }

        return 0;
    }
};
