import java.io.*;
import java.util.*;
import java.math.*;

class Main {
	public static BigInteger bigSqrt(BigInteger n) {
	    BigInteger a = BigInteger.ONE;
	    BigInteger b = n.shiftRight(1).add(BigInteger.valueOf(2));
	    while (b.compareTo(a) >= 0) {
	        BigInteger mid = a.add(b).shiftRight(1);
	        if (mid.multiply(mid).compareTo(n) > 0)
	            b = mid.subtract(BigInteger.ONE);
	        else
	            a = mid.add(BigInteger.ONE);
	    }
	    return a.subtract(BigInteger.ONE);
	}

	public static void main(String[] args) {
		Scanner scn = new Scanner(System.in);
		int caseNum = scn.nextInt();
		for (int t = 0; t < caseNum; t++) {
			BigInteger jessie = scn.nextBigInteger();
			BigInteger justin = jessie.multiply(jessie).subtract(jessie).shiftRight(1);

			BigInteger jessieSqrt = bigSqrt(jessie);
			BigInteger justinSqrt = bigSqrt(justin);

			Boolean jessieIsSq = false, justinIsSq = false;

			if (jessieSqrt.multiply(jessieSqrt).compareTo(jessie) == 0) {
				jessieIsSq = true;
			}

			if (justinSqrt.multiply(justinSqrt).compareTo(justin) == 0) {
				justinIsSq = true;
			}

			if (jessieIsSq) {
				if (justinIsSq) {
					System.out.println("Arena of Valor");
				} else {
					System.out.println("Hearth Stone");
				}
			} else {
				if (justinIsSq) {
					System.out.println("Clash Royale");
				} else {
					System.out.println("League of Legends");
				}
			}
		}
 	}
}