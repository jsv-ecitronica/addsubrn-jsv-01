#include <stdio.h>
#include <string.h> 
#include "addsubrn.h"


/********************************************************
*Subtraction of roman nuerals (min - sub)
*Arguments: Minuend (min), Subtrahend (sub) 
*********************************************************/
int SubRomanNumerals(char *min, char *sub, char *ope){
   //
   int code;
   //
   char min_temp[MAX_LEN*2] = {""};
   char sub_temp[MAX_LEN*2] = {""};
   //
   SubstituteSubstractiveValues(min, min_temp);
   SubstituteSubstractiveValues(sub, sub_temp);
   //
   printf("\nSubtraction phase 1, substitute substractive values: minuend - subtrahend = %s - %s", min_temp, sub_temp);
   //
   //Cross symbols
   //
   int i; //iterators   
   char symbol;
   //char symbol_sup;
   int steps = 0;
   int cont = 2;
   while (cont){
      //
      if (sub_temp[0] == '\0') {
         if (min_temp[0] == '\0'){
            code = SUBTRACTION_IS_ZERO;
         } else {
            code = OK;
            for (i=0; i< MAX_LEN*2; i++){
               ope[i] = min_temp[i];
            }
         }
         break;
      }
      if (steps > 6) {
         code = SUBTRACTION_NOT_POSSIBLE;
         break;
      }
      //
      switch(steps){
         case 0: symbol = 'I'; break;
         case 1: symbol = 'V'; break;
         case 2: symbol = 'X'; break;
         case 3: symbol = 'L'; break;
         case 4: symbol = 'C'; break;
         case 5: symbol = 'D'; break;
         case 6: symbol = 'M'; break;
         default: break;   
      }
      //
      //cross-out symbols
      //
      int cont_symbols_min = 0;
      int cont_symbols_sub = 0;
      //
      //int cont_symbols_sup_num1 = 0;
      //int cont_symbols_sup_num2 = 0;
      //
      int index_symbol_min = -1;
      int index_symbol_sub = -1;
      //
      for (i=0; i < MAX_LEN*2; i++){
         if (min_temp[i] == symbol){
            if (index_symbol_min == -1) index_symbol_min = i; 
            cont_symbols_min++;
         }
         //if (min_temp[i] == symbol_sup) cont_symbols_sup_num1++;
         //
         if (sub_temp[i] == symbol){
            if (index_symbol_sub == -1) index_symbol_sub = i;
            cont_symbols_sub++;
         }
         //if (sub_temp[i] == symbol_sup) cont_symbols_sup_num2++;
      }
      //
      if (cont_symbols_min > 0 && cont_symbols_sub > 0){
         //direct cross-out
         int symbols_to_delete = cont_symbols_min;
         if (cont_symbols_sub < cont_symbols_min) 
            symbols_to_delete = cont_symbols_sub;
         //
         while (symbols_to_delete > 0) {
            for (i=index_symbol_min; i < MAX_LEN*2 - 1; i++) {
               min_temp[i] = min_temp[i+1];
            }
            for (i=index_symbol_sub; i < MAX_LEN*2 - 1; i++) {
               sub_temp[i] = sub_temp[i+1];
            }
            symbols_to_delete--;
         }
      } else if (cont_symbols_sub > 0){
         //expand superior symbol in minuend
         int result = SubstituteNextSuperiorOfSymbol(min_temp, symbol);
         if (result == NOK) {
            code = SUBTRACTION_NOT_POSSIBLE;
            break;
         }
      } else if (cont_symbols_sub == 0){
         steps++;
      }
      //
      printf("\nSubtraction phase %d, cross-out symbol '%c': minuend - subtrahend = %s - %s", (cont++), symbol, min_temp, sub_temp); 
   }
   
   if (code == OK){
      SubstituteValuesToSubstractiveValues(ope);
      printf("\nSubtraction phase %d, substitute to substractive values, sub = %s", (cont++), ope);
   }
   return code;

}

