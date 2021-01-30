#include <cstdio>
extern "C" {
    void Socket_exp1();
}
int main()
{
    Socket_exp1();
    printf("%s 向你问好!\n", "basic");
    return 0;
}