#include <bits/stdc++.h>
// MEMOIZATION
int helper(vector<vector<int>> &point, vector<vector<int>>& dp, int idx, int day, int task){
    if(idx==day){
        return 0;
    }
    if(dp[idx][task]!=-1){ return dp[idx][task]; }
    int mx=INT_MIN;
    for(int i=0; i<=2; i++){
        if(i!=task){
            int a= helper(point, dp, idx+1, day, i);
            mx=max(mx, a);
        }
    }
    mx+=point[idx][task];
    dp[idx][task]=mx;
    return mx;
}

int ninjaTraining(int n, vector<vector<int>> &points){
    int mx=INT_MIN;
    vector<vector<int>> dp1(n+1, vector<int>(3, -1));
    vector<vector<int>> dp2(n+1, vector<int>(3, -1));
    vector<vector<int>> dp3(n+1, vector<int>(3, -1));
    int a= helper(points, dp1, 0, n, 0);
    int b= helper(points, dp2, 0, n, 1);
    int c= helper(points, dp3, 0, n, 2);
    mx=max(a, max(b, c));
    return mx;
}

//--------------------------------------------------------------------------------------------------
// DP
int helper(vector<vector<int>> &point, int day){
    vector<vector<int>> dp(day+1, vector<int>(3));
    for(int j=0; j<3; j++){
        dp[day][j]=0;
    }
    for(int i=day-1; i>=0; i--){
        for(int j=0; j<3; j++){
            int mx=INT_MIN;
            for(int task=0; task<=2; task++){
                if(task!=j){
                    mx=max(mx, dp[i+1][task]);
                }
            }
            mx+=point[i][j];
            dp[i][j]=mx;
        }
    }
    // now just find the maximum of 0th row (day)
    return *max_element(dp[0].begin(), dp[0].end());
}

int ninjaTraining(int n, vector<vector<int>> &points){
    return helper(points, n);
}