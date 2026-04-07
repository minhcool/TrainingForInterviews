#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;



const long long ADDRESS_LIMIT = 256;

class IP4Iterator{
private:
    long long startIp, endIp, currentIp;
    bool increasing;
public:
    long long getDigit(char c){
        if(c >= '0' && c <= '9') return c - '0';
        return -1;
    }
    long long getIntAddress(const string &ip){
        long long curNum = 0, ans = 0;
        for(auto c : ip){
            long long num = getDigit(c);
            if(num < 0){
                ans = (ans << 8) | curNum;
                curNum = 0;
            }
            else{
                curNum = (curNum * 10 + num);
            }
        }
        ans = (ans << 8) | curNum;
        return ans;
    }
    long long toInt(string num){
        long long ans = 0;
        for(auto c : num){
            ans = (ans * 10 + getDigit(c));
        }
        return ans;
    }
    string toString(long long num){
        string ans = "";
        while(num){
            long long unit = num % 10;
            ans += char('0' + unit);
            num /= 10;
        }
        if(!ans.length()) ans = "0";
        reverse(ans.begin(), ans.end());
        return ans;
    }
    string getStringAddress(long long ip){
        string ans;
        ans += toString(ip >> 24);
        ans += '.';
        ans += toString((ip >> 16) & 255);
        ans += '.';
        ans += toString((ip >> 8) & 255);
        ans += '.';
        ans += toString(ip & 255);
        return ans;
    }
    void check(const string &startIp, const string &endIp, bool increasing){
        if(increasing){
            if(getIntAddress(startIp) > getIntAddress(endIp)){
                throw runtime_error("Iterator increasing, startIp must be <= endIp");
            }
        }
        else{
            if(getIntAddress(startIp) < getIntAddress(endIp)){
                throw runtime_error("Iterator decreasing, endIp must be <= startIp");
            }
        }
    }
    IP4Iterator(string startIp, string endIp, bool increasing){
        check(startIp, endIp, increasing);
        this->startIp = this->currentIp = getIntAddress(startIp);
        if(increasing) this->currentIp--;
        else this->currentIp++;
        this->endIp = getIntAddress(endIp);
        this->increasing = increasing;
    }
    pair<string, long long> getNumFixedBit(const string &ip){
        long long itr = ip.length() - 1;
        while(itr >= 0 && getDigit(ip[itr]) >= 0) itr--;
        itr++;
        return make_pair(ip.substr(0, itr - 1), toInt(ip.substr(itr)));
    }
    pair<long long, long long> getRange(const string &ip){
        pair<string, long long> getFixed = getNumFixedBit(ip);
        long long prefix = getFixed.second;
        long long getAddress = getIntAddress(getFixed.first);
        long long hostBits = 32 - prefix;
        long long rangeBits = (hostBits == 32 ? -1 : ((1 << hostBits) - 1));
        pair<long long, long long> range;
        range.first = (getAddress & ~(rangeBits));
        range.second = range.first + rangeBits;
        return range;
    }
    IP4Iterator(string ip, bool increasing){
        this->increasing = increasing;
        pair<long long, long long> range = getRange(ip);
        this->startIp = range.first;
        this->endIp = range.second;
        if(!increasing) swap(this->startIp, this->endIp);
        if(increasing) this->currentIp = this->startIp - 1;
        else this->currentIp = this->startIp + 1;
    }
    bool hasNext(){
        return (currentIp != endIp);   
    }
    string getNextIp(){
        if(!hasNext()){
            throw runtime_error("This is the endIp");
        }
        currentIp++;
        return getStringAddress(currentIp);
    }   
    string getLastIp(){
        if(!hasNext()){
            throw runtime_error("This is the endIp");
        }
        currentIp--;
        return getStringAddress(currentIp);
    } 
    string next(){
        if(increasing) return getNextIp();
        else return getLastIp();
    }
};

int main(){
    IP4Iterator it1("255.255.14.255", "255.255.15.2", true);
    while(it1.hasNext()){
        cout << it1.next() << "\n";
    }
    cout << "\n";

    IP4Iterator it2("255.255.15.2", "255.255.14.255", false);
    while(it2.hasNext()){
        cout << it2.next() << "\n";
    }
    cout << "\n";

    IP4Iterator it3("1.1.1.1", "1.1.1.1", true);
    while(it3.hasNext()){
        cout << it3.next() << "\n";
    }
    cout << "\n";

    IP4Iterator it4("0.0.0.254", "0.0.1.1", true);
    while(it4.hasNext()){
        cout << it4.next() << "\n";
    }
    cout << "\n";

    IP4Iterator it5("192.168.1.0/30", true);
    while(it5.hasNext()){
        cout << it5.next() << "\n";
    }
    cout << "\n";
}