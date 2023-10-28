package chap05_reculsive;

public class Factorial {
    public static void main(String[] args) {
        System.out.println(result(0));
    }
    static int result(int num) {
        if (num > 1) {
            return num * result(num - 1);
        } else {
            return 1;
        }
    }
}
