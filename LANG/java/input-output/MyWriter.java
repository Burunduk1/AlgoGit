import java.io.*;
		
	static class MyWriter {
		BufferedOutputStream out;

		final int bufSize = 1 << 16;
		int n;
		byte b[] = new byte[bufSize];

		MyWriter( OutputStream out ) {
			this.out = new BufferedOutputStream(out, bufSize);
			this.n = 0;
		}

		byte c[] = new byte[20];
		void print( int x ) throws IOException {
			int cn = 0;
			if (n + 20 >= bufSize)
				flush();
			if (x < 0) {
				b[n++] = (byte)('-');
				x = -x;
			}
			while (cn == 0 || x != 0) {
				c[cn++] = (byte)(x % 10 + '0');
				x /= 10;
			}
			while (cn-- > 0)
				b[n++] = c[cn];
		}

		void print( char x ) throws IOException {
			if (n == bufSize)
				flush();
			b[n++] = (byte)x;
		}

		void print( String s ) throws IOException {
			for (int i = 0; i < s.length(); i++)
				print(s.charAt(i));
		}
		void println( String s ) throws IOException {
			print(s);
			println();
		}

		static final String newLine = System.getProperty("line.separator");
		void println() throws IOException {
			print(newLine);
		}

		void flush() throws IOException {
			out.write(b, 0, n);
			n = 0;
		}
		void close() throws IOException {
			flush();
			out.close();
		}
	}

// MyWriter out = new MyWriter(System.out);
// MyWriter	out = new MyWriter(new FileOutputStream("a.out"));
// out.close(); // don't forget
