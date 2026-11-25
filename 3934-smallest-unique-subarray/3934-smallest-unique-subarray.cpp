class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        // Build suffix array by prefix doubling
        vector<int> sa(n), rnk(n), tmp(n);
        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rnk[i] = nums[i];
        }
        for (int k = 1;; k <<= 1) {
            auto cmp = [&](int a, int b) {
                if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
                int ra = a + k < n ? rnk[a + k] : -1;
                int rb = b + k < n ? rnk[b + k] : -1;
                return ra < rb;
            };
            sort(sa.begin(), sa.end(), cmp);
            tmp[sa[0]] = 0;
            for (int i = 1; i < n; i++)
                tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            rnk = tmp;
            if (rnk[sa[n - 1]] == n - 1) break;
        }

        // Kasai: lcp[i] = LCP of suffixes sa[i-1] and sa[i]
        vector<int> lcp(n, 0);
        for (int i = 0, h = 0; i < n; i++) {
            if (rnk[i] > 0) {
                int j = sa[rnk[i] - 1];
                while (i + h < n && j + h < n && nums[i + h] == nums[j + h]) h++;
                lcp[rnk[i]] = h;
                if (h > 0) h--;
            } else {
                h = 0;
            }
        }

        int ans = n;
        for (int p = 0; p < n; p++) {
            int i = sa[p];
            int m = 0;
            if (p > 0) m = max(m, lcp[p]);
            if (p + 1 < n) m = max(m, lcp[p + 1]);
            if (m + 1 <= n - i) ans = min(ans, m + 1);
        }
        return ans;
    }
};