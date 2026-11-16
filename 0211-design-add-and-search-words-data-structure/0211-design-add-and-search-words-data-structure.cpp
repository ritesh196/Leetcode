
class WordDictionary {
    struct TrieNode {
        TrieNode* child[26];
        bool isEnd;

        TrieNode() {
            for (int i = 0; i < 26; i++) {
                child[i] = nullptr;
            }
            isEnd = false;
        }
    };

    TrieNode* root;

    bool dfs(string &word, int index, TrieNode* node) {
        if (index == word.size()) {
            return node->isEnd;
        }

        if (word[index] == '.') {
            for (int i = 0; i < 26; i++) {
                if (node->child[i] &&
                    dfs(word, index + 1, node->child[i])) {
                    return true;
                }
            }
            return false;
        }

        int pos = word[index] - 'a';

        if (!node->child[pos]) {
            return false;
        }

        return dfs(word, index + 1, node->child[pos]);
    }

public:
    WordDictionary() {
        root = new TrieNode();
    }

    void addWord(string word) {
        TrieNode* curr = root;

        for (char ch : word) {
            int pos = ch - 'a';

            if (!curr->child[pos]) {
                curr->child[pos] = new TrieNode();
            }

            curr = curr->child[pos];
        }

        curr->isEnd = true;
    }

    bool search(string word) {
        return dfs(word, 0, root);
    }
};


/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */