        int curChar() throws IOException {
            if (bn == k) {
                k = in.read(b, 0, bufSize);
                bn = 0;
            }
            return bn >= k ? -1 : b[bn];
        }
        boolean seekEof() throws IOException {
        	while (curChar() != -1 && curChar() <= 32)
        		nextChar();
        	return curChar() == -1;
        }
