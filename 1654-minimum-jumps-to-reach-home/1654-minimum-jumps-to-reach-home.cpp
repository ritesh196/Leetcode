
class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        const int LIMIT = 6000;

        vector<bool> blocked(LIMIT + 1, false);
        vector<vector<bool>> visited(LIMIT + 1, vector<bool>(2, false));

        for (int pos : forbidden) {
            blocked[pos] = true;
        }

        queue<tuple<int, int, int>> q;

        q.push({0, 0, 0});
        visited[0][0] = true;

        while (!q.empty()) {
            auto [pos, back, steps] = q.front();
            q.pop();

            if (pos == x) {
                return steps;
            }

            int forward = pos + a;

            if (forward <= LIMIT &&
                !blocked[forward] &&
                !visited[forward][0]) {

                visited[forward][0] = true;
                q.push({forward, 0, steps + 1});
            }

            int backward = pos - b;

            if (back == 0 &&
                backward >= 0 &&
                !blocked[backward] &&
                !visited[backward][1]) {

                visited[backward][1] = true;
                q.push({backward, 1, steps + 1});
            }
        }

        return -1;
    }
};
