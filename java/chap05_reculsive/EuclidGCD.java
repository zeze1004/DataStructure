package chap05_reculsive;

public class EuclidGCD {
    // 정수 x, y의 최대공약수를 구하여 반환
    // x가 y보다 더 큰 수
    static int gcd(int x, int y) {
        if (y == 0)
            return x;
        else
            return gcd(y, x % y);
    }

    public static void main(String[] args) {
        System.out.println(gcd(22, 8));
    }
}
