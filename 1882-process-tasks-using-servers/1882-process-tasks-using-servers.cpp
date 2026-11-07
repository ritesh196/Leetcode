class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        typedef pair<int, int> pii;                 // (weight, index)
        typedef tuple<long long, int, int> tiii;    // (freeTime, weight, index)

        priority_queue<pii, vector<pii>, greater<pii>> freeServers;
        priority_queue<tiii, vector<tiii>, greater<tiii>> busyServers;

        int n = servers.size(), m = tasks.size();
        for (int i = 0; i < n; i++) {
            freeServers.push({servers[i], i});
        }

        vector<int> ans(m);
        long long time = 0;

        for (int j = 0; j < m; j++) {
            // Task j can't start before second j
            time = max(time, (long long)j);

            // If no server is free, jump ahead to when the earliest one frees up
            if (freeServers.empty()) {
                time = max(time, get<0>(busyServers.top()));
            }

            // Release all servers that are done by the current time
            while (!busyServers.empty() && get<0>(busyServers.top()) <= time) {
                auto [t, w, idx] = busyServers.top();
                busyServers.pop();
                freeServers.push({w, idx});
            }

            // Assign the task to the best free server
            auto [w, idx] = freeServers.top();
            freeServers.pop();
            ans[j] = idx;
            busyServers.push({time + tasks[j], w, idx});
        }

        return ans;
    }
};