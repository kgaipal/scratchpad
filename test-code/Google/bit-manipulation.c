/* http://www.somacon.com/p125.php */
#include <stdio.h>

int main()
{
	int a = 1;
	int b = 0x23;
	int c = 3;

	printf("%d %x %d\n", ~1, 3, 3);
	/* printf("%d %d %d %d\n", a|b|c, a&b&c, a^b^c, ~c); */
	/* printf("%d %d\n", a||b||c, a&&b&&c); */

	return 0;
}
