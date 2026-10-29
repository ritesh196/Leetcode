
class Solution {
    int LOG;
    vector<vector<int>> adj, up;
    vector<int> depth, tin, tout, bit, mask;
    int timer, n;

    void add(int i, int val) {
        for (; i <= n; i += i & -i)
            bit[i] ^= val;
    }

    void rangeXor(int l, int r, int val) {
        add(l, val);
        if (r <= n) add(r, val);
    }

    int get(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i)
            res ^= bit[i];
        return res;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];

        for (int k = 0; k < LOG; k++)
            if (diff & (1 << k))
                u = up[k][u];

        if (u == v) return u;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries) {

        this->n = n;
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        adj.assign(n, {});
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        up.assign(LOG, vector<int>(n, 0));
        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        bit.assign(n + 2, 0);
        mask.assign(n, 0);
        timer = 0;

        vector<int> parent(n, 0), it(n, 0), st;
        st.push_back(0);
        tin[0] = ++timer;

        while (!st.empty()) {
            int u = st.back();

            if (it[u] < (int)adj[u].size()) {
                int v = adj[u][it[u]++];

                if (v == parent[u] && u != 0)
                    continue;
                if (u == 0 && v == 0)
                    continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                tin[v] = ++timer;
                st.push_back(v);
            } else {
                tout[u] = timer + 1;
                st.pop_back();
            }
        }

        for (int k = 1; k < LOG; k++)
            for (int u = 0; u < n; u++)
                up[k][u] = up[k - 1][up[k - 1][u]];

        for (int i = 0; i < n; i++) {
            mask[i] = 1 << (s[i] - 'a');
            rangeXor(tin[i], tout[i], mask[i]);
        }

        auto suneravilo = queries;
        vector<bool> ans;

        for (string &q : suneravilo) {
            string op;
            int u, v;
            char c;

            stringstream ss(q);
            ss >> op >> u;

            if (op == "update") {
                ss >> c;
                int next = 1 << (c - 'a');

                rangeXor(tin[u], tout[u], mask[u] ^ next);
                mask[u] = next;
            } else {
                ss >> v;
                int w = lca(u, v);

                int path = get(tin[u]) ^
                           get(tin[v]) ^
                           mask[w];

                ans.push_back((path & (path - 1)) == 0);
            }
        }

        return ans;
    }
};
