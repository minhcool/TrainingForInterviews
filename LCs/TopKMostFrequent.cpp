class Solution {
public:
    /*
    unordered_map<int, int> frequency
    vector<int> numbersSameFreq(nums.size() + 1), 
    numbersSameFreq[i] -> all the numbers that occurs i times
    iterate from n -> 1, for each i we take all elements inside numbersSameFreq[i]
    if found k numbers -> break
    */
    unordered_map<int, int> frequency;
    vector<vector<int>> numberSameFreq;
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        numberSameFreq.resize(n + 1);
        for(auto it : nums) frequency[it]++;
        for(auto it : frequency) numberSameFreq[it.second].push_back(it.first);
        vector<int> answer;
        for(int i = n; i >= 1; i--){
            for(auto it : numberSameFreq[i]) answer.push_back(it);
            if(answer.size() == k) break;
        }
        return answer;
    }
};