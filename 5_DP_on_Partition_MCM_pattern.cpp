// This pattern is also called partition DP pattern

// index:     0   1   2   3   4         [n=5]
//  arr:    [ 10  20  30  40  50 ]
//                'i'         'j'       [initially i=1, j=n-1]
//                'k' 'k' 'k'           [for(int k=i; k<=j-1; k++)]

//     call   f(i, k) + f(k+1, j) + arr[i-1]*arr[k]*arr[j]

// for k==1:   f(1,1)  + f(2, 4)  + arr[0]* arr[1]* arr[4]     👉 (A)|(BCD)
// for k==2:   f(1,2)  + f(3, 4)  + arr[0]* arr[2]* arr[4]     👉 (AB)|(CD)
// for k==3:   f(1,3)  + f(4, 4)  + arr[0]* arr[3]* arr[4]     👉 (ABC)|(D)


// Recursion
int helper(vector<int>& arr, int i, int j){
    if(i==j){
        return 0;
    }
    int ans=1e9;
    for(int k=i; k<=j-1; k++){
        int res= helper(arr, i, k) + helper(arr, k+1, j);
        res+=(arr[i-1]*arr[k]*arr[j]);
        ans= min(ans, res);
    }
    return ans;
}
int matrixMultiplication(vector<int> &arr, int n){
    return helper(arr, 1, n-1); // NOTE: we called 👉 f(1, n-1)
}

// DP
int matrixMultiplication(vector<int> &arr, int n){
    vector<vector<int>> dp(n, vector<int>(n));
    for(int i=0; i<n; i++){
        dp[i][i]=0;
    }

    //In recursion 'i' goes from [ 1 --> n-1 ]
    //             'j' goes from [n-1 ---> 1 ]
    // So, in tabulation we go in reverse order. But as 👉 [j has to be >=i], so we wrote loop as below

    for(int i=n-1; i>=1; i--){
        for(int j=i; j<=n-1; j++){
            if(i==j){ continue; }
            
            int ans=1e9;
            for(int k=i; k<=j-1; k++){
                int res= dp[i][k] + dp[k+1][j] ;
                res+=(arr[i-1]*arr[k]*arr[j]);
                ans= min(ans, res);
            }
            dp[i][j]=ans;
        }
    }
    return dp[1][n-1];
}

//-----------------------------------------------------------------------------------------------------------------------------------------

VARIATIONS :

1. Minimum Cost to Cut a Stick:      Notes & Explainations are in copy
// Basic Recursion
    
    int helper(vector<int>& cut, int i, int j){
        if(i>j){ // no possible cut point found
            return 0;
        }
        
        int minCost=INT_MAX;
        
        for(int k=i; k<=j; k++){
            // subproblems ar independent (as cut point are sorted) & can be solved individually
            int a= helper(cut, i, k-1);
            int b= helper(cut, k+1, j);
            int cost= cut[j+1]-cut[i-1];
            
            minCost=min(minCost, a+b+cost);
        }
        
        return minCost;
    }
    
    int minCost(int n, vector<int>& cut) {
        cut.insert(cut.begin(), 0);
        cut.push_back(n);
        // The two above operation are done to easyily calculate length of stick
        
        sort(cut.begin(), cut.end()); 
        // to eiminate dependency of sub-problems from each other so that they can be solved individually
        
        return helper(cut, 1, cut.size()-2);
    }
        
//--------------------------------------------------------------------------------------------------------  
    // Tabulation
    
    int minCost(int n, vector<int>& cut) {
        cut.insert(cut.begin(), 0);
        cut.push_back(n);
        
        sort(cut.begin(), cut.end()); 
        
        vector<vector<int>> dp(cut.size(), vector<int>(cut.size(), 0)); 
        
        // Go in reverse order from recusrion
        for(int i=cut.size()-2; i>=1; i-- ){ 
            for(int j=1; j<=cut.size()-2; j++){
                
                // Base Case
                if(i>j){ continue; } // as DP is initialized with 0
                
                int minCost=INT_MAX;
        
                for(int k=i; k<=j; k++){
                    // subproblems ar independent (as cut point are sorted) & can be solved individually
                    int a= dp[i][k-1];
                    int b= dp[k+1][j];
                    int cost= cut[j+1]-cut[i-1];

                    minCost=min(minCost, a+b+cost);
                }
                dp[i][j]=minCost;
            }
        }
        return dp[1][cut.size()-2];
    }



2. Burst Balloons:       Notes & Explainations are in copy
Code is exactly same as "Minimum Cost to Cut a Stick" but thought process is completely different !
// Basic Recursion
    
    int helper(vector<int>& num, int i, int j){
        if(i>j){  // no baloon found to burst
            return 0;
        }
        
        int maxCoin=INT_MIN;
        
        for(int k=i; k<=j; k++){
            // assuming 'num[k]' is busted in last step (when there is only num[k] left to burst)
            // num[]={ <any ele from i till k-1 idx>, num[k] }
            int cost=num[i-1]*num[k]*num[j+1];
            
            // Now we are at 2nd last step, & left with 2 elements
            int a= helper(num, i, k-1); // num[]={ <any ele from i till k-1 idx>, num[k] }
            int b= helper(num, k+1, j); // num[]={ num[k], <any ele from k+1 till j idx> }
            
            maxCoin= max(maxCoin, a+b+cost);
        }
        
        return maxCoin;
    }
    
    int maxCoins(vector<int>& num) {
        num.insert(num.begin(), 1);
        num.push_back(1);
        // The two above operation are done to avoid edge cases to consider 1 in case of out of bound index
        
        return helper(num, 1, num.size()-2);
    }
  
//--------------------------------------------------------------------------------------------------------  
    // Tabulation
    
    int maxCoins(vector<int>& num) {
        num.insert(num.begin(), 1);
        num.push_back(1);
        
        vector<vector<int>> dp(num.size(), vector<int>(num.size(), 0));
        
        // Go in reverse order from recusrion
        for(int i=num.size()-2; i>=1; i--){
            for(int j=1; j<=num.size()-2; j++){
                
                if(i>j){ continue; } // Base Case : Already filled with 0
                
                int maxCoin=INT_MIN;
                
                for(int k=i; k<=j; k++){
                    int cost=num[i-1]*num[k]*num[j+1];

                    int a= dp[i][k-1]; 
                    int b= dp[k+1][j]; 

                    maxCoin= max(maxCoin, a+b+cost);
                }
                dp[i][j]=maxCoin;
            }
        }
        return dp[1][num.size()-2];
    }



3. Boolean Evaluation:       Notes & Explainations are in copy
// Basic Recursion
    
    int helper(string& exp, int i, int j, bool isTrue){
        if(i>j){ return 0; }
        if(i==j){
            if(isTrue==true && exp[i]=='T'){ return 1; }
            if(isTrue==false && exp[i]=='F'){ return 1; }
            return 0;
        }
        
        int ways=0;
        for(int k=i+1; k<=j-1; k+=2){
            char operand=exp[k];
            int x1= helper(exp, i, k-1, true); int y1= helper(exp, i, k-1, false);
            int x2= helper(exp, k+1, j, true); int y2= helper(exp, k+1, j, false);
            
            if(operand=='|'){
                if(isTrue==true){ ways+=((x1*x2)+(y1*x2)+(x1*y2)); } // we are looking for true
                if(isTrue==false){ ways+=(y1*y2); } // we are looking for false
            }
            else if(operand=='&'){
                if(isTrue==true){ ways+=(x1*x2); }
                if(isTrue==false){ ways+=((x1*y2)+(y1*x2)+(y1*y2)); }
            }
            else if(operand=='^'){
                if(isTrue==true){ ways+=((y1*x2)+(x1*y2)); }
                if(isTrue==false){ ways+=((x1*x2)+(y1*y2)); }
            }
        }
        return ways;
    }

    int evaluateExp(string & exp) {
        return helper(exp, 0, exp.size()-1, true); // we are looking for true
    }
  
//--------------------------------------------------------------------------------------------------------  
    // Tabulation
    
    int evaluateExp(string & exp) {
        int n=exp.size();
        vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(2, 0)));
        
        for(int i=n-1; i>=0; i--){
            for(int j=0; j<=n-1; j++){
                if(i>j){ continue; }
                if(i==j){
                    dp[i][j][1]=(exp[i]=='T');
                    dp[i][j][0]=(exp[i]=='F');
                }
                else{
                    ll waysT=0; // number of ways to return TRUE
                    ll waysF=0; // number of ways to return FALSE
                    
                    for(int k=i+1; k<=j-1; k+=2){
                        
                        char operand=exp[k];
                        int x1= dp[i][k-1][1]; int y1=dp[i][k-1][0];
                        int x2= dp[k+1][j][1]; int y2= dp[k+1][j][0];

                        if(operand=='|'){
                            
                            waysT= (waysT + ( (x1*x2)%m +(y1*x2)%m +(x1*y2)%m )%m )%m;
                            waysF= (waysF + (y1*y2)%m )%m;
                        }
                        else if(operand=='&'){
                            waysT= (waysT + (x1*x2)%m )%m;
                            waysF= (waysF + ( (x1*y2)%m +(y1*x2)%m +(y1*y2)%m )%m )%m;
                        }
                        else if(operand=='^'){
                            waysT= (waysT + ( (y1*x2)%m +(x1*y2)%m )%m )%m;
                            waysF= (waysF + ( (x1*x2)%m +(y1*y2)%m )%m )%m;
                        }
                    }
                    dp[i][j][1]=waysT%m;
                    dp[i][j][0]=waysF%m;
                }
            }
        }
        return (int)dp[0][n-1][1];
    }



4. Palindrome Partitioning II:        Notes & Explainations are in copy
// Basic Recursion
    
    bool isPalindrome(string& s, int start, int end){
        while(start<=end){
            if(s[start]!=s[end]){
                return false;
            }
            start++; end--;
        }
        return true;
    }
    int helper(string& s, int idx){
        if(idx==s.size()){
            return 0;
        }
        
        int mini=INT_MAX;
        for(int k=idx; k<s.size(); k++){  // try to cut at every possible partition indexes (which are palindrome ofc)
            if(isPalindrome(s, idx, k)==true){
                int a= helper(s, k+1);
                mini=min(mini, a);
            }
        }
        return mini+1;
    }
    int minCut(string s) {
        return helper(s, 0)-1;  // -1 because we are also counting abcdb| as a partion & counting +1
    }
  
//--------------------------------------------------------------------------------------------------------  
    // Tabulation
    
    int minCut(string s) {
        
        int n=s.size();
        vector<int> dp(n+1);
        
        dp[n]=0;
        for(int i=n-1; i>=0; i--){
            int mini=INT_MAX;
            for(int k=i; k<s.size(); k++){
                if(isPalindrome(s, i, k)==true){
                    int a= dp[k+1];
                    mini=min(mini, a);
                }
            }
            dp[i]= mini+1;
        }
        return dp[0]-1;
    }



5. Partition Array for Maximum Sum:        Notes & Explainations are in copy
// Basic Recursion
    
    int helper(vector<int>& arr, int idx, int k){
        if(idx==arr.size()){
            return 0;
        }
        
        int largestSum=INT_MIN;
        int len=0; int mx=INT_MIN;
        
        for(int div=idx; div< min(arr.size(), idx+k); div++){
            len++; mx= max(mx, arr[div]);
            int a= (len*mx) + helper(arr, div+1, k);
            
            largestSum= max(largestSum, a);
        }
        return largestSum;
    }
    
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        return helper(arr, 0, k);
    }
  
//--------------------------------------------------------------------------------------------------------  
    // Tabulation
    
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n=arr.size();
        vector<int> dp(n+1);
        
        dp[n]=0;
        
        for(int i=n-1; i>=0; i--){
            int largestSum=INT_MIN;
            int len=0; int mx=INT_MIN;

            for(int div=i; div< min(arr.size(), i+k); div++){
                len++; mx= max(mx, arr[div]);
                int a= (len*mx) + dp[div+1];

                largestSum= max(largestSum, a);
            }
            dp[i]=largestSum;
        }
        
        return dp[0];
    }

//-----------------------------------------------------------------------------------------------------------------------------------------

VERDICT:

a. Identification is everything. In this pattern there will always be concern about partiotion (or when diffrenet partition point gives different answers and you have to find the maximum OR the minimum result)

b. In partion DP, after partition:
    a. The 2 subproblems must be INDEPENDENT to each other & should be solved SEPARATELY. 
    b. First figure out wheather the sub-problem are dependend on each other or not. 
    c. If dependend, then figure out what could be done to make them independend.
👉 Like in problem 1, we sort the cut index to make sub-problem independent & solved them separately (ofc using recursion)
👉 Like in problem 2, we though in reverse order i.e last step to first step and make sub-problem independent
👉 In problem 3, sub-problem was already independent (but there the catch is: You need to think about both T and F, and apply PnC for every operand)

// Problem 1,2 3 are very tough. There is no point of figuring out the solution without knowing about the problem.

c. Problem 4, 5 was preety straigh forward. Just partiotion at every POSSIBLE index & pass rest to recursion. Calculate the max/min from every possible partion & return that as answer. There sub-problems were independent to each other



