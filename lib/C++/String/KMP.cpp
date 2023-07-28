// started time: 2023.7.27
// author: pan__

namespace String {
    /* Use the KMP Algorithm */
    template<class T> std::vector<int> prefix_function(const std::vector<T>& s) {
        size_t n = size(s);
        std::vector<int> pi(n);
        for (int i = 1; i < n; ++i) {
            int j = pi[i-1];
            while (j > 0 && s[i] != s[j])
                j = pi[j-1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    }

    template<class T> std::vector<int> z_function(const std::vector<T>& s) {
        size_t n = size(s);
        if (n == 0) return {};
        std::vector<int> z(n);
        for (int i = 1, j = 0; i < n; ++i) {
            int& k = z[i];
            k = (j + z[j] < i) ? 0 : std::min(j + z[j] - i, z[i - j]);
            while (i + k < n && s[k] == s[i + k]) k++;
            if (j + z[j] < i + z[i]) j = i;
        }
        /* Note: The front is the length */
        z.front() = (int) n;
        return z;
    }
};
