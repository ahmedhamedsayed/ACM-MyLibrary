import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class ProblemB {

	public static int n, k, tst = 0;
	public static BigInteger[][][] memo;
	public static BigInteger[][] save;

	static BigInteger solve(int rem, int cnt, int isK) {
		if (rem == 0) {
			if (isK == 1 && cnt == 0)
				return BigInteger.ONE;
			return BigInteger.ZERO;
		}
		if (memo[rem][cnt][isK] != null) {
			return memo[rem][cnt][isK];
		}
		BigInteger ret = new BigInteger("0");
		if (cnt < k) {
			int nxtK = ((cnt + 1 == k) | (isK == 1)) ? 1 : 0;
			ret = ret.add(solve(rem - 1, cnt + 1, nxtK));
		}
		if (cnt > 0) {
			ret = ret.add(solve(rem - 1, cnt - 1, isK));
		}
		return memo[rem][cnt][isK] = ret;
	}

	public static void preCalc() {
		save = new BigInteger[51][51];
		for (int j = 1; j <= 50; ++j) {
			memo = new BigInteger[101][51][2];
			for (int i = j; i <= 50; ++i) {
				n = i;
				k = j;
				save[n][k] = solve(2 * n, 0, 0);
			}
		}
	}

	public static void main(String[] args) throws IOException {
		preCalc();
		boolean enter = false;
		BufferedReader in = new BufferedReader(new FileReader("brackets.in"));
		PrintWriter out = new PrintWriter(new FileWriter("brackets.out"));
		while (true) {
			StringTokenizer input = new StringTokenizer(in.readLine());
			n = Integer.valueOf(input.nextToken());
			k = Integer.valueOf(input.nextToken());
			if (n == 0 && k == 0)
				break;
			if (enter)
				out.print("\n");
			enter = true;
			out.println("Case " + ++tst + ": " + save[n][k]);
		}
		out.close();
		in.close();
	}
}
