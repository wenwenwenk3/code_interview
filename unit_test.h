//
// Created by kai.chen on 2024/5/12.
//

#ifndef CODE_INTERVIEW_UNIT_TEST_H
#define CODE_INTERVIEW_UNIT_TEST_H
#include "bit_op.h"

void testSingleNumberII(){
    typedef struct{
        vector<int> nums;
        int k;
        int expected;
    }field;
    vector<field> testcases = {
            {.nums = {2,2,3,2}, .k =  3, .expected = 3}
    };
    for(const auto& testcase : testcases){
        assert(testcase.expected == singleNumberII(testcase.nums, testcase.k));
    }
}


#endif //CODE_INTERVIEW_UNIT_TEST_H
