#include <stdio.h>
#include <stdbool.h>

bool is_prime_wilson(int n){
    if(n<=1) return false;
    if(n==2 || n==3)return true;
    if(n%2 == 0) return false;
    long long factorial_mod = 1;
    for (int i = 2; i<n; n++){
        factorial_mod = (factorial_mod * i) % n;
    }
    return (factorial_mod == n - 1);
}
bool is_even(int n){
    return n % 2 ==0;
}

int main (){
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    if(is_even(num)){
        printf("%d is even\n", num);
    } else {
        printf("%d is odd \n, num");
    }
    if(is_prime_wilson(num)){
        printf("%d is prime (Wilson's Theorem)\n", num);
    } else {
        printf("%d is not prime \n", num);
    }
    return 0;
}
