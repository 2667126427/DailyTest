#include <stdio.h>
int main()
{
    int i, n, s = 1;
    printf("Please enter n:");
    scanf("%d", &n); //1 �������û��ȡ��ַ��
    for (i = 1; i <= n; i++) //2 for�����ǷֺŸ���3����䣬���Ƕ���
        s = s * i;
    printf("%d!=%d\n", n, s);
    return 0;
}
// return 0;//3 return 0;Ӧ����main���Ӧ��������
