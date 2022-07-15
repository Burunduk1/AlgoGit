/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

import java.util.*;
import java.io.*;

public class x_bufreader {
	static public void main(String[] args) throws Exception {
		new x_bufreader().run();
	}
	public void run() throws Exception {
		final String NAME = "meeting";
		BufferedReader in = new BufferedReader(new FileReader(NAME + ".in"));
		PrintWriter out = new PrintWriter(new File(NAME + ".out"));

		out.close();
	}
}
