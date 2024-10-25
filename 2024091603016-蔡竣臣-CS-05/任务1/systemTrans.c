#include <stdio.h>
#include <string.h> 

/**头文件 <stdio.h> <string.h>
 * 
 * @brief 将十进制数转换为二进制数
 * 
 * @param decimal 十进制数
 * 
 * @return 无返回值
 */
void decimalToBinary(int decimal) {
    int bits = sizeof(int) * 8; 
    char binary[bits + 1]; 
    binary[bits] = '\0'; 

    for (int i = bits - 1; i >= 0; i--) {
        binary[i] = (decimal % 2) + '0'; 
        decimal /= 2; 
    }

    int start = 0;
    while (start < bits - 1 && binary[start] == '0') {
        start++;
    }
    printf("Binary equivalent: %s\n", binary + start);
} 

/**头文件 <stdio.h> <string.h>
 *
 * @brief 将二进制数转换为十进制数
 *
 * @param binary 二进制数
 *
 * @return 十进制数
 */
int binaryToDecimal(const char *binary) {
    int decimal = 0;
    int length = strlen(binary);
    for (int i = 0; i < length; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            printf("Invalid binary number.\n");
            return -1; // 返回一个错误码
        }
        decimal = decimal * 2 + (binary[i] - '0'); // 计算十进制值
    }
    return decimal;
}


int main() {
    int decimalNumber;
    printf("Enter a decimal number: ");
    scanf("%d", &decimalNumber);
    decimalToBinary(decimalNumber); 

    char binaryNumber[65]; 
    printf("Enter a binary number: ");
    scanf("%64s", binaryNumber); 
    int x = binaryToDecimal(binaryNumber);
    if (x != -1) {
        printf("Decimal equivalent: %d\n", x);
    }

    return 0;
}


