#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fail(char *pat, int *failure)
{
	failure[0] = -1;
	int i, j;
	int n = strlen(pat);
	for (j = 1; j <= n; j++) {
		i = failure[j - 1];
		while (j >= 0 && pat[j] != pat[i + 1]) {
			i = failure[i + 1];
		}
		if (pat[j] == pat[i + 1]) {
			failure[j] = i + 1;
		} else {
			failure[j] = -1;
		}
	}
}

int pmatch(char *pat, char *s, int *failure)
{
	int plen = strlen(pat);
	int slen = strlen(s);
	int i = 0, j = 0;

	while (i < plen && j < slen) {
		if (pat[i] == pat[j]) {
			i++;
			j++;
		} else if (i == 0) {
			j++;
		} else {
			i = failure[i - 1] + 1;
		}
	}

	return i == plen ? j - plen : -1;
}

int main()
{

	return 0;
}