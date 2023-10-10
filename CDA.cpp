#include <random>
using namespace std;


template <typename elmtype>
class CDA {
    private:
    elmtype* arr;
    elmtype* linearArray; // An array used for reseting the orginal array 'arr'
    int size, capacity;
    int head, tail, cur;
    int binaryIndex, binaryUpper, binaryLower; // These indecies are used to help save the indecies checked for in the binary search
    elmtype* fixArray (elmtype* a) { // resets the array from 0 to size - 1
        cur = head;
        elmtype value = a[cur];
        elmtype* newArray = new elmtype[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = a[cur];
            if (cur == capacity - 1) {
                cur = 0;
            }
            else {
                cur++;
            }
        }
        newArray[0] = value;
        head = 0;
        tail = size - 1;
        return newArray;
    }
    void Merge(elmtype* a, int front, int middle, int back) { // takes the segemented array and sorts it
        int n1 = middle - front + 1; // first half of the array
        int n2 = back - middle; // second half of the array
        elmtype* left = new elmtype[n1]; 
        elmtype* right = new elmtype[n2];
        for (int i = 0; i < n1; i++) { 
            left[i] = a[front + i];
        }
        for (int j = 0; j < n2; j++) {
            right[j] = a[middle + j + 1];
        }
        int i = 0;
        int j = 0;
        bool finishedLeft = false;
        bool finishedRight = false;
        for (int k = front; k <= back; k++) { //boolean determines whether to go back into the left or right array
            if (finishedLeft == false) { // if one side is finished, then you just add values from the the other side, begint the array that isn't finished
                if (finishedRight == false && left[i] > right[j]){
                    a[k] = right[j];
                    j++;
                    if (j >= n2) {
                        finishedRight = true;
                    }
                    if (k == back) {
                        j--;
                    }
                }
                else {
                    a[k] = left[i];
                    i++;
                    if (i >= n1) {
                        finishedLeft = true;
                    }
                    if (k == back) {
                        i--;
                    }
                }
            }
            else if (finishedRight == false){
                if (finishedLeft == false && right[j] > left[i] ) {
                    a[k] = left[i];
                    i++;
                    if (k == back) {
                        i--;
                    }
                    if (i >= n1) {
                        finishedLeft = true;
                    }
                }
                else {
                    a[k] = right[j];
                    j++;
                    if (j >= n2) {
                        finishedRight = true;
                    }
                    if (k == back) {
                        j--;
                    }
                } 
            }
        }
    }
    void MergeSort(elmtype* a, int front, int back) {
        if (front >= back) { // exits process if the front is greater than or equal to the back
            return;
        }
        if (front < back) {
            int middle = (front + back) / 2;
            MergeSort(a, front, middle); // partitions the array for the first half of the values
            MergeSort(a, middle + 1, back); // partitions the array for the second half of the values
            Merge(a, front, middle, back);
        }
    }
    int bSearch(elmtype value, int low, int high, int index) { // basic binary search
        if (arr[index] == value) { // if the value being looked for equals the index in the array you are at, then you return the index
            return index;
        }
        else if ((index == high && low == high - 1) || (index == low && high == low + 1)) { // If there are only 2 indecies left to check
            int indexCheck;
            for (indexCheck = index; indexCheck < capacity; indexCheck++) {  
                if (arr[indexCheck] > value) { // if the index's value is greater then we break because we have already passed the index with the value we are looking for
                    break;
                }
            }
            if (arr[indexCheck] > value) { // if the value is not found in the list then we return a value for the index
                binaryIndex = ~(indexCheck); // the binary index turn into the negative bitwise counterpart of indexCheck
                if (binaryIndex < 0) { 
                    binaryIndex = binaryIndex;
                }
                else {
                    binaryIndex = -binaryIndex;
                }
            }
            else { // binary index returns the bitwise counterpart of the size of the array
                binaryIndex = (~size);
            }
            return binaryIndex;
        }
        else if (value > arr[index]) { // narrows the range of elements to the top half of the array that is left
            low = index;
            if (low != (high - 1)) {
                index = (high + low) / 2;
            }
            else {
                index = high;
            }
            return bSearch(value, low, high, index);
        }
        else if (value < arr[index]) { // narrows the range of elements to the bottom half of the array that is left
            high = index;
            if (high != (low + 1)) {
                index = (high + low) / 2;
            }
            else {
                index = low;
            }
            return bSearch(value, low, high, index);
        }
        
    }
    int partition(elmtype* a, int low, int high, int pivotIndex) { // splits the array up into a quick 
        elmtype value = a[pivotIndex];
        int front = low;
        swap(a[pivotIndex], a[high]); // I move the item at the pivotIndex to the back of the array to avoid issues
        for (int i = low; i < high; i++) {
            if (a[i] < value) {
                swap(a[i], a[front]); // puts all of the smallest values on one side and moves the largest to the other
                front++;
            }
        }
        swap(a[high],a[front]); // at the end puts the original pivotIndex value at the front of the array and returns the front index
        return front;
    }
    elmtype quickSelect(elmtype* a, int k) {
        int front = head; // front and back represent the 2 ends of the array
        int back = tail;
        while (front <= back) {
            int pivotIndex = rand() % (back - front + 1) + front; // I select a random pivot based on front and back
            int partitionIndex = partition(a, front, back, pivotIndex); // I selecet a partitionIndex that is used to see if I have landed on the kth smallest element
            if (k - 1 == partitionIndex) { // If the element's index is found return the element
                return a[partitionIndex];
            }
            else if (k - 1 < partitionIndex) { // If the kth - 1 index is less than the partitionIndex then I set back to the middle of the front and back index
                back = partitionIndex - 1;
            } 
            else { // If the kth - 1 index is greater than the partitionIndex then I set front to the middle ofthe front and back index
                front = partitionIndex + 1;
            }
        }
        return a[0];
    }
    public:
    CDA() {
        srand(0);
        head = 0;
        tail = 0;
        size = 0;
        capacity = 1;
        arr = new elmtype[capacity];
        linearArray = new elmtype[capacity];
    }
    ~CDA() {
        delete[] linearArray;
    }
    CDA(int s) {
        srand(0);
        head = 0;
        tail = 0;
        size = s;
        capacity = s;
        arr = new elmtype [capacity];
        linearArray = new elmtype[capacity];
    }    
    CDA(int s, elmtype init) {
        srand(0);
        head = 0;
        tail = s - 1;
        size = s;
        capacity = s;
        arr = new elmtype[capacity];
        linearArray = new elmtype[capacity];
        fill_n(arr, capacity, init);
        fill_n(linearArray, capacity, init);
    }
    CDA(const CDA& src) {
        srand(0);
        head = src.head;
        tail = src.tail;
        size = src.size;
        capacity = src.capacity;
        arr = new elmtype[capacity];
        linearArray = new elmtype[capacity];
    } 
    elmtype& operator[](int i) {
        if ((i > size - 1) || (i < 0)) {
            cout << i << " is out of bounds" << endl;
        }
        int index = (head + i) % capacity;
        return arr[index];
    }
    CDA& operator=(CDA& src) {
        this -> arr = new elmtype[src.capacity];
        this -> size = src.size;
        this -> capacity = src.capacity;
        this -> head = src.head;
        this -> tail = src.tail;
        this -> cur = src.head;
        for (int i = 0; i < size; i++) {
            this -> arr[cur] = src[i];
            if (cur == capacity - 1) {
                this -> cur = 0;
            }
            else {
                this -> cur++;
            }
        }
        return *this;
    }
    void AddEnd(elmtype v) {
        cur = head;
        if (size == capacity) { // resizes array if the size equals capacity
            capacity *= 2;
            size++;
            int previousSize = size - 1;
            linearArray = new elmtype[capacity];
            for (int i = 0; i < size; i++) {
                if (i < size - 1) {
                    linearArray[i] = arr[cur];
                }
                else {
                    linearArray[i] = v;
                }
                if (cur == previousSize - 1) {
                    cur = 0;
                }
                else {
                    cur++;
                }
            }
            arr = linearArray;
            head = 0;
            tail = size - 1;
        }
        else {
            tail = (tail + 1) % capacity;
            arr[tail] = v;
            linearArray[tail] = v;
            size++;
        }
    }
    void AddFront(elmtype v) {
        if (size == capacity) { 
            capacity *= 2;
            int previousSize = size - 1;
            size++;
            linearArray = new elmtype[capacity];
            elmtype value = arr[tail];
            for (int i = 0; i < size; i++) {
                if (i == 0) {
                    linearArray[i] = v;
                }
                else { 
                    linearArray[i] = arr[cur];
                    if (cur == previousSize) {
                        cur = 0;
                    }
                    else {
                        cur++;
                    }
                    
                }
            }
            linearArray[size - 1] = value;
            arr = linearArray;
            head = 0;
            tail = size - 1;
        }
        else {
            if (head - 1 < 0) {
                cur = capacity - 1;
            }
            else {
                cur = head - 1;
            }
            head = cur;
            arr[head] = v;
            size++;
        }   
    }
    int Length() {
        return size;
    }
    int Capacity() {
        return capacity;
    }
    void DelEnd() {
        cur = head;
        elmtype value;
        if (tail - 1 < 0) {
            tail = capacity - 1; 
        }
        else {
            tail--;
        }
        size--;
        if (size <= (capacity / 4)) {
            capacity = capacity / 2;
            linearArray = new elmtype[capacity];
            for (int i = 0; i < size; i++) {
                linearArray[i] = arr[cur];
                if (cur == capacity - 1) {
                    cur = 0;
                } 
                else {
                    cur++;
                }
            }
            arr = linearArray;
            tail = size - 1;
        }
    }
    void DelFront() {
        if (head + 1 == capacity) {
            head = 0;
        }
        else {
            head++;
        }
        size--;
        cur = head;
        if (size <= (capacity / 4)) {
            capacity = capacity / 2;
            linearArray = new elmtype[capacity]; 
            for (int i = 0; i < size; i++) {
                linearArray[i] = arr[cur];
                if (cur == capacity - 1) {
                    cur = 0;
                } 
                else {
                    cur++;
                }
            }
            arr = linearArray;
            head = 0;
            tail = size - 1;
        }
    }
    elmtype Select(int k) {
        arr = fixArray(arr);
        elmtype value = quickSelect(arr, k);
        return value;
    }
    void Sort() {
        arr = fixArray(arr);
        MergeSort(arr, head, tail);
    }
    int Search(elmtype e) {
        int index = -1;
        cur = head;
        for (int i = 0; i < size; i++) {
            if (arr[cur] == e) {
                index = i;
                break;
            }
            else if (cur == capacity - 1) {
                cur = 0;
            }
            else {
                cur++;
            }
        }
        return index;
    }
    int BinSearch(elmtype e) {
        if (linearArray[tail / 2] == e) {
            binaryIndex = tail / 2;
            return binaryIndex;
        }
        else if (e > linearArray[tail / 2]) {
            binaryLower = tail / 2;
            binaryUpper = tail;
            binaryIndex = ((binaryUpper + binaryLower) / 2);
            return bSearch(e, binaryLower, binaryUpper, binaryIndex);
        }
        else if (e < linearArray[tail / 2]) {
            binaryUpper = tail / 2;
            binaryLower = head;
            binaryIndex = ((binaryLower + binaryUpper) / 2);
            return bSearch(e, binaryLower, binaryUpper, binaryIndex);
        }
    }
};