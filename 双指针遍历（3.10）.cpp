#include<stdio.h>
#include<stdlib.h>
int comps(int val1, int val2) {
	int ret = 0;
	if (val1 <= val2) {
		ret = val1;
	}
	else {
		ret = val2;
	}
	return ret;
}
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	double mid;
	int newlength = nums1Size + nums2Size;
	if (newlength == 0) {
		return 0.0;
	}
	//新数组存储合并后的数组
	int* newarr = (int*)malloc(newlength * sizeof(int));

	int i = 0;
	int* p = nums1, * q = nums2;
	while (p < nums1 + nums1Size || q < nums2 + nums2Size) {
		if (p == nums1 + nums1Size) {
			for (; q < nums2 + nums2Size; q++, i++) {
				newarr[i] = *q;
			}
			break;//复制完后退出循环
		}
		if (q == nums2 + nums2Size) {
			for (; p < nums1 + nums1Size; p++, i++) {
				newarr[i] = *p;
			}
			break;
		}
		newarr[i] = comps(*p, *q);
		if (newarr[i] == *p && p < nums1 + nums1Size) {//保证没有越界时p++

			p++;
		}
		else {
			if (q < nums2 + nums2Size)//保证没有越界时q++
				q++;
		}
		i++;

	}

	if (newlength % 2 == 0) {
		mid = ((double)newarr[(newlength / 2)] + (double)newarr[(newlength / 2) - 1]) / 2;
	}
	else {
		mid = newarr[newlength / 2];
	}
	free(newarr);
	return mid;
}