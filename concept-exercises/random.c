#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_CTYPE, "");
	wprintf(L"%lc\n", 0x241A);
}
