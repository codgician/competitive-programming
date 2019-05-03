import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    public static BigInteger fastPow(BigInteger a, BigInteger n) {
        BigInteger ans = BigInteger.ONE;
        while (n.compareTo(BigInteger.ZERO) == 1) {
            if (n.mod(BigInteger.valueOf(2)).compareTo(BigInteger.ONE) == 0) {
                ans = ans.multiply(a);
            }
            a = a.pow(2);
            n = n.shiftRight(1);
        }
        return ans;
    }

    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        int caseNum = scn.nextInt();
        for (int t = 1; t <= caseNum; t++) {
            BigInteger color = scn.nextBigInteger();
            BigInteger ans = fastPow(color, BigInteger.valueOf(8)).add(fastPow(color, BigInteger.valueOf(4)).multiply(BigInteger.valueOf(17))).add(color.multiply(color).multiply(BigInteger.valueOf(6))).divide(BigInteger.valueOf(24));
            String str = ans.toString();
            System.out.print("Case " + t + ": ");
            if (str.length() >= 15) {
                System.out.println(str.substring(str.length() - 15));
            } else {
                System.out.println(str);
            }
        }
    }
}