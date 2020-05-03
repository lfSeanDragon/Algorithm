#include<iostream>
#include<cmath>  
#include<vector>
#include<cmath>
using namespace std;
/*
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。
注意你不能在买入股票前卖出股票。

示例 1:
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
*/
int maxProfit(vector<int>& prices) {
    if(prices.size() <= 1) {
        return 0;
    }
    int min = prices[0],max = 0;
    for(int i = 1; i < prices.size(); ++i) {
        max = fmax(max,prices[i] - min);
        min = fmin(min,prices[i]);
    } 
    return max;
}

int main(){
    
    int arr[6] = { 7,1,5,3,6,4 };
    vector<int> prices;    
    for (int i = 0; i < 7; i++){
        prices.push_back(arr[i]);    
    }
    cout<< "max value: "<< maxProfit(prices)<< endl;
    return 0;
}