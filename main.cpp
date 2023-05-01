#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void bubbleSort(int arr[],int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (n -i)-1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void selectionSort(int array[], int size){
    for (int i = 0; i < size-1; ++i) {
        int minIndex = i;
        for (int j = i+1; j < size; ++j) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        swap(array[minIndex],array[i]);
    }
}

void insertionSort(int array[], int size){
    for (int i = 1; i < size; ++i) {
        int key = array[i];
        int j = i-1;
        while (j >= 0 && array[j] > key) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}

void merge(int left[], int right[], int array[], int leftSize, int rightSize){
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        }else{
            array[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < leftSize) {
        array[k] = left[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        array[k] = right[j];
        j++;
        k++;
    }
}
void mergeSort(int array[], int size){
    if (size < 2) {
        return;
    }
    int mid = size/2;
    int left[mid];
    int right[size-mid];
    for (int i = 0; i < mid; ++i) {
        left[i] = array[i];
    }
    for (int i = mid; i < size; ++i) {
        right[i-mid] = array[i];
    }
    mergeSort(left,mid);
    mergeSort(right,size-mid);
    merge(left,right,array,mid,size-mid);
}

void quickSort(int array[], int low, int high){
    if (low < high) {
        int pivot = array[high];
        int i = low-1;
        for (int j = low; j < high; ++j) {
            if (array[j] < pivot) {
                i++;
                swap(array[i],array[j]);
            }
        }
        swap(array[i+1],array[high]);
        int pi = i+1;
        quickSort(array,low,pi-1);
        quickSort(array,pi+1,high);
    }
}

vector<int> sortArray(vector<int>& nums) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i : nums)
        pq.push(i);
    for(int i=0;i<nums.size();i++){
        nums[i] = pq.top();
        pq.pop();
    }
    return nums;
}

int main() {
    int x[5]={5,4,3,2,1};
    vector<int> v = {5,4,3,2,1};
    for (int i : x) {
        cout<<i<<" ";
    }
    cout<<endl;
//    quickSort(x,0,4);
//    mergeSort(x,5);
    sortArray(v);
    for (int i : v) {
        cout<<i<<" ";
    }

}
