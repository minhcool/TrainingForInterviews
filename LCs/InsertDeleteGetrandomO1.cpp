class RandomizedSet {
public:
    /*
    vector<int> numbers; // stores all numbers that is in the set
    unordered_map<int, int> position; // store positions of number inside the "numbers" vector
    - insertions/deletions -> look up on the position unordered_map to get position of number inside the "numbers" vector
    - swap the element that we want to erase with the last element of vector
    - pop_back
    */
    vector<int> numbers;
    unordered_map<int, int> position;
    RandomizedSet() {
        numbers.clear();
        position.clear();
    }
    
    bool insert(int val) {
        if(position.find(val) != position.end()){
            return false;
        }
        numbers.push_back(val);
        position[val] = numbers.size() - 1;
        return true;
    }
    
    bool remove(int val) {
        if(position.find(val) == position.end()){
            return false;
        }
        int pos = position[val];
        swap(numbers[pos], numbers[numbers.size() - 1]);
        position[numbers[pos]] = pos;
        position.erase(val);
        numbers.pop_back();
        return true;
    }
    
    int getRandom() {
        return numbers[rand() % numbers.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */