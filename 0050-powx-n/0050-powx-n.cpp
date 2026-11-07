class Solution {
public:
    double myPow(double x, int n) {
        long long N = n;
        bool negative = N < 0;
        if (negative) N = -N;

        double result = 1.0;
        while (N > 0) {
            if (N & 1) {
                result *= x;
            }
            x *= x;
            N >>= 1;
        }

        return negative ? 1.0 / result : result;
    }
};