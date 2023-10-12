package chap03;

import java.util.Arrays;
import java.util.Scanner;

public class BinarySearchTester {
    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);

        System.out.println("배열 수를 입력하세요: ");
        int num = stdIn.nextInt();
        int[] x = new int[num];

        // 첫 요소 입력 받고 나머지 요소들은 반복문으로 입력 받음
        System.out.println("오름차순으로 입력하세요: ");
        System.out.print("x[0]: ");
        x[0] = stdIn.nextInt();

        for (int i = 1; i < num; i++) {
            do {
                System.out.print("x[" + i + "] : ");
                x[i] = stdIn.nextInt();
            } while (x[i] < x[i - 1]); // 바로 앞 요소보다 작은 수를 입력하면 다시 입력 받음
        }

        System.out.println("검색할 값을 입력하세요: ");
        int ky = stdIn.nextInt();

        int idx = Arrays.binarySearch(x, ky); // 배열 x에서 값이 ky인 요소를 검색

        if (idx == -1)
            System.out.println("배열에 검색할 값이 없습니다.");
        else
            System.out.println("그 값은 x[" + idx + "]에 있습니다.");
    }
}
