template <class T>
T** init( int h, int w ) {
  T** s = new T*[h];
  s[0] = new T[h * w]();
  for (int j = 1; j < h; j++)
    s[j] = s[j - 1] + w;
  return s;
}
