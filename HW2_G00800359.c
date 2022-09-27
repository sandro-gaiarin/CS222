#include <stdio.h>
int get_input(); //prompt user for an int and return int to main()
int compute_sum(int val); //display each multiple of 3 or 5, return sum of printed numbers

int main() {
   int userNum = 0;
   int resultSum = 0;
   userNum = get_input();
   if (userNum != 0) {
      resultSum = compute_sum(userNum);
   
      printf("Sum of all multiples of 3 or 5 is %d", resultSum);
   }
}

int get_input() {
   int n = 0;
   printf("Enter an integer [1, 999999]");
   scanf("%d", &n);
   if (n > 999999 || n < 1) {
      printf("Number out of range");
      return 0;
   }
   return n;
}

int compute_sum(int val) {
   int i;
   int sum = 0;
   for (i = 0; i < val; i++) {
      if (i % 3 == 0 || i % 5 == 0) {
            printf("%d", i);
            sum += i;
      }
   }
   return sum;
}