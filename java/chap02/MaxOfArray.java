package chap02;

import java.util.Scanner;

public class MaxOfArray {
    // 배열 a의 최댓값을 구하여 반환
    static int maxOf(int[] a) {
        int max = a[0];
        for (int i = 1; i < a.length; i++)
            if (a[i] > max)
                max = a[i];
        return max;
    }

    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);

        System.out.println("키의 최댓값을 구합니다.");
        System.out.println("사람 수: ");
        int num = stdIn.nextInt(); // 배열의 개수를 입력받음 nextInt()

        int[] height = new int[num]; // 배열 개수가 num인 배열을 생성

        for (int i = 0; i < num; i++) {
            System.out.println("height[" + i + "]: ");
            height[i] = stdIn.nextInt(); // 배열의 개수만큼 키를 입력 받음
        }
        System.out.println("최댓값은 " + maxOf(height) + "입니다.");
    }
}
