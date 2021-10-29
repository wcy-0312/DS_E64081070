#include <stdio.h>

int Fibonacci_recursive(int i);
int Fibonacci_iterative(int n);

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", Fibonacci_recursive(n));
    printf("%d\n", Fibonacci_iterative(n));

    return (0);
}

int Fibonacci_recursive(int i)
{
    if (i == 0)
        return 0;
    else if (i == 1)
        return 1;
    else
        return Fibonacci_recursive(i - 1) + Fibonacci_recursive(i - 2);
}

int Fibonacci_iterative(int n)
{
    int a = 0, b = 1, temp;
    for (int i = 1; i < n; i++)
    {
        temp = b;
        b = a + b;
        a = temp;
    }

    return b;
}