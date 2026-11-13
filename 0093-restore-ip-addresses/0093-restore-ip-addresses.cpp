
class Solution {
public:
    vector<string> ans;

    void solve(string s, int index, int parts, string curr) {
        if (parts == 4 && index == s.size()) {
            curr.pop_back();
            ans.push_back(curr);
            return;
        }

        if (parts >= 4 || index >= s.size())
            return;

        for (int len = 1; len <= 3 && index + len <= s.size(); len++) {
            string sub = s.substr(index, len);

            if (sub.size() > 1 && sub[0] == '0')
                break;

            int num = stoi(sub);

            if (num > 255)
                break;

            solve(s, index + len, parts + 1, curr + sub + ".");
        }
    }

    vector<string> restoreIpAddresses(string s) {
        ans.clear();

        if (s.size() < 4 || s.size() > 12)
            return ans;

        solve(s, 0, 0, "");

        return ans;
    }
};
