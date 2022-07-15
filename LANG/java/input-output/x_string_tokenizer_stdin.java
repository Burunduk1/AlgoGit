/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

import java.util.*;
import java.io.*;

public class x_string_tokenizer_stdin {
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
		new x_string_tokenizer_stdin().run();
	}
	public void run() throws Exception {
		in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);

		int a = nextInt();
		int b = nextInt();
		out.println(a + b);

		out.close();
	}
}
