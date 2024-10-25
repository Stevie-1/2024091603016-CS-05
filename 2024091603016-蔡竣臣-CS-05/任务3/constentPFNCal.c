#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <math.h>

typedef struct PointFixedNumber{
    char system; 
    char sign;
    char fraction[130];
    char integer[130];
}PFN; 

/**头文件 <stdio.h> <string.h> */
void halfGetExpression(PFN *pfn2, char *operator, FILE *fp){

    char expression[263]; 

    fscanf(fp, "%[^\n]", expression); 
    fgetc(fp);
    if (expression[0] == '0' && expression[1] == '\0'){
        return;
    }


    int location = 0;
    int carry = 0;

    //获取运算符
    *operator = expression[location];
    location++; 
    carry = location;

    //获取第二个定点数的整数部分
    while (expression[location] != '.'){
        pfn2->integer[location-carry] = expression[location];
        location++;
    } 
    pfn2->integer[location-carry] = '\0'; // pfn2->integer的终止 

    int i = 0;
    while (1){ //pfn2->integer的前置空格
        if (pfn2->integer[i] == ' '){
            i++;
        }
        else{
            break;
        }
    } 
    char *tmp;
    tmp = pfn2->integer + i; 
    strcpy(pfn2->integer, tmp);

    if (pfn2->integer[0] == '('){
        pfn2->sign = '-'; 
        char *tmp; 
        tmp = pfn2->integer + 2;
        strcpy(pfn2->integer, tmp);
    }
    else{
        pfn2->sign = '\0';
    }
    location++; 
    carry = location;



    //获取第二个定点数的小数部分
    while (expression[location]!= '\0'){
        pfn2->fraction[location-carry] = expression[location];
        location++;
    } 


    if (pfn2->fraction[location-carry-1] == ')'){ //pfn2->fraction的终止 
        pfn2->system = pfn2->fraction[location-2-carry];
        pfn2->fraction[location-carry-2] = '\0';
    } 
    else{ 
        pfn2->system = pfn2->fraction[location-carry-1];
        pfn2->fraction[location-carry-1] = '\0';
    } 
}

void getOperation(char *operator, FILE *fp){
    *operator = fgetc(fp);
    fgetc(fp); 
    return;
}

/**头文件 <stdio.h> <string.h>;   
 * 
 * @brief 将二进制数的整数部分转换为十进制数 
 * 
 * @param binary 一个指向字符数组的指针，存储二进制数的整数部分 
 * 
 * @return 无返回值
 */
void binaryToDecimal_Integer(char *binary) {
    int decimal = 0;
    int length = strlen(binary);
    for (int i = 0; i < length; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            printf("Invalid binary number.\n");
            return; 
        }
        decimal = decimal * 2 + (binary[i] - '0'); 
    } 
    sprintf(binary, "%d", decimal);
    return;
} 

/**头文件 <stdio.h> <string.h> <stdlib.h> <math.h>；
 * 
 * @brief 将二进制数的小数部分转换为十进制数 
 * 
 * @param fraction 一个指向字符数组的指针，存储二进制数的小数部分 
 * 
 * @return 无返回值
*/
void binaryToDecimal_Traction(char *fraction) {
    double tmp = 0;
    int length = strlen(fraction); 

    for (int i = 0; i < length; i++) { 
        tmp += (fraction[i] - '0') * pow(2, -i-1);
    } 

    for (int i = 0; ;i++){
        tmp *= 10; 
        if ((int)tmp == tmp){ 
            break;
        }

    } 
    sprintf(fraction, "%d", (int)tmp);   
    return;
}

/**头文件 <stdio.h> <string.h> 
 * 
 * @brief 初始化一个定点数并将其转换为十进制数
 * 
 * @param pfn 一个指向PFN结构体的指针
 * 
 * @return 无返回值
*/
void initPFNAndStoreInDecimal(PFN *pfn, FILE *fp){
    char tmpInteger[130] = "0";
    char tmpFraction[130] = "0";
    char system; 
    char sign = '\0'; 
    char string[130]; 
    int carry_1 = 0; 
    int carry_2 = 0;
    int location = 0;
    

    fscanf(fp, "%s", string); 
    fgetc(fp);

    if (string[0] == '-')  {
        sign = string[0]; 
        location++; 
        carry_1++;
    } 
    
    while (string[location] != '.'){ 
        tmpInteger[location-carry_1] = string[location];
        location++; 
        carry_2++;
    } 
    tmpInteger[location-carry_1] = '\0';
    location++; 
    carry_2++;
    while (string[location] != 'B' && string[location]!= 'D'){
        tmpFraction[location-carry_1-carry_2] = string[location];
        location++;
    } 
    tmpFraction[location-carry_1-carry_2] = '\0';
    system = string[location];
    strcpy(pfn->integer, tmpInteger); 
    strcpy(pfn->fraction, tmpFraction);
    pfn->system = system; 
    pfn->sign = sign;




    if (system != 'D'){ 
        if (system == 'B'){
            binaryToDecimal_Integer(pfn->integer);
            binaryToDecimal_Traction(pfn->fraction); 
            pfn->system = 'D';
        }
        else{
            printf("请输入二进制或十进制数。\n");
        }
    }
}

