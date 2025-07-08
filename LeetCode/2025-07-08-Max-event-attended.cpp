class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        // Sort events by end time
        sort(events.begin(), events.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });

        // Extract start times for binary search
        vector<int> endTimes;
        for (auto &e : events) endTimes.push_back(e[1]);

        // DP table: dp[i][j] = max value using first i events and j picks
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        for (int i = 1; i <= n; i++) {
            int start = events[i - 1][0];
            int value = events[i - 1][2];

            // Find last non-overlapping event
            int prev = upper_bound(endTimes.begin(), endTimes.begin() + i - 1, start - 1) - endTimes.begin();

            for (int j = 1; j <= k; j++) {
                // Skip current or take it with last non-overlapping
                dp[i][j] = max(dp[i - 1][j], dp[prev][j - 1] + value);
            }
        }

        return dp[n][k];
    }
};
