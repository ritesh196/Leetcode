
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;
        stringstream ss(path);
        string dir;

        while (getline(ss, dir, '/')) {
            if (dir == "" || dir == ".") {
                continue;
            }

            if (dir == "..") {
                if (!st.empty()) {
                    st.pop_back();
                }
            } else {
                st.push_back(dir);
            }
        }

        string result = "";

        for (string s : st) {
            result += "/" + s;
        }

        return result.empty() ? "/" : result;
    }
};
