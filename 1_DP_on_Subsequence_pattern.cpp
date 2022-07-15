// Basic Recursion

bool helper(vector<int>& arr, int n, int k){
    if(k==0){ 
        return true;
    }
    if(n==0){ 
        if(arr[0]==k){ return true; }
        return false;
    }

    bool take= false;
    if(k>=arr[n]){
        take= helper(arr, n-1, k-arr[n], dp);
    }
    
    bool notTake= helper(arr, n-1, k, dp);
    return take|| notTake;
}

bool subsetSumToK(int n, int k, vector<int> &arr) {
    return helper(arr,n-1, k);
}

// DP
bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<bool>> dp(n, vector<bool>(k+1));
    
    // row denotes index, k denotes column
    // if target==0 , whole col will be true
    for(int i=0; i<n; i++){
        dp[i][0]=true;
    }
    
    for(int j=0; j<=k; j++){
        if(arr[0]==j){
            dp[0][j]=true;
        }
        else{
            if(j!=0) dp[0][j]=false;  // as dp[0][0] is already filled in prev base case
        }
    }
    for(int i=1; i<n; i++){
        for(int j=1; j<=k; j++){
            bool take= false;
            if(j>=arr[i]){ take= dp[i-1][j-arr[i]]; }
            bool notTake= dp[i-1][j];
            dp[i][j]= take||notTake;
        }
    }
    return dp[n-1][k];
}

//-----------------------------------------------------------------------------------------------------------------
VARIATIONS :

1. Partition Equal Subset Sum: 
    subsetSumToK where [ target=SUM(arr)/2 ]

2. Partition a set into two subsets such that the difference of subset sums is minimum: 
    We know after finding subsetSumToK, we have our DP array filled, where in the last row, we can query for wheather we have any subsequence whose sum is the given target 't' --> i.e at dp[n][t]

3. Number Of Subsets :
    Here number of subset is asked, so (take + noTake)

4. Partitions With Given Difference:
    we want S1>S2 and S1-S2=D. Let sum of array element be 'total'
    So, if so count number of subset with sum S1, these many sunset with sum s2= total-S1 exist. So, S1-S2=D can be rewritten as 
    S1-(total-S1)=D. OR, S1=(total-D)/2. 
    So we need to find number of subset with sum S1 (Or (total-D)/2 ).
    // ---- BASE CASE MODIFICATION: ---- (due to constraints that arr[i] can be 0 also)
            if(n==0){
                if(k==0 && arr[0]==0){ return 2; } // either take OR noTake, dono se answer milega
                else if(k==0 && arr[0]!=0){ return 1; } // only noTake, dono se answer milega
                else if(k!=0 && arr[0]==k){ return 1; } // only Take, dono se answer milega
                else if(k!=0 && arr[0]==0){ return 0; } // koi answer nhi milega
            }

5. Target Sum (using +, -) :
    This question is same question as 'Partitions With Given Difference'. Take sum of all '+' wala at a side (say S1), sum of all '-' wala at a side (say S2), and ou quey is number of subset such that S1-S2=target.

6. 0 1 Knapsack:
    Same logic with slight variation in base case '<=' intead of '='
            if(maxWt==0){ return 0; }
            if(n==0){
                if(maxWt>=weight[0]){
                    return value[0];
                }
                return 0;
            }

7. Minimum Elements (Minimum Coins):
            if(target==0){
                return 0;
            }
            if(n==0){
                if(terget%num[n]==0){
                    return terget/num[n];
                }
                return 1e9;
            }

8. Ways To Make Coin Change :
            if(target==0){
                return 1;
            }
            if(n==0){
                if(target%deno[n]==0){
                    return 1; // In that case we have to take it. So only 1 option (i.e take). So return 1
                }
                return 0;
            }

9. Unbounded Knapsack :
            if(maxWt==0){
                return 0;
            }
            if(n==0){
                if(maxWt>=weight[0]){
                    return (maxWt/weight[0])*profit[0];
                }
                return 0;
            }

10. Rod cutting problem :
    Nearly same as Unbounded knapsack.


VERDICT:
// Recursion starts from lastIdx --> firstIdx.
    Always think of base case at the end (after writting recurrance)

// BASE CASES ARE SIMILAR [Except 4, where a[i] can be 0 too].
    While identifying base case : --> think of what if target is achieved + also think of first index
        if(target achived){  /* code */  }
        if(index==0){  /* code */   }

// Take OR notTake in maximum cases.
    a. For maximimum profit: --> while take, add profit value, return max(take, notTake);
    b. For number of ways: --> return (take + notTake)

// Tabulation [firstIdx --> lastIdx]. Opposite to that of recursion
    a. Write Base Case from recursion (thinking of all the possible way in which might we hit base case (in recursion), & fill these cells)
    b. fill rest of the grid (in opposite fashion to that of recursion), using recurrance relation [copy-paste] from Recursion.

