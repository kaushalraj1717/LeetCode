class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        for (auto &e : invocations)
            adj[e[0]].push_back(e[1]);

        vector<int> vis(n, 0);

        // DFS to mark all suspicious methods
        function<void(int)> dfs = [&](int u) {
            vis[u] = 1;
            for (int v : adj[u]) {
                if (!vis[v])
                    dfs(v);
            }
        };

        dfs(k);

        // If any non-suspicious method invokes a suspicious one,
        // nothing can be removed.
        for (auto &e : invocations) {
            int u = e[0], v = e[1];
            if (!vis[u] && vis[v]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        // Remove suspicious methods
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!vis[i])
                ans.push_back(i);
        }

        return ans;
    }
};