/**头文件 <stdio.h> <string.h>;   全局变量 PFN
 * 
 * @brief 初始化一个定点数并将其转换为十进制数
 * 
 * @param pfn 一个指向PFN结构体的指针
 * 
 * @return 无返回值
*/
void PFNStoredInDecimal(PFN *pfn){
    char tmpInteger[130] = "0";
    char tmpFraction[130] = "0";
    char system; 
    char sign = '\0'; 
    char string[130]; 
    int carry_1 = 0; 
    int carry_2 = 0;
    int location = 0;
    
    sprintf(string, "%c%s.%s%c", pfn->sign, pfn->integer, pfn->fraction, pfn->system); 


    if (string[0] == '-')  {
        sign = string[0]; 
        location++; 
        carry_1++;
    }
    else{
        sign = string[0]; 
        string[0] = '+';
        char *temp = string; 
        strcpy(string, ++temp);
    }
    
    while (string[location] != '.'){ 
        tmpInteger[location-carry_1] = string[location];
        location++; 
        carry_2++;
    } 
    tmpInteger[location-carry_1] = '\0';
    location++; 
    carry_2++;
    while (string[location] != 'B' && string[location]!= 'D'){
        tmpFraction[location-carry_1-carry_2] = string[location];
        location++;
    } 
    tmpFraction[location-carry_1-carry_2] = '\0';
    system = string[location];
    strcpy(pfn->integer, tmpInteger); 
    strcpy(pfn->fraction, tmpFraction);
    pfn->system = system; 
    pfn->sign = sign;




    if (system != 'D'){ 
        if (system == 'B'){
            binaryToDecimal_Integer(pfn->integer);
            binaryToDecimal_Traction(pfn->fraction); 
            pfn->system = 'D';
        }
        else{
            printf("请输入二进制或十进制数。\n");
        }
    }
}

/**头文件<stdio.h>;   全局变量 PFN 
 * 
 * @brief 打印一个定点数
 * 
 * @param pfn 一个PFN结构体，存储要打印的定点数
 * 
 * @return 无返回值
*/
void printPFN(PFN pfn){
    printf("%c%s.%s%c\n", pfn.sign, pfn.integer, pfn.fraction, pfn.system);
}

/**头文件 <stdio.h> <malloc.h> 
 * @brief 该函数输入一个字符串数组的指针，释放其内存
 * 
 * @param char *bigNumber 输入一个字符串数组的指针
 * 
 * @return void 无参数输出
 */
void freeBigNumberPtr(char *bigNumber){
    free(bigNumber); 
    bigNumber = NULL; 
    return;
}

/**头文件 <stdio.h> <stdlib.h> <string.h>
 * @brief 该函数输入两个字符串数组的指针，将其相加，并返回一个指向和的字符串数组的指针
 * 
 * @param char *bigNumber1 输入一个字符串数组的指针 
 * @param char *bigNumber2 输入一个字符串数组的指针
 * 
 * @return char * 一个指向和的字符串数组的指针
 */
char *bigNumberAdd(char *bigNumber1, char *bigNumber2){    
        int length1 = strlen(bigNumber1); 
        int length2 = strlen(bigNumber2); 
        int carry = 0;
        int maxLength = length1 > length2 ? length1 : length2; 
        char *result = malloc((maxLength + 2) * sizeof(char)); 
        if (result == NULL) {
            printf("内存分配失败，程序错误\n");
            return NULL;
        }
        result[maxLength + 1] = '\0'; 

        for (int i = 0; i <= maxLength; i++) {
            int num1 = i < length1 ? bigNumber1[length1 - 1 - i] - '0' : 0; 
            int num2 = i < length2 ? bigNumber2[length2 - 1 - i] - '0' : 0; 
            int sum = num1 + num2 + carry;
            carry = sum / 10; 
            result[maxLength - i] = (sum % 10) + '0'; 
        }

        for (int i = 0; i < maxLength;) { 
            if (result[i] == '0'){
                result++;
            }
            else{
                break;
            }
        } 
        if (result[0] == '\0'){
            result[0] = '0'; 
            result[1] = '\0';
        }
        return result;         
}

/**头文件 <stdio.h> <stdlib.h> <string.h>
 * @brief 该函数输入两个字符串数组的指针，将其相减，并返回一个指向和的字符串数组的指针
 * 
 * @param char *bigNumber1 输入一个字符串数组的指针，作为被减数 
 * @param char *bigNumber2 输入一个字符串数组的指针，作为减数
 * 
 * @return char * 一个指向和的字符串数组的指针
 */
char *bigNumberSub(char *bigNumber1, char *bigNumber2){             
        int length1 = strlen(bigNumber2); 
        int length2 = strlen(bigNumber1); 
        
        if (length1 > length2){ 
            int maxLength = length1; 
            char *result = malloc((maxLength + 2) * sizeof(char));
            if (result == NULL) {
                printf("内存分配失败，程序错误\n");
                return NULL;
            }
                result[maxLength + 1] = '\0';
            int carry = 0;
            for (int i = 0; i <= maxLength; i++) {
                int num1 = i < length1 ? bigNumber2[length1 - 1 - i] - '0' : 0; 
                int num2 = i < length2 ? bigNumber1[length2 - 1 - i] - '0' : 0; 
                int sum = num1 - num2 + carry;
                carry = sum >= 0 ? 0 : -1; 
                sum = sum < 0? sum + 10 : sum;
                result[maxLength - i] = (sum % 10) + '0'; 
            } 
            for (int i = 0; i < maxLength;) { 
            if (result[i] == '0'){
                    result++;
                }
            else{
                break;
                }
            } 
            char *finalResult = malloc(129*sizeof(char)); 
            finalResult[0] = '-'; 
            strcpy(finalResult + 1, result); 
            result = finalResult;
            return result;
        } 
        else if(length1 < length2){ 
            int maxLength = length2; 
            char *result = malloc((maxLength + 2) * sizeof(char)); 
            if (result == NULL) {
                printf("内存分配失败，程序错误\n");
                return NULL;
            }
                result[maxLength + 1] = '\0'; 

            int carry = 0;
            for (int i = 0; i <= maxLength; i++) {
                int num1 = i < length1 ? bigNumber2[length1 - 1 - i] - '0' : 0; 
                int num2 = i < length2 ? bigNumber1[length2 - 1 - i] - '0' : 0; 
                int sum = num2 - num1 + carry;
                carry = sum >= 0 ? 0 : -1; 
                sum = sum < 0? sum + 10 : sum;
                result[maxLength - i] = (sum % 10) + '0'; 
            }
            for (int i = 0; i < maxLength;) { 
                if (result[i] == '0'){
                    result++;
                }
                else{
                    break;
                    }
                }                
                return result;
        } 
        else{  
            int maxLength = length1;  
            for (int i = 0; i < maxLength; i++){
                if (bigNumber2[i] > bigNumber1[i]){ 
                    char *result = malloc((maxLength + 2) * sizeof(char));
                    if (result == NULL) {
                        printf("内存分配失败，程序错误\n");
                        return NULL;
                    }
                    result[maxLength + 1] = '\0';
                    int carry = 0;
                    for (int i = 0; i <= maxLength; i++) {
                        int num1 = i < length1 ? bigNumber2[length1 - 1 - i] - '0' : 0; 
                        int num2 = i < length2 ? bigNumber1[length2 - 1 - i] - '0' : 0; 
                        int sum = num1 - num2 + carry;
                        carry = sum >= 0 ? 0 : -1; 
                        sum = sum < 0? sum + 10 : sum;
                        result[maxLength - i] = (sum % 10) + '0'; 
                    } 
                    for (int i = 0; i < maxLength;) { 
                        if (result[i] == '0'){
                            result++;
                        }    
                        else{
                            break;
                        }
                    }
                    char *finalResult = malloc(129*sizeof(char)); 
                    finalResult[0] = '-'; 
                    strcpy(finalResult + 1, result); 
                    result = finalResult;
                    return result;
                } 
                else if (bigNumber2[i] < bigNumber1[i]){  
                    char *result = malloc((maxLength + 2) * sizeof(char)); 
                    if (result == NULL) {
                    printf("内存分配失败，程序错误\n");
                    return NULL;
                    }
                    result[maxLength + 1] = '\0'; 

                    int carry = 0;
                    for (int i = 0; i <= maxLength; i++) {
                        int num1 = i < length1 ? bigNumber2[length1 - 1 - i] - '0' : 0; 
                        int num2 = i < length2 ? bigNumber1[length2 - 1 - i] - '0' : 0; 
                        int sum = num2 - num1 + carry;
                        carry = sum >= 0 ? 0 : -1; 
                        sum = sum < 0? sum + 10 : sum;
                        result[maxLength - i] = (sum % 10) + '0'; 
                    }
                    for (int i = 0; i < maxLength;) { 
                        if (result[i] == '0'){
                            result++;
                        }
                        else{
                            break;
                        }
                    } 
                    return result;
                }
                else{
                    continue;
                } 
            } 
            char *result = malloc(2 * sizeof(char));
            result[0] = '0';
            result[1] = '\0';
            return result;
        }     
} 

