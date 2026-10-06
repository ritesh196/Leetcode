class Solution {
public:
    string countAndSay(int n) {
        string result = "1";

        for (int i = 1; i < n; i++) {
            string next = "";

            for (int j = 0; j < result.size(); ) {
                int count = 0;
                char ch = result[j];

                while (j < result.size() && result[j] == ch) {
                    count++;
                    j++;
                }

                next += to_string(count);
                next += ch;
            }

            result = next;
        }

        return result;
    }
};