/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

import java.util.*;
import java.io.*;

public class x_tokenizer {
    StreamTokenizer in;
    int nextInt() throws IOException {
        in.nextToken();
        return (int)in.nval;
    }
    String next() throws IOException {
        in.nextToken();
        return in.sval;
    }

    static public void main(String[] args) throws Exception {
        new x_tokenizer().run();
    }
    public void run() throws Exception {
        final String NAME = "sum";
        in = new StreamTokenizer(new BufferedReader(new FileReader(NAME + ".in")));
        PrintWriter out = new PrintWriter(new File(NAME + ".out"));

        int a = nextInt();
        int b = nextInt();
        out.println(a + b);

        out.close();
    }
}
