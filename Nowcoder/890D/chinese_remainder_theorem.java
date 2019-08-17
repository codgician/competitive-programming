import java.io.*;
import java.util.*;
import java.math.*;
 
public class Main {
    static BigInteger mods[] = new BigInteger[1010];
    static BigInteger csts[] = new BigInteger[1010];
 
    static BigInteger x, y;
 
    public static BigInteger extEuclid(BigInteger a, BigInteger b) {
        if (b.compareTo(BigInteger.ZERO) == 0) {
            x = BigInteger.ONE; y = BigInteger.ZERO;
            return a;
        }
        BigInteger gcd = extEuclid(b, a.mod(b));
        BigInteger tmp = x;
        x = y; y = tmp.subtract(y.multiply(a.divide(b)));
        return gcd;
    }
 
    public static BigInteger crt(int equNum) {
        BigInteger modProd = mods[0], ans = csts[0];
        for (int i = 1; i < equNum; i++) {
            BigInteger a = modProd, b = mods[i];
            BigInteger c = (csts[i].subtract(ans.mod(b)).add(b)).mod(b);
            BigInteger gcd = extEuclid(a, b);
            BigInteger bg = b.divide(gcd);
 
            if (c.mod(gcd).compareTo(BigInteger.ZERO) != 0) {
                return BigInteger.valueOf(-1);
            }
 
            BigInteger cntAns = c.divide(gcd).mod(bg).multiply(x).mod(bg).add(bg).mod(bg);
            ans = ans.add(modProd.multiply(cntAns));
            modProd = modProd.multiply(bg);
        }
 
        return ans.mod(modProd).add(modProd).mod(modProd);
    }
 
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        int equNum = scn.nextInt(); BigInteger lim = scn.nextBigInteger();
        for (int i = 0; i < equNum; i++) {
            mods[i] = scn.nextBigInteger();
            csts[i] = scn.nextBigInteger();
        }
 
        BigInteger ret = crt(equNum);
        if (ret.compareTo(BigInteger.ZERO) == -1) {
            System.out.println("he was definitely lying");
        } else if (ret.compareTo(lim) == 1) {
            System.out.println("he was probably lying");
        } else {
            System.out.println(ret);
        }
    }
}