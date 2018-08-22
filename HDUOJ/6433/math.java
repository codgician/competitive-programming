import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner (new BufferedInputStream(System.in));
        int caseNum = scanner.nextInt();
        for (int t = 0; t < caseNum; t++) {
            int num = scanner.nextInt();
            BigInteger ans = BigInteger.valueOf(2);
            ans = ans.pow(num);
            System.out.println(ans);
        }
    }
}