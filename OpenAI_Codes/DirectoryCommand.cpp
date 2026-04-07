#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<string>
#include<iostream>
using namespace std;

class DirectoryCommand{
public:
    vector<string> split(string path) {
        vector<string> parts;
        string cur = "";
        for (char c : path) {
            if(c == '/'){
                if(!cur.empty()){
                    parts.push_back(cur);
                    cur.clear();
                }
            } 
            else cur += c;
        }
        if (!cur.empty()) parts.push_back(cur);
        return parts;
    }

    string buildPath(vector<string> &stk) {
        if (stk.empty()) return "/";
        string ans = "";
        for (auto &s : stk) ans += "/" + s;
        return ans;
    }

    string resolve(string path, const unordered_map<string,string> &mp) {
        unordered_set<string> seen;
        while (mp.count(path)) {
            if (seen.count(path)) break;
            seen.insert(path);
            path = mp.at(path);
        }
        return path;
    }

    string cd(string pwd, string input, const unordered_map<string,string> &mp) {
        vector<string> stk;
        if (input[0] != '/') {
            vector<string> base = split(pwd);
            for (auto &s : base) stk.push_back(s);
        }
        vector<string> parts = split(input);
        for (auto &p : parts) {
            if (p == ".") continue;
            else if(p == ".."){
                if (!stk.empty()) stk.pop_back();
            } 
            else{
                stk.push_back(p);
            }
            string curPath = buildPath(stk);
            string resolved = resolve(curPath, mp);

            if (resolved != curPath) {
                stk = split(resolved);
            }
        }

        return buildPath(stk);
    }
};

int main() {
    DirectoryCommand dc;

    unordered_map<string,string> mp;
    mp["/home/bugs/lola"] = "/home/lola";
    mp["/a"] = "/b";
    mp["/b"] = "/c";
    mp["/c"] = "/a";
    mp["/x/y"] = "/z";

    cout << dc.cd("/home/bugs", ".", mp) << endl; 
    cout << dc.cd("/home/bugs", "bunny", mp) << endl; 
    cout << dc.cd("/home/bugs", "../daffy", mp) << endl;


    cout << dc.cd("/a/b/c", "././d", mp) << endl;
    cout << dc.cd("/a/b/c", "../../x", mp) << endl; 
    cout << dc.cd("/", "../../x", mp) << endl; 

    cout << dc.cd("/home/bugs", "lola/../basketball", mp) << endl;

    cout << dc.cd("/x", "y/file", mp) << endl;  

    cout << dc.cd("/", ".", mp) << endl;  
    cout << dc.cd("/", "..", mp) << endl;
    cout << dc.cd("/a", "", mp) << endl; 

    return 0;
}