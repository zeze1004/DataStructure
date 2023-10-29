package chap06_sort;

public class BubbleSort {
    static void swap(int[] a, int idx1, int idx2) {
        int t = a[idx1];
        a[idx1] = a[idx2];
        a[idx2] = t;
    }

    // 버블정렬
    static void bubbleSort(int[] a, int n) {
        // 두 번째 반복문에서 j가 i 보다 같거나 작을시 반복문이 종료되는 이유는
        // 처음 반복문이 돌 때, 가장 작은 수가 배열의 첫 번째로 swap 됐으므로
        // i = 1일 때, j는 2까지만 비교하면 됨 (a[1] > a[2])
        for (int i = 0; i < n - 1; i++) {
            // 교환 번수
            int exchg = 0;
            for (int j = n - 1; j > i; j--) {
                if (a[j - 1] > a[j]) {
                    swap(a, a[j - 1], a[j]);
                    exchg++;
                }
                if (exchg == 0) break; // 더 이상 교환이 이뤄지지 않으면 반복문을 종료함
            }
        }
    }
}
