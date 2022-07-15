// Here We will discuss all possible variations of Buy and Sell Stocks Problem

--------------------------------  Problem 1: Buy and Sell Stock 1: We can have 1 tarnsaction  ---------------------------------------

int maxProfit(vector<int>& price) {
    int maxi= INT_MIN; // keep a track of maximum value 
    int profit=0; // initially profit is 0
    
    for(int i=price.size()-1; i>=0; i--){
        
        maxi=max(maxi, price[i]);
        profit= max(profit, maxi-price[i]);
    }
    
    return profit;
}
//-----------------------------------------------------------------------------------------------------------------------------------------



------------------------------  Problem 2:  Buy and Sell Stock 2: We can have INFINITE tarnsaction  -----------------------------------
--------APPROACH 1--------:

// I have my state transition diagram as [bsbsbs...]
//   So, if I am at 'b', I have 2 option i) Remain at bought state 'b' (dont sell the stock) OR ii) Sell stock & come to sold state 's'.
//   Similarly, I have 2 option if I am at 's' i) Remain at sold state 's' (dont buy the stock) OR ii) Buy stock & come to bought state 'b'.

a. ------ Using DP/Recursion ------

int helper(vector<int>& price, int idx, int bs){ // return profit
    //3rd parameter denotes bought state (=1 we bought a stock which hasnot sold yet, =0 means we can buy new stock). [Initially 0]
    if(idx==price.size()){
        return 0; // we cannot make any more profit
    }
    
    if(bs==0){
        int op1= helper(price, idx+1, 0); // we have not bough new stocks, so we remain at bs=0
        int op2= -price[idx] + helper(price, idx+1, 1); // we bought a stock today so, my bs become 1
        return max(op1, op2);
    }
    else if(bs==1){
        int op1= helper(price, idx+1, 1); // we didnot sold stock so, we remain at bs=1
        int op2= price[idx]+helper(price, idx+1, 0); // we sold stock, so my bs become 0
        return max(op1, op2);
    }
    return 0; // just for nothing
}

b. --- Using State Transition diagram ----

int maxProfit(vector<int>& price) {
    //sequence is [bs bs bs ...]
        
    int n=price.size();
    vector<int> bsp(n); // brought state profit 
    vector<int> ssp(n); // sold state profit
    
    bsp[0]=-price[0]; // Initially my profit was 0 RS. Ans I have to bought the stock, & profit -ve me chala gya
    ssp[0]=0;
    
    for(int i=1; i<price.size(); i++){
        bsp[i] =max( bsp[i-1], ssp[i-1]+(-price[i]) );
        ssp[i]= max( ssp[i-1], bsp[i-1]+price[i] );
    }
    
    return ssp[n-1];
}


--------APPROACH 2--------:

//In part 1 we are required to make a single transaction & maximise the profit, but here we can do INFINITE transanctions. So, we can do this in greedy way: 
//    1) Buy stocks at local minima & sell it in next local maxima
//    2) We buy stocks on i-1 & sell it on next day if(price[i-1]<price[i])
//  Think why 1) and 2) are appearantly same.....

int maxProfit(vector<int>& price) {
        
    int profit=0;
    for(int i=1; i<prices.size(); i++){
        if(prices[i-1] < prices[i]){
            profit+=(prices[i]-prices[i-1]);
        }
    }
    return profit;
}
//-----------------------------------------------------------------------------------------------------------------------------------------



---------------------------  PROBLEM 3: Buy and Sell Stock 3: We can have atmost 2 tarnsaction  -----------------------------------
// We can replicate the ideology of [ problem2-approach1-using recursion ] here also. We just need to add a 4th parameter 'cnt' which keep count of how many transaction has been performed so far

int helper(vector<int>& price, int idx, int bs, int cnt){ // return profit
    //3rd parameter denotes bought state (=1 we bought a stock which hasnot sold yet, =0 means we can buy new stock). [Initially 0]
    // We also keep a counter which is initially 2
    
    if(cnt==0){ // maximum limit of transaction has exceeds
        return 0; // we cannot make any more profit
    }
    if(idx==price.size()){
        return 0; // we cannot make any more profit
    }
    
    if(bs==0){
        int op1= helper(price, idx+1, 0, cnt); // we have not bough new stocks, so we remain at bs=0
        int op2= -price[idx] + helper(price, idx+1, 1, cnt); // we bought a stock today so, my bs become 1
        return max(op1, op2);
    }
    else if(bs==1){
        int op1= helper(price, idx+1, 1, cnt); // we didnot sold stock so, we remain at bs=1
        int op2= price[idx]+helper(price, idx+1, 0, cnt-1); // we sold stock,so my bs become 0. As 1 transaction completed,so cnt-1
        return max(op1, op2);
    }
    return 0; // just for nothing
}
//-----------------------------------------------------------------------------------------------------------------------------------------



