public class Median_of_two_sorted_arrays {
    public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int len1 = nums1.length;
        int len2 = nums2.length;
        int size = len1 + len2;
        if(size % 2 == 1)
            return findKth(nums1,  0, len1, nums2, 0, len2, size/2 + 1);
        else
            return (findKth(nums1, 0, len1, nums2, 0, len2, size/2)
                  + findKth(nums1, 0, len1, nums2, 0, len2, size/2 + 1)) / 2;
    }

    private static double findKth(int[] nums1, int start1, int len1,
                            int[] nums2, int start2, int len2, int k)
    {
        if(len1 - start1 > len2 - start2) // 传进来的时候统一让短的数组为nums1
            return findKth(nums2, start2, len2, nums1, start1, len1, k);
        if(len1 - start1 == 0) // 表示nums1已经全部加入前k个了，第k个为nums2[k-1];
            return nums2[k - 1];
        if(k == 1) // k==1表示已经找到第k-1小的数，下一个数为两个数组start开始的最小值
            return Math.min(nums1[start1], nums2[start2]);
        int p1 = start1 + Math.min(len1 - start1, k/2); // p1和p2记录当前需要比较的那个位
        int p2 = start2 + k - p1 + start1;
        System.out.printf("p1,p2 %d %d\n", p1,p2);
        if(nums1[p1 - 1] < nums2[p2 - 1])
            return findKth(nums1, p1, len1, nums2, start2, len2, k - p1 + start1);
        else if(nums1[p1 - 1] > nums2[p2 - 1])
            return findKth(nums1, start1, len1, nums2, p2, len2, k - p2 + start2);
        else
            return nums1[p1 - 1];
    }

    private static double findKth_v2(int[] nums1, int start1, int len1,
                            int[] nums2, int start2, int len2, int k)
    {
        if(len1 - start1 > len2 - start2) // 传进来的时候统一让短的数组为nums1
            return findKth(nums2, start2, len2, nums1, start1, len1, k);
        if(len1 - start1 == 0) // 表示nums1已经全部加入前k个了，第k个为nums2[k-1];
            return nums2[k - 1];
        if(k == 1) // k==1表示已经找到第k-1小的数，下一个数为两个数组start开始的最小值
            return Math.min(nums1[start1], nums2[start2]);
        int p1 = start1 + Math.min(len1 - start1, k/2); // p1和p2记录当前需要比较的那个位
        int p2 = start2 + k - p1 + start1;
        System.out.printf("p1,p2 %d %d\n", p1,p2);
        if(nums1[p1 - 1] < nums2[p2 - 1])
            return findKth(nums1, p1, len1, nums2, start2, len2, k - p1 + start1);
        else if(nums1[p1 - 1] > nums2[p2 - 1])
            return findKth(nums1, start1, len1, nums2, p2, len2, k - p2 + start2);
        else
            return nums1[p1 - 1];
    }

    public static void main(String[] args) {
        int[] A = {1,2,3,10,11,12};
        int[] B = {4,5,6,7,8,9};
        double median = Median_of_two_sorted_arrays.findMedianSortedArrays(A,B);
        System.out.printf("median:%f",median);
    }
}