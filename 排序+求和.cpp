/*给你一个整数数组 nums ，判断是否存在三元组[nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。
请你返回所有和为 0 且不重复的三元组。注意：答案中不可以包含重复的三元组
*******思路：先排有序（升序），一次循环取一个，在通过双指针low（指向数组头）high（尾），if（s[i]+*low+*high<0）：low++让和增大，else：high--让值减小*********；*/
/*   i 去重：同一个数字不要当第一个数两次
     left 去重：找到答案后，左边相同数字跳过
     right 去重：找到答案后，右边相同数字跳过
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int partition(int* nums, int low, int high) {//分治，让pivot基准左边比它小，右边大
	int pivot = nums[low];//记住nums[low]即pivot基准值，最后放到low对应的位置
	while (low < high) {
		while (low < high && nums[high] >= pivot) {// 从右到左找到第一个比基准pivot小的
			high--;
		}
		nums[low] = nums[high];
		while (low < high && nums[low] <= pivot) {//从左到右找到第一个比基准pivot大的
			low++;
		}
		nums[high] = nums[low];
	}
	nums[low] = pivot;//完成pivot（即第一个元素）的左右分治
	return low;
}
// 快速排序递归函数
void quickSort(int* nums,int low,int high ){
	if (low < high) {
		int pi = partition(nums, low, high);
			quickSort(nums, low, pi - 1);
			quickSort(nums, pi + 1, high);

	}
}
int** threeSum(int* nums, int size, int* returnSize, int** returnColumnSizes) {
	/*result 存数据，returnColumnSizes 存形状
	result  -->  [ptr0]  -->  [a0, b0, c0]
             [ptr1]  -->  [a1, b1, c1]
             [ptr2]  -->  [a2, b2, c2]*/
	*(returnSize) = 0;
	int capacity = 8;/*capacity是指针数组中存储的三元组数组的首地址的个数*/
	int** result = (int**)malloc(sizeof(int*) * capacity);/*指针数组result存储每个三元组的首地址*/
	quickSort(nums, 0, size - 1);
	if (nums[0] > 0 || nums[size - 1] < 0) {/*剪枝*/
		*returnSize = 0;
		*returnColumnSizes = NULL;
		return NULL;
	}
	for(int i=0;i<size-2;i++){
		if (i>0&&nums[i] == nums[i - 1]) continue;//去重，以i为第一元素的三元组已在上一个三元组中被包含
		int sum = 0;
		
		int left = i+1;
		int right = size - 1;
		
		while (left < right) {/*一保证left和right不同，二是循环判断条件，left++，right--不断逼近目标值，当left==right，区域内搜索完毕，指向下一个i*/
			sum = nums[i] + nums[right] + nums[left];
			if (sum == 0) {//找到一个目标三元组
				if (*returnSize >= capacity) {
					capacity *= 2;
					result = (int**)realloc(result, capacity * sizeof(int*));
				}
				int* triple = (int*)malloc(sizeof(int) * 3);
				triple[0] = nums[i];
				triple[1] = nums[left];
				triple[2] = nums[right];
				result[*returnSize] = triple;
				(*returnSize)++;

				while (left < right && nums[right] == nums[right - 1]) right--; /*跳过重复的（已被包含在一组解中的）*right*/

				while (left < right && nums[left] == nums[left + 1]) left++; /*跳过重复的（已被包含在一组解中的）*left*/
				left++, right--;
			}/*在left和right不满足：sum==0*/
			else if (sum < 0) {
				left++;
			}
			else {
				right--;
			}
		}
		
	}
	if ((*returnSize) > 0) {
		*returnColumnSizes = (int*)malloc(sizeof(int) * (*(returnSize)));
		for (int i = 0; i < *returnSize; i++) {
			(*returnColumnSizes)[i] = 3;
		}
	}
	else {
		*returnColumnSizes = NULL;
	}
	return result;

}