------------------------------  PROBLEM 4: Buy and Sell Stock 4: We can have atmost K tarnsaction  -----------------------------------
// Here instead of 2, now we have to do atmost K transaction. Just replace 'cnt' of above function as K. Ans rest of the code as it is.

int maxProfit(int transac, vector<int>& price) {
    int n=price.size();
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(transac+1))); //[idx, bs, cnt]
    
    for(int i=0; i<=n; i++){
        for(int j=0; j<=1; j++){
            dp[i][j][0]=0;
        }
    }
    for(int j=0; j<=1; j++){
        for(int k=0; k<=transac; k++){
            dp[n][j][k]=0;
        }
    }
    
    for(int i=n-1; i>=0; i--){
        for(int j=0; j<=1; j++){
            for(int k=1; k<=transac; k++){
                if(j==0){
                    int op1= dp[i+1][0][k]; 
                    int op2= dp[i+1][1][k] + (-price[i]);
                    dp[i][j][k]= max(op1, op2);
                }
                else if(j==1){
                    int op1= dp[i+1][1][k];
                    int op2= dp[i+1][0][k-1] + price[i];
                    dp[i][j][k]= max(op1, op2);
                }
                
            }
        }
    }
    return dp[0][0][transac];
}
//-----------------------------------------------------------------------------------------------------------------------------------------



------------------------------  PROBLEM 5: Buy and Sell Stock 5: With cooldown of 1 day  -----------------------------------
// cooldown of one day is given
// so the sequence is [bsc bsc bsc ...]
//   1. So, if I am at 'b', I have 2 option i) Purana bought state ko continue kiya OR ii) purana cooldown state ka profit se aaj ka stock kharid liya
//   2. Similarly, I have 2 option if I am at 's' i) Purana wala sold state ko continue kiya OR ii) purana bought state ko aaj ke keemat me bech diya
//   3. Similarly, I have 2 option If I am at 'c  i) Purana Cooldown state ko continue kiya OR ii) Purana sold state se cooldown pe aya

int maxProfit(vector<int>& price) {
    int n=price.size();
    vector<int> bsp(n); // brought state profit 
    vector<int> ssp(n); // sold state profit
    vector<int> csp(n); // cooldown state profit
    
    bsp[0]=-price[0]; // Initially my profit was 0 RS. Ans I have to bought the stock, & profit -ve me chala gya
    ssp[0]=0;
    csp[0]=0;
    
    for(int i=1; i<price.size(); i++){
        bsp[i] =max( bsp[i-1], csp[i-1]+(-price[i]) );
        ssp[i]= max( ssp[i-1], bsp[i-1]+price[i] );
        csp[i]= max( csp[i-1], ssp[i-1] );
    }
    
    // maxprofit would be either in ssp[n-1] OR in csp[n-1]
    return max(ssp[n-1], csp[n-1]);
}
//-----------------------------------------------------------------------------------------------------------------------------------------



---------------------------  PROBLEM 6: Buy and Sell Stock 6: INFINITE trabsaction with transaction fee  --------------------------------
// We can replicate the ideology of [ problem2-approach1-using state transition diagram ] here also. Just we need to subtract transation fee from ssp[i] ( i.e after completion of a transaction )
int maxProfit(vector<int>& price, int fee) {
    //sequence is [bs bs bs ...]
    
    int n=price.size();
    vector<int> bsp(n); // brought state profit 
    vector<int> ssp(n); // sold state profit

    bsp[0]=-price[0]; // Initially my profit was 0 RS. Ans I have to bought the stock, & profit -ve me chala gya
    ssp[0]=0;

    for(int i=1; i<price.size(); i++){
        bsp[i] =max( bsp[i-1], ssp[i-1]+(-price[i]) );
        ssp[i]= max( ssp[i-1], bsp[i-1]+price[i]-fee );
    }

    return ssp[n-1];
}
//-----------------------------------------------------------------------------------------------------------------------------------------


---------------- NOTE: ----------------
//   1. All the recursion/DP approaches can be optimized to tabulation and can be best space optimized using space optimization technique.
//   2. All state transition diagram code can be done using just variable (and not array) [as we just need the previous profit only] (inspired from space optimization technique of tabulation)



