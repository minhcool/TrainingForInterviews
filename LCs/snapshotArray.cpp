class SnapshotArray {
public:
/*
vector<pair<int, int> allHistoryValues(length);
- for number x, save all of its historical value <time, value> 
*/
    int totalSnaps;
    vector<vector<pair<int, int>>> allHistoryValues;
    SnapshotArray(int length) {
        allHistoryValues.resize(length);
        // at time 0, value of all positions are 0
        for(int i = 0; i < length; i++) allHistoryValues[i].push_back(make_pair(0, 0));
        totalSnaps = 0;
    }
    
    void set(int index, int val) {
        allHistoryValues[index].push_back({totalSnaps, val});
    }
    
    int snap() {
        totalSnaps++;
        return totalSnaps - 1;
    }
    
    int get(int index, int snap_id) {
        // get the latest timestamp possible which time is not larger then snap_id
        // as the timestamps are increasing in time, we can binary search to search for the timestamp
        vector<pair<int, int>>::iterator it = lower_bound(allHistoryValues[index].begin(), allHistoryValues[index].end(), make_pair(snap_id + 1, -1));
        it--;
        return (*it).second;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */