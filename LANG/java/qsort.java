import java.util.Random;

public class X {
    int key[];

	int compare( int x, int y ) {
		return key[x] < key[y] ? -1 : (key[x] > key[y] ? 1 : 0);
	}

	static Random rand = new Random();

	void qsort( int p[], int l, int r ) {
		if (l >= r) {
			return;
		}
		int i = l, j = r, x = p[l + rand.nextInt(r - l)];
		while (i <= j) {
			while (compare(p[i], x) < 0) i++;
			while (compare(p[j], x) > 0) j--;
			if (i <= j) {
				int tmp = p[i]; p[i] = p[j]; p[j] = tmp;
				i++;
				j--;
			}
		}
		qsort(p, l, j);
		qsort(p, i, r);
	}
}
