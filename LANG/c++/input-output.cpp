#include <cstdio>

const int bufs_len = 1 << 13;

int rbuf_pos, rbuf_len;
unsigned char rbuf[bufs_len];

int readChar() {
	if (rbuf_pos == rbuf_len)
		rbuf_pos = 0, rbuf_len = fread(rbuf, 1, bufs_len, stdin);
	if (rbuf_pos == rbuf_len)
		return -1; // end of file
	return rbuf[rbuf_pos++];
}

int readInt() {
	int x = 0, c = readChar(), neg = 0;
	while (c != -1 && c < 32)
		c = readChar();
	if (c == '-')
        neg = 1, c = readChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = readChar();
	return neg ? -x : x;
}

void readWord(char *s) {
	int c = readChar(), n = 0;
	while (c != -1 && c < 32)
		c = readChar();
	while (c > 32)
		s[n++] = c, c = readChar();
	s[n] = 0;
}

int wbuf_pos;
unsigned char wbuf[bufs_len];

struct Flusher {
	~Flusher() {
		if (wbuf_pos > 0)
			fwrite(wbuf, 1, wbuf_pos, stdout), wbuf_pos = 0;
	}
} _flusher;

void writeChar(int c) {
	wbuf[wbuf_pos++] = c;
	if (wbuf_pos == bufs_len)
		fwrite(wbuf, 1, wbuf_pos, stdout), wbuf_pos = 0;
}

void writeInt(int x, char end = 0) {
	if (x < 0)
		writeChar('-'), x = -x;
	char s[20];
	int pos = 0;
	while (!pos || x)
		s[pos++] = '0' + x % 10, x /= 10;
	while (pos--)
		writeChar(s[pos]);
	if (end)
		writeChar(end);
}
