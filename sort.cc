class Solution {
public:

    vector<int> sortArray(vector<int>& nums){
        vector<int> res;
        int low = *min_element(nums.begin(), nums.end());
        int high = *max_element(nums.begin(), nums.end());
        int n = high-low+1;
        vector<int> bucket(n);
        for (auto& x: nums) ++bucket[x-low];
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < bucket[i]; ++j){
                res.push_back(i+low);
            }
        }
        return res;
    }

    //归并排序 将数组分治处理排序然后边合并边处理。时间复杂度O(nlogn),空间复杂度O(n);
    vector<int> merge_sort(vector<int>& nums, int l, int r){
        if (l > r) return{};
        if (l == r) return {nums[l]};
        int mid = l + (r-l)/2;
        vector<int> res;
        auto l_v = merge_sort(nums,l,mid);
        auto r_v = merge_sort(nums, mid+1,r);
        int i = 0, j = 0;
        while(i < l_v.size() && j < r_v.size()){
            if (l_v[i] <= r_v[j]) res.push_back(l_v[i++]);
            else res.push_back(r_v[j++]);
        }
        while(i < l_v.size()) res.push_back(l_v[i++]);
        while(j < r_v.size()) res.push_back(r_v[j++]);

        return res;
    }

    vector<int> sortArray_merge(vector<int>& nums){
        return merge_sort(nums,0, nums.size()-1);
    }



    //快速排序 为枢纽元素找到正确位置。时间复杂度最好(nlogn)，最坏O(n²); 空间复杂度O(logN);
    void quick_sort(vector<int>& nums, int l, int r){
        if(l >= r) return;
        int cur = l;
        swap(nums[r], nums[(l+r)/2]);
        for (int i = l; i < r; ++i){
            if (nums[i] < nums[r]) swap(nums[cur++], nums[i]);
        }
        swap(nums[cur],nums[r]);
        quick_sort(nums, l, cur-1);
        quick_sort(nums,cur+1, r);
    }
    vector<int> sortArray_quick_sort(vector<int>& nums){
        quick_sort(nums, 0, nums.size()-1);
        return nums;
    }

    //堆排序 下滤 时间复杂度O(nlogn);空间O(1);
    #define LEFT_CHILD(i) (2*(i)+1)  //i从0开始索引
    // 下滤， 找到第一个不是叶子节点的节点
    void perce_down(vector<int>& nums, int i, int len){
        int child, tmp;
        for (tmp = nums[i]; LEFT_CHILD(i) < len; i=child){
            child = LEFT_CHILD(i);
            if (child != len-1 && nums[child+1] > nums[child])  //比较左右孩子大小。 
                ++child;
            if (nums[child] > tmp) nums[i] = nums[child]; //i作父节点，开始往下找，只要比i节点大就往父节点赋值。
            else break;
        }
        nums[i] = tmp;
    }
    vector<int> sortArray_heap(vector<int>& nums){
        int len = nums.size();
        for (int i = len/2-1/*第一个非叶子节点开始往根节点进行比较过滤*/; i >= 0; --i)
            perce_down(nums, i, len);
        for (int i = len-1; i > 0; --i){
            swap(nums[0], nums[i]);
            perce_down(nums, 0, i);
        }
        return nums;
    }


    //希尔排序。在间隔希尔增量的位置上做插入排序。好的希尔增量可以达到好的时间复杂度。时间复杂度最坏O(n²)
    vector<int> sortArray_shell(vector<int>& nums){
        vector<int> res = nums;
        int len = res.size();
        int tmp, j;
        for(int ic = len/2; ic > 0; ic /= 2){//希尔排序比插入排序多的步骤。当ic缩减到1时，就蜕变成插入排序。
            for (int i = ic; i < len; ++i){
                tmp = res[i];
                for (j = i; j >= ic && res[j-ic] > tmp; j-= ic) res[j] = res[j-ic];
                res[j] = tmp;
            }
        }
        return res;
    }
    //插入排序,最坏情况就是完全逆序，时间复杂度O(n²); 最好情况下就是完全升序，时间复杂度O(n);
    vector<int> sortArray_insert(vector<int>& nums){
        vector<int> res = nums;
        int tmp,j;
        for (int i = 1; i < res.size(); ++i){
            tmp = res[i];
            for (j = i; j > 0 /*j>=1 */&& res[j-1] > tmp; --j) res[j] = res[j-1];
            res[j] = tmp;
        }
        return res;
    }
    //选择排序,时间复杂度O(n²)
    vector<int> sortArray_select(vector<int>& nums) {
        vector<int> res = nums;
        int min_i;
        for (int i = 0; i < res.size()-1; ++i){
            min_i = i;
            for (int j = i+1; j < res.size(); ++j){
                if (res[j] < res[min_i]) min_i = j;
            }
            swap(res[i], res[min_i]);
        }
        return res;
    }
    //冒泡排序,时间复杂度O(n²)
    vector<int> sortArray_bubble(vector<int>& nums) {
        vector<int> res = nums;
        for (int i = 0; i < res.size(); ++i){
            for (int j = 1; j < res.size() - i; ++j){
                if (res[j] < res[j-1]) swap(res[j], res[j-1]);
            }
        }
        return res;
    }
};
