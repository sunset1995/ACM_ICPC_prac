#include <cstdio>
using namespace std;

long long dis2(long long r1, long long g1, long long b1,
				long long r2, long long g2, long long b2) {
	long long r = r1 - r2;
	long long g = g1 - g2;
	long long b = b1 - b2;
	return r*r + g*g + b*b;
}

int main() {
	const char colorName[16][20] = {
		"White",
		"Silver",
		"Gray",
		"Black",
		"Red",
		"Maroon",
		"Yellow",
		"Olive",
		"Lime",
		"Green",
		"Aqua",
		"Teal",
		"Blue",
		"Navy",
		"Fuchsia",
		"Purple"
	};
	long long c[16][3] = {
		{255, 255, 255},
		{192, 192, 192},
		{128, 128, 128},
		{0,   0,   0  },
		{255, 0,   0  },
		{128, 0,   0  },
		{255, 255, 0  },
		{128, 128, 0  },
		{0,   255, 0  },
		{0,   128, 0  },
		{0,   255, 255},
		{0,   128, 128},
		{0,   0,   255},
		{0,   0,   128},
		{255, 0,   255},
		{128, 0,   128}
	};
	int r, g, b;
	while( scanf("%d%d%d", &r, &g, &b)!=EOF ) {
		if( r==-1 && g==-1 && b==-1 )
			break;
		int minid = 0;
		long long mind = dis2(c[0][0], c[0][1], c[0][2], r, g, b);
		for(int i=1; i<16; ++i) {
			long long nowd = dis2(c[i][0], c[i][1], c[i][2], r, g, b);
			if( nowd < mind ) {
				mind = nowd;
				minid = i;
			}
		}
		puts(colorName[minid]);
	}
	return 0;
}
