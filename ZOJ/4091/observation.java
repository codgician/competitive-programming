import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main(String [] args) {
        Scanner scn = new Scanner(System.in);
        int caseNum = scn.nextInt();
        for (int t = 0; t < caseNum; t++) {
            BigInteger num = scn.nextBigInteger();
            BigInteger ans = num;

            int oneNum = 0;
            while (num.compareTo(BigInteger.ZERO) == 1) {
                if (num.mod(BigInteger.valueOf(2)).compareTo(BigInteger.ZERO) == 1)
                    oneNum = oneNum + 1;
                num = num.shiftRight(1);
            }

            ans = ans.subtract(BigInteger.valueOf(oneNum));
            System.out.println(ans);
        }

    }
}