/********************************************************
*Substitute Values 
*Example: V = IIIII, X = VV, L = XXXXX, C = LXXXXX
*********************************************************/
int SubstituteNextSuperiorOfSymbol(char *num, char symbol){
//
   //printf("\nSubstitute Values for superior of symbol %c", symbol);
   char temp[MAX_LEN*2] = {""};
   int i,j;
   int index_superior = -1;
   //
   char s1; //for possible superior symbols
   char s2;
   char s3;
   char s4;
   char s5;
   char s6;
   //
   switch(symbol){
      case 'I': s1='V'; s2='X'; s3='L'; s4='C'; s5='D'; s6='M'; break;
      case 'V': s1='-'; s2='X'; s3='L'; s4='C'; s5='D'; s6='M'; break;
      case 'X': s1='-'; s2='-'; s3='L'; s4='C'; s5='D'; s6='M'; break;
      case 'L': s1='-'; s2='-'; s3='-'; s4='C'; s5='D'; s6='M'; break;
      case 'C': s1='-'; s2='-'; s3='-'; s4='-'; s5='D'; s6='M'; break;
      case 'D': s1='-'; s2='-'; s3='-'; s4='-'; s5='-'; s6='M'; break;
      case 'M': s1='-'; s2='-'; s3='-'; s4='-'; s5='-'; s6='-'; break;
      default: break;   
   }
   //
   for (i = MAX_LEN*2 - 1; i >= 0 ; i--){
      if ((num[i]==s1 || num[i]==s2 || num[i]==s3 || num[i]==s4 || num[i]==s5 || num[i]==s6) && num[i] != '\0') {
         index_superior = i;
         break;
      }   
   }
   //printf("\nindex_superior = %d", index_superior);
   if (index_superior == -1) return NOK;
   //
   j=0; //iterator for temp
   //
   for (i = 0; num[i] != '\0'; i++ ){
      if (i == index_superior) {
         if (num[index_superior] == 'V') {
            //replace V with IIIII
            temp[j++] = 'I'; temp[j++] = 'I'; temp[j++] = 'I'; temp[j++] = 'I'; temp[j++] = 'I'; 
         } else if (num[index_superior] == 'X') {
            //replace X with VV
            temp[j++] = 'V'; temp[j++] = 'V';
         } else if (num[index_superior] == 'L') {
            //replace L with XXXXX
            temp[j++] = 'X'; temp[j++] = 'X'; temp[j++] = 'X'; temp[j++] = 'X'; temp[j++] = 'X'; 
         } else if (num[index_superior] == 'C') {
            //replace C with LL
            temp[j++] = 'L'; temp[j++] = 'L';
         } else if (num[index_superior] == 'D') {
            //replace D with CCCCC
            temp[j++] = 'C'; temp[j++] = 'C'; temp[j++] = 'C'; temp[j++] = 'C'; temp[j++] = 'C'; 
         } else if (num[index_superior] == 'M') {
            //replace M with DD
            temp[j++] = 'D'; temp[j++] = 'D';
         }
      } else {
         temp[j++] = num[i];
      } 
   }
   //
   for (i=0; i < MAX_LEN*2 ; i++){
      num[i] = temp[i];
   }
   //
   return OK;
}




/********************************************************
*Addition of roman nuerals
*
*********************************************************/
int AddRomanNumerals(char *num1, char *num2, char *ope){

   //printf("\nAddition");
   char num1_temp[MAX_LEN*2] = {""};
   char num2_temp[MAX_LEN*2] = {""};
   
   SubstituteSubstractiveValues(num1, num1_temp);
   SubstituteSubstractiveValues(num2, num2_temp);
   
   printf("\nAddition phase 1, substitute substractive values, num1 = %s ; num2 = %s", num1_temp, num2_temp);
   //
   //Concatenate and sort
   //
   int steps = 0;
   char symbol;
   int i1 = 0;//iterator for num1_temp
   int i2 = 0;//iterator for num2_temp
   int i3 = 0;//iterator for ope
   while(1){
      switch(steps){
         case 0: symbol = 'M'; break;
         case 1: symbol = 'D'; break;
         case 2: symbol = 'C'; break;
         case 3: symbol = 'L'; break;
         case 4: symbol = 'X'; break;
         case 5: symbol = 'V'; break;
         case 6: symbol = 'I'; break;
         default: break;   
      }
      //
      if (num1_temp[i1] == symbol){
         ope[i3++] = num1_temp[i1++];
      }
      if (num2_temp[i2] == symbol){
         ope[i3++] = num2_temp[i2++];
      }
      if (num1_temp[i1] != symbol && num2_temp[i2] != symbol){
         steps++;
      }
      if (num1_temp[i1] == '\0' && num2_temp[i2] == '\0'){
         break;
      }
   }
   printf("\nAddition phase 2, concatenate and sort, add = %s", ope);
   //
   CombineGroupsOfSymbols(ope);
   printf("\nAddition phase 3, combine groups, add = %s", ope);
   //
   SubstituteValuesToSubstractiveValues(ope);
   printf("\nAddition phase 4, substitute to substractive values, add = %s", ope);
   // 
   int code = ValidateRoman(ope, false);
   printf("\nAddition phase 5, validate range ");
   if (code == OK){
      printf("OK");
   } else {
      printf("NOK");
   }
   //
   return code;
}