/**头文件 <stdio.h> <stdlib.h> <string.h>
 * @brief 该函数输入两个字符串数组的指针，将其相乘，并返回一个指向和的字符串数组的指针
 * 
 * @param char *bigNumber1 输入一个字符串数组的指针 
 * @param char *bigNumber2 输入一个字符串数组的指针
 * 
 * @return char * 一个指向和的字符串数组的指针
 */
char *bigNumberMul(char *bigNumber1, char *bigNumber2){ 
        int length1 = strlen(bigNumber1); 
        int length2 = strlen(bigNumber2); 
        char *result = malloc(length1*length2 + 1);  //free 
            if (result == NULL){
                printf("内存分配失败，程序错误");
                return NULL;
            }
            result[0] = '0'; 
            result[1] = '\0'; 

        for (int i = 0; i < length1; i++) {
            int mul1 = bigNumber1[length1 - 1 -i] - '0'; 
            int carry1 = 0; 
            char *inresult1 = malloc(length1*length2 + 1); 
            if (inresult1 == NULL){
                printf("内存分配失败，程序错误");
                return NULL;
            } 
            inresult1[length1*length2] = '\0';
            
            for (int j = 0; j < length1*length2; j++){ 
                int mul2 = j < length2 ? bigNumber2[length2 - 1 - j] - '0' : 0;
                int sum = mul1*mul2 + carry1; 
                carry1 = sum/10;
                sum = sum%10; 
                inresult1[length1*length2 - 1 - j] = sum + '0';
            } 

            int times = 0;
            for (int j = 0; j < length1*length2;){
                if (inresult1[j] == '0'){
                    inresult1++; 
                    times++;
                }
                else{
                    break;
                }
            } 
            char *inresult2 = malloc(length1*length2 + 1);  
            if (inresult2 == NULL){
                printf("内存分配失败，程序错误");
                return NULL;
            } 
            for (int j = 0; j < i; j++){
                inresult2[j] = '0';
            } 
            if (i >= 1){
                inresult2[i] = '\0'; 
            } 
            else{
                inresult2[0] = '\0';
            } 

            strcat(inresult1, inresult2); 
            char *bigNumber1 = result; 
            char *bigNumber2 = inresult1;
            int length1 = strlen(bigNumber1); 
            int length2 = strlen(bigNumber2); 
            int carry2 = 0;
            int maxLength = length1 > length2 ? length1 : length2; 
            char *inresult3 = malloc((maxLength + 2) * sizeof(char)); 
            if (inresult3 == NULL) {
                printf("内存分配失败，程序错误\n");
                return NULL;
            }
            inresult3[maxLength + 1] = '\0'; 

            for (int j = 0; j <= maxLength; j++) { 
                int num1 = j < length1 ? bigNumber1[length1 - 1 - j] - '0' : 0; 
                int num2 = j < length2 ? bigNumber2[length2 - 1 - j] - '0' : 0; 
                int sum = num1 + num2 + carry2;
                carry2 = sum / 10;
                inresult3[maxLength - j] = (sum % 10) + '0'; 
            }

            for (int j = 0; j < (maxLength+1);){
                if (inresult3[j] == '0'){
                    inresult3++;
                } 
                else{ 
                    break;
                }
            } 
            result = inresult3; 
            inresult1 -= times;
            //free(inresult1); 
            inresult1 = NULL;
            free(inresult2); 
            inresult2 = NULL; 
        } 
        return result;
} 

void fillString(char *str, int targetLength, char padChar) {
    int currentLength = strlen(str);
    int i;
    for (i = currentLength; i < targetLength; i++) {
        strncat(str, &padChar, 1);
    }
}





/**头文件 <stdio.h> <stdlib.h> <string.h>;   全局变量 PFN; */
PFN *PFNAdd(PFN *pfn1, PFN *pfn2){ 
    PFN *result = malloc(sizeof(PFN)); 
    if (result == NULL) {
        printf("内存分配失败，程序错误\n");
        return NULL;
    } 
    result->system = 'D';



    if (pfn1->sign == '\0' && pfn2->sign == '\0'){
        result->sign = '\0'; 
        int length = strlen(pfn1->fraction) > strlen(pfn2->fraction)? strlen(pfn1->fraction) : strlen(pfn2->fraction);
        strcpy(result->integer, bigNumberAdd(pfn1->integer, pfn2->integer)); 
        fillString(pfn1->fraction, length, '0'); 
        fillString(pfn2->fraction, length, '0');
        strcpy(result->fraction, bigNumberAdd(pfn1->fraction, pfn2->fraction)); 

		char temp[260];
		temp[0] = '\0'; //小数左侧补0
		fillString(temp, length-strlen(result->fraction), '0');  
		temp[length-strlen(result->fraction)] = '\0';
		strcat(temp, result->fraction); 
		strcpy(result->fraction, temp); 
        
        if (strlen(result->fraction) > strlen(pfn1->fraction)){
            char temp[131]; 
            strcpy(temp, result->fraction);//char *temp = result->fraction; 
            temp[1] = '\0';
            strcpy(result->integer, bigNumberAdd(result->integer, temp)); 

            strcpy(temp, result->fraction); 
            strcpy(result->fraction, temp + 1);
        } 

		for (int i = strlen(result->fraction); ; i--){ //处理小数部分右0
			if (result->fraction[i-1] == '0'){
				result->fraction[i-1] = '\0';
			}
			else{
				break;
			}			
		}
		temp[0] = '\0'; //小数左侧补0
		fillString(temp, length-strlen(result->fraction), '0');  
		temp[length-strlen(result->fraction)] = '\0';
		strcat(temp, result->fraction); 
		strcpy(result->fraction, temp); 
        return result;
    }
    else if (pfn1->sign == '-' && pfn2->sign == '-'){
        result->sign = '-'; 
        int length = strlen(pfn1->fraction) > strlen(pfn2->fraction)? strlen(pfn1->fraction) : strlen(pfn2->fraction);
        strcpy(result->integer, bigNumberAdd(pfn1->integer, pfn2->integer)); 
        fillString(pfn1->fraction, length, '0'); 
        fillString(pfn2->fraction, length, '0');
        strcpy(result->fraction, bigNumberAdd(pfn1->fraction, pfn2->fraction)); 

		char temp[260];
		temp[0] = '\0'; //小数左侧补0
		fillString(temp, length-strlen(result->fraction), '0');  
		temp[length-strlen(result->fraction)] = '\0';
		strcat(temp, result->fraction); 
		strcpy(result->fraction, temp); 

        if (strlen(result->fraction) > strlen(pfn1->fraction)){
            char temp[131]; 
            strcpy(temp, result->fraction);//char *temp = result->fraction; 
            temp[1] = '\0';
            strcpy(result->integer, bigNumberAdd(result->integer, temp)); 

            strcpy(temp, result->fraction); 
            strcpy(result->fraction, temp + 1);
        } 

		for (int i = strlen(result->fraction); ; i--){ //处理小数部分右0
			if (result->fraction[i-1] == '0'){
				result->fraction[i-1] = '\0';
			}
			else{
				break;
			}			
		}
		temp[0] = '\0'; //小数左侧补0
		fillString(temp, length-strlen(result->fraction), '0');  
		temp[length-strlen(result->fraction)] = '\0';
		strcat(temp, result->fraction); 
		strcpy(result->fraction, temp); 
        return result;
    }
    else{
    	//调整次序 
		if (pfn1->sign == '-' && pfn2->sign == '\0'){
			PFN *tmp = pfn1; 
			pfn1 = pfn2; 
			pfn2 = tmp;
		} 
		//无脑处理pfn1-pfn2 
		strcpy(result->integer, bigNumberSub(pfn1->integer, pfn2->integer)); //处理整数部分
		int length = strlen(pfn1->fraction) > strlen(pfn2->fraction)? strlen(pfn1->fraction) : strlen(pfn2->fraction); //处理小数部分 
        fillString(pfn1->fraction, length, '0'); 
        fillString(pfn2->fraction, length, '0');
		strcpy(result->fraction, bigNumberSub(pfn1->fraction, pfn2->fraction));
		
		//检查符号
		if ((result->integer[0] == '-' && result->fraction[0] == '-') || (result->integer[0] != '-' && result->fraction[0] != '-')){ 
			if (result->integer[0] == '-'){ //处理符号，处理整数负号
				result->sign = '-';
				char *tmp = result->integer; 
				strcpy(result->integer, tmp + 1);
			}
			else{
				result->sign = '\0';
			}
			if (result->fraction[0] == '-'){ //处理小数负号 
			char *tmp = result->fraction; 
			strcpy(result->fraction, tmp + 1);
			} 
			for (int i = strlen(result->fraction); ; i--){ //处理小数部分右0
				if (result->fraction[i-1] == '0'){
					result->fraction[i-1] = '\0';
				}
				else{
					break;
				}			
			}
			char temp[260];
			temp[0] = '\0'; //最终小数左侧补0
			fillString(temp, length-strlen(result->fraction), '0');  
			temp[length-strlen(result->fraction)] = '\0';
			strcat(temp, result->fraction); 
			strcpy(result->fraction, temp);
		}
		else{ 
			if (result->integer[0] != '0'){ 
				if (result->integer[0] == '-'){ //处理符号，处理整数负号
					result->sign = '-';
					char *tmp = result->integer; 
					strcpy(result->integer, tmp + 1);
				}
				else{
					result->sign = '\0';
				}
		
				strcpy(result->integer, bigNumberSub(result->integer, "1"));//整数退位 
				if (result->fraction[0] == '-'){//处理小数负号
					char *tmp = result->fraction;
					strcpy(result->fraction, tmp + 1);
				}
			    char temp[260] = "1"; //小数补位 
				fillString(temp, length+1, '0');  
				temp[length+1] = '\0';
				strcpy(result->fraction, bigNumberSub(temp, result->fraction)); 
				temp[0] = '0'; //最终小数左侧补0
				fillString(temp, length-strlen(result->fraction), '0');  
				temp[length-strlen(result->fraction)] = '\0';
				strcat(temp, result->fraction); 
				strcpy(result->fraction, temp);
				for (int i = strlen(result->fraction); ; i--){ //最终小数右侧去0
					if (result->fraction[i-1] == '0'){
						result->fraction[i-1] = '\0';
					}
					else{
						break;
					}			
				} 
				if (result->fraction[0] == '\0'){
					result->fraction[0] = '0';
					result->fraction[1] = '\0';
				}
			}
			else{ 
				if (result->fraction[0] == '-'){ //处理符号
					result->sign = '-'; 
					char *tmp = result->fraction;
					strcpy(result->fraction, tmp + 1);
				}
				else{
					result->sign = '\0';
				} 
				char temp[260]; 
				temp[0] = '\0'; //最终小数左侧补0
				fillString(temp, length-strlen(result->fraction), '0');  
				temp[length-strlen(result->fraction)] = '\0';
				strcat(temp, result->fraction); 
				strcpy(result->fraction, temp);
			}


		}
		return result;

    }


}

PFN *PFNSub(PFN *pfn1, PFN *pfn2){ 
	//定义结果
    PFN *result = malloc(sizeof(PFN)); 
    if (result == NULL) {
        printf("内存分配失败，程序错误\n");
        return NULL;
    } 
	//处理进制
    result->system = 'D';



    if (pfn1->sign == '\0' && pfn2->sign == '-'){
        result->sign = '\0'; 
        int length = strlen(pfn1->fraction) > strlen(pfn2->fraction)? strlen(pfn1->fraction) : strlen(pfn2->fraction);
        strcpy(result->integer, bigNumberAdd(pfn1->integer, pfn2->integer)); 
        fillString(pfn1->fraction, length, '0'); 
        fillString(pfn2->fraction, length, '0');
        strcpy(result->fraction, bigNumberAdd(pfn1->fraction, pfn2->fraction)); 

		char temp[260];
		temp[0] = '\0'; //小数左侧补0
		fillString(temp, length-strlen(result->fraction), '0');  
		temp[length-strlen(result->fraction)] = '\0';
		strcat(temp, result->fraction); 
		strcpy(result->fraction, temp); 
        
        if (strlen(result->fraction) > strlen(pfn1->fraction)){
            char temp[131]; 
            strcpy(temp, result->fraction);//char *temp = result->fraction; 
            temp[1] = '\0';
            strcpy(result->integer, bigNumberAdd(result->integer, temp)); 

            strcpy(temp, result->fraction); 
            strcpy(result->fraction, temp + 1);
        } 

		for (int i = strlen(result->fraction); ; i--){ //处理小数部分右0
			if (result->fraction[i-1] == '0'){
				result->fraction[i-1] = '\0';
			}
			else{
				break;
			}			
		}
		temp[0] = '\0'; //小数左侧补0
		fillString(temp, length-strlen(result->fraction), '0');  
		temp[length-strlen(result->fraction)] = '\0';
		strcat(temp, result->fraction); 
		strcpy(result->fraction, temp); 
        return result;
    }
    else if (pfn1->sign == '-' && pfn2->sign == '\0'){
        result->sign = '-'; 
        int length = strlen(pfn1->fraction) > strlen(pfn2->fraction)? strlen(pfn1->fraction) : strlen(pfn2->fraction);
        strcpy(result->integer, bigNumberAdd(pfn1->integer, pfn2->integer)); 
        fillString(pfn1->fraction, length, '0'); 
        fillString(pfn2->fraction, length, '0');
        strcpy(result->fraction, bigNumberAdd(pfn1->fraction, pfn2->fraction)); 

		char temp[260];
		temp[0] = '\0'; //小数左侧补0
		fillString(temp, length-strlen(result->fraction), '0');  
		temp[length-strlen(result->fraction)] = '\0';
		strcat(temp, result->fraction); 
		strcpy(result->fraction, temp); 

        if (strlen(result->fraction) > strlen(pfn1->fraction)){
            char temp[131]; 
            strcpy(temp, result->fraction);//char *temp = result->fraction; 
            temp[1] = '\0';
            strcpy(result->integer, bigNumberAdd(result->integer, temp)); 

            strcpy(temp, result->fraction); 
            strcpy(result->fraction, temp + 1);
        } 

		for (int i = strlen(result->fraction); ; i--){ //处理小数部分右0
			if (result->fraction[i-1] == '0'){
				result->fraction[i-1] = '\0';
			}
			else{
				break;
			}			
		}
		temp[0] = '\0'; //小数左侧补0
		fillString(temp, length-strlen(result->fraction), '0');  
		temp[length-strlen(result->fraction)] = '\0';
		strcat(temp, result->fraction); 
		strcpy(result->fraction, temp); 
        return result;
    }
	else{ 
		//调整次序 
		if (pfn1->sign == '-' && pfn2->sign == '-'){
			PFN *tmp = pfn1; 
			pfn1 = pfn2; 
			pfn2 = tmp;
		} 
		//无脑处理pfn1-pfn2 
		strcpy(result->integer, bigNumberSub(pfn1->integer, pfn2->integer)); //处理整数部分
		int length = strlen(pfn1->fraction) > strlen(pfn2->fraction)? strlen(pfn1->fraction) : strlen(pfn2->fraction); //处理小数部分 
        fillString(pfn1->fraction, length, '0'); 
        fillString(pfn2->fraction, length, '0');
		strcpy(result->fraction, bigNumberSub(pfn1->fraction, pfn2->fraction));
		
		//检查符号
		if ((result->integer[0] == '-' && result->fraction[0] == '-') || (result->integer[0] != '-' && result->fraction[0] != '-')){ 
			if (result->integer[0] == '-'){ //处理符号，处理整数负号
				result->sign = '-';
				char *tmp = result->integer; 
				strcpy(result->integer, tmp + 1);
			}
			else{
				result->sign = '\0';
			}
			if (result->fraction[0] == '-'){ //处理小数负号 
			char *tmp = result->fraction; 
			strcpy(result->fraction, tmp + 1);
			} 
			for (int i = strlen(result->fraction); ; i--){ //处理小数部分右0
				if (result->fraction[i-1] == '0'){
					result->fraction[i-1] = '\0';
				}
				else{
					break;
				}			
			}
			char temp[260];
			temp[0] = '\0'; //最终小数左侧补0
			fillString(temp, length-strlen(result->fraction), '0');  
			temp[length-strlen(result->fraction)] = '\0';
			strcat(temp, result->fraction); 
			strcpy(result->fraction, temp);
		}
		else{ 
			if (result->integer[0] != '0'){ 
				if (result->integer[0] == '-'){ //处理符号，处理整数负号
					result->sign = '-';
					char *tmp = result->integer; 
					strcpy(result->integer, tmp + 1);
				}
				else{
					result->sign = '\0';
				}
		
				strcpy(result->integer, bigNumberSub(result->integer, "1"));//整数退位 
				if (result->fraction[0] == '-'){//处理小数负号
					char *tmp = result->fraction;
					strcpy(result->fraction, tmp + 1);
				}
			    char temp[260] = "1"; //小数补位 
				fillString(temp, length+1, '0');  
				temp[length+1] = '\0';
				strcpy(result->fraction, bigNumberSub(temp, result->fraction)); 
				temp[0] = '0'; //最终小数左侧补0
				fillString(temp, length-strlen(result->fraction), '0');  
				temp[length-strlen(result->fraction)] = '\0';
				strcat(temp, result->fraction); 
				strcpy(result->fraction, temp);
				for (int i = strlen(result->fraction); ; i--){ //最终小数右侧去0
					if (result->fraction[i-1] == '0'){
						result->fraction[i-1] = '\0';
					}
					else{
						break;
					}			
				} 
				if (result->fraction[0] == '\0'){
					result->fraction[0] = '0';
					result->fraction[1] = '\0';
				}
			}
			else{ 
				if (result->fraction[0] == '-'){ //处理符号
					result->sign = '-'; 
					char *tmp = result->fraction;
					strcpy(result->fraction, tmp + 1);
				}
				else{
					result->sign = '\0';
				} 
				char temp[260]; 
				temp[0] = '\0'; //最终小数左侧补0
				fillString(temp, length-strlen(result->fraction), '0');  
				temp[length-strlen(result->fraction)] = '\0';
				strcat(temp, result->fraction); 
				strcpy(result->fraction, temp);
			}


		}
		return result;
	}
}

PFN *PFNMul(PFN *pfn1, PFN *pfn2){ 
	//定义结果
	PFN *result = malloc(sizeof(PFN)); 
    if (result == NULL) {
        printf("内存分配失败，程序错误\n");
        return NULL;
    } 
	//处理符号
	if (pfn1->sign == pfn2->sign){
		result->sign = '\0';
	} 
	else{
		result->sign = '-';
	}

	//处理进制
	result->system = 'D'; 
	
	
	//处理数字
	char num1[259], num2[259];	//合并小数和整数
	num1[0] = '\0'; 
	num2[0] = '\0';
	strcat(num1, pfn1->integer); 
	strcat(num1, pfn1->fraction); 
	strcat(num2, pfn2->integer); 
	strcat(num2, pfn2->fraction);

	int LengthOfFraction = strlen(pfn1->fraction) + strlen(pfn2->fraction);		//记算小数位数
	
	//乘法处理 
	char *resultNum = bigNumberMul(num1, num2);
	
	//分离小数和整数
	char *tmp = resultNum;
	int LengthOfInteger = strlen(resultNum) - LengthOfFraction; 
	strncpy(result->integer, tmp, LengthOfInteger); 
	result->integer[LengthOfInteger] = '\0';
	strcpy(result->fraction, tmp + LengthOfInteger); 

    for (int i = strlen(result->fraction); ; i--){ //处理小数部分右0
        if (result->fraction[i-1] == '0'){
            result->fraction[i-1] = '\0';
        }
        else{
            break;
        }			
    } 
    if (result->fraction[0] == '\0'){
        result->fraction[0] = '0';
        result->fraction[1] = '\0';
    }
    
	
	//返回结果
	return result;
}



int main(){ 
    //定义操作数和操作符和结果
    PFN pfn1, pfn2; 
    char operation; 
    PFN *result; 
    PFN *temp;

    FILE *fp; 
    fp = fopen("/tmp/CS_M_02.txt", "r");


    initPFNAndStoreInDecimal(&pfn1, fp); 
    printPFN(pfn1); 

    for (int i = 0; i < 14; i++){

        getOperation(&operation, fp); 
        printf("%c", operation);

        initPFNAndStoreInDecimal(&pfn2, fp); 
        PFNStoredInDecimal(&pfn2);
        printPFN(pfn2);
        
        //根据操作符进行运算，得到结果
        if (operation == '+'){
            result = PFNAdd(&pfn1, &pfn2);
        } 

        if (operation == '-'){
            result = PFNSub(&pfn1, &pfn2);
        }

        if (operation == '*'){
            result = PFNMul(&pfn1, &pfn2);
        } 
        printf("=");
        printPFN(*result);
        pfn1.sign = result->sign; 
        strcpy(pfn1.integer, result->integer); 
        strcpy(pfn1.fraction, result->fraction); 
        pfn1.system = result->system;

    }


    

    fclose(fp);






        //根据操作符进行运算，得到结果
        /*if (operation == '+'){
            result = PFNAdd(&pfn1, &pfn2);
        } 

        if (operation == '-'){
            result = PFNSub(&pfn1, &pfn2);
        }

        if (operation == '*'){
            result = PFNMul(&pfn1, &pfn2);
        } 

        printPFN(*result);
        pfn1.sign = result->sign; 
        strcpy(pfn1.integer, result->integer); 
        strcpy(pfn1.fraction, result->fraction); 
        pfn1.system = result->system; 

        temp->sign = pfn2.sign;
        strcpy(temp->integer, pfn2.integer);
        strcpy(temp->fraction, pfn2.fraction);
        temp->system = pfn2.system;*/

    
    return 0;
}