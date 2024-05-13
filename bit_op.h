//
// Created by kai.chen on 2024/5/11.
//
//      1. 统计二进制中 1 的个数
//      2. 不用额外变量交换两个数
//      3. 不做任何比较找出更大的数
//          3.1 转换为k进制数
//
//      4. 其他数都出现偶数次，找出"出现奇数次"的数(只有一个)
//          变体4.1：有两个出现奇数次，其他出现偶数次，找出这两个数
//          4.2 找出只出现一次的数，其他都出现k次
//

#ifndef CODE_INTERVIEW_BIT_OP_H
#define CODE_INTERVIEW_BIT_OP_H
#include "common.h"

// 1. 统计二进制中 1 的个数
//  思路：
//      (1) 常规思路：每次 与1相"与"，向右移一位。(这样每次判断最后一位是否为1，并且如果是的话每次抹掉一个1，时间复杂度：O(z)z是整数二进制长度：32)
//      (2) 一般思路：每次 与x-1相"与"，相当于每次去掉了最右侧一个1。(时间复杂度是 二进制中1的个数)
//      (3) 思路3：每次 x- (x & (~x+1)), 也相当于每次去掉了最右侧一个1. // x & (x取反+1)的结果就是最后一个1的十进制表示
//   注：这题还有很多逆天算法：如平行算法，MIT hackmem算法...
int countOne(int x){
    int count = 0;
    while(x!=0){
        count = count + x&1;
        x = x>>1;
    }
    return count;
}
// 推荐写法：
int countOneII(int x){
    int count = 0;
    while(x!=0){
        count++;
        x = x&(x-1);
    }
    return count;
}
// __builtin_popcount: 查表实现，时间复杂度为 O(logN), N为二进制位数
int countOneII_2(int x){ return __builtin_popcount(x); }
// int bitCountII(int x) {
//    //table是0到15转化为二进制时1的个数
//    int table[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
//    int count = 0;
//    while (x != 0) {//通过每4位计算一次，求出包含1的个数
//        count += table[i & 0xf];
//        x >>= 4;
//    }
//    return count;
//}

// 2. 不用额外变量交换两个数
//  思路: 使用"异或"运算
void swap_yihuo(int *a, int *b){
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

// 3. 不做任何比较找出更大的数
//  思路：判断 a-b 的符号即可
int sign(int x){
    return ((x>>31) & 1) ^ 0x1;
}
int getMax(int a, int b){
    int diff = a-b;
    int sgA = sign(diff);  // sgA 如果a更大才为1，否则为0
    int sgB = sgA ^ 0x1;  // 这里和1异或表示取反
    return sgA * a + sgB *b;
} // 但是这个方法有一个缺陷，就是a – b的值可能会溢出，返回结果就不正确。比如a为最小值INT_MIN（-2147483648），b为1，那a – b就会溢出。

int getMax2(int a, int b){
    int diff, sgA, sgB, sgDiff;
    int x, y, result1, result2;

    diff = a - b;
    sgA = sign(a);
    sgB = sign(b);
    sgDiff = sign(diff);

    x = sgA ^ sgB;
    y = x ^ 0x1; // a和b符号相同，那么x == 0，y == 1，且这种情况a – b的值肯定不会溢出
                 //  -如果a – b >= 0，那么sgDiff == 1，result1==1, result2==0 程序结果返回a
                 //  -如果a – b < 0，那么sgDiff == 0，程序结果返回b
                 // 二、a和b的符号不同，x == 1，y == 0
                 //   假设a >= 0，那么b < 0，sgA == 1，sgB == 0，程序结果返回a
                 //   假设a < 0，那么b >= 0，signBit_a == 0，signBit_b == 1，程序结果返回b
    result1 = x * sgA + y * sgDiff;
    result2 = result1 ^ 0x1;

    return (a * result1 + b * result2);
}


// 3. 转换为k进制数
vector<int> convertToKSystemNum(int n, int k){
    vector<int> bitNumKSystem(32);
    int idx = 0;
    while(n != 0){
        bitNumKSystem[idx++] = n % k;
        n = n/k;
    }
    return bitNumKSystem;
}
int convertFromKSystemNum(vector<int>& nums, int k){
    int res = 0;
    for(size_t i = nums.size()-1; i >= 0; i--){
        res = res*k + nums[i];
    }
    return res;
}


// 4. single number 其他数都出现偶数次，找出出现奇数次的数
//  思路：异或运算
int singleNumber(const vector<int>& nums){
    int res = 0;
    for(const auto& num : nums){
        res ^= num;
    }
    return res;
} // 时间O(n), 空间O(1)

// 4.1 如果有两个数出现奇数次
//  思路：直观的解法是哈希表记录出现次数，遍历一遍哈希表就可以找出来，时间O(n), 空间O(n)
//  另一种思路是：一次异或得到的结果A^B (假设剩下的两个数是A和B)
//      找出A^B又做的第一个等于1的位；在这位上一定有A=0，B=1
vector<int> singleNumberIII(const vector<int>& nums){
    int AB = 0, A = 0, B = 0;
    for(const auto& num : nums){
        AB ^= num;
    }
    int rightOneBit;
    if(AB == INT_MIN) rightOneBit = AB; // INT_MIN -2147483648是补码表示，只有一个符号位为1
    else rightOneBit = AB & (~AB + 1); // a & (a取反+1)的结果就是最后一个1的十进制表示

    // 再遍历一遍数组，每次只和第k位上是1的整数异或，其他的数忽略，自然就能得到A
    for(const auto& num : nums){
        if((num & rightOneBit) != 0){
            A = A^num;
        }
    }
    B = AB ^ A;
    return vector<int>{A, B};
} // 时间O(n), 空间O(1)

// 4.2 找出只出现一次的数，其他都出现k次
// 思路：判断每个二进制位该是多少
int singleNumberII(const vector<int>& nums, int k){
    int ans = 0;
    for(int i = 0; i< 32; i++){
        int onesCnt = 0;
        for(const auto & num: nums){
            onesCnt += (num>>i) & 1;
        }
        if(onesCnt % k != 0){
            ans |= (1<<i);
        }
    }
    return ans;
}


#endif //CODE_INTERVIEW_BIT_OP_H
