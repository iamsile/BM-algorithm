//
//  main.cpp
//  BM algorithm
//
//  Created by taowei on 13-12-11.
//  Copyright (c) 2013年 taowei. All rights reserved.
//

#include <iostream>
#include <string.h>
using namespace std;

void calBmBc(char *pattern, int m, int bmBc[]) {
	int i;
	for (i = 0; i < 256; i++)
		bmBc[i] = m;
	for (i = 0; i < m - 1; i++)
		bmBc[pattern[i]] = m - 1 - i;
}

void suffix(char *pattern, int m, int suff[]) {
	int f , g, i;
	suff[m - 1] = m;
	///f = 0;
	g = m -1;
	for (i = m - 2; i >= 0; i--)
		if (i > g && suff[i + m - 1 - f] < i - g)
			suff[i] = suff[i + m - 1 - f];
		else {
			if (i < g)
				g = i;
			f = i;
			while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
				g--;
			suff[i] = f - g;
		}
}

void calBmGs(char *pattern, int m, int bmGs[]) {
	int i, j, suff[256];
	suffix(pattern, m, suff);
	for (i = 0; i < m; i++)
		bmGs[i] = m;
	for (i = m - 1, j = 0; i >= 0; i--)
		if (suff[i] == i + 1) {
			for (; j < m - 1 - i; j++)
				if (bmGs[j] == m)
					bmGs[j] = m - 1 - i;
		}
	for (i = 0; i <= m - 2; i++)
		bmGs[m - 1 - suff[i]] = m - 1 - i;
}

void BoyerMoore(char *pattern, int m, char *text, int n) {
	int i, j = 0, bmBc[256], bmGs[256];
	calBmBc(pattern, m, bmBc);
	calBmGs(pattern, m, bmGs);

	while (j <= n - m) {
		for (i = m -1; i >= 0 && pattern[i] == text[i + j]; i--);
			if (i < 0) {
				printf("good! the position is %d\n", j);
				j += bmGs[0];
				return;
			} else
				j += max(bmBc[text[i + j]] - m + 1 + i, bmGs[i]);
	}
	printf("No!\n");
}

int main(int argc, const char * argv[])
{
	char a[1000],b[1000];
	while (scanf("%s%s",a,b) != EOF) {
		if (!strlen(a)&&!strlen(b))
			return 0;
		BoyerMoore(b, strlen(b), a, strlen(a));
	}
	return 0;
}

