#include<stdio.h>
#include<math.h>

int getKthElem(int* nums1,int len1, int* nums2,int len2, int K) {
	int index1 = 0, index2 = 0;
	while (1) {
		// 边界情况1：数组1已全部排除，第 k 小的元素必然在数组2中
		// 此时数组2的起始位置为 index2，需要取该位置起的第 k 个元素，即 nums2[index2 + k - 1]
		if (index1== len1 ) {
			return nums2[index2 + K - 1];
		}
		if (index2 == len2 ) {
			//nums2走完，第k小的数为nums1[index1+K-1]
			return nums1[index1 + K - 1];
		}
		if (K == 1) {
			//k==1，二者中较小者为第一小元素
			return (nums1[index1] <= nums2[index2] ? nums1[index1] : nums2[index2]);
		}

		//正常情况:
		int half = K / 2;
		int compare_index1 = index1 + half - 1;
		int compare_index2 = index2 + half - 1;
		//当数组走完时，直接取最后元素防越界;
		if (compare_index1 >= len1 - 1) {
			compare_index1 = len1 - 1;

		}
		if (compare_index2 >= len2 - 1) {
			compare_index2 = len2 - 1;
		}
		int pivot1 = nums1[compare_index1];
		int pivot2 = nums2[compare_index2];
		if (pivot1 <= pivot2) {
			int count = compare_index1 - index1 + 1;//排除pivot前的元素，
			//原本的第K小变为排除count个元素之后的第k-count小元素；
			K -= count;
			index1 = compare_index1 + 1;
		}
		else {
			int count =  compare_index2 - index2 + 1;
			K -= count;
			index2 = compare_index2 + 1;
		}
	}


}
double findmedian_arr(int* nums1, int len1, int* nums2, int len2) {
	int length = len1 + len2;
	if (length % 2 == 1) {
		int midIndex = length / 2;
		return (double)getKthElem(nums1, len1, nums2, len2, midIndex + 1);

	}
	else {
		int midIndex1 = length / 2;
		int midIndex2 = length / 2 - 1;
		double left = (double)getKthElem(nums1, len1, nums2, len2, midIndex2 + 1);
		double right = (double)getKthElem(nums1, len1, nums2, len2, midIndex1 + 1);
		return (left + right) / 2.0;
	}
}