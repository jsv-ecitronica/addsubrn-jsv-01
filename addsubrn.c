#include <stdio.h>
#include "addsubrn.h"


int main() {

   char number1[MAX_LEN] = {""};
   char number2[MAX_LEN] = {""};
   char addition[MAX_LEN*2] = {""};
   char subtraction_n1_n2[MAX_LEN*2] = {""};
   char subtraction_n2_n1[MAX_LEN*2] = {""};
   
   printf("*************************************************************");
   printf("\n* Welcome to program for aritmethic of roman numerals !!!");
   printf("\n* Operations available: addition and subtraction");
   printf("\n* Allowed symbols:      i,v,x,l,c,d,m and I,V,X,L,C,D,M ");
   printf("\n* Range of operation:   I to MMMCMXCIX (1 to 3999) ");
   printf("\n* Designed by Javier Soto Vargas - javiersotovargas@gmail.com");
   printf("\n*************************************************************");
   printf("\n");
   
   int code;
   //   
   bool printMsg = true;
   do{
      code = ReadNumber("Please introduce the first Roman Numeral: ", number1);
      if (code == OK) code = ConvertUppercaseValidateChar(number1);
      if (code == OK) code = ValidateRoman(number1, printMsg);
      //printf("\ncode = %d",code);
   }while(code != OK);
   //
   do{
      code = ReadNumber("Please introduce the second Roman Numeral: ", number2);
      if (code == OK) code = ConvertUppercaseValidateChar(number2);
      if (code == OK) code = ValidateRoman(number2, printMsg);
   }while(code != OK);
   //
   printf("\n************************************************");
   code = AddRomanNumerals(number1, number2, addition);
   printf ("\n");
   if (code == OK){
      printf ("\nAddition : %s + %s = %s",number1, number2, addition);
   } else {
      printf ("\nAddition out of range max value is MMMCMXCIX");
   }
   printf("\n************************************************");
   printf ("\n");
   code = SubRomanNumerals(number1, number2, subtraction_n1_n2);
   printf ("\n");
   if (code == OK){
      printf ("\nSubtraction : %s - %s = %s",number1, number2, subtraction_n1_n2);
   } else if (code == SUBTRACTION_IS_ZERO) {
      printf ("\nSubtraction : %s - %s =  ; it is zero, no roman symbol for zero !!!",number1, number2); 
   } else if (code == SUBTRACTION_NOT_POSSIBLE) {
      printf ("\nSubtraction : %s - %s ; it is not possible, negative number !!!",number1, number2); 
   } else {
      printf ("\nSubtraction : %s - %s ; ERROR !!!",number1, number2); 
   }
   //
   printf("\n************************************************");
   printf ("\n");
   code = SubRomanNumerals(number2, number1, subtraction_n2_n1);
   printf ("\n");
   if (code == OK){
      printf ("\nSubtraction : %s - %s = %s",number2, number1, subtraction_n2_n1);
   } else if (code == SUBTRACTION_IS_ZERO) {
      printf ("\nSubtraction : %s - %s =  ; it is zero, no roman symbol for zero !!!",number1, number2); 
   } else if (code == SUBTRACTION_NOT_POSSIBLE) {
      printf ("\nSubtraction : %s - %s ; it is not possible, negative number !!!",number2, number1);
   } else {
      printf ("\nSubtraction : %s - %s ; ERROR !!!",number1, number2); 
   }
   
   printf("\n************************************************");
   printf("\n* End of program !!!");
   printf("\n************************************************");
   printf("\n\n");
   
   return 0;
}


