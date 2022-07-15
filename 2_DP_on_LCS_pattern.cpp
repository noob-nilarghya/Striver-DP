// Basic Recursion
int helper(string& s1, string& s2, int m, int n){
    if(m<0 || n<0){ return 0; }

    if(s1[m]==s2[n]){
        return 1+helper(s1, s2, m-1, n-1);
    }
    // else
    int op1= helper(s1, s2, m-1, n);
    int op2=helper(s1, s2, m, n-1);
    return max(op1, op2);
}

int getLengthOfLCS(string & str1, string & str2) {
    int m=str1.size(); int n=str2.size();
    return helper(str1, str2, m-1, n-1);
}


// DP

/*   This base case: if(m<0 || n<0){ return 0; } is impossible to replicate in tabulation. So we will shift the index, where dp[i][j] represent LCS for string (s1 from [0, i-1], s2 from [0, j-1])  */


int getLengthOfLCS(string & s1, string & s2) {
    int m=s1.size(); int n=s2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1));

    for(int i=0; i<=m; i++){ // if j==0 OR n<0 --> return 0
        dp[i][0]=0;
    }
    for(int j=0; j<=n; j++){ // if i==0 OR m<9 --> return 0
        dp[0][j]=0;
    }
    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            if(s1[i-1]==s2[j-1]){ // ideally it should be (s1[i]==s2[i]), but as we have shifted index
                dp[i][j]=1+dp[i-1][j-1];
            }
            else{
                int op1=dp[i-1][j]; int op2=dp[i][j-1];
                dp[i][j]=max(op1, op2);
            }
        }
    }
    return dp[m][n];
}

//-----------------------------------------------------------------------------------------------------

VRIATIONS :

1. Print the LCS :
    we will proceeds through reverse enginnering on DP array. while filling DP table, if char matched, we take value from ⇖. If not matched, we take max from [🠔,🠕]. We will just proceed in reverse way.

        int i=m; int j=n; string ans="";
        while(i!=0 && j!=0){
            if(s[i-1]==t[j-1]){
                ans.push_back(s[i-1]);
                i--; j--; // move diagonally up ⇖
            }
            else{
                if(dp[i][j]==dp[i-1][j]){
                    i--; // move up 🠕
                }
                else if(dp[i][j]==dp[i][j-1]){
                    j--; // move left 🠔
                }
            }
        }
        reverse(ans.begin(), ans.end());
        cout<<ans<<endl;

2. Longest Common Substring : 
    Here unlike LCS, if uumatched character found, we should stop the counting & reset it to 0 ( we cannot carry forward our counting as this is not sub-seq). If matching char found (say at i,j), we check what is the LC substring at (i-1, j-1). We can either start counting from 1 (dp[i][j]=1) if dp[i-1][j-1]=0, OR, we can carry forward our counting dp[i][j]=dp[i-1][j-1]+1;

        if(s1[i-1]==s2[j-1]){
            dp[i][j]=dp[i-1][j-1]+1;
            maxi=max(maxi, dp[i][j]);
        }
        else{
            dp[i][j]=0;
        }
    Answer (Longest common Substring) is the max value in whole 2D DP array (i.e maxi);
    FOLLOW UP: We can print longest common Substring too !

3. Minimum insertions to make a string palindrome :
    Reverse the original string & find LCS(orgStr, revStr).

4. Minimum Number of Deletions and Insertions to make 2 string equal :
    int LCS= lcs(s1, s2);       // LCS is that common part of string which need not to be altered
    int a=s1.size()-LCS; int b=s2.size()-LCS;       return a+b;

5. Shortest Common Supersequence [IMP] :
    Perform the tabulation to find LCS (s1, s2), & fill the 2D DP array. 
    Find the actual LCS string with the help of filled DP array.
    Find the actual result (Shortest Common Supersequence) with the help of S1, S2, and LCS string.
    https://leetcode.com/problems/shortest-common-supersequence/discuss/2247105/CPP-oror-Break-into-3-sub-problem-and-solve-oror-Variation-of-LCS

6. Distinct Subsequences of 's' which equals 't'
    Count Ways so, [ take+notTake concept ]

        int helper(string& s, string& t, int m, int n){
            if(n<0){ // if t is exhausted, that means we found one sub-seq of s that equals t
                return 1;
            }
            if(m<0 && n>=0){ // if s is exhausted, but t is not. So there is no way we can make a sub-seq of s ehich equals t
                return 0;
            }
            
            int take=0;
            if(s[m]==t[n]){ // character matched
                take= helper(s, t, m-1, n-1);
            }
            int notTake= helper(s, t, m-1, n);
            return (take+notTake);
        }
    Note: In case of overflow (even with ll), used 'double', and while returning answer, typecast it into int
    https://leetcode.com/problems/distinct-subsequences/submissions/

