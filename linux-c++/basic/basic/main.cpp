#include <cstdio>
extern "C" {
    void Socket_exp1();
    void File_exp1();
}
int main()
{
    File_exp1();
    Socket_exp1();
    printf("%s 向你问好!\n", "basic");
    return 0;
}