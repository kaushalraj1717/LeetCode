class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int k_min =1;
        int k_max = *max_element(piles.begin(), piles.end());


        while(k_min < k_max){
            int mid= (k_min + k_max)/2;

            int totalHours = 0;
            for (int pile : piles) {
                totalHours += (pile + mid - 1) / mid;
            }

            if(totalHours <= h){
                k_max= mid;
            }
            else{
                 k_min = mid + 1;

            }

        }

        return k_min;
    }
};