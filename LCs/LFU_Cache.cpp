//https://leetcode.com/problems/lfu-cache/submissions/1876599426/
struct node{
    int key, value;
    node *next, *prev;
    node(int _key, int _value){
        key = _key;
        value = _value;
        next = prev = nullptr;
    }
    void eraseNode(){
        if(prev != nullptr) prev->next = next;
        if(next != nullptr) next->prev = prev;
    }
};

class LFUCache {
public:
    /*
    Maintain
    - For each frequency, a linked list that begins with the least favorite key
    -> Know first & last element
    - For each key, its frequency and current address 
    - CurrentMinimumFrequency -> minimum frequency of any element inside the cache
    - 
    */
    int maximumCapacity = 0;
    unordered_map<int, int> frequency;
    unordered_map<int, node*> address;
    unordered_map<int, node*> first, last;
    int minimumOccurence;
    LFUCache(int capacity) {
        maximumCapacity = capacity;
        minimumOccurence = 0;
    }
    int getSize(){
        return (frequency.size());
    }
    void deleteNode(int key){
        if(address.find(key) == address.end()) return;
        int keyFrequency = frequency[key];
        node* keyAddress = address[key];
        // phase 1: delete the key from every place (in case freq[key] > 0)
        if(keyFrequency > 0){
            if(first[keyFrequency] == keyAddress){
                first[keyFrequency] = keyAddress->next;
            }
            if(last[keyFrequency] == keyAddress){
                last[keyFrequency] = keyAddress->prev;
            }
            keyAddress->eraseNode();
        }
    }
    void evict(){
        node* toEvict = first[minimumOccurence];
        int evictKey = toEvict->key;
        //cout << evictKey << " " << minimumOccurence << "\n";
        deleteNode(evictKey);
        delete address[evictKey];
        address.erase(evictKey);
        frequency.erase(evictKey);
    }
    // add 1 to the counter of key
    void update(int key){
        //cout << key << "\n";
        if(address.find(key) == address.end()) return;
        bool newKey = (frequency[key] == 0);
        //cout << "NEWKEY\n";
        if(newKey == 1){
            if(getSize() > maximumCapacity) evict();
        }
        deleteNode(key);
        // phase 2: add the key back after increasing the frequency
        frequency[key]++;
        //cout << "FREQUENCY " << key << " " << frequency[key] << "\n";
        int keyFrequency = frequency[key];
        node* keyAddress = address[key];
        if(last[keyFrequency] != nullptr){
            last[keyFrequency]->next = keyAddress;
        }
        keyAddress->prev = last[keyFrequency];
        keyAddress->next = nullptr;
        last[keyFrequency] = keyAddress;
        if(first[keyFrequency] == nullptr) first[keyFrequency] = keyAddress;
        if(minimumOccurence == 0) minimumOccurence = 1;
        minimumOccurence = min(minimumOccurence, keyFrequency);
        while(first.find(minimumOccurence) == first.end() || first[minimumOccurence] == nullptr) minimumOccurence += 1;
        
    }
    int get(int key) {
        //cout << "GET\n";
        update(key);
        node* keyNode = (address.find(key) != address.end() ? address[key] : nullptr);
        if(keyNode == nullptr) return -1;
        return keyNode->value;
    }
    
    void put(int key, int value) {
        if(address.find(key) == address.end()){
            frequency[key] = 0;
            address[key] = new node(key, value);
        }
        else address[key]->value = value;
        //cout << "PUT\n";
        update(key);
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */