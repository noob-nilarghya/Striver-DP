// Recursion : As it is a question related to sub-sequence, we always know, we will either gonna [take || notTake]

int helper(vector<int>& nums, int currIdx, int prevIdx){ // return length [ signifies length of LIS sarting at currIdx with prevIdx as -1]
    if(currIdx==nums.size()){
        return 0; // length 0 of LIS is possible
    }
    
    int notTake= helper(nums, currIdx+1, prevIdx);
    int take=-1e9;
    if(prevIdx==-1 || nums[prevIdx]<nums[currIdx]){
        take= helper(nums, currIdx+1, currIdx) + 1;
    }

    return max(take, notTake);
}


// DP
int lengthOfLIS(vector<int>& nums) {
    // return helper(nums, 0, -1);

    // As in recursion, we having base case for (currIdx==nums.size()), so we need row of n+1 size. Also as prevIdx, we can hae value as -1, so due to index shifting we also need col of size n+1

    int n=nums.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1));
    
    for(int j=0; j<=n; j++){
        dp[n][j]=0;
    }
    
    // Go in reverse order from recursion
    for(int i=n-1; i>=0; i--){
        for(int j=i-1; j>=-1; j--){ // prevIdx could be at max i-1 till -1
            int notTake= dp[i+1][j+1]; // every [j] in DP should be [j+1]
            int take=-1e9;
            if(j==-1 || nums[j]<nums[i]){
                take= dp[i+1][i+1] +1;
            }
            dp[i][j+1]=max(take, notTake);
        }
    }
    return dp[0][-1+1]; // actually we want dp[0][-1] (the parameter with which we had started recursion)
}


// OPtimized Tabulation
int lengthOfLIS(vector<int>& nums) {
    vector<int> temp(nums.size()); // temp[i] stores maximum len of LIS ended at nums[i]
    
    temp[0]=1;
    for(int i=1; i<nums.size(); i++){
        int mx=INT_MIN;
        for(int j=i-1; j>=0; j--){
            if(nums[j]< nums[i]){
                mx=max(mx,temp[j]);
            }
        }
        if(mx==INT_MIN){ // no ele smaller than nums[i] found from [0, i-1]
            temp[i]=1;
        }
        else { temp[i]= mx+1; }
    }
    return *max_element(temp.begin(), temp.end());
}


// Print LIS (Basically doing OPtimized Tabulation with some mod)
int lengthOfLIS(vector<int>& nums) {
    
    vector<int> temp(nums.size()); // temp[i] stores maximum len of LIS ended at nums[i]
    vector<int> hash(nums.size()); // used to print acttual LIS. hash[i] stores index of ele that ocuur prior to nums[i] in actual LIS
    for(int i=0; i<nums.size(); i++){ hash[i]=i; } // initial status of hash
    
    temp[0]=1;
    for(int i=1; i<nums.size(); i++){
        int mx=INT_MIN;
        for(int j=i-1; j>=0; j--){
            if(nums[j]< nums[i]){
                if(mx<temp[j]){ // new val to update
                    hash[i]=j; mx=temp[j]; // basically here hash[i] is storing index of prev ele where max LIS len found
                }
            }
        }
        if(mx==INT_MIN){ // no ele smaller than nums[i] found from [0, i-1]
            temp[i]=1;
        }
        else { temp[i]= mx+1; }
    }
    // hash array is ready, if hash[idx]!=idx, then it means { nums[hash[idx]] is the prev ele of nums[idx] in actual LIS }
    
    int mx=temp[0]; int idx=0;
    for(int i=1; i<nums.size(); i++){
        if(temp[i]>mx){
            mx=temp[i]; idx=i;
        }
    }
    // temp[idx] has the maximum value (i.e len of LIS) which also ended at nums[idx]

    vector<int> printLIS;
    while(hash[idx]!=idx){
        printLIS.push_back(nums[idx]); // storing element of actual LIS in reverse order
        idx=hash[idx];
    }
    printLIS.push_back(nums[idx]);

    reverse(printLIS.begin(), printLIS.end()); // reverse vector to get actual LIS
    return printLIS;
}


