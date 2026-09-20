class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m= word2.size();

        vector<int> suf(m+1, n);

        int p= n-1;

        for(int j= m-1; j>=0; j--){
            while(p >= 0 && word1[p] != word2[j])
            p--;
            if(p<0)
              break;

            suf[j] = p;
            p--;  
        }

        vector<int> ans;
        int i = 0;
        bool mismatchUsed = false;

        for(int j=0; j<m; j++){
            while(i<n){
                if(word1[i] == word2[j]){
                    ans.push_back(i);
                    i++;
                    break;
                }

                if (!mismatchUsed &&
                    (j == m - 1 || (suf[j + 1] < n && suf[j + 1] > i))){
                     ans.push_back(i);
                     i++;
                     mismatchUsed = true;
                     break;
                }
                i++;
            }

            if(ans.size() != j+1)
                return{};
        }

        return ans;
    }
};