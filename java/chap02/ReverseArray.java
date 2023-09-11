package chap02;

import java.util.Arrays;
import java.util.Scanner;

public class ReverseArray {
    // a[idx1]과 a[idx2] 의 값을 바꿈
    static void swap(int[] a, int idx1, int idx2) {
        int t = a[idx1]; a[idx1] = a[idx2]; a[idx2] = t;
    }

    // 배열 a의 요소를 역순으로 정렬
    static void reverse(int[] a) {
        for (int i = 0; i < a.length / 2; i++) { // 배열의 요소와 그 대칭에 있는 요소의 값을 바꾸므로 전체 길이의 반만 반복하면 됨
            swap(a, i, a.length - i - 1);
        }
    }

    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);

        System.out.println("배열 길이: ");
        int num = stdIn.nextInt();

        int[] x = new int[num]; // 입력받은 배열길이로 배열 생성

        for (int i = 0; i < num; i++) {
            System.out.println("x[" + i + "]: ");
            x[i] = stdIn.nextInt(); // 배열 값 입력
        }

        reverse(x); // 배열 a의 요소를 역순으로 정렬

        System.out.println("역순으로 정렬함");
        System.out.println("x = " + Arrays.toString(x)); // 모든 요소를 쉼표로 구분하여 [] 문자열 출력
    }


}
