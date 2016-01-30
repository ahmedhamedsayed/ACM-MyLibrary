import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class ProblemA {
	public static int m, p, sz;
	public static BigInteger n;
	public static int[][] matrix;

	public static void matrixPow() {
		int inc[][] = new int[sz][sz];
		for (int i = 0; i < sz; ++i)
			inc[i][i] = 1;
		n = n.subtract(BigInteger.ONE);
		while (n.compareTo(BigInteger.ZERO) > 0) {
			if (n.testBit(0))
				inc = matrixMul(inc, matrix);
			n = n.shiftRight(1);
			matrix = matrixMul(matrix, matrix);
		}
		matrix = inc;
	}

	public static int[][] matrixMul(int[][] a1, int[][] a2) {
		int[][] ret = new int[sz][sz];
		for (int i = 0; i < sz; ++i) {
			for (int j = 0; j < sz; ++j) {
				int cur = 0;
				for (int k = 0; k < sz; ++k)
					cur = (cur + (a1[i][k] * a2[k][j])) % p;
				ret[i][j] = cur;
			}
		}
		return ret;
	}

	public static int check(int i, int j) {
		for (int k = 0; k < m - 1; ++k) {
			int bit1 = (i >> (k + 0)) & 1;
			int bit2 = (i >> (k + 1)) & 1;
			int bit3 = (j >> (k + 0)) & 1;
			int bit4 = (j >> (k + 1)) & 1;
			if (bit1 == bit2 && bit2 == bit3 && bit3 == bit4)
				return 0;
		}
		return 1;
	}

	public static void fillMatrix() {
		for (int i = 0; i < sz; ++i)
			for (int j = 0; j < sz; ++j)
				matrix[i][j] = check(i, j);
	}

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("nice.in"));
		StringTokenizer input = new StringTokenizer(in.readLine());
		in.close();
		n = new BigInteger(input.nextToken());
		m = Integer.valueOf(input.nextToken());
		p = Integer.valueOf(input.nextToken());
		sz = 1 << m;
		matrix = new int[sz][sz];
		fillMatrix();
		matrixPow();
		int ret = 0;
		for (int i = 0; i < sz; ++i)
			for (int j = 0; j < sz; ++j)
				ret = (ret + matrix[i][j]) % p;
		PrintWriter out = new PrintWriter(new FileWriter("nice.out"));
		out.println(ret);
		out.close();
	}
}
