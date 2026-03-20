#include"接口.h"
/*分治思路：让基准pivot=low,即n[0]，high指表尾元素，从表尾找到比pivot大的元素，从low开始找比pi大的元素实现pi右边小，左边大*/
int partition(int* nums, int low, int high) {
	int pivot = nums[low];
	
	while (low < high) {
		while (low < high && nums[high] >= pivot) {
			high--;
			
		}
		nums[low] = nums[high];
		while (low<high && nums[low]<=pivot) {
			low++;
			
		}
		//循环停止时，找到第一个左侧比pivot大的：
		nums[high] = nums[low];
	}
	nums[low] = pivot;
	return low;
}
void QuickSort(int* nums, int low, int high) {
	if (low < high) {
		int pi = partition(nums, low, high);
		QuickSort(nums, low, pi - 1);
		QuickSort(nums, pi + 1, high);
	}

}
/*先排序，在排序好的数组中，直接取中间元素，nums[mid],target>mid,表示两个因数在mid之前，*/
// 递归折半查找：不断缩小区间，加速找到两数之和

void findRecursive(
    int* nums,       // 排序后的数组
    int left,        // 当前查找区间的左边界
    int right,       // 当前查找区间的右边界
    int target,      // 目标和
    int** res,       // 存储找到的所有答案
    int* returnSize  // 已经找到几组答案
) {
    // 递归终止条件：区间无效（左 >= 右），无法找两个数，直接退出
    if (left >= right) return;
    int mid = (left + right) / 2;
   
    // 剪枝（超级加速）
    // 1. 区间里最小的两个数加起来都 > target → 不可能找到
    // 2. 区间里最大的两个数加起来都 < target → 不可能找到

    if (nums[left] + nums[left + 1] > target) return;
    if (nums[right] + nums[right - 1] < target) return;
	
    // 递归折半核心逻辑：
    // 根据 mid 的大小，判断答案在 左半区 / 右半区
    // 情况1：mid 本身都比 target 大
    // → 两个数一定都在 左半部分
    if (nums[mid] > target) {
        // 递归只搜索左半边
        findRecursive(nums, left, mid - 1, target, res, returnSize);
    }  
    // 情况2：mid * 2 都小于 target
    // 两个数必须都很大，一定在 右半部分

    else if (nums[mid] * 2 < target) {
        // 递归只搜索右半边
        findRecursive(nums, mid + 1, right, target, res, returnSize);
    }

    // 情况3：无法再折半
    // nums[mid] <= target 并且 nums[mid] * 2 >= target
    // 两个数可能一个在左、一个在右
    //不能再砍区间，在整个当前区间用双指针找

    else {
        // 双指针初始化：区间左端 + 右端
        int l = left;
        int r = right;

        while (l < r) {
            int sum = nums[l] + nums[r];
            // 找到一组解
            if (sum == target) {
                // 开辟空间存储这一组 [a,b]
                int* pair = (int*)malloc(sizeof(int) * 2);
                pair[0] = nums[l];
                pair[1] = nums[r];
                // 放入结果数组
                res[(*returnSize)++] = pair;
                // 去重
                while (l < r && nums[l] == nums[l + 1]) l++;
                while (l < r && nums[r] == nums[r - 1]) r--;
                // 移动指针
                l++;
                r--;
            }
            // 和太小 → 左指针右移（变大）
            else if (sum < target) {
                l++;
            }
            // 和太大 → 右指针左移（变小）
            else {
                r--;
            }
        }

        // 这个区间找完
        return;
    }
}

int** twoSum(
    int* nums,
    int numsSize,
    int target,
    int* returnSize,    // 输出：找到几组答案
    int** returnColumnSizes // 输出：每组几个数
) {
    *returnSize = 0;
    int** result = (int**)malloc(sizeof(int*) * 100);
    QuickSort(nums, 0, numsSize - 1);
    findRecursive(nums, 0, numsSize - 1, target, result, returnSize);   
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    return result;
}
