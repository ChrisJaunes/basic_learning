public class test_abs{
    public static void main(String args[]){
        Integer a = -1;
        double b = 2;
        long c = -9223372036854775808L;
        long d = -9223372036854775807L;
        System.out.println(Math.abs(a));
        System.out.println(Math.abs(b));
        System.out.println(Math.abs(c));
        System.out.println(Math.abs(d));
    }
}