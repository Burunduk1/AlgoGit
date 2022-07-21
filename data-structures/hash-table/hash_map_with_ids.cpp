#include <vector>
#include <cassert>
#include <cinttypes>

using namespace std;

template<const int MAX_SIZE, class HashType = int>
struct HashMap {
	HashType hash[MAX_SIZE];
	int64_t f[MAX_SIZE];
	int cc, used[MAX_SIZE];
	vector<int> ids;

	HashMap() { 
		cc = 1;
		ids.reserve(MAX_SIZE);
	}
	void clear() { 
		cc++, ids.clear();
	}

	int position(HashType H) const {
		int i = (uint64_t)H * 239017u % MAX_SIZE; 
		while (used[i] == cc && hash[i] != H)
			if (++i == MAX_SIZE)
				i = 0;
		return i;
	}
	bool count(HashType H) const {
		return used[position(H)] == cc;
	}
	int64_t& operator[](HashType H) {
		int i = position(H);
		if (used[i] != cc) {
			used[i] = cc, hash[i] = H, f[i] = 0;
			ids.push_back(i);
			assert((int)ids.size() < MAX_SIZE * 0.9);
		}
		return f[i];
	}
	int size() const { 
		return ids.size(); 
	}
};

using HashTable = HashMap<int(1e6+3), int64_t>;
HashTable s1, s2, newItems;