/********************************************************
*Substitute to substrative values 
*Example: IIII = IV, VIIII = IX, LXXXX = XC
*********************************************************/
void SubstituteValuesToSubstractiveValues(char *ope){
//
   char temp[MAX_LEN*2] = {""};
   int i,j;
   int cont_symbol = 0;
   //
   i=0;
   for (; i < MAX_LEN*2; i++){
      if(ope[i] == '\0'){
         break;
      }
      cont_symbol++;
   }
   //printf("cont_symbol = %d",cont_symbol);
   //
   i = cont_symbol-1;
   j = 0;
   //
   //Substitute substractives values
   //temp is inverted
   for (; i >= 0; i--){
      if (i >= 4 && ope[i-4]=='V' && ope[i-3]=='I' && ope[i-2]=='I'&& ope[i-1]=='I' && ope[i]=='I') {
         //replace VIIII with IX 
         temp[j++] = 'X'; temp[j++] = 'I';
         i = i-4;
      } else if (i >= 3 && ope[i-3]=='I' && ope[i-2]=='I' && ope[i-1]=='I' && ope[i]=='I') {
         //replace IIII with IV
         temp[j++] = 'V'; temp[j++] = 'I'; 
         i = i-3;
      } else if (i >= 4 && ope[i-4]=='L' && ope[i-3]=='X' && ope[i-2]=='X'&& ope[i-1]=='X' && ope[i]=='X') {
         //replace LXXXX with XC
         temp[j++] = 'C'; temp[j++] = 'X'; 
         i = i-4;
      } else if (i >= 3 && ope[i-3]=='X' && ope[i-2]=='X' && ope[i-1]=='X' && ope[i]=='X') {
         //replace XXXX with XL
         temp[j++] = 'L'; temp[j++] = 'X'; 
         i = i-3;
      } else if (i >= 4 && ope[i-4]=='D' && ope[i-3]=='C' && ope[i-2]=='C'&& ope[i-1]=='C' && ope[i]=='C') {
         //replace DCCCC with CM
         temp[j++] = 'M'; temp[j++] = 'C'; 
         i = i-4;
      } else if (i >= 3 && ope[i-3]=='C' && ope[i-2]=='C' && ope[i-1]=='C' && ope[i]=='C') {
         //replace CCCC with CD
         temp[j++] = 'D'; temp[j++] = 'C'; 
         i = i-3;
      } else {
         //assign symbol directly
         temp[j++] = ope[i];
      }
   }
   //printf("\ntemp = %s",temp);
   //reorder temp and copy to ope
   i=0; j--;
   for (; i <= MAX_LEN*2; i++){
      if (j-i >= 0){
         ope[i] = temp[j-i];
      } else {
         ope[i] = '\0';
      }
   }
   //printf("\ndest_num = %s",dest_num);
}





