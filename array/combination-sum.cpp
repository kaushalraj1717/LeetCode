class Solution {
public:
    vector<vector<int>> ans;

    void solve(vector<int>& candidates, int target, int start,
               vector<int>& current) {

        // Target achieved
        if (target == 0) {
            ans.push_back(current);
            return;
        }

        for (int i = start; i < candidates.size(); i++) {

            // Since candidates are positive
            if (candidates[i] > target)
                break;

            // Choose
            current.push_back(candidates[i]);

            // i, not i+1 -> same number can be reused
            solve(candidates, target - candidates[i], i, current);

            // Backtrack
            current.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {

        sort(candidates.begin(), candidates.end());

        vector<int> current;
        solve(candidates, target, 0, current);

        return ans;
    }
};