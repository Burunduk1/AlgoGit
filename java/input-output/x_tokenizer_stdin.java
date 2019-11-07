/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

import java.util.*;
import java.io.*;

public class x_tokenizer_stdin {
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
        new x_tokenizer_stdin().run();
    }
    public void run() throws Exception {
        in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        PrintWriter out = new PrintWriter(System.out);

        int a = nextInt();
        int b = nextInt();
        out.println(a + b);

        out.close();
    }
}
