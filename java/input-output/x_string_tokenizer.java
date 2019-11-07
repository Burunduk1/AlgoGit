/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

import java.util.*;
import java.io.*;

public class x_string_tokenizer {
	StringTokenizer tok = new StringTokenizer("");
	BufferedReader in;

	String next() throws IOException {
		while (!tok.hasMoreElements())
			tok = new StringTokenizer(in.readLine());
		return tok.nextToken();
	}
	int nextInt() throws IOException {
		return Integer.parseInt(next());
	}

	static public void main(String[] args) throws Exception {
		new x_string_tokenizer().run();
	}
	public void run() throws Exception {
		final String NAME = "sum";
		in = new BufferedReader(new FileReader(NAME + ".in"));
		PrintWriter out = new PrintWriter(new File(NAME + ".out"));

		int a = nextInt();
		int b = nextInt();
		out.println(a + b);

		out.close();
	}
}
