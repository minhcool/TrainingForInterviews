#include<iostream>
#include<set>
#include<vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

class Node{
    int nodeId;
    int subtreeSize;
    set<int> remainingChildren;
    vector<int> allChildren;
    int parentNodeId;
    Node(int nodeId, int parentNodeId, const vector<int> &children_ids){
        this->nodeId = nodeId;
        this->parentNodeId = parentNodeId;
        allChildren = children_ids;
        for(auto child_id : children_ids) remainingChildren.insert(child_id);
        subtreeSize = 1;
    }
    int stringToInt(string s){
        int ans = 0;
        for(auto digit : s){
            int value = (digit - '0');
            ans = (ans * 10 + value);
        }
        return ans;
    }
    std::string intToString(int x){
        std::string ans;
        while(x){
            int unitDigit = x % 10;
            ans += char('0' + unitDigit);
            x /= 10;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
    void sendWithRetry(int nodeId, const std::string &message, int startDelay = 10, int retry = 3, int multiplyDelay = 2){
        int curDelay = startDelay;
        for(int i = 0; i < retry; i++){
            try{
                sendMessage(nodeId, message);
            }
            catch(const exception& ex){
                cout << "ERROR: " << ex.what() << endl;
                sleep(curDelay);
                curDelay *= multiplyDelay;
                continue;
            }
        }
    }
    void receiveMessage(int fromNodeId, const std::string& message){
        if(fromNodeId == parentNodeId){
            for(auto child_ids : allChildren){
                sendWithRetry(child_ids, message);
            }
        }
        else{
            if(remainingChildren.find(fromNodeId) == remainingChildren.end()) return;
            remainingChildren.erase(fromNodeId);
            subtreeSize += stringToInt(message);
            if(remainingChildren.empty()){
                sendWithRetry(parentNodeId, intToString(subtreeSize));
            }
        }
    }
    void sendMessage(int nodeId, const std::string& message){
        // IMPLEMENTED
    }
};