/********************************************************
*Combine groups of symbols
*Example: IIIII = V, VV = X, CCCCC = D
*********************************************************/
void CombineGroupsOfSymbols(char *ope){

   int steps = 0;
   char symbol;
   //
   while(steps <= 6){
      switch(steps){
         case 0: symbol = 'I'; break;
         case 1: symbol = 'V'; break;
         case 2: symbol = 'X'; break;
         case 3: symbol = 'L'; break;
         case 4: symbol = 'C'; break;
         case 5: symbol = 'D'; break;
         case 6: symbol = 'M'; break;
         default: break;   
      }
      //
      //Calculate repetitions of a symbol
      //
      int index_first = -1;   //first occurrence of symbol
      int cont_symbols = 0;   //number of repetitions of a symbol
      int i;
      for (i = 0; i < MAX_LEN*2; i++){//i iterator
         if (ope[i] == '\0'){
            break;
         }
         if (ope[i] == symbol){
            if (index_first == -1){
               index_first = i; //index to first ocurrence of symbol
            }
            cont_symbols++;
         }
      }
      //
      //replace symbol
      //
      if (symbol == 'I' || symbol == 'X' || symbol == 'C'){
         if (cont_symbols >= 5) {
            if (symbol == 'I') ope[index_first] = 'V';
            if (symbol == 'X') ope[index_first] = 'L';
            if (symbol == 'C') ope[index_first] = 'D';
            //
            for (i = index_first+1; i < MAX_LEN*2; i++){//i iterator from index+1 of first occurrence
               if (i+4 < MAX_LEN*2){
                  ope[i] = ope[i+4];
               } else {
                  ope[i] = '\0';
               }                           
            }
         } else { 
            steps++;
         }
      }
      //
      if (symbol == 'V' || symbol == 'L'|| symbol == 'D'){
         if (cont_symbols >= 2) {
            if (symbol == 'V') ope[index_first] = 'X';
            if (symbol == 'L') ope[index_first] = 'C';
            if (symbol == 'D') ope[index_first] = 'M';
            //
            for (i = index_first+1; i < MAX_LEN*2; i++){//i iterator from index+1 of first occurrence
               if (i+1 < MAX_LEN*2){
                  ope[i] = ope[i+1];
               } else {
                  ope[i] = '\0';
               }                           
            }
         } else { 
            steps++;
         }
      }
      if (symbol == 'M'){
         steps++;
      }       
   }
}




/********************************************************
*Substitute substrative values 
*Example: IV = IIII, IX = VIIII: XC = LXXXX
*********************************************************/
void SubstituteSubstractiveValues(char *ori_num, char *dest_num){
//
   char temp[MAX_LEN*2] = {""};
   int i,j;
   int cont_symbol = 0;
   //
   i=0;
   for (; i < MAX_LEN; i++){
      if(ori_num[i] == '\0'){
         break;
      }
      cont_symbol++;
   }
   //
   i = cont_symbol-1;
   j = 0;
   //printf("\ncont_symbol = %d", cont_symbol);   
   //
   //Substitute substractives values
   //temp is inverted
   for (; i >= 0; i--){
      if (i > 0 && ori_num[i-1] == 'I' && ori_num[i] == 'V') {
         //replace IV with IIII
         temp[j++] = 'I'; temp[j++] = 'I'; temp[j++] = 'I'; temp[j++] = 'I'; 
         i--;
      } else if (i > 0 && ori_num[i-1] == 'I' && ori_num[i] == 'X') {
         //replace IX with VIIII
         temp[j++] = 'I'; temp[j++] = 'I'; temp[j++] = 'I'; temp[j++] = 'I'; temp[j++] = 'V';
         i--;
      } else if (i > 0 && ori_num[i-1] == 'X' && ori_num[i] == 'L') {
         //replace XL with XXXX
         temp[j++] = 'X'; temp[j++] = 'X'; temp[j++] = 'X'; temp[j++] = 'X';
         i--;
      } else if (i > 0 && ori_num[i-1] == 'X' && ori_num[i] == 'C') {
         //replace XC with LXXXX
         temp[j++] = 'X'; temp[j++] = 'X'; temp[j++] = 'X'; temp[j++] = 'X'; temp[j++] = 'L';
         i--;
      } else if (i > 0 && ori_num[i-1] == 'C' && ori_num[i] == 'D') {
         //replace CD with CCCC
         temp[j++] = 'C'; temp[j++] = 'C'; temp[j++] = 'C'; temp[j++] = 'C';
         i--;
      } else if (i > 0 && ori_num[i-1] == 'C' && ori_num[i] == 'M') {
         //replace CM with DCCCC
         temp[j++] = 'C'; temp[j++] = 'C'; temp[j++] = 'C'; temp[j++] = 'C'; temp[j++] = 'D';
         i--;
      } else {
         //assign symbol directly
         temp[j++] = ori_num[i];
      }
   }
   //printf("\ntemp = %s",temp);
   //reorder temp and copy to dest_num
   i=0; j--;
   for (; i <= j ; i++){
      dest_num[i] = temp[j-i];
   }
   //printf("\ndest_num = %s",dest_num);
}




