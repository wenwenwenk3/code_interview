//
// Created by kai.chen on 2024/5/11.
//

#ifndef CODE_INTERVIEW_BIT_OP_H
#define CODE_INTERVIEW_BIT_OP_H
#include "common.h"

// 1. single number 其他数都出现偶数次，找出出现奇数次的数
//  思路：异或运算
int singleNumber(const vector<int>& nums){
    int res = 0;
    for(const auto& num : nums){
        res ^= num;
    }
    return res;
} // 时间O(n), 空间O(1)

// 1.2 如果有两个数出现奇数次
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
}

// 1.1 找出只出现一次的数，其他都出现k次
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
