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

        while (scn.hasNext()) {
            BigInteger n = scn.nextBigInteger();
            BigInteger m = scn.nextBigInteger();

            BigInteger ans = fastPow(m, n.pow(2)).add(fastPow(m, n.pow(2).add(n).shiftRight(1)).shiftLeft(1));
            if (n.mod(BigInteger.valueOf(2)).compareTo(BigInteger.ONE) == 0)
                ans = ans.add(fastPow(m, n.pow(2).subtract(BigInteger.ONE).shiftRight(2).add(BigInteger.ONE)).shiftLeft(1).add(fastPow(m, n.pow(2).subtract(BigInteger.ONE).shiftRight(1).add(BigInteger.ONE)))).add(fastPow(m, n.multiply(n.subtract(BigInteger.ONE).divide(BigInteger.valueOf(2)).add(BigInteger.ONE))).shiftLeft(1));
            else
                ans = ans.add(fastPow(m, n.pow(2).shiftRight(2)).shiftLeft(1).add(fastPow(m, n.pow(2).shiftRight(1)).multiply(BigInteger.valueOf(3))));
            ans = ans.shiftRight(3);
            System.out.println(ans);
        }
    }
}