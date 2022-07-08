const double TL = 3.0; // seconds

bool checkTL() {
	static int cnt = 0, isTL = 0;
	if (++cnt == 10000) 
		cnt = 0, isTL |= clock() > (TL - 0.1) * CLOCKS_PER_SEC;
	return isTL;
}
