package chap06_sort;

public class QuickSort {
    static void swap(int[] a, int idx1, int idx2) {
        int t = a[idx1]; a[idx1] = a[idx2]; a[idx2] = t;
    }

    // 퀵 정렬
    static void quickSort(int[] a, int left, int right) {
        int pl = left;
        int pr = right;
        int x = a[(pl + pr) / 2]; // 피벗(가운데 기준값)

        do {
            while (a[pl] < x) pl++;
            while (a[pr] > x) pr--;
            if (pl <= pr)
                swap(a, pl++, pr--);
        } while (pl < pr);

        if (left < pr) quickSort(a, left, pr);
        if (pl < right) quickSort(a, pl, right);
    }

    public static void main(String[] args) {
        int[] x = {135, 4632, 653, 34, 1, 8, 7, 4, 5, 2, 6, 3, 9, 0, 13, 56365, 324, 4095, 243};
        quickSort(x, 0, x.length - 1);

         for (int i = 0; i < x.length; i++) {
             System.out.println(x[i]);
         }
    }
}
