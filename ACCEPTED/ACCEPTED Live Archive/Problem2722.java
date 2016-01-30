import java.math.BigInteger;
import java.util.Scanner;

public class Problem2722 {
	public static StringBuilder x, y, tx;
	public static int mx;

	public static String convertToBin(String cur) {
		String ret = "";
		BigInteger bin = new BigInteger(cur);
		while (bin != BigInteger.ZERO) {
			ret = (!bin.testBit(0) ? "0" : "1") + ret;
			bin = bin.shiftRight(1);
		}
		return ret.substring(1);
	}

	public static BigInteger convertToDec(String cur) {
		BigInteger two = new BigInteger("2");
		BigInteger ret = new BigInteger("0");
		int power = 0;
		for (int i = cur.length() - 1; i >= 0; --i) {
			if (cur.charAt(i) == '1')
				ret = ret.add(two.pow(power));
			++power;
		}
		return ret;
	}

	public static void change(int rem) {
		for (int i = 0; i < 2; ++i) {
			if (rem - i >= 0) {
				String str = ((x.charAt(rem - i) == '0') ? "1" : "0");
				x = x.replace(rem - i, rem - i + 1, str);
			}
		}
	}

	public static BigInteger inStart(int rem, String ret) {
		BigInteger ret1 = getRet(rem - 1, false, "0" + ret);
		change(rem);
		BigInteger ret2 = getRet(rem - 1, false, "1" + ret);
		if (ret1.equals(new BigInteger("-1")))
			return ret2;
		else if (ret2.equals(new BigInteger("-1")))
			return ret1;
		else
			return ((ret1.compareTo(ret2) < 0) ? ret1 : ret2);
	}

	public static BigInteger getRet(int rem, boolean start, String ret) {
		if (rem == -1) {
			if (x.toString().equals(y.toString())) {
				x = tx;
				return convertToDec(ret);
			} else {
				x = tx;
				return new BigInteger("-1");
			}
		}
		if (start) {
			return inStart(rem, ret);
		} else if (x.charAt(rem + 1) == y.charAt(rem + 1)) {
			return getRet(rem - 1, false, "0" + ret);
		} else {
			String str = ((x.charAt(rem + 1) == '0') ? "1" : "0");
			x = x.replace(rem + 1, rem + 2, str);
			change(rem);
			return getRet(rem - 1, false, "1" + ret);
		}
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		String a, b;
		int tst = 0;
		boolean enter = false;
		while (true) {
			a = in.next();
			b = in.next();
			if (a.equals("0") && b.equals("0"))
				break;
			if (enter)
				System.out.println("");
			enter = true;
			String X = convertToBin(a);
			String Y = convertToBin(b);
			int len1 = X.length(), len2 = Y.length();
			mx = Math.max(len1, len2);
			for (int i = 0; i < mx - len1; ++i)
				X = "0" + X;
			for (int i = 0; i < mx - len2; ++i)
				Y = "0" + Y;
			x = new StringBuilder(X);
			y = new StringBuilder(Y);
			tx = new StringBuilder(x);
			BigInteger ret = getRet(mx - 1, true, "");
			System.out.print("Case Number " + (++tst) + ": ");
			if (ret.toString().equals("-1"))
				System.out.println("impossible");
			else
				System.out.println(ret);
		}
		in.close();
	}
}