/********************************************************
*Convert to uppercase and validate characters
*
*********************************************************/
int ConvertUppercaseValidateChar(char *num){
   int code = OK;
   int i; //for iterators
   for (i = 0; i < MAX_LEN; i++) {
      if (num[i] == '\0') {
         break;
      } else {
         num[i] = num[i] & 0xdf;
         if (num[i] != 'I' && num[i] != 'V' && num[i] != 'X' && num[i] != 'L' && 
             num[i] != 'C' && num[i] != 'D' && num[i] != 'M'){
            code = CHAR_IS_NO_ROMAN;
            printf ("\nOne or more characters are not roman numerals, please introduce a valid number");
            break;
         }
      }
   }   
   return code;
}

/********************************************************
*Validate roman number.
*Validate secuence of symbols
*********************************************************/
int ValidateRoman (char *num, bool printMsg){
   int code = OK;
   int contConsecutive = 0; //counter for consecutive symbols
   int contI = 0; 
   int contV = 0; 
   int contX = 0; 
   int contL = 0; 
   int contC = 0; 
   int contD = 0;
   int contM = 0; 
   int contOthers = 0; 
   //
   bool p = printMsg;
   //
   int i; //for iterators
   for (i=0; ; i++){
      if (num[i] == '\0') {
         break;
      }
      //
      switch (num[i]){
         case 'I': contI++; break;
         case 'V': contV++; break;
         case 'X': contX++; break;
         case 'L': contL++; break;
         case 'C': contC++; break;
         case 'D': contD++; break;
         case 'M': contM++; break;
         default: contOthers++; break;
      }
      //
      if (i == 0){
         contConsecutive = 1;
      } else {
         if (num[i-1] == num[i]){
            contConsecutive++;
         } else {
            contConsecutive = 1;
         }
         //validate no more than three I,X,C,M
         if (contConsecutive == 4 && (num[i] == 'I' || num[i] == 'X' || num[i] == 'C' || num[i] == 'M')) {
            code = MORE_THAN_THREE_IXCM_ROMAN;
            if(p) printf ("The roman numeral can not contain more than three consecutive symbols: I, X, C or M");
            break;
         }
         //validate no more than one V,L,D
         if (contV > 1 || contL > 1 || contD > 1) {
            code = MORE_THAN_ONE_VLD_ROMAN;
            if(p) printf ("The roman numeral can not contain more than one symbol: V, L or D");
            break;
         }
         //validate possible letters before M
         if (num[i] == 'M') {
            if (contI > 0 || contV > 0 || contX > 0 || contL > 0 || contD > 0){
               if(p) printf("The symbols I, V, X, L or D can not be located to the left of symbol M.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (contC > 1){
               //ejem: ccm
               if(p) printf("The symbols C can not be located to the left of symbol M more than once.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (contConsecutive >= 2 && contC > 0){
               //ejem: cmm
               if(p) printf("The symbol C can not be located to the left of two or more symbols M.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } 
         }
         //validate possible letters before D
         if (num[i] == 'D') {
            if (contI > 0 || contV > 0 || contX > 0 || contL > 0){
               if(p) printf("The symbols I, V, X or L can not be located to the left of symbol D.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (contC > 1){
               //ejem: ccd
               if(p) printf("The symbols C can not be located to the left of symbol D more than once.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (i >= 2 && num[i-1] == 'M' && contC > 0 ){
               //ejem cmdc, cmd
               if(p) printf("The symbol C can not be located to the left of two symbol with higher value.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            }
         } 
         //validate possible letters before C
         if (num[i] == 'C') {
            if (contI > 0 || contV > 0 || contL > 0){
               if(p) printf("The symbols I, V or X can not be located to the left of symbol C.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (contX > 1){
               //ejem: xxc
               if(p) printf("The symbols X can not be located to the left of symbol C more than once.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (contConsecutive >= 2 && contX > 0){
               //ejem: xcc
               if(p) printf("The symbol X can not be located to the left of two or more symbols C.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (i >= 2 && num[i-1] == 'D' && contC > 1 ){
               //ejem cdc
               if(p) printf("The symbol C can not be located to the left and to the rigth of symbol D.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (i >= 2 && num[i-1] == 'M' && contC > 1 ){
               //ejem cmc
               if(p) printf("The symbol C can not be located to the left and to the rigth of symbol M.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            }
         }
         //validate possible letters before L
         if (num[i] == 'L') {
            if (contI > 0 || contV > 0){
               if(p) printf("The symbols I or V can not be located to the left of symbol L.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (contX > 1){
               //ejem: xxl
               if(p) printf("The symbols X can not be located to the left of symbol L more than once.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (i >= 2 && num[i-1] == 'C' && contX > 0 ){
               //ejem xclx, xcl
               if(p) printf("The symbol X can not be located to the left of two symbol with higher value.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            }
         } 
         //validate possible letters before X
         if (num[i] == 'X') {
            if (contV > 0){
               if(p) printf("The symbol V can not be located to the left of symbol X.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (contI > 1){
               //ejem: iix
               if(p) printf("The symbols X can not be located to the left of symbol X more than once.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (contConsecutive >= 2 && contI > 0){
               //ejem: ixx
               if(p) printf("The symbol I can not be located to the left of two or more symbols X.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (i >= 2 && num[i-1] == 'L' && contX > 1 ){
               //ejem xlx
               if(p) printf("The symbol X can not be located to the left and to the rigth of symbol L.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (i >= 2 && num[i-1] == 'C' && contX > 1 ){
               //ejem xcx
               if(p) printf("The symbol X can not be located to the left and to the rigth of symbol C.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            }
         }
         //validate possible letters before V
         if (num[i] == 'V') {
            if (contI > 1){
               //ejem: iiv
               if(p) printf("The symbols I can not be located to the left of symbol V more than once.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            } else if (i >= 2 && num[i-1] == 'X' && contI > 0 ){
               //ejem ixvi, ixv
               if(p) printf("The symbol I can not be located to the left of two symbol with higher value.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            }
         }
         //validate possible letters before I
         if (num[i] == 'I') {
            if (i >= 2 && num[i-1] == 'V' && contI > 1 ){
               //ejem ivi
               if(p) printf("The symbol I can not be located to the left and to the rigth of symbol V.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            }else if (i >= 2 && num[i-1] == 'X' && contI > 1 ){
               //ejem ixi
               if(p) printf("The symbol I can not be located to the left and to the rigth of symbol X.");
               code = SYNTAX_ERROR_ROMAN;
               break;
            }
         } 
      }
      
   }
   //
   return code;

}
/********************************************************
*Read numbers function
*
*
*
*********************************************************/
int ReadNumber(char *msg, char *num){
   int code;
   //printf("\nStarting ReadNumber function");
   //char buff[MAX_LEN];

   code = GetLine (msg, num, MAX_LEN);
   if (code == NO_INPUT) {
       
   }else if (code == TOO_LONG){
      printf ("\nThe maximun length is %d, the number was cutted !!!",(MAX_LEN-1));
      //printf ("\nNumber: %s",buff);
      code = OK;
   }else if (code == OK){
      //printf ("\nNumber: %s",buff);
   }else{
      printf ("\nUndefined number option !!!");
   }
   return code;           
}
/********************************************************
*get line function
*
//Reference: 
//http://stackoverflow.com/questions/4023895/how-to-read-string-entered-by-user-in-c 
*********************************************************/
int GetLine (char *msg, char *num, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (msg != NULL) {
        printf ("\n%s", msg);
        fflush (stdout);
        
    }
    if (fgets (num, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (num[strlen(num)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    num[strlen(num)-1] = '\0';
    return OK;
}