// Find Length of LIS using Binary Search
int longestIncreasingSubsequence(int arr[], int n){
    vector<int> temp;
    temp.push_back(arr[0]);
    for(int i=1; i<n; i++){
        if(temp[temp.size()-1]<arr[i]){
            temp.push_back(arr[i]);
        }
        else if(temp[temp.size()-1] >= arr[i]){
            int pos= lower_bound(temp.begin(), temp.end(), arr[i])-temp.begin(); // just find [ ele >=arr[i] ], & overwrite
            temp[pos]=arr[i];
        }
    }
    // NOTE: temp is not LIS (even temp might not be a sub-sequence also). 
    // We re just concerned about length of LIS (which is temp.size)
    return temp.size();
}

//----------------------------------------------------------------------------------------------------------------------------


VRIATIONS :

1. Divisible Set : 

As longest subset can be returned in any order. We can sort the array & frame this question in LIS print pattern. In LIS(OPtimized Tabulation), we find if(nums[j]< nums[i]), & update temp[i] accordingly. Here we will check for if(arr[i]%arr[j]==0). We need to check divisibility with all pairs, but here we are checking with just prev ele? This will still works becuase, [say in actual LIS,             (0th ele)> (1st ele)> (2nd ele) and (1th ele)%(0st ele) ==0 and (2nd ele)%(1st ele) ==0, then autometically (0th ele)%(2st ele) ==0].


2. Longest String Chain :

Pattern can be observed from question name itself. Instead of temp array to keep record of len, here we use 
[ map<string, int> ]   {maximum len of LIS starts with string, maxLen}


3. Longest Bitonic Sequence :
First increasing & then decreasing. So we make two vector temp1 (where temp1[i] stores maximum len of LINCREASING S ended at nums[i] from [0,i]), temp2 (where temp2[i] stores maximum len of L DECREASING S started at nums[i] from [i,n-1]). Finally we get longest len of botonic sequence AS mx= max( mx, temp1[i]+temp2[i]-1 ); [-1 because, 'nums[i]' repeats twice]

        int longestBitonicSequence(vector<int>& arr, int n) {
            vector<int> temp1(n); temp1[0]=1;   vector<int> temp2(n); temp2[n-1]=1;
            
            for(int i=1; i<n; i++){
                int mx=INT_MIN;
                for(int j=i-1; j>=0; j--){
                    if(arr[i]> arr[j]){
                        mx=max(mx, temp1[j]);
                    }
                }
                if(mx==INT_MIN){ temp1[i]=1; }
                else{ temp1[i]= mx+1; }
            }
            
            for(int i=n-2; i>=0; i--){
                int mx=INT_MIN;
                for(int j=i+1; j<n; j++){
                    if(arr[i]>arr[j]){
                        mx=max(mx, temp2[j]);
                    }
                }
                if(mx==INT_MIN){ temp2[i]=1; }
                else{ temp2[i]= mx+1; }
            }

            int mx=INT_MIN;
            for(int i=0; i<n; i++){
                mx=max(mx, temp1[i]+temp2[i]-1);
            }
            return mx;
        } 



4. Number of Longest Increasing Subsequence [IMP] :
Cant be explained. See video: https://www.youtube.com/watch?v=cKVl1TFdNXg&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=48

        int findNumberOfLIS(vector<int> &arr){
            int n=arr.size();
            vector<int> temp(n);  vector<int> cnt(n);
            temp[0]=1; cnt[0]=1;
            
            for(int i=1; i<n; i++){
                int mx=INT_MIN; int count=0;
                for(int j=i-1; j>=0; j--){
                    
                    if(arr[i]> arr[j]){
                        if(mx<temp[j]){ // new mx found, update count, update mx
                            count=cnt[j]; mx=temp[j];
                        }
                        else if(mx==temp[j]){ // multiple sub-seq with maxLen found, add up their count
                            count+=cnt[j];
                        }
                    }
                }
                if(mx==INT_MIN){ 
                    temp[i]=1; cnt[i]=1;
                }
                else{ 
                    temp[i]= mx+1; cnt[i]=count;
                }
            }
            
            int mx=*max_element(temp.begin(), temp.end()); // maxLen
            
            int count=0;
            for(int i=0; i<n; i++){
                if(temp[i]==mx){ // add up all cnt of maxLen sub-seq
                    count+=cnt[i];
                }
            }
            return count;
        }



VERDICT:

// Identification is everything. Whenever question involves 'LONGEST' and 'SEQUENCE'. Atleast once think of LIS pattern
// Nearly all of the problem based on LIS can be solved intuitively using 'OPtimized Tabulation' method
// Whenever we are required to print actual sequence, 'hash' method need to be followed
// Number of Longest Increasing Subsequence [IMP] is hard to think with no clue, so keep in touch with this qn