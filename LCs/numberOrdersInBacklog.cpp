//https://leetcode.com/problems/number-of-orders-in-the-backlog/submissions/1876660933/
class Solution {
public:
    const int mod = 1e9 + 7;
    /*
    1 map for the buy orders in the current backlog (large -> small)
    1 map for the sell orders in the backlog (small -> large)

    get buy order in, price p, quant q
    -> repetitively compare the price of buy order with the price of the cheapest sell order
    not match -> break
    matches -> 
    sell order has price p1, quant q1 (p1 <= p)
    -> trade min(q, q1) stocks 
    -> either we don't have buy orders anymore (q < q1), or the sell offer doesn't exist anymore (q > q1), or both
    -> O(n * log2(n)), n = number of orders
    */
    map<int, long long, greater<int>> buyOffers;// greater<int> -> sort the buy offers from large to small
    map<int, long long> sellOffers;// sort from small to large
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        for(auto order : orders){
            int price = order[0], amount = order[1], type = order[2];
            // buy order
            if(type == 0){
                // still have something to trade, and there are stocks in the sell backlog
                while(amount > 0 && !sellOffers.empty()){
                    int curPrice = (*sellOffers.begin()).first, curAmount = (*sellOffers.begin()).second;
                    if(curPrice > price) break;
                    if(curAmount > amount){
                        curAmount -= amount;
                        sellOffers[curPrice] = curAmount;
                        amount = 0;
                    }
                    else{
                        amount -= curAmount;
                        sellOffers.erase(curPrice);
                    }
                }
                if(amount > 0){
                    buyOffers[price] += amount;
                }
            }
            else{// sell order
                int price = order[0], amount = order[1], type = order[2];
                // buy order
                while(amount > 0 && !buyOffers.empty()){
                    int curPrice = (*buyOffers.begin()).first, curAmount = (*buyOffers.begin()).second;
                    if(curPrice < price) break;
                    if(curAmount > amount){
                        curAmount -= amount;
                        buyOffers[curPrice] = curAmount;
                        amount = 0;
                    }
                    else{
                        amount -= curAmount;
                        buyOffers.erase(curPrice);
                    }
                }
                if(amount > 0){
                    sellOffers[price] += amount;
                }
            }
        }        
        int answer = 0;
        for(auto order : buyOffers) answer = (answer + order.second) % mod;
        for(auto order : sellOffers) answer = (answer + order.second) % mod;
        return answer;
    }
};