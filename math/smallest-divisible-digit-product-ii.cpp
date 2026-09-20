// LeetCode 3348. Smallest Divisible Digit Product II
// Time:  O(n) plus a tiny O(A*B) precompute (A<=46, B<=29 since t<=1e14)
// Space: O(A*B)

class Solution {
public:
    string smallestNumber(string num, long long t) {
        // ---- 1. Factor t = 2^A * 3^B * 5^C * 7^D. Anything left over -> impossible.
        long long tt = t;
        int A = 0, B = 0, C = 0, D = 0;
        while (tt % 2 == 0) { tt /= 2; A++; }
        while (tt % 3 == 0) { tt /= 3; B++; }
        while (tt % 5 == 0) { tt /= 5; C++; }
        while (tt % 7 == 0) { tt /= 7; D++; }
        if (tt != 1) return "-1";

        int L = (int)num.size();

        auto contrib = [](int dig, int &ea, int &eb, int &ec, int &ed) {
            ea = eb = ec = ed = 0;
            switch (dig) {
                case 2: ea = 1; break;
                case 3: eb = 1; break;
                case 4: ea = 2; break;
                case 5: ec = 1; break;
                case 6: ea = 1; eb = 1; break;
                case 7: ed = 1; break;
                case 8: ea = 3; break;
                case 9: eb = 2; break;
                default: break; // 1 (or 0, only used for prefix bookkeeping)
            }
        };

        // ---- 2. dp[i][j] = min # of digits (from {2,3,4,6,8,9}) needed so that
        //          exponent-of-2 sum >= i AND exponent-of-3 sum >= j.
        vector<vector<int>> dp(A + 1, vector<int>(B + 1, 0));
        static const int da[6] = {1, 0, 2, 1, 3, 0}; // digits 2,3,4,6,8,9
        static const int db[6] = {0, 1, 0, 1, 0, 2};
        for (int i = 0; i <= A; i++) {
            for (int j = 0; j <= B; j++) {
                if (i == 0 && j == 0) continue;
                int best = INT_MAX;
                for (int k = 0; k < 6; k++) {
                    int ni = max(i - da[k], 0), nj = max(j - db[k], 0);
                    if (ni == i && nj == j) continue; // digit gives no progress here, skip
                    best = min(best, dp[ni][nj] + 1);
                }
                dp[i][j] = best;
            }
        }

        auto minDigits = [&](long long ra, long long rb, long long rc, long long rd) -> long long {
            int i = (int)max(0LL, min(ra, (long long)A));
            int j = (int)max(0LL, min(rb, (long long)B));
            return (long long)dp[i][j] + rc + rd;
        };

        // ---- 3. Build the lexicographically smallest zero-free suffix of length Len
        //         that still meets requirement (ra,rb,rc,rd). Caller guarantees feasibility.
        auto buildSuffix = [&](long long ra, long long rb, long long rc, long long rd, long long Len) {
            string res;
            res.reserve((size_t)Len);
            for (long long pos = 0; pos < Len; pos++) {
                long long remaining = Len - pos - 1;
                for (int dig = 1; dig <= 9; dig++) {
                    int ea, eb, ec, ed;
                    contrib(dig, ea, eb, ec, ed);
                    long long nra = max(ra - ea, 0LL), nrb = max(rb - eb, 0LL);
                    long long nrc = max(rc - ec, 0LL), nrd = max(rd - ed, 0LL);
                    if (minDigits(nra, nrb, nrc, nrd) <= remaining) {
                        res.push_back(char('0' + dig));
                        ra = nra; rb = nrb; rc = nrc; rd = nrd;
                        break;
                    }
                }
            }
            return res;
        };

        // ---- 4. Does num itself already work?
        {
            bool zeroFree = true;
            long long ra = A, rb = B, rc = C, rd = D;
            for (char ch : num) {
                int dig = ch - '0';
                if (dig == 0) { zeroFree = false; break; }
                int ea, eb, ec, ed;
                contrib(dig, ea, eb, ec, ed);
                ra = max(ra - ea, 0LL); rb = max(rb - eb, 0LL);
                rc = max(rc - ec, 0LL); rd = max(rd - ed, 0LL);
            }
            if (zeroFree && ra == 0 && rb == 0 && rc == 0 && rd == 0) return num;
        }

        // ---- 5. Same-length search: pivot at the rightmost feasible position
        //         (can't extend the tight prefix past num's first '0').
        int firstZero = L;
        for (int i = 0; i < L; i++) if (num[i] == '0') { firstZero = i; break; }
        int limit = min(firstZero, L - 1);

        vector<long long> pa(limit + 2, 0), pb(limit + 2, 0), pc(limit + 2, 0), pd(limit + 2, 0);
        for (int i = 0; i <= limit; i++) {
            int dig = num[i] - '0';
            int ea, eb, ec, ed;
            contrib(dig, ea, eb, ec, ed);
            pa[i + 1] = pa[i] + ea; pb[i + 1] = pb[i] + eb;
            pc[i + 1] = pc[i] + ec; pd[i + 1] = pd[i] + ed;
        }

        for (int i = limit; i >= 0; i--) {
            int startDig = num[i] - '0';
            for (int dig = startDig + 1; dig <= 9; dig++) {
                int ea, eb, ec, ed;
                contrib(dig, ea, eb, ec, ed);
                long long totalA = pa[i] + ea, totalB = pb[i] + eb;
                long long totalC = pc[i] + ec, totalD = pd[i] + ed;
                long long lra = max((long long)A - totalA, 0LL);
                long long lrb = max((long long)B - totalB, 0LL);
                long long lrc = max((long long)C - totalC, 0LL);
                long long lrd = max((long long)D - totalD, 0LL);
                long long remainingLen = L - i - 1;
                if (minDigits(lra, lrb, lrc, lrd) <= remainingLen) {
                    string suf = buildSuffix(lra, lrb, lrc, lrd, remainingLen);
                    return num.substr(0, i) + char('0' + dig) + suf;
                }
            }
        }

        // ---- 6. No same-length answer: go to the shortest longer length that works.
        long long M0 = minDigits(A, B, C, D);
        long long newLen = max((long long)L + 1, M0);
        return buildSuffix(A, B, C, D, newLen);
    }
};