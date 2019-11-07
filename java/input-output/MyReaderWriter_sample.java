/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

import java.util.*;
import java.io.*;
import java.math.*;

public class x_fast {
	static public void main(String[] args) throws Exception {
		new x_fast().run();
	}
	public void run() throws Exception {
		final String NAME = "meeting";
		MyReader in = new MyReader(new FileInputStream(NAME + ".in"));
		MyWriter out = new MyWriter(new FileOutputStream(NAME + ".out"));

		int n = in.nextInt();
		out.print(n);
		for (int i = 0; i < n; i++) {
			out.println();
			out.print(in.nextWord());
		}
		out.close();
	}
}
