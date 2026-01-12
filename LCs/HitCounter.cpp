class HitCounter {
public:
    queue<int> pq ;
    HitCounter() {
        
    }
    
    void hit(int timestamp) {
        pq.push(timestamp);
    }
    
    int getHits(int timestamp) {
        while(!pq.empty() && pq.front() <= timestamp-300 ){
             pq.pop();
        }
        return pq.size();
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */