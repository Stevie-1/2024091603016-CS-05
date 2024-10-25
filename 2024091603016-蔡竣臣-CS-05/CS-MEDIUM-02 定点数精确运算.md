# CS-MEDIUM-02 定点数精确运算

## 课前准备--文件操作 

1. 代码如下：

	```c
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
	    fgetc(fp);
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
	
	int main(){ 
	
	    FILE *fp; 
	    fp = fopen("/tmp/CS_M_02.txt", "r");
	    for (int i = 0; i < 15; i++){
	        PFN pfn;
	        initPFNAndStoreInDecimal(&pfn, fp); 
	        printPFN(pfn); 
	    }
	    fclose(fp);
	    return 0; 
	}
	```

2. 截图见getPFNFromFile.png;





## 任务1

1. **为什么会出现这样的现象？** 

	1. **有限的内存和无限的数据导致无法避免的误差**：计算机储存本质是二进制数。计算机内存有限度，而0.1和0.2的二进制都是无限循环小数。当0.1或0.2在计算机中转化为二进制时，计算机只能保留有限的位数，必然导致数据的损失，这是误差产生的原因之一。 
	2. **有效位数的限制**：在当代CPU广泛应用的IEEE 754标准下，float的有效位仅有23位，这会导致23位之后的有效数字丢失，产生误差。

2. **该如何获得精确值呢？** 

	1. 在C语言中，引入` <mpfr.h>`头文件，可进行高精度运算

	```c
	#include <stdio.h>
	#include <mpfr.h>
	
	int main() {
	    mpfr_t op1, op2, result; //声明并初始化 MPFR 变量
	    mpfr_init2(op1, 128); //初始化为 128 位精度
	    mpfr_init2(op2, 128);
	    mpfr_init2(result, 128);
	
	    mpfr_set_d(op1, 0.1, MPFR_RNDN); //将值 0.1 和 0.2 设置到 MPFR 变量中
	    mpfr_set_d(op2, 0.2, MPFR_RNDN); 
	    
	    mpfr_add(result, op1, op2, MPFR_RNDN); //使用 MPFR 函数执行加法运算
	
	    printf("Result: %0.16f\n", mpfr_get_d(result, MPFR_RNDN)); //将结果打印为双精度浮点数
	
	    mpfr_clear(op1); //清理 MPFR 变量以释放内存
	    mpfr_clear(op2);
	    mpfr_clear(result);
	
	    return 0;
	}
	```

	2. 把定点数拆分为**正负号**，**整数部分的整数**，**小数点**，**小数部分的整数**，**进制符号**，则可以利用无误差的整数运算进行运算，结果在不溢出的情况下是准确的。然而面对溢出问题，我们可以把**整数和小数部分用字符数组**的方式表示和运算，这样以来溢出问题也可以解决，哪怕会带来更高的运算成本。

1. **课前热身：请提交代码实现二进制与十进制的相互转化。** 

	代码见systemTrans.c



## 任务2

### Step1 定点数的表示与存储

1. 代码如下 

	```c
	#include <stdio.h> 
	#include <string.h> 
	#include <stdlib.h> 
	#include <math.h>
	
	typedef struct PointFixedNumber{
	    char system; 
	    char sign;
	    unsigned fraction;
	    unsigned integer;
	}PFN; 
	
	/**头文件 <stdio.h> <stdlib.h>
	 *  @brief 该函数输入一个整数，将其转换为字符串数组，并返回一个指向该字符串数组的指针 
	 * 
	 *  @param integer 输入一个整数
	 * 
	 *  @return char * 一个指向字符串数组的指针
	*/
	char *IntToChar(int integer){ 
	    char *str;
	    str = (char*)malloc(sizeof(char)*10); //free
	    sprintf(str, "%d", integer);
	    return str;
	} 
	
	/**头文件 <stdio.h> <string.h>
	 *
	 * @brief 将二进制数转换为十进制数
	 *
	 * @param binary 二进制数
	 *
	 * @return 十进制数
	 */
	int binaryToDecimal_Integer(const char *binary) {
	    int decimal = 0;
	    int length = strlen(binary);
	    for (int i = 0; i < length; i++) {
	        if (binary[i] != '0' && binary[i] != '1') {
	            printf("Invalid binary number.\n");
	            return -1; 
	        }
	        decimal = decimal * 2 + (binary[i] - '0'); 
	    }
	    return decimal;
	} 
	
	/**头文件 <stdio.h> <string.h> <math.h>  
	 * 
	 * @brief 将二进制数转换为十进制数
	 *
	 * @param binary 二进制数
	 *
	 * @return 十进制数
	 */
	int binaryToDecimal_Traction(const char *fraction) {
	    int decimal = 0; 
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
	
	    decimal = (int)tmp;   
	    return decimal;
	}
	
	/**头文件 <stdio.h> <string.h> <stdlib.h> <math.h>
	 * 
	 *  @brief 输入一个定点数，将其转换为十进制数，并存储在结构体中 
	 * 
	 *  @param pfn 一个指向结构体的指针 
	 * 
	 *  @return 无返回值
	 */
	void initPFNAndStoreInDecimal(PFN *pfn){
	    int integer = 0;
	    int fraction = 0;
	    char system; 
	    char sign; 
	    char string[130]; 
	    int location = 0;
	    
	    printf("输入一个定点数："); 
	    scanf("%129s", string);
	    if (string[0] == '-')  {
	        sign = string[0]; 
	        location++;
	    } 
	    while (string[location] != '.'){
	        integer = integer * 10 + (string[location] - '0');
	        location++;
	    } 
	    location++;
	    while (string[location] != 'B' && string[location]!= 'D'){
	        fraction = fraction * 10 + (string[location] - '0');
	        location++;
	    }
	    system = string[location];
	    pfn->integer = integer;
	    pfn->fraction = fraction; 
	    pfn->system = system; 
	    pfn->sign = sign;
	
	
	
	
	    if (system != 'D'){ 
	        if (system == 'B'){
	            char *integerStr;
	            char *fractionStr;
	            integerStr = IntToChar(integer); //free
	            fractionStr = IntToChar(fraction);  //free
	
	            pfn->integer = binaryToDecimal_Integer(integerStr);
	            pfn->fraction = binaryToDecimal_Traction(fractionStr); 
	            pfn->system = 'D';
	        }
	        else{
	            printf("请输入二进制或十进制数。\n");
	        }
	    }
	}
	
	/**头文件 <stdio.h>
	 *
	 * @brief 输出一个定点数
	 *
	 * @param pfn 一个指向结构体的指针
	 *
	 * @return 无返回值
	 */
	void printPFN(PFN pfn){
	    printf("%c%d.%d%c\n", pfn.sign, pfn.integer, pfn.fraction, pfn.system);
	}
	
	int main(){ 
	    PFN pfn;
	    initPFNAndStoreInDecimal(&pfn);
	    printPFN(pfn);
	}
	```

	2. 截图见pointFixedNumberStore.png





### Step 2 实现精确计算 

1. 由于代码太长，请见pointFixedNumberCalculate.c 
2. 截图见pointFixedNumberCalculate.png





## 任务3

1. 由于代码太长，请见constentPFNCal.c 
2. 截图见constentPFNCal.png