7. Edit Distance :
    If char is matched, well & good, shrink both strings. But if not matched, we have 3 possibility (NOTE: char are S1[m], and S2[n]):
    a.delete char s1[m] from s1        b.replace char s1[m] with char s2[n]       c.insert char s2[n] at the end of s1

        int helper(string& s1, string& s2, int m, int n){
            if(m<0){
                // s1 exhausted, now to make s1 into s2. Isertion into S1 --> (remaining len of s2) number of times
                return n+1; // +1 as 'n' is index of 0 based indexing
            }
            if(n<0){
                // s2 exhausted, now to make s1 into s2. Deletion from S1 --> (remaining len of s1) number of times
                return m+1; // +1 as 'm' is index of 0 based indexing
            }
            
            if(s1[m]==s2[n]){ // char matched
                return helper(s1, s2, m-1, n-1);
            }
            int a= helper(s1, s2, m-1, n); // delete char s1[m] from s1. So [m --> m-1]
            int b= helper(s1, s2, m-1, n-1); // replace char s1[m] with char s2[n]. Now s1[m] and s2[n] matched, so [m --> m-1], [n--> n-1]
            int c= helper(s1, s2, m, n-1); // insert char s2[n] at the end of s1. Now last char of both string matched. So [n --> n-1]
            
            return min(a, min(b, c))+1; // as one operation (either insert, del, replace) will be counted
        }

8. Wildcard Matching [IMP]: 
    Question will be simple if S2 only has '?', but here S2 also have '*', which matches with any consecutive sequence of characters (including the empty sequence).So, we dont know with how many consecutive sequence * will match with, So, we call recursion to match * with every possible consecutive sequence of s1 of len 0,1,2,3 so on.. 
    So, here whenever we has (s1[m]!=s2[n] && s2[n]=='*'), make multiple recursive call like:
       a. f(m, n-1)   [* matches with empty sequence of s1]
       b. f(m-1, n-1) [* matches with length 1 consecutive sequence of s1]
       c. f(m-2, n-1) [* matches with length 2 consecutive empty sequence of s1], and so on until s1 ends [ f(-1, n-1) ]
    If any of the call return true, we also return true
    f('abcdef', 'abc*') --> we have (s1[m]!=s2[n] && s2[n]=='*'), so we call for f('abcdef', 'abc'), f('abcde', 'abc'),
    f('abcd', 'abc'), f('abc', 'abc'), ... ('','abc'). And we know among these call f('abc','abc') will return true, & we return True

        bool helper(string& s1, string& s2, int m, int n){
            if(m<0 && n<0){ // both has exhausted
                return true;
            }
            if(m>=0 && n<0){ // S2 exhausted , but not S1
                return false;
            }
            if(m<0 && n>=0){ // S1 has exhausted, but not S2 --> remaining all char of S2 have to be *
                while(n>=0){
                    if(s2[n]!='*'){  return false;  }
                    n--;
                }
                return true;
            }
            
            if(s1[m]==s2[n] || s2[n]=='?'){  // match
                return helper(s1, s2, m-1, n-1);
            }
            if(s1[m]!=s2[n] && s2[n]!='*'){ return false; } // Unmatched & also s2[n]!='*', so there is no way out. Return F
            
            // S1[m] != S2[n] && S2[n]=='*'
            int idx=m+1; // as we can take no char from S1[m] for corresponding * in S2[n]
            while(idx>=0){
                bool a= helper(s1, s2, idx-1, n-1);  // multiple recursive call until s1 ends [ f(-1, n-1) ]
                if(a==true){ return true; }
                idx--;
            }
            
            return false;
        }



VERDICT:
// Recursion starts with [lastIdx --> firstIdx] (i at m-1, j at n-1)
    a. In general string maching method is used.
    b. Think of base case at the end (after writting recurrance)
       
// Base Cases are similar
    Think of cases when (i < 0) [s1 moves out of size] + (j < 0) [s2 moves out of size] + their PnC (at max 3 possibility)
        if(i<0 && j<0){  /* Code */  }    // If required
        if(i<0 && j>=0){  /* Code */  }   // If required
        if(i>=0 && j<0){  /* Code */  }   // If required

// match OR notMatched in maximum cases:
    a. Think and analyse of if s1[i] matched with s2[j]. If match what will you do.
    b. IF not match what will you do
    c. In case of maximum or minimum length is asked: --> max/min of (cases when not matched)
    d. In case of count ways [pt 6], (take [match condition generally] + notTake [unMatched- condition generally])

// Tabulation [index shifting is always occured as i<0 OR j<0 can't be valid index, so we treat this as row=0 OR col=0 in DP arry]
    a. Allocate dp[m+1][n+1] (1 size extra as we are shifting index)
    b. DP[i][j] denotes ( s1[0, i-1], s2[0, j-1] ) [due to index shifting]
    c. Write Base Case from recursion (thinking of all the possible way in which might we hit base case (in recursion), & fill these cells)
    d. fill rest of the grid (in opposite fashion to that of recursion), using recurrance relation [copy-paste] from Recursion.

// ZHK: In case of overflow (even with ll), used 'double', and while returning answer, typecast it into int

          