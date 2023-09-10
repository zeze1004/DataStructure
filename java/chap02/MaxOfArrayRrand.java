package chap02;

import java.util.Random;
import java.util.Scanner;

public class MaxOfArrayRrand {
    static int maxOf(int[] a) {
        int max = a[0];
        for (int i = 1; i < a.length; i++)
            if (a[i] > max)
                max = a[i];
        return max;
    }

    public static void main(String[] args) {
        Random rand = new Random();
        Scanner stdIn = new Scanner(System.in);

        System.out.println("키의 최댓값을 구합니다.");
        System.out.println("사람 수: ");
        int num = stdIn.nextInt(); // 배열의 개수를 입력받음 nextInt()

        int[] height = new int[num]; // 배열 개수가 num인 배열을 생성

        System.out.println("키는 아래와 같습니다.");
        for (int i = 0; i < num; i++) {
            height[i] = 100 + rand.nextInt(90); // 랜덤수가 0~89까지 생성됨(+100)
            System.out.println("height[" + i + "]: " + height[i]);
        }
        System.out.println("최댓값은 " + maxOf(height) + "입니다.");
    }
}
