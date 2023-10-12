package chap03;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class PhyExamSearch {
    static class PhyscData {
        private String name;
        private int height;
        private double vision;

        // 생성자
        public PhyscData(String name, int height, double vision) {
            this.name = name;
            this.height = height;
            this.vision = vision;
        }

        // 문자열로 만들어 변환하는 메서드
        public String toString() {
            return name + " " + height + " " + vision;
        }

        // 키의 오름차순으로 정렬하기 위한 comparator
        public static final Comparator<PhyscData> HEIGHT_ORDER = new HeightOrderComparator();

        private static class HeightOrderComparator implements Comparator<PhyscData> {
            public int compare(PhyscData d1, PhyscData d2) {
                // d1 > d2면 return 1, d1 < d2면 return -1, 같으면 return 0
                return (d1.height > d2.height) ? 1 :
                        (d1.height < d2.height) ? -1 : 0;
            }
        }
    }

    public static void main(String[] args) {
        Scanner stdIn = new Scanner(System.in);
        PhyscData[] x = {
            new PhyscData("김소정", 142, 0.3),
            new PhyscData("조대정", 143, 0.3),
            new PhyscData("구현정", 153, 0.3),
            new PhyscData("대조현", 163, 0.3),
            new PhyscData("김대현", 173, 0.3),
        };
        System.out.print("키가 몇인가요: ");

        int height = stdIn.nextInt();
        int idx = Arrays.binarySearch(
                x,
                new PhyscData("", height, 0.0),
                PhyscData.HEIGHT_ORDER
                );
        if (idx < 0)
            System.out.println("그 키를 가진 학생은 없습니다");
        else
            System.out.println("학생은 " + x[idx]);

    }
}
