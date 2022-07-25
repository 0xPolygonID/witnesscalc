#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <cstring>
#include "fr.hpp"

int tests_run = 0;
int tests_failed = 0;

bool is_equal(const FrRawElement a, const FrRawElement b)
{
    return std::memcmp(a, b, sizeof(FrRawElement)) == 0;
}

bool is_equal(const PFrElement a, const PFrElement b)
{
    return std::memcmp(a, b, sizeof(FrElement)) == 0;
}

std::string format(uint64_t val)
{
    std::ostringstream  oss;

    oss << "0x" << std::hex << std::setw(16) << std::setfill('0') << val;

    return oss.str();
}

std::string format(uint32_t val)
{
    std::ostringstream  oss;

    oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << val;

    return oss.str();
}

std::string format(int32_t val)
{
    std::ostringstream  oss;

    oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << val;

    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const FrRawElement val)
{
    os << format(val[0]) << ","
       << format(val[1]) << ","
       << format(val[2]) << ","
       << format(val[3]);

    return os;
}

std::ostream& operator<<(std::ostream& os, const PFrElement val)
{
    os  << format(val->shortVal) << ", "
        << format(val->type)     << ", "
        << val->longVal;

    return os;
}

template <typename T1, typename T2, typename T3>
void compare_Result(const T1 expected, const T1 computed, const T2 A, const T3 B, int idx, std::string TestName)
{
    if (!is_equal(expected, computed))
    {
        std::cout << TestName << ":" << idx << " failed!" << std::endl;
        std::cout << "A: " << A << std::endl;
        std::cout << "B: " << B << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << "Computed: " << computed << std::endl;
        std::cout << std::endl;
        tests_failed++;
    }

    tests_run++;
}

template <typename T1, typename T2>
void compare_Result(const T1 expected, const T1 computed, const T2 A, int idx, std::string test_name)
{
    if (!is_equal(expected, computed))
    {
        std::cout << test_name << ":" << idx << " failed!" << std::endl;
        std::cout << "A: " << A << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << "Computed: " << computed << std::endl;
        std::cout << std::endl;
        tests_failed++;
    }

    tests_run++;
}

void Fr_Rw_Neg_unit_test()
{
    //Fr_Rw_Neg_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0xa1f0fac9f8000001,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    //Fr_Rw_Neg_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    //Fr_Rw_Neg_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x43e1f593f0000003,0x2833e84879b97090,0xb85045b68181585d,0x30644e72e131a029};
    //Fr_Rw_Neg_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0x43e1f593f0000003,0x2833e84879b97092,0xb85045b68181585e,0x30644e72e131a02a}; 
    //Fr_Rw_Neg_test 5:
    FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
    FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;
    FrRawElement pRawResult5_c;

    Fr_rawNeg(pRawResult0_c, pRawA0);
    Fr_rawNeg(pRawResult1_c, pRawA1);
    Fr_rawNeg(pRawResult2_c, pRawA2);
    Fr_rawNeg(pRawResult3_c, pRawA3);
    Fr_rawNeg(pRawResult5_c, pRawA5);

    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawA0, 0, "Fr_Rw_Neg_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawA1, 1, "Fr_Rw_Neg_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawA2, 2, "Fr_Rw_Neg_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawA3, 3, "Fr_Rw_Neg_unit_test");
    compare_Result(pRawResult5, pRawResult5_c, pRawA5, pRawA5, 5, "Fr_Rw_Neg_unit_test");
}

void Fr_Rw_copy_unit_test()
{
    //Fr_Rw_copy_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    //Fr_Rw_copy_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x1,0x0,0x0,0x0};
    //Fr_Rw_copy_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0xfffffffffffffffe,0x0,0x0,0x0};
    //Fr_Rw_copy_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;

    Fr_rawCopy(pRawResult0_c, pRawA0);
    Fr_rawCopy(pRawResult1_c, pRawA1);
    Fr_rawCopy(pRawResult2_c, pRawA2);
    Fr_rawCopy(pRawResult3_c, pRawA3);

    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawA0, 0, "Fr_Rw_copy_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawA1, 1, "Fr_Rw_copy_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawA2, 2, "Fr_Rw_copy_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawA3, 3, "Fr_Rw_copy_unit_test");
}


void Fr_Rw_add_unit_test()
{
    //Fr_rawAdd Test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FrRawElement pRawResult0= {0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba};
    //Fr_rawAdd Test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x3,0x0,0x0,0x0};
    //Fr_rawAdd Test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0xfffffffffffffffd,0x1,0x0,0x0};
    //Fr_rawAdd Test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement pRawResult3= {0xbc1e0a6c0ffffffc,0xd7cc17b786468f6d,0x47afba497e7ea7a1,0xcf9bb18d1ece5fd5};
    //Fr_rawAdd Test 6:
    FrRawElement pRawA6= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    FrRawElement pRawB6= {0x0,0x0,0x0,0x0};
    FrRawElement pRawResult6= {0x0,0x0,0x0,0x0};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;
    FrRawElement pRawResult6_c;

    Fr_rawAdd(pRawResult0_c, pRawA0, pRawB0);
    Fr_rawAdd(pRawResult1_c, pRawA1, pRawB1);
    Fr_rawAdd(pRawResult2_c, pRawA2, pRawB2);
    Fr_rawAdd(pRawResult3_c, pRawA3, pRawB3);
    Fr_rawAdd(pRawResult6_c, pRawA6, pRawB6);


    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawB0, 0, "Fr_Rw_add_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawB1, 1, "Fr_Rw_add_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawB2, 2, "Fr_Rw_add_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawB3, 3, "Fr_Rw_add_unit_test");
    compare_Result(pRawResult6, pRawResult6_c, pRawA6, pRawB6, 6, "Fr_Rw_add_unit_test");
}

void Fr_Rw_sub_unit_test()
{
    //Fr_Rw_sub_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FrRawElement pRawResult0= {0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f};
    //Fr_Rw_sub_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    //Fr_Rw_sub_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    //Fr_Rw_sub_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement pRawResult3= {0x43e1f593f0000000,0x2833e84879b97090,0xb85045b68181585c,0x30644e72e131a028};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;

    Fr_rawSub(pRawResult0_c, pRawA0, pRawB0);
    Fr_rawSub(pRawResult1_c, pRawA1, pRawB1);
    Fr_rawSub(pRawResult2_c, pRawA2, pRawB2);
    Fr_rawSub(pRawResult3_c, pRawA3, pRawB3);

    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawB0, 0, "Fr_Rw_sub_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawB1, 1, "Fr_Rw_sub_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawB2, 2, "Fr_Rw_sub_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawB3, 3, "Fr_Rw_sub_unit_test");


}

void Fr_Rw_mul_unit_test()
{
    //Fr_Rw_mul_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FrRawElement pRawResult0= {0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d};
    //Fr_Rw_mul_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39};
    //Fr_Rw_mul_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x8663902cfae5d423,0x95d2440ac403ddd3,0x1ad411b88e349a0f,0x1ebf106109e4fa8d};
    //Fr_Rw_mul_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement pRawResult3= {0xd13604f1e300865c,0xba58b3d2a99f4ba5,0x1b4e415146d47f95,0x55c593ff9cfbf0a};
    //Fr_Rw_mul_test 4:
    FrRawElement pRawA4= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB4= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult4= {0x1d0a8ff4c8e5744c,0x6fd9959908f97ec,0xdfe72d24fcdef34e,0xd1c7f8bb929dbb};
    //Fr_Rw_mul_test 5:
    FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
    FrRawElement pRawB5= {0x2,0x0,0x0,0x0};
    FrRawElement pRawResult5= {0x0,0x0,0x0,0x0};   
    //Fr_Rw_mul_test 8:
    FrRawElement pRawA8= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB8= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    FrRawElement pRawResult8= {0x0,0x0,0x0,0x0};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;
    FrRawElement pRawResult4_c;
    FrRawElement pRawResult5_c;
    FrRawElement pRawResult8_c;

    Fr_rawMMul(pRawResult0_c, pRawA0, pRawB0);
    Fr_rawMMul(pRawResult1_c, pRawA1, pRawB1);
    Fr_rawMMul(pRawResult2_c, pRawA2, pRawB2);
    Fr_rawMMul(pRawResult3_c, pRawA3, pRawB3);
    Fr_rawMMul(pRawResult4_c, pRawA4, pRawB4);
    Fr_rawMMul(pRawResult5_c, pRawA5, pRawB5);
    Fr_rawMMul(pRawResult8_c, pRawA8, pRawB8);

    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawB0, 0, "Fr_Rw_mul_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawB1, 1, "Fr_Rw_mul_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawB2, 2, "Fr_Rw_mul_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawB3, 3, "Fr_Rw_mul_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA4, pRawB4, 4, "Fr_Rw_mul_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA5, pRawB5, 5, "Fr_Rw_mul_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA8, pRawB8, 8, "Fr_Rw_mul_unit_test");


}

void Fr_Rw_Msquare_unit_test()
{
    //Fr_Rw_Msquare_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0x9907e2cb536c4654,0xd65db18eb521336a,0xe31a6546c6ec385,0x1dad258dd14a255c};
    //Fr_Rw_Msquare_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0xdc5ba0056db1194e,0x90ef5a9e111ec87,0xc8260de4aeb85d5d,0x15ebf95182c5551c};
    //Fr_Rw_Msquare_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0xa36e2021c3cb4871,0x9ccfdd64549375be,0xfabb3edd8b138d5d,0x1f90d859c5779848};
    //Fr_Rw_Msquare_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0x3ff409a0d3b30d18,0xca2027949dd16d47,0x6c8c4187ce125dad,0x3b5af5c48558e40};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;

    Fr_rawMSquare(pRawResult0_c, pRawA0);
    Fr_rawMSquare(pRawResult1_c, pRawA1);
    Fr_rawMSquare(pRawResult2_c, pRawA2);
    Fr_rawMSquare(pRawResult3_c, pRawA3);

    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawA0, 0, "Fr_Rw_Msquare_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawA1, 1, "Fr_Rw_Msquare_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawA2, 2, "Fr_Rw_Msquare_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawA3, 3, "Fr_Rw_Msquare_unit_test");
}

void Fr_Rw_mul1_unit_test()
{
    //Fr_Rw_mul1_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FrRawElement pRawResult0= {0xf599ddfbad86bc06,0xec1c0a17893c85cd,0x5d482c29ab80ec64,0x4d4face96bf58f3};
    //Fr_Rw_mul1_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB1= {0x2,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39};
    //Fr_Rw_mul1_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x8663902cfae5d423,0x95d2440ac403ddd3,0x1ad411b88e349a0f,0x1ebf106109e4fa8d};
    //Fr_Rw_mul1_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement pRawResult3= {0x35f905313fdf50bb,0x5bab176e33b97efa,0xafd63944c55782d,0x1402c8cfdb71d335};    
    //Fr_Rw_mul1_test 9:
    FrRawElement pRawA9= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    FrRawElement pRawB9= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult9= {0x0,0x0,0x0,0x0};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;
    FrRawElement pRawResult9_c;

    Fr_rawMMul1(pRawResult0_c, pRawA0, pRawB0[0]);
    Fr_rawMMul1(pRawResult1_c, pRawA1, pRawB1[0]);
    Fr_rawMMul1(pRawResult2_c, pRawA2, pRawB2[0]);
    Fr_rawMMul1(pRawResult3_c, pRawA3, pRawB3[0]);
    Fr_rawMMul1(pRawResult9_c, pRawA9, pRawB9[0]);

    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawB0, 0, "Fr_Rw_mul1_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawB1, 1, "Fr_Rw_mul1_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawB2, 2, "Fr_Rw_mul1_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawB3, 3, "Fr_Rw_mul1_unit_test");
    compare_Result(pRawResult9, pRawResult9_c, pRawA9, pRawB9, 9, "Fr_Rw_mul1_unit_test");

}

void Fr_Rw_ToMontgomery_unit_test()
{
    //Fr_Rw_ToMontgomery_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d};
    //Fr_Rw_ToMontgomery_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0xac96341c4ffffffb,0x36fc76959f60cd29,0x666ea36f7879462e,0xe0a77c19a07df2f};
    //Fr_Rw_ToMontgomery_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x5b9a85c0dc5fb590,0x293a0258129f96b,0xd31fd70514055493,0x546132966296a07};
    //Fr_Rw_ToMontgomery_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0x8eaddd03c0bcc45a,0x1d0775cf53f57853,0xacb9a1fdb8079310,0x1b7838d45d9b3577};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;

    Fr_rawToMontgomery(pRawResult0_c, pRawA0);
    Fr_rawToMontgomery(pRawResult1_c, pRawA1);
    Fr_rawToMontgomery(pRawResult2_c, pRawA2);
    Fr_rawToMontgomery(pRawResult3_c, pRawA3);

    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawA0, 0, "Fr_Rw_ToMontgomery_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawA1, 1, "Fr_Rw_ToMontgomery_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawA2, 2, "Fr_Rw_ToMontgomery_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawA3, 3, "Fr_Rw_ToMontgomery_unit_test");
}

void Fr_Rw_IsEq_unit_test()
{
    //Fr_rawIsEq 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawB0= {0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5};
    FrRawElement pRawResult0= {0x0};
    //Fr_rawIsEq 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawB1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x1};
    //Fr_rawIsEq 2:
    FrRawElement pRawA2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawB2= {0xffffffffffffffff,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x1};
    //Fr_rawIsEq 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawB3= {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement pRawResult3= {0x0};

    //Fr_rawIsEq 7:
    FrRawElement pRawA7= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    FrRawElement pRawB7= {0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029};
    FrRawElement pRawResult7= {0x1};

    FrRawElement pRawResult0_c = {0};
    FrRawElement pRawResult1_c = {0};
    FrRawElement pRawResult2_c = {0};
    FrRawElement pRawResult3_c = {0};
    FrRawElement pRawResult7_c = {0};

    pRawResult0_c[0] = Fr_rawIsEq(pRawA0, pRawB0);
    pRawResult1_c[0] = Fr_rawIsEq(pRawA1, pRawB1);
    pRawResult2_c[0] = Fr_rawIsEq(pRawA2, pRawB2);
    pRawResult3_c[0] = Fr_rawIsEq(pRawA3, pRawB3);
    pRawResult7_c[0] = Fr_rawIsEq(pRawA7, pRawB7);

    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawB0, 0, "Fr_Rw_IsEq_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawB1, 1, "Fr_Rw_IsEq_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawB2, 2, "Fr_Rw_IsEq_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawB3, 3, "Fr_Rw_IsEq_unit_test");
    compare_Result(pRawResult7, pRawResult7_c, pRawA7, pRawB7, 7, "Fr_Rw_IsEq_unit_test");
}

void Fr_rawIsZero_unit_test()
{
    //Fr_rawIsZero_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0x0};
    //Fr_rawIsZero_test 1:
    FrRawElement pRawA1= {0x0,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0x1};
    //Fr_rawIsZero_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x0};
    //Fr_rawIsZero_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0x0};

    //Fr_rawIsZero_test 5:
    FrRawElement pRawA5= {0x0,0x0,0x0,0x0};
    FrRawElement pRawResult5= {0x1};

    FrRawElement pRawResult0_c = {0};
    FrRawElement pRawResult1_c = {0};
    FrRawElement pRawResult2_c = {0};
    FrRawElement pRawResult3_c = {0};
    FrRawElement pRawResult5_c = {0};

    pRawResult0_c[0] = Fr_rawIsZero(pRawA0);
    pRawResult1_c[0] = Fr_rawIsZero(pRawA1);
    pRawResult2_c[0] = Fr_rawIsZero(pRawA2);
    pRawResult3_c[0] = Fr_rawIsZero(pRawA3);
    pRawResult5_c[0] = Fr_rawIsZero(pRawA5);

    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawA0, 0, "Fr_rawIsZero_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawA1, 1, "Fr_rawIsZero_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawA2, 2, "Fr_rawIsZero_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawA3, 3, "Fr_rawIsZero_unit_test");
    compare_Result(pRawResult5, pRawResult5_c, pRawA5, pRawA5, 5, "Fr_rawIsZero_unit_test");
}

void Fr_Rw_FromMontgomery_unit_test()
{
    //Fr_Rw_FromMontgomery_test 0:
    FrRawElement pRawA0= {0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014};
    FrRawElement pRawResult0= {0x55b425913927735a,0xa3ac6d7389307a4d,0x543d3ec42a2529ae,0x256e51ca1fcef59b};
    //Fr_Rw_FromMontgomery_test 1:
    FrRawElement pRawA1= {0x1,0x0,0x0,0x0};
    FrRawElement pRawResult1= {0xdc5ba0056db1194e,0x90ef5a9e111ec87,0xc8260de4aeb85d5d,0x15ebf95182c5551c};
    //Fr_Rw_FromMontgomery_test 2:
    FrRawElement pRawA2= {0xfffffffffffffffe,0x0,0x0,0x0};
    FrRawElement pRawResult2= {0x26d7659f271a8bb3,0x21364eeee929d8a6,0xd869189184a2650f,0x2f92867a259f026d};
    //Fr_Rw_FromMontgomery_test 3:
    FrRawElement pRawA3= {0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe,0xfffffffffffffffe};
    FrRawElement pRawResult3= {0x3114fb0a8790445e,0x3c686fb82b0dbda3,0xa509fd6ff15d77e,0x247132c3c886548};

    FrRawElement pRawResult0_c;
    FrRawElement pRawResult1_c;
    FrRawElement pRawResult2_c;
    FrRawElement pRawResult3_c;

    Fr_rawFromMontgomery(pRawResult0_c, pRawA0);
    Fr_rawFromMontgomery(pRawResult1_c, pRawA1);
    Fr_rawFromMontgomery(pRawResult2_c, pRawA2);
    Fr_rawFromMontgomery(pRawResult3_c, pRawA3);

    compare_Result(pRawResult0, pRawResult0_c, pRawA0, pRawA0, 0, "Fr_Rw_FromMontgomery_unit_test");
    compare_Result(pRawResult1, pRawResult1_c, pRawA1, pRawA1, 1, "Fr_Rw_FromMontgomery_unit_test");
    compare_Result(pRawResult2, pRawResult2_c, pRawA2, pRawA2, 2, "Fr_Rw_FromMontgomery_unit_test");
    compare_Result(pRawResult3, pRawResult3_c, pRawA3, pRawA3, 3, "Fr_Rw_FromMontgomery_unit_test");
}


void Fr_copy_unit_test()
{
    //Fr_copy_test 0:
    FrElement pA0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_copy_test 1:
    FrElement pA1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_copy_test 2:
    FrElement pA2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_copy_test 3:
    FrElement pA3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_copy(&Result0_c, &pA0);
    Fr_copy(&Result1_c, &pA1);
    Fr_copy(&Result2_c, &pA2);
    Fr_copy(&Result3_c, &pA3);

    compare_Result(&pResult0, &Result0_c, &pA0, &pA0, 0, "Fr_copy_unit_test");
    compare_Result(&pResult1, &Result1_c, &pA1, &pA1, 1, "Fr_copy_unit_test");
    compare_Result(&pResult2, &Result2_c, &pA2, &pA2, 2, "Fr_copy_unit_test");
    compare_Result(&pResult3, &Result3_c, &pA3, &pA3, 3, "Fr_copy_unit_test");
}

void Fr_copyn_unit_test()
{
    //Fr_copy_test 0:
    FrElement pA0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_copy_test 1:
    FrElement pA1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_copy_test 2:
    FrElement pA2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_copy_test 3:
    FrElement pA3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult3= {0x0,0x0,{0x0,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_copyn(&Result0_c, &pA0,0);
    Fr_copyn(&Result1_c, &pA1,1);
    Fr_copyn(&Result2_c, &pA2,1);
    Fr_copyn(&Result3_c, &pA3,0);

    compare_Result(&pResult0, &Result0_c, &pA0, &pA0, 0, "Fr_copyn_unit_test");
    compare_Result(&pResult1, &Result1_c, &pA1, &pA1, 1, "Fr_copyn_unit_test");
    compare_Result(&pResult2, &Result2_c, &pA2, &pA2, 2, "Fr_copyn_unit_test");
    compare_Result(&pResult3, &Result3_c, &pA3, &pA3, 3, "Fr_copyn_unit_test");
}



void Fr_toNormal_unit_test()
{
    //Fr_toNormal_test 0:
    FrElement pA0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_toNormal_test 1:
    FrElement pA1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_toNormal_test 2:
    FrElement pA2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_toNormal_test 3:
    FrElement pA3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult3= {0x0,0x80000000,{0x55b425913927735a,0xa3ac6d7389307a4d,0x543d3ec42a2529ae,0x256e51ca1fcef59b}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_toNormal(&Result0_c, &pA0);
    Fr_toNormal(&Result1_c, &pA1);
    Fr_toNormal(&Result2_c, &pA2);
    Fr_toNormal(&Result3_c, &pA3);

    compare_Result(&pResult0, &Result0_c, &pA0, &pA0, 0, "Fr_toNormal_unit_test");
    compare_Result(&pResult1, &Result1_c, &pA1, &pA1, 1, "Fr_toNormal_unit_test");
    compare_Result(&pResult2, &Result2_c, &pA2, &pA2, 2, "Fr_toNormal_unit_test");
    compare_Result(&pResult3, &Result3_c, &pA3, &pA3, 3, "Fr_toNormal_unit_test");
}

void Fr_mul_s1s2_unit_test()
{
    //Fr_mul_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_mul_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x0,0x80000000,{0x1188b480,0x0,0x0,0x0}};
    //Fr_mul_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x80000000,{0x3fffffff00000001,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_mul(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_mul(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_mul(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c, &pA_s1s20, &pB_s1s20, 0, "Fr_mul_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c, &pA_s1s21, &pB_s1s21, 1, "Fr_mul_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c, &pA_s1s22, &pB_s1s22, 2, "Fr_mul_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c, &pA_s1s23, &pB_s1s23, 3, "Fr_mul_s1s2_unit_test");
}

void Fr_mul_l1nl2n_unit_test()
{
    //Fr_mul_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0xc0000000,{0x592c68389ffffff6,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_mul_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0xc0000000,{0x1497892315a07fe1,0x930f99e96b3b9535,0x73b1e28430b17066,0x29e821cd214b6d6b}};
    //Fr_mul_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0xc0000000,{0x19094ca438fc19d0,0x4f1502bc99846068,0x5cc3236f2303a977,0x17808a731cd75a48}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_mul(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_mul(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_mul(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c, &pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_mul_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c, &pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_mul_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c, &pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_mul_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c, &pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_mul_l1nl2n_unit_test");
}

void Fr_mul_l1ml2n_unit_test()
{
    //Fr_mul_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0x80000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0x80000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_mul(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_mul(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_mul(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_mul_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_mul_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_mul_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_mul_l1ml2n_unit_test");
}

void Fr_mul_l1ml2m_unit_test()
{
    //Fr_mul_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0xc0000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0xc0000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0xc0000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_mul(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_mul(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_mul(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_mul_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_mul_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_mul_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_mul_l1ml2m_unit_test");
}

void Fr_mul_l1nl2m_unit_test()
{
    //Fr_mul_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0x80000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0x80000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_mul(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_mul(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_mul(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0, 0, "Fr_mul_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1, 1, "Fr_mul_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2, 2, "Fr_mul_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3, 3, "Fr_mul_l1nl2m_unit_test");
}

void Fr_mul_l1ns2n_unit_test()
{
    //Fr_mul_l1ns2n_test 0:
    FrElement pA_l1ns2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns2n0= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns2n0= {0x0,0xc0000000,{0x592c68389ffffff6,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_mul_l1ns2n_test 1:
    FrElement pA_l1ns2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns2n1= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ns2n_test 2:
    FrElement pA_l1ns2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns2n2= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns2n2= {0x0,0xc0000000,{0x2d67d8d2e0004952,0xaddd11ecde7f7ae3,0xed975f635da0de4d,0x1a7fe303489132eb}};
    //Fr_mul_l1ns2n_test 3:
    FrElement pA_l1ns2n3= {0x7fffffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns2n3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns2n3= {0x0,0xc0000000,{0x90dd4dd6a1de9254,0xe2fe3be3bc047346,0xda25203224bdc5a8,0xbf3a7101ab99a89}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ns2n0, &pB_l1ns2n0);
    Fr_mul(&Result1_c, &pA_l1ns2n1, &pB_l1ns2n1);
    Fr_mul(&Result2_c, &pA_l1ns2n2, &pB_l1ns2n2);
    Fr_mul(&Result3_c, &pA_l1ns2n3, &pB_l1ns2n3);

    compare_Result(&pResult_l1ns2n0, &Result0_c,&pA_l1ns2n0, &pB_l1ns2n0, 0, "Fr_mul_l1ns2n_unit_test");
    compare_Result(&pResult_l1ns2n1, &Result1_c,&pA_l1ns2n1, &pB_l1ns2n1, 1, "Fr_mul_l1ns2n_unit_test");
    compare_Result(&pResult_l1ns2n2, &Result2_c,&pA_l1ns2n2, &pB_l1ns2n2, 2, "Fr_mul_l1ns2n_unit_test");
    compare_Result(&pResult_l1ns2n3, &Result3_c,&pA_l1ns2n3, &pB_l1ns2n3, 3, "Fr_mul_l1ns2n_unit_test");
}

void Fr_mul_s1nl2n_unit_test()
{
    //Fr_mul_s1nl2n_test 0:
    FrElement pA_s1nl2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2n0= {0x0,0xc0000000,{0x592c68389ffffff6,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_mul_s1nl2n_test 1:
    FrElement pA_s1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_s1nl2n_test 2:
    FrElement pA_s1nl2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1nl2n2= {0x0,0xc0000000,{0x3c79e7002385099,0x69bfe0da5a608f7b,0x3dbd93ce32b4e2b3,0x773561b6a940451}};
    //Fr_mul_s1nl2n_test 3:
    FrElement pA_s1nl2n3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1nl2n3= {0x7fffffff,0x80000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_s1nl2n3= {0x0,0xc0000000,{0x7c8b07120fa19dd4,0x19b02d60cfbeb467,0xe1f374b7a57d8ed5,0x22a83208b264056d}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_s1nl2n0, &pB_s1nl2n0);
    Fr_mul(&Result1_c, &pA_s1nl2n1, &pB_s1nl2n1);
    Fr_mul(&Result2_c, &pA_s1nl2n2, &pB_s1nl2n2);
    Fr_mul(&Result3_c, &pA_s1nl2n3, &pB_s1nl2n3);

    compare_Result(&pResult_s1nl2n0, &Result0_c,&pA_s1nl2n0, &pB_s1nl2n0, 0, "Fr_mul_s1nl2n_unit_test");
    compare_Result(&pResult_s1nl2n1, &Result1_c,&pA_s1nl2n1, &pB_s1nl2n1, 1, "Fr_mul_s1nl2n_unit_test");
    compare_Result(&pResult_s1nl2n2, &Result2_c,&pA_s1nl2n2, &pB_s1nl2n2, 2, "Fr_mul_s1nl2n_unit_test");
    compare_Result(&pResult_s1nl2n3, &Result3_c,&pA_s1nl2n3, &pB_s1nl2n3, 3, "Fr_mul_s1nl2n_unit_test");
}

void Fr_mul_s1nl2m_unit_test()
{
    //Fr_mul_s1nl2m_test 0:
    FrElement pA_s1nl2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_s1nl2m_test 1:
    FrElement pA_s1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_s1nl2m_test 2:
    FrElement pA_s1nl2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1nl2m2= {0x0,0x80000000,{0xd708561abffca754,0x6c6d984a2702a36a,0xc0f6e8587da122fb,0x164b29d2c31ce3ab}};
    //Fr_mul_s1nl2m_test 3:
    FrElement pA_s1nl2m3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1nl2m3= {0x7fffffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_s1nl2m3= {0x0,0x80000000,{0xab57780eac37ddd2,0x9ffb06c643291bf,0xb327f5cb01f66c9e,0x2f40c4dcc2ed6d85}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_s1nl2m0, &pB_s1nl2m0);
    Fr_mul(&Result1_c, &pA_s1nl2m1, &pB_s1nl2m1);
    Fr_mul(&Result2_c, &pA_s1nl2m2, &pB_s1nl2m2);
    Fr_mul(&Result3_c, &pA_s1nl2m3, &pB_s1nl2m3);

    compare_Result(&pResult_s1nl2m0, &Result0_c,&pA_s1nl2m0, &pB_s1nl2m0, 0, "Fr_mul_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m1, &Result1_c,&pA_s1nl2m1, &pB_s1nl2m1, 1, "Fr_mul_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m2, &Result2_c,&pA_s1nl2m2, &pB_s1nl2m2, 2, "Fr_mul_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m3, &Result3_c,&pA_s1nl2m3, &pB_s1nl2m3, 3, "Fr_mul_s1nl2m_unit_test");
}

void Fr_mul_l1ms2n_unit_test()
{
    //Fr_mul_l1ms2n_test 0:
    FrElement pA_l1ms2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2n0= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1ms2n_test 1:
    FrElement pA_l1ms2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2n1= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ms2n_test 2:
    FrElement pA_l1ms2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2n2= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2n2= {0x0,0x80000000,{0x5d70bdff3d855140,0xfab648d14060e580,0xc8cd54f7f14513ba,0x23995be618ce6b27}};
    //Fr_mul_l1ms2n_test 3:
    FrElement pA_l1ms2n3= {0xffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pB_l1ms2n3= {-1,0x0,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_l1ms2n3= {0x0,0x80000000,{0xab57780eac37ddd2,0x9ffb06c643291bf,0xb327f5cb01f66c9e,0x2f40c4dcc2ed6d85}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ms2n0, &pB_l1ms2n0);
    Fr_mul(&Result1_c, &pA_l1ms2n1, &pB_l1ms2n1);
    Fr_mul(&Result2_c, &pA_l1ms2n2, &pB_l1ms2n2);
    Fr_mul(&Result3_c, &pA_l1ms2n3, &pB_l1ms2n3);

    compare_Result(&pResult_l1ms2n0, &Result0_c,&pA_l1ms2n0, &pB_l1ms2n0, 0, "Fr_mul_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n1, &Result1_c,&pA_l1ms2n1, &pB_l1ms2n1, 1, "Fr_mul_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n2, &Result2_c,&pA_l1ms2n2, &pB_l1ms2n2, 2, "Fr_mul_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n3, &Result3_c,&pA_l1ms2n3, &pB_l1ms2n3, 3, "Fr_mul_l1ms2n_unit_test");
}

void Fr_mul_l1ns2m_unit_test()
{
    //Fr_mul_l1ns2m_test 0:
    FrElement pA_l1ns2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns2m0= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns2m0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1ns2m_test 1:
    FrElement pA_l1ns2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns2m1= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ns2m_test 2:
    FrElement pA_l1ns2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns2m2= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns2m2= {0x0,0x80000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_l1ns2m_test 3:
    FrElement pA_l1ns2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns2m3= {0x0,0x80000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ns2m0, &pB_l1ns2m0);
    Fr_mul(&Result1_c, &pA_l1ns2m1, &pB_l1ns2m1);
    Fr_mul(&Result2_c, &pA_l1ns2m2, &pB_l1ns2m2);
    Fr_mul(&Result3_c, &pA_l1ns2m3, &pB_l1ns2m3);

    compare_Result(&pResult_l1ns2m0, &Result0_c,&pA_l1ns2m0, &pB_l1ns2m0, 0, "Fr_mul_l1ns2m_unit_test");
    compare_Result(&pResult_l1ns2m1, &Result1_c,&pA_l1ns2m1, &pB_l1ns2m1, 1, "Fr_mul_l1ns2m_unit_test");
    compare_Result(&pResult_l1ns2m2, &Result2_c,&pA_l1ns2m2, &pB_l1ns2m2, 2, "Fr_mul_l1ns2m_unit_test");
    compare_Result(&pResult_l1ns2m3, &Result3_c,&pA_l1ns2m3, &pB_l1ns2m3, 3, "Fr_mul_l1ns2m_unit_test");
}

void Fr_mul_l1ms2m_unit_test()
{
    //Fr_mul_l1ms2m_test 0:
    FrElement pA_l1ms2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2m0= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m0= {0x0,0xc0000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_l1ms2m_test 1:
    FrElement pA_l1ms2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2m1= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_l1ms2m_test 2:
    FrElement pA_l1ms2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2m2= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2m2= {0x0,0xc0000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_l1ms2m_test 3:
    FrElement pA_l1ms2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms2m3= {0x0,0xc0000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_l1ms2m0, &pB_l1ms2m0);
    Fr_mul(&Result1_c, &pA_l1ms2m1, &pB_l1ms2m1);
    Fr_mul(&Result2_c, &pA_l1ms2m2, &pB_l1ms2m2);
    Fr_mul(&Result3_c, &pA_l1ms2m3, &pB_l1ms2m3);

    compare_Result(&pResult_l1ms2m0, &Result0_c,&pA_l1ms2m0, &pB_l1ms2m0, 0, "Fr_mul_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m1, &Result1_c,&pA_l1ms2m1, &pB_l1ms2m1, 1, "Fr_mul_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m2, &Result2_c,&pA_l1ms2m2, &pB_l1ms2m2, 2, "Fr_mul_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m3, &Result3_c,&pA_l1ms2m3, &pB_l1ms2m3, 3, "Fr_mul_l1ms2m_unit_test");
}

void Fr_mul_s1ml2m_unit_test()
{
    //Fr_mul_s1ml2m_test 0:
    FrElement pA_s1ml2m0= {0x1,0x40000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m0= {0x0,0xc0000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_s1ml2m_test 1:
    FrElement pA_s1ml2m1= {0x0,0x40000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_s1ml2m_test 2:
    FrElement pA_s1ml2m2= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1ml2m2= {0x0,0xc0000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_s1ml2m_test 3:
    FrElement pA_s1ml2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1ml2m3= {0x0,0xc0000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_s1ml2m0, &pB_s1ml2m0);
    Fr_mul(&Result1_c, &pA_s1ml2m1, &pB_s1ml2m1);
    Fr_mul(&Result2_c, &pA_s1ml2m2, &pB_s1ml2m2);
    Fr_mul(&Result3_c, &pA_s1ml2m3, &pB_s1ml2m3);

    compare_Result(&pResult_s1ml2m0, &Result0_c,&pA_s1ml2m0, &pB_s1ml2m0, 0, "Fr_mul_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m1, &Result1_c,&pA_s1ml2m1, &pB_s1ml2m1, 1, "Fr_mul_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m2, &Result2_c,&pA_s1ml2m2, &pB_s1ml2m2, 2, "Fr_mul_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m3, &Result3_c,&pA_s1ml2m3, &pB_s1ml2m3, 3, "Fr_mul_s1ml2m_unit_test");
}

void Fr_mul_s1ml2n_unit_test()
{
    //Fr_mul_s1ml2n_test 0:
    FrElement pA_s1ml2n0= {0x1,0x40000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2n0= {0x0,0x80000000,{0xb8b7400adb62329c,0x121deb53c223d90f,0x904c1bc95d70baba,0x2bd7f2a3058aaa39}};
    //Fr_mul_s1ml2n_test 1:
    FrElement pA_s1ml2n1= {0x0,0x40000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_mul_s1ml2n_test 2:
    FrElement pA_s1ml2n2= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1ml2n2= {0x0,0x80000000,{0xcba5e0bbd0000003,0x789bb8d96d2c51b3,0x28f0d12384840917,0x112ceb58a394e07d}};
    //Fr_mul_s1ml2n_test 3:
    FrElement pA_s1ml2n3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1ml2n3= {0x0,0x80000000,{0xdea6a001d841e408,0xffd01934b5bef5d1,0xedc4ef0cf4a2b471,0x1d8f65bdb91d796f}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_mul(&Result0_c, &pA_s1ml2n0, &pB_s1ml2n0);
    Fr_mul(&Result1_c, &pA_s1ml2n1, &pB_s1ml2n1);
    Fr_mul(&Result2_c, &pA_s1ml2n2, &pB_s1ml2n2);
    Fr_mul(&Result3_c, &pA_s1ml2n3, &pB_s1ml2n3);

    compare_Result(&pResult_s1ml2n0, &Result0_c,&pA_s1ml2n0, &pB_s1ml2n0, 0, "Fr_mul_s1ml2n_unit_test");
    compare_Result(&pResult_s1ml2n1, &Result1_c,&pA_s1ml2n1, &pB_s1ml2n1, 1, "Fr_mul_s1ml2n_unit_test");
    compare_Result(&pResult_s1ml2n2, &Result2_c,&pA_s1ml2n2, &pB_s1ml2n2, 2, "Fr_mul_s1ml2n_unit_test");
    compare_Result(&pResult_s1ml2n3, &Result3_c,&pA_s1ml2n3, &pB_s1ml2n3, 3, "Fr_mul_s1ml2n_unit_test");
}

void Fr_sub_s1s2_unit_test()
{
    //Fr_sub_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {-1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_sub_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {-2,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_sub_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x8638,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_sub_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_sub(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_sub(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_sub(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c,&pA_s1s20, &pB_s1s20, 0, "Fr_sub_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c,&pA_s1s21, &pB_s1s21, 1, "Fr_sub_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c,&pA_s1s22, &pB_s1s22, 2, "Fr_sub_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c,&pA_s1s23, &pB_s1s23, 3, "Fr_sub_s1s2_unit_test");
}

void Fr_sub_l1nl2n_unit_test()
{
    //Fr_sub_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x80000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x80000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0x80000000,{0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f}};
    //Fr_sub_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_sub(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_sub(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_sub(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c,&pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_sub_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c,&pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_sub_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c,&pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_sub_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c,&pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_sub_l1nl2n_unit_test");
}

void Fr_sub_l1ml2n_unit_test()
{
    //Fr_sub_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0xc0000000,{0xeab58d5b5000000c,0xba3afb1d3af7d63d,0xeb72fed7908ecc00,0x144f5eefad21e1ca}};
    //Fr_sub_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0xc0000000,{0xeab58d5b5000000b,0xba3afb1d3af7d63d,0xeb72fed7908ecc00,0x144f5eefad21e1ca}};
    //Fr_sub_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0xc0000000,{0x435c21e84340ffc0,0x69d157661fe10190,0x52eb5c769f20dc41,0xb39cdedf0cc6a98}};
    //Fr_sub_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0xc0000000,{0x4cfb5842b1de9252,0xbaca539b424b02b5,0x21d4da7ba33c6d4b,0xdb8f589d3987fa60}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_sub(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_sub(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_sub(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_sub_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_sub_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_sub_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_sub_l1ml2n_unit_test");
}

void Fr_sub_l1ml2m_unit_test()
{
    //Fr_sub_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0xc0000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0xc0000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0xc0000000,{0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f}};
    //Fr_sub_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_sub(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_sub(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_sub(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_sub_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_sub_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_sub_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_sub_l1ml2m_unit_test");
}

void Fr_sub_l1nl2m_unit_test()
{
    //Fr_sub_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0xc0000000,{0xac96341c4ffffff9,0x36fc76959f60cd29,0x666ea36f7879462e,0xe0a77c19a07df2f}};
    //Fr_sub_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0xc0000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0xc0000000,{0xafecfa7621de925c,0x249d7e2789cff7d0,0x9ca74de630c88892,0xf161aa724469bd7}};
    //Fr_sub_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0xc0000000,{0xf6e69d513e216daf,0x6d6994ad376e6ddb,0x967b6b3ade44eb11,0x54d4f5d5a7a9a5c9}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_sub(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_sub(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_sub(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0, 0, "Fr_sub_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1, 1, "Fr_sub_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2, 2, "Fr_sub_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3, 3, "Fr_sub_l1nl2m_unit_test");
}

void Fr_sub_s1nl2m_unit_test()
{
    //Fr_sub_s1nl2m_test 0:
    FrElement pA_s1nl2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m0= {0x0,0xc0000000,{0xac96341c4ffffff9,0x36fc76959f60cd29,0x666ea36f7879462e,0xe0a77c19a07df2f}};
    //Fr_sub_s1nl2m_test 1:
    FrElement pA_s1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m1= {0x0,0xc0000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1nl2m_test 2:
    FrElement pA_s1nl2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1nl2m2= {0x0,0xc0000000,{0xbb4f6fd511db39ad,0x186f5d9843a64987,0x34ad651b29e5a276,0x1434592143ce9f06}};
    //Fr_sub_s1nl2m_test 3:
    FrElement pA_s1nl2m3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1nl2m3= {0x7fffffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_s1nl2m3= {0x0,0xc0000000,{0x5b2db70b90000008,0x996b59fb541213f9,0x8a31e7fd8a896a8c,0xd2be2524285b6124}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_s1nl2m0, &pB_s1nl2m0);
    Fr_sub(&Result1_c, &pA_s1nl2m1, &pB_s1nl2m1);
    Fr_sub(&Result2_c, &pA_s1nl2m2, &pB_s1nl2m2);
    Fr_sub(&Result3_c, &pA_s1nl2m3, &pB_s1nl2m3);

    compare_Result(&pResult_s1nl2m0, &Result0_c,&pA_s1nl2m0, &pB_s1nl2m0, 0, "Fr_sub_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m1, &Result1_c,&pA_s1nl2m1, &pB_s1nl2m1, 1, "Fr_sub_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m2, &Result2_c,&pA_s1nl2m2, &pB_s1nl2m2, 2, "Fr_sub_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m3, &Result3_c,&pA_s1nl2m3, &pB_s1nl2m3, 3, "Fr_sub_s1nl2m_unit_test");
}

void Fr_sub_l1ms2n_unit_test()
{
    //Fr_sub_l1ms2n_test 0:
    FrElement pA_l1ms2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2n0= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n0= {0x0,0xc0000000,{0xeab58d5b5000000c,0xba3afb1d3af7d63d,0xeb72fed7908ecc00,0x144f5eefad21e1ca}};
    //Fr_sub_l1ms2n_test 1:
    FrElement pA_l1ms2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2n1= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n1= {0x0,0xc0000000,{0xeab58d5b5000000b,0xba3afb1d3af7d63d,0xeb72fed7908ecc00,0x144f5eefad21e1ca}};
    //Fr_sub_l1ms2n_test 2:
    FrElement pA_l1ms2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2n2= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2n2= {0x0,0xc0000000,{0xb8deb6dbc80092a3,0xc7a02fb580223d7d,0xff069beb7a81106c,0x1ccd9ecd208995c2}};
    //Fr_sub_l1ms2n_test 3:
    FrElement pA_l1ms2n3= {0xffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pB_l1ms2n3= {-1,0x0,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_l1ms2n3= {0x0,0xc0000000,{0xe8b43e885ffffff9,0x8ec88e4d25a75c97,0x2e1e5db8f6f7edd0,0x5da6294eb8d63f05}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1ms2n0, &pB_l1ms2n0);
    Fr_sub(&Result1_c, &pA_l1ms2n1, &pB_l1ms2n1);
    Fr_sub(&Result2_c, &pA_l1ms2n2, &pB_l1ms2n2);
    Fr_sub(&Result3_c, &pA_l1ms2n3, &pB_l1ms2n3);

    compare_Result(&pResult_l1ms2n0, &Result0_c,&pA_l1ms2n0, &pB_l1ms2n0, 0, "Fr_sub_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n1, &Result1_c,&pA_l1ms2n1, &pB_l1ms2n1, 1, "Fr_sub_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n2, &Result2_c,&pA_l1ms2n2, &pB_l1ms2n2, 2, "Fr_sub_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n3, &Result3_c,&pA_l1ms2n3, &pB_l1ms2n3, 3, "Fr_sub_l1ms2n_unit_test");
}

void Fr_sub_l1ms2m_unit_test()
{
    //Fr_sub_l1ms2m_test 0:
    FrElement pA_l1ms2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2m0= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m0= {0x0,0xc0000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ms2m_test 1:
    FrElement pA_l1ms2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2m1= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m1= {0x0,0xc0000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ms2m_test 2:
    FrElement pA_l1ms2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2m2= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2m2= {0x0,0xc0000000,{0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f}};
    //Fr_sub_l1ms2m_test 3:
    FrElement pA_l1ms2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms2m3= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1ms2m0, &pB_l1ms2m0);
    Fr_sub(&Result1_c, &pA_l1ms2m1, &pB_l1ms2m1);
    Fr_sub(&Result2_c, &pA_l1ms2m2, &pB_l1ms2m2);
    Fr_sub(&Result3_c, &pA_l1ms2m3, &pB_l1ms2m3);

    compare_Result(&pResult_l1ms2m0, &Result0_c,&pA_l1ms2m0, &pB_l1ms2m0, 0, "Fr_sub_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m1, &Result1_c,&pA_l1ms2m1, &pB_l1ms2m1, 1, "Fr_sub_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m2, &Result2_c,&pA_l1ms2m2, &pB_l1ms2m2, 2, "Fr_sub_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m3, &Result3_c,&pA_l1ms2m3, &pB_l1ms2m3, 3, "Fr_sub_l1ms2m_unit_test");
}

void Fr_sub_s1ml2m_unit_test()
{
    //Fr_sub_s1ml2m_test 0:
    FrElement pA_s1ml2m0= {0x1,0x40000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m0= {0x0,0xc0000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1ml2m_test 1:
    FrElement pA_s1ml2m1= {0x0,0x40000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m1= {0x0,0xc0000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1ml2m_test 2:
    FrElement pA_s1ml2m2= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1ml2m2= {0x0,0xc0000000,{0x8638148449de9259,0x401bb97259805e65,0x4fde9f9ded052ba9,0x161b5687f14a8b6f}};
    //Fr_sub_s1ml2m_test 3:
    FrElement pA_s1ml2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1ml2m3= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_s1ml2m0, &pB_s1ml2m0);
    Fr_sub(&Result1_c, &pA_s1ml2m1, &pB_s1ml2m1);
    Fr_sub(&Result2_c, &pA_s1ml2m2, &pB_s1ml2m2);
    Fr_sub(&Result3_c, &pA_s1ml2m3, &pB_s1ml2m3);

    compare_Result(&pResult_s1ml2m0, &Result0_c,&pA_s1ml2m0, &pB_s1ml2m0, 0, "Fr_sub_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m1, &Result1_c,&pA_s1ml2m1, &pB_s1ml2m1, 1, "Fr_sub_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m2, &Result2_c,&pA_s1ml2m2, &pB_s1ml2m2, 2, "Fr_sub_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m3, &Result3_c,&pA_s1ml2m3, &pB_s1ml2m3, 3, "Fr_sub_s1ml2m_unit_test");
}

void Fr_sub_l1ns2_unit_test()
{
    //Fr_sub_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x80000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x80000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x0,0x80000000,{0xa1f0fac9f7ffe448,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_sub_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x80000000,{0xffffffffffff0000,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_sub(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_sub(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_sub(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c,&pA_l1ns20, &pB_l1ns20, 0, "Fr_sub_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c, &pA_l1ns21, &pB_l1ns21, 1, "Fr_sub_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c, &pA_l1ns22, &pB_l1ns22, 2, "Fr_sub_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c,&pA_l1ns23, &pB_l1ns23, 3, "Fr_sub_l1ns2_unit_test");
}

void Fr_sub_s1l2n_unit_test()
{
    //Fr_sub_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x80000000,{0x43e1f593f0000000,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x80000000,{0x43e1f593efffffff,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x80000000,{0x28290f4e41df344a,0xd435ad96965d16ae,0x2c06c2792dc5d7d7,0x2e4d7dc161e35b84}};
    //Fr_sub_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x0,0x80000000,{0x43e1f593f0010001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029}};
    //Fr_sub_s1l2n_test 4:
    FrElement pA_s1l2n4= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n4= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n4= {0x0,0x80000000,{0x87c3eb27e0000002,0x5067d090f372e122,0x70a08b6d0302b0ba,0x60c89ce5c2634053}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};
    FrElement Result4_c= {0,0,{0,0,0,0}};

    Fr_sub(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_sub(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_sub(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_sub(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);
    Fr_sub(&Result4_c, &pA_s1l2n4, &pB_s1l2n4);

    compare_Result(&pResult_s1l2n0, &Result0_c,&pA_s1l2n0, &pB_s1l2n0, 0, "Fr_sub_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c,&pA_s1l2n1, &pB_s1l2n1, 1, "Fr_sub_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c,&pA_s1l2n2, &pB_s1l2n2, 2, "Fr_sub_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c,&pA_s1l2n3, &pB_s1l2n3, 3, "Fr_sub_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n4, &Result4_c,&pA_s1l2n4, &pB_s1l2n4, 4, "Fr_sub_s1l2n_unit_test");
}

void Fr_add_s1s2_unit_test()
{
    //Fr_add_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x3,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_add_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x2,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_add_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0xbda8,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_add_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x80000000,{0xfffffffe,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_add(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_add(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_add(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c,&pA_s1s20, &pB_s1s20, 0, "Fr_add_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c,&pA_s1s21, &pB_s1s21, 1, "Fr_add_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c,&pA_s1s22, &pB_s1s22, 2, "Fr_add_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c,&pA_s1s23, &pB_s1s23, 3, "Fr_add_s1s2_unit_test");
}

void Fr_add_l1nl2n_unit_test()
{
    //Fr_add_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x80000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0x80000000,{0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba}};
    //Fr_add_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x80000000,{0xbc1e0a6c0ffffffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_add(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_add(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_add(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c,&pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_add_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c,&pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_add_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c,&pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_add_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c,&pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_add_l1nl2n_unit_test");
}

void Fr_add_l1ml2n_unit_test()
{
    //Fr_add_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0xc0000000,{0x592c68389ffffff7,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_add_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0xc0000000,{0x592c68389ffffff6,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_add_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0xc0000000,{0x85d3abacbf0040,0xbe6290e259d86f01,0x6564e93fe2607c1b,0x252a8084f0653591}};
    //Fr_add_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0xc0000000,{0x6f22b2295e216dab,0x1d01c41c43fb8cb9,0x25dadfcddb423a57,0xf40c58efe5466576}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_add(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_add(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_add(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_add_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_add_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_add_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_add_l1ml2n_unit_test");
}

void Fr_add_l1ml2m_unit_test()
{
    //Fr_add_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0xc0000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0xc0000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0xc0000000,{0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba}};
    //Fr_add_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0xc0000000,{0xbc1e0a6c0ffffffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_add(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_add(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_add(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_add_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_add_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_add_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_add_l1ml2m_unit_test");
}

void Fr_add_l1nl2m_unit_test()
{
    //Fr_add_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0xc0000000,{0xac96341c4ffffffd,0x36fc76959f60cd29,0x666ea36f7879462e,0xe0a77c19a07df2f}};
    //Fr_add_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0xc0000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0xc0000000,{0xe75ec7017e216daa,0xcc99f38b5088ab96,0xb53a5460d83f899c,0x1343bc0a22e32522}};
    //Fr_add_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0xc0000000,{0x6f22b2295e216dab,0x1d01c41c43fb8cb9,0x25dadfcddb423a57,0xf40c58efe5466576}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_add(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_add(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_add(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0, 0, "Fr_add_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1, 1, "Fr_add_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2, 2, "Fr_add_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3, 3, "Fr_add_l1nl2m_unit_test");
}

void Fr_add_s1nl2m_unit_test()
{
    //Fr_add_s1nl2m_test 0:
    FrElement pA_s1nl2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m0= {0x0,0xc0000000,{0xac96341c4ffffffd,0x36fc76959f60cd29,0x666ea36f7879462e,0xe0a77c19a07df2f}};
    //Fr_add_s1nl2m_test 1:
    FrElement pA_s1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1nl2m1= {0x0,0xc0000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_s1nl2m_test 2:
    FrElement pA_s1nl2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1nl2m2= {0x0,0xc0000000,{0xf2c13c606e1e14fb,0xc06bd2fc0a5efd4d,0x4d406b95d15ca380,0x1861fa84426b2851}};
    //Fr_add_s1nl2m_test 3:
    FrElement pA_s1nl2m3= {-1,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1nl2m3= {0x7fffffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_s1nl2m3= {0x0,0xc0000000,{0xd369cbe3b0000004,0x4903896a609f32d5,0x19915c908786b9d1,0x71f5883e65f820d0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_s1nl2m0, &pB_s1nl2m0);
    Fr_add(&Result1_c, &pA_s1nl2m1, &pB_s1nl2m1);
    Fr_add(&Result2_c, &pA_s1nl2m2, &pB_s1nl2m2);
    Fr_add(&Result3_c, &pA_s1nl2m3, &pB_s1nl2m3);

    compare_Result(&pResult_s1nl2m0, &Result0_c,&pA_s1nl2m0, &pB_s1nl2m0, 0, "Fr_add_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m1, &Result1_c,&pA_s1nl2m1, &pB_s1nl2m1, 1, "Fr_add_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m2, &Result2_c,&pA_s1nl2m2, &pB_s1nl2m2, 2, "Fr_add_s1nl2m_unit_test");
    compare_Result(&pResult_s1nl2m3, &Result3_c,&pA_s1nl2m3, &pB_s1nl2m3, 3, "Fr_add_s1nl2m_unit_test");
}

void Fr_add_l1ms2n_unit_test()
{
    //Fr_add_l1ms2n_test 0:
    FrElement pA_l1ms2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2n0= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n0= {0x0,0xc0000000,{0x592c68389ffffff7,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_add_l1ms2n_test 1:
    FrElement pA_l1ms2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2n1= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2n1= {0x0,0xc0000000,{0x592c68389ffffff6,0x6df8ed2b3ec19a53,0xccdd46def0f28c5c,0x1c14ef83340fbe5e}};
    //Fr_add_l1ms2n_test 2:
    FrElement pA_l1ms2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2n2= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2n2= {0x0,0xc0000000,{0x8b033eb827ff6d5d,0x6093b892f9973313,0xb949a9cb070047f0,0x1396afa5c0a80a66}};
    //Fr_add_l1ms2n_test 3:
    FrElement pA_l1ms2n3= {0xffff,0xc0000000,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pB_l1ms2n3= {-1,0x0,{0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff,0x7fffffffffffffff}};
    FrElement pResult_l1ms2n3= {0x0,0xc0000000,{0xd369cbe3b0000004,0x4903896a609f32d5,0x19915c908786b9d1,0x71f5883e65f820d0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1ms2n0, &pB_l1ms2n0);
    Fr_add(&Result1_c, &pA_l1ms2n1, &pB_l1ms2n1);
    Fr_add(&Result2_c, &pA_l1ms2n2, &pB_l1ms2n2);
    Fr_add(&Result3_c, &pA_l1ms2n3, &pB_l1ms2n3);

    compare_Result(&pResult_l1ms2n0, &Result0_c,&pA_l1ms2n0, &pB_l1ms2n0, 0, "Fr_add_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n1, &Result1_c,&pA_l1ms2n1, &pB_l1ms2n1, 1, "Fr_add_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n2, &Result2_c,&pA_l1ms2n2, &pB_l1ms2n2, 2, "Fr_add_l1ms2n_unit_test");
    compare_Result(&pResult_l1ms2n3, &Result3_c,&pA_l1ms2n3, &pB_l1ms2n3, 3, "Fr_add_l1ms2n_unit_test");
}

void Fr_add_l1ms2m_unit_test()
{
    //Fr_add_l1ms2m_test 0:
    FrElement pA_l1ms2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms2m0= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m0= {0x0,0xc0000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_l1ms2m_test 1:
    FrElement pA_l1ms2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms2m1= {0x2,0x40000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms2m1= {0x0,0xc0000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_l1ms2m_test 2:
    FrElement pA_l1ms2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms2m2= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms2m2= {0x0,0xc0000000,{0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba}};
    //Fr_add_l1ms2m_test 3:
    FrElement pA_l1ms2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms2m3= {0x0,0xc0000000,{0xbc1e0a6c0ffffffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1ms2m0, &pB_l1ms2m0);
    Fr_add(&Result1_c, &pA_l1ms2m1, &pB_l1ms2m1);
    Fr_add(&Result2_c, &pA_l1ms2m2, &pB_l1ms2m2);
    Fr_add(&Result3_c, &pA_l1ms2m3, &pB_l1ms2m3);

    compare_Result(&pResult_l1ms2m0, &Result0_c,&pA_l1ms2m0, &pB_l1ms2m0, 0, "Fr_add_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m1, &Result1_c,&pA_l1ms2m1, &pB_l1ms2m1, 1, "Fr_add_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m2, &Result2_c,&pA_l1ms2m2, &pB_l1ms2m2, 2, "Fr_add_l1ms2m_unit_test");
    compare_Result(&pResult_l1ms2m3, &Result3_c,&pA_l1ms2m3, &pB_l1ms2m3, 3, "Fr_add_l1ms2m_unit_test");
}

void Fr_add_s1ml2m_unit_test()
{
    //Fr_add_s1ml2m_test 0:
    FrElement pA_s1ml2m0= {0x1,0x40000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m0= {0x0,0xc0000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_s1ml2m_test 1:
    FrElement pA_s1ml2m1= {0x0,0x40000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1ml2m1= {0x0,0xc0000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_s1ml2m_test 2:
    FrElement pA_s1ml2m2= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1ml2m2= {0x0,0xc0000000,{0xbda9e10fa6216da7,0xe8182ed62039122b,0x6871a618947c2cb3,0x1a48f7eaefe714ba}};
    //Fr_add_s1ml2m_test 3:
    FrElement pA_s1ml2m3= {0xffff,0x40000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1ml2m3= {0x0,0xc0000000,{0xbc1e0a6c0ffffffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_s1ml2m0, &pB_s1ml2m0);
    Fr_add(&Result1_c, &pA_s1ml2m1, &pB_s1ml2m1);
    Fr_add(&Result2_c, &pA_s1ml2m2, &pB_s1ml2m2);
    Fr_add(&Result3_c, &pA_s1ml2m3, &pB_s1ml2m3);

    compare_Result(&pResult_s1ml2m0, &Result0_c,&pA_s1ml2m0, &pB_s1ml2m0, 0, "Fr_add_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m1, &Result1_c,&pA_s1ml2m1, &pB_s1ml2m1, 1, "Fr_add_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m2, &Result2_c,&pA_s1ml2m2, &pB_s1ml2m2, 2, "Fr_add_s1ml2m_unit_test");
    compare_Result(&pResult_s1ml2m3, &Result3_c,&pA_s1ml2m3, &pB_s1ml2m3, 3, "Fr_add_s1ml2m_unit_test");
}

void Fr_add_l1ns2_unit_test()
{
    //Fr_add_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x80000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x0,0x80000000,{0xa1f0fac9f8001bb8,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_add_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x80000000,{0xbc1e0a6c1000fffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_add(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_add(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_add(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c,&pA_l1ns20, &pB_l1ns20, 0, "Fr_add_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c,&pA_l1ns21, &pB_l1ns21, 1, "Fr_add_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c,&pA_l1ns22, &pB_l1ns22, 2, "Fr_add_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c,&pA_l1ns23, &pB_l1ns23, 3, "Fr_add_l1ns2_unit_test");
}

void Fr_add_s1l2n_unit_test()
{
    //Fr_add_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x80000000,{0x3,0x0,0x0,0x0}};
    //Fr_add_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_add_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x80000000,{0x1bb8e645ae220f97,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    //Fr_add_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x0,0x80000000,{0xbc1e0a6c1000fffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xcf9bb18d1ece5fd6}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_add(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_add(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_add(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_add(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c,&pA_s1l2n0, &pB_s1l2n0, 0, "Fr_add_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c,&pA_s1l2n1, &pB_s1l2n1, 1, "Fr_add_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c,&pA_s1l2n2, &pB_s1l2n2, 2, "Fr_add_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c,&pA_s1l2n3, &pB_s1l2n3, 3, "Fr_add_s1l2n_unit_test");
}

void Fr_toInt_unit_test()
{
    //Fr_toInt_test 0:
    FrElement pA0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrRawElement pRawResult0= {0xa1f0};
    //Fr_toInt_test 1:
    FrElement pA1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrRawElement pRawResult1= {0xa1f0};
    //Fr_toInt_test 2:
    FrElement pA2= {0x0,0x80000000,{0xa1f0,0x0,0x0,0x0}};
    FrRawElement pRawResult2= {0xa1f0};

    FrRawElement pRawResult0_c = {0};
    FrRawElement pRawResult1_c = {0};
    FrRawElement pRawResult2_c = {0};

    pRawResult0_c[0] = Fr_toInt(&pA0);
    pRawResult1_c[0] = Fr_toInt(&pA1);
    pRawResult2_c[0] = Fr_toInt(&pA2);

    compare_Result(pRawResult0, pRawResult0_c,&pA0,&pA0, 0, "Fr_toInt_unit_test");
    compare_Result(pRawResult1, pRawResult1_c,&pA1,&pA1, 1, "Fr_toInt_unit_test");
    compare_Result(pRawResult2, pRawResult2_c,&pA2,&pA2, 2, "Fr_toInt_unit_test");
    //compare_rawResult(pRawResult3, pRawResult3_c,pA2,pA2, 3, "Fr_toInt_unit_test");
}

void Fr_lt_s1s2_unit_test()
{
    //Fr_lt_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_lt(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_lt(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_lt(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c,&pA_s1s20, &pB_s1s20, 0, "Fr_lt_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c,&pA_s1s21, &pB_s1s21, 1, "Fr_lt_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c,&pA_s1s22, &pB_s1s22, 2, "Fr_lt_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c,&pA_s1s23, &pB_s1s23, 3, "Fr_lt_s1s2_unit_test");
}

void Fr_lt_l1nl2n_unit_test()
{
    //Fr_lt_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_lt(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_lt(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_lt(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c,&pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_lt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c,&pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_lt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c,&pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_lt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c,&pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_lt_l1nl2n_unit_test");
}

void Fr_lt_l1ml2n_unit_test()
{
    //Fr_lt_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_lt(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_lt(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_lt(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_lt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_lt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_lt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_lt_l1ml2n_unit_test");
}

void Fr_lt_l1ml2m_unit_test()
{
    //Fr_lt_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_lt(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_lt(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_lt(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_lt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_lt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_lt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_lt_l1ml2m_unit_test");
}

void Fr_lt_l1nl2m_unit_test()
{
    //Fr_lt_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_lt(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_lt(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_lt(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0, 0, "Fr_lt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1, 1, "Fr_lt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2, 2, "Fr_lt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3, 3, "Fr_lt_l1nl2m_unit_test");
}

// 6
void Fr_lt_s1l2m_unit_test()
{
    //Fr_lt_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_lt(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_lt(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_lt(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c,&pA_s1l2m0, &pB_s1l2m0, 0, "Fr_lt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c,&pA_s1l2m1, &pB_s1l2m1, 1, "Fr_lt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c,&pA_s1l2m2, &pB_s1l2m2, 2, "Fr_lt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c,&pA_s1l2m3, &pB_s1l2m3, 3, "Fr_lt_s1l2m_unit_test");
}

void Fr_lt_l1ms2_unit_test()
{
    //Fr_lt_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_lt(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_lt(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_lt(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c,&pA_l1ms20, &pB_l1ms20, 0, "Fr_lt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c,&pA_l1ms21, &pB_l1ms21, 1, "Fr_lt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c,&pA_l1ms22, &pB_l1ms22, 2, "Fr_lt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c,&pA_l1ms23, &pB_l1ms23, 3, "Fr_lt_l1ms2_unit_test");
}

void Fr_lt_l1ns2_unit_test()
{
    //Fr_lt_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_lt(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_lt(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_lt(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c,&pA_l1ns20, &pB_l1ns20, 0, "Fr_lt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c,&pA_l1ns21, &pB_l1ns21, 1, "Fr_lt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c,&pA_l1ns22, &pB_l1ns22, 2, "Fr_lt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c,&pA_l1ns23, &pB_l1ns23, 3, "Fr_lt_l1ns2_unit_test");
}

void Fr_lt_s1l2n_unit_test()
{
    //Fr_lt_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lt_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lt(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_lt(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_lt(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_lt(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c,&pA_s1l2n0, &pB_s1l2n0, 0, "Fr_lt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c,&pA_s1l2n1, &pB_s1l2n1, 1, "Fr_lt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c,&pA_s1l2n2, &pB_s1l2n2, 2, "Fr_lt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c,&pA_s1l2n3, &pB_s1l2n3, 3, "Fr_lt_s1l2n_unit_test");
}

void Fr_geq_s1s2_unit_test()
{
    //Fr_geq_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_geq(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_geq(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_geq(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c,&pA_s1s20, &pB_s1s20, 0, "Fr_geq_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c,&pA_s1s21, &pB_s1s21, 1, "Fr_geq_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c,&pA_s1s22, &pB_s1s22, 2, "Fr_geq_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c,&pA_s1s23, &pB_s1s23, 3, "Fr_geq_s1s2_unit_test");
}

void Fr_geq_l1nl2n_unit_test()
{
    //Fr_geq_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_geq(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_geq(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_geq(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c,&pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_geq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c,&pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_geq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c,&pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_geq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c,&pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_geq_l1nl2n_unit_test");
}

void Fr_geq_l1ml2n_unit_test()
{
    //Fr_geq_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_geq(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_geq(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_geq(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_geq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_geq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_geq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_geq_l1ml2n_unit_test");
}

void Fr_geq_l1ml2m_unit_test()
{
    //Fr_geq_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_geq(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_geq(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_geq(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_geq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_geq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_geq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_geq_l1ml2m_unit_test");
}

void Fr_geq_l1nl2m_unit_test()
{
    //Fr_geq_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_geq(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_geq(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_geq(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0, 0, "Fr_geq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1, 1, "Fr_geq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2, 2, "Fr_geq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3, 3, "Fr_geq_l1nl2m_unit_test");
}

void Fr_geq_s1l2m_unit_test()
{
    //Fr_geq_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_geq(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_geq(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_geq(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c,&pA_s1l2m0, &pB_s1l2m0, 0, "Fr_geq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c,&pA_s1l2m1, &pB_s1l2m1, 1, "Fr_geq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c,&pA_s1l2m2, &pB_s1l2m2, 2, "Fr_geq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c,&pA_s1l2m3, &pB_s1l2m3, 3, "Fr_geq_s1l2m_unit_test");
}

void Fr_geq_l1ms2_unit_test()
{
    //Fr_geq_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_geq(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_geq(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_geq(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c,&pA_l1ms20, &pB_l1ms20, 0, "Fr_geq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c,&pA_l1ms21, &pB_l1ms21, 1, "Fr_geq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c,&pA_l1ms22, &pB_l1ms22, 2, "Fr_geq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c, &pA_l1ms23, &pB_l1ms23,3, "Fr_geq_l1ms2_unit_test");
}

void Fr_geq_l1ns2_unit_test()
{
    //Fr_geq_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_geq(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_geq(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_geq(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c, &pA_l1ns20, &pB_l1ns20, 0, "Fr_geq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c,&pA_l1ns21, &pB_l1ns21, 1, "Fr_geq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c,&pA_l1ns22, &pB_l1ns22, 2, "Fr_geq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c,&pA_l1ns23, &pB_l1ns23, 3, "Fr_geq_l1ns2_unit_test");
}

void Fr_geq_s1l2n_unit_test()
{
    //Fr_geq_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_geq_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_geq(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_geq(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_geq(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_geq(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c,&pA_s1l2n0, &pB_s1l2n0, 0, "Fr_geq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c,&pA_s1l2n1, &pB_s1l2n1, 1, "Fr_geq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c,&pA_s1l2n2, &pB_s1l2n2, 2, "Fr_geq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c,&pA_s1l2n3, &pB_s1l2n3, 3, "Fr_geq_s1l2n_unit_test");
}

void Fr_neg_unit_test()
{
    //Fr_neg_test 0:
    FrElement pA0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //FrElement pResult0= {0xffff5e10,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pResult0= {-41456,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neg_test 1:
    FrElement pA1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult1= {-41456,0x0,{0x0,0x0,0x0,0x0}};
    //FrElement pResult1= {0xffff5e10,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neg_test 2:
    FrElement pA2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult2= {0xa1f0,0x80000000,{0xa1f0fac9f8000001,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    //Fr_neg_test 3:
    FrElement pA3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000001,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};

    //Fr_neg_test 4:
    FrElement pA4= {INT_MIN,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult4= {0x0,0x80000000,{0x80000000,0x0,0x0,0x0}};

    //Fr_neg_test 5:
    FrElement pA5= {INT_MAX,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pResult5= {INT_MIN+1, 0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};
    FrElement Result4_c= {0,0,{0,0,0,0}};
    FrElement Result5_c= {0,0,{0,0,0,0}};

    Fr_neg(&Result0_c, &pA0);
    Fr_neg(&Result1_c, &pA1);
    Fr_neg(&Result2_c, &pA2);
    Fr_neg(&Result3_c, &pA3);
    Fr_neg(&Result4_c, &pA4);
    Fr_neg(&Result5_c, &pA5);

    compare_Result(&pResult0, &Result0_c,&pA0,&pA0, 0, "Fr_neg_unit_test");
    compare_Result(&pResult1, &Result1_c,&pA1,&pA1, 1, "Fr_neg_unit_test");
    compare_Result(&pResult2, &Result2_c,&pA2,&pA2, 2, "Fr_neg_unit_test");
    compare_Result(&pResult3, &Result3_c,&pA3,&pA3, 3, "Fr_neg_unit_test");
    compare_Result(&pResult4, &Result4_c,&pA4,&pA4, 4, "Fr_neg_unit_test");
    compare_Result(&pResult5, &Result5_c,&pA5,&pA5, 5, "Fr_neg_unit_test");
}

void Fr_eq_s1s2_unit_test()
{
    //Fr_eq_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_eq(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_eq(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_eq(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c,&pA_s1s20, &pB_s1s20, 0, "Fr_eq_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c,&pA_s1s21, &pB_s1s21, 1, "Fr_eq_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c,&pA_s1s22, &pB_s1s22, 2, "Fr_eq_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c,&pA_s1s23, &pB_s1s23, 3, "Fr_eq_s1s2_unit_test");
}

void Fr_eq_l1nl2n_unit_test()
{
    //Fr_eq_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_eq(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_eq(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_eq(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c,&pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_eq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c,&pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_eq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c,&pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_eq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c,&pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_eq_l1nl2n_unit_test");
}

void Fr_eq_l1ml2n_unit_test()
{
    //Fr_eq_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_eq(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_eq(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_eq(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_eq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_eq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_eq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_eq_l1ml2n_unit_test");
}

void Fr_eq_l1ml2m_unit_test()
{
    //Fr_eq_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_eq(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_eq(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_eq(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_eq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_eq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_eq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_eq_l1ml2m_unit_test");
}

void Fr_eq_l1nl2m_unit_test()
{
    //Fr_eq_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_eq(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_eq(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_eq(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0, 0, "Fr_eq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1, 1, "Fr_eq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2, 2, "Fr_eq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3, 3, "Fr_eq_l1nl2m_unit_test");
}

void Fr_eq_s1l2m_unit_test()
{
    //Fr_eq_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_eq(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_eq(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_eq(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c,&pA_s1l2m0, &pB_s1l2m0, 0, "Fr_eq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c,&pA_s1l2m1, &pB_s1l2m1, 1, "Fr_eq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c, &pA_s1l2m2, &pB_s1l2m2, 2, "Fr_eq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c,&pA_s1l2m3, &pB_s1l2m3, 3, "Fr_eq_s1l2m_unit_test");
}

void Fr_eq_l1ms2_unit_test()
{
    //Fr_eq_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_eq(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_eq(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_eq(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c,&pA_l1ms20, &pB_l1ms20, 0, "Fr_eq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c,&pA_l1ms21, &pB_l1ms21, 1, "Fr_eq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c,&pA_l1ms22, &pB_l1ms22, 2, "Fr_eq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c,&pA_l1ms23, &pB_l1ms23, 3, "Fr_eq_l1ms2_unit_test");
}

void Fr_eq_l1ns2_unit_test()
{
    //Fr_eq_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_eq(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_eq(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_eq(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c,&pA_l1ns20, &pB_l1ns20, 0, "Fr_eq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c,&pA_l1ns21, &pB_l1ns21, 1, "Fr_eq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c,&pA_l1ns22, &pB_l1ns22, 2, "Fr_eq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c,&pA_l1ns23, &pB_l1ns23, 3, "Fr_eq_l1ns2_unit_test");
}

void Fr_eq_s1l2n_unit_test()
{
    //Fr_eq_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_eq_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_eq(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_eq(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_eq(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_eq(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c,&pA_s1l2n0, &pB_s1l2n0, 0, "Fr_eq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c,&pA_s1l2n1, &pB_s1l2n1, 1, "Fr_eq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c,&pA_s1l2n2, &pB_s1l2n2, 2, "Fr_eq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c,&pA_s1l2n3, &pB_s1l2n3, 3, "Fr_eq_s1l2n_unit_test");
}

void Fr_neq_s1s2_unit_test()
{
    //Fr_neq_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_neq(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_neq(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_neq(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c,&pA_s1s20, &pB_s1s20, 0, "Fr_neq_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c,&pA_s1s21, &pB_s1s21, 1, "Fr_neq_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c,&pA_s1s22, &pB_s1s22, 2, "Fr_neq_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c,&pA_s1s23, &pB_s1s23, 3, "Fr_neq_s1s2_unit_test");
}

void Fr_neq_l1nl2n_unit_test()
{
    //Fr_neq_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_neq(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_neq(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_neq(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c,&pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_neq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c,&pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_neq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c,&pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_neq_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c,&pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_neq_l1nl2n_unit_test");
}

void Fr_neq_l1ml2n_unit_test()
{
    //Fr_neq_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_neq(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_neq(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_neq(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_neq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_neq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_neq_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_neq_l1ml2n_unit_test");
}

void Fr_neq_l1ml2m_unit_test()
{
    //Fr_neq_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_neq(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_neq(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_neq(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_neq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_neq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_neq_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_neq_l1ml2m_unit_test");
}

void Fr_neq_l1nl2m_unit_test()
{
    //Fr_neq_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_neq(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_neq(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_neq(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0, 0, "Fr_neq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1, 1, "Fr_neq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2, 2, "Fr_neq_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3, 3, "Fr_neq_l1nl2m_unit_test");
}

// 6
void Fr_neq_s1l2m_unit_test()
{
    //Fr_neq_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_neq(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_neq(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_neq(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c,&pA_s1l2m0, &pB_s1l2m0, 0, "Fr_neq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c,&pA_s1l2m1, &pB_s1l2m1, 1, "Fr_neq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c,&pA_s1l2m2, &pB_s1l2m2, 2, "Fr_neq_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c,&pA_s1l2m3, &pB_s1l2m3, 3, "Fr_neq_s1l2m_unit_test");
}

void Fr_neq_l1ms2_unit_test()
{
    //Fr_neq_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x1,0x0,{0x0,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_neq(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_neq(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_neq(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c,&pA_l1ms20, &pB_l1ms20, 0, "Fr_neq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c,&pA_l1ms21, &pB_l1ms21, 1, "Fr_neq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c,&pA_l1ms22, &pB_l1ms22, 2, "Fr_neq_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c,&pA_l1ms23, &pB_l1ms23, 3, "Fr_neq_l1ms2_unit_test");
}

void Fr_neq_l1ns2_unit_test()
{
    //Fr_neq_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_neq(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_neq(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_neq(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c,&pA_l1ns20, &pB_l1ns20, 0, "Fr_neq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c,&pA_l1ns21, &pB_l1ns21, 1, "Fr_neq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c,&pA_l1ns22, &pB_l1ns22, 2, "Fr_neq_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c,&pA_l1ns23, &pB_l1ns23, 3, "Fr_neq_l1ns2_unit_test");
}

void Fr_neq_s1l2n_unit_test()
{
    //Fr_neq_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_neq_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_neq(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_neq(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_neq(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_neq(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c,&pA_s1l2n0, &pB_s1l2n0, 0, "Fr_neq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c,&pA_s1l2n1, &pB_s1l2n1, 1, "Fr_neq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c,&pA_s1l2n2, &pB_s1l2n2, 2, "Fr_neq_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c,&pA_s1l2n3, &pB_s1l2n3, 3, "Fr_neq_s1l2n_unit_test");
}

void Fr_gt_s1s2_unit_test()
{
    //Fr_gt_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_gt(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_gt(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_gt(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c,&pA_s1s20, &pB_s1s20, 0, "Fr_gt_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c,&pA_s1s21, &pB_s1s21, 1, "Fr_gt_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c,&pA_s1s22, &pB_s1s22, 2, "Fr_gt_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c,&pA_s1s23, &pB_s1s23, 3, "Fr_gt_s1s2_unit_test");
}

void Fr_gt_l1nl2n_unit_test()
{
    //Fr_gt_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_gt(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_gt(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_gt(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c,&pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_gt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c,&pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_gt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c,&pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_gt_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c,&pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_gt_l1nl2n_unit_test");
}

void Fr_gt_l1ml2n_unit_test()
{
    //Fr_gt_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_gt(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_gt(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_gt(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_gt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_gt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_gt_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_gt_l1ml2n_unit_test");
}

void Fr_gt_l1ml2m_unit_test()
{
    //Fr_gt_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_gt(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_gt(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_gt(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_gt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_gt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_gt_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_gt_l1ml2m_unit_test");
}

void Fr_gt_l1nl2m_unit_test()
{
    //Fr_gt_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_gt(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_gt(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_gt(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0,0, "Fr_gt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1,1, "Fr_gt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2,2, "Fr_gt_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3,3, "Fr_gt_l1nl2m_unit_test");
}

void Fr_gt_s1l2m_unit_test()
{
    //Fr_gt_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_gt(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_gt(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_gt(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c,&pA_s1l2m0, &pB_s1l2m0, 0, "Fr_gt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c,&pA_s1l2m1, &pB_s1l2m1, 1, "Fr_gt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c,&pA_s1l2m2, &pB_s1l2m2, 2, "Fr_gt_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c,&pA_s1l2m3, &pB_s1l2m3, 3, "Fr_gt_s1l2m_unit_test");
}

void Fr_gt_l1ms2_unit_test()
{
    //Fr_gt_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x0,0x0,{0x0,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_gt(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_gt(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_gt(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c,&pA_l1ms20, &pB_l1ms20, 0, "Fr_gt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c,&pA_l1ms21, &pB_l1ms21, 1, "Fr_gt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c,&pA_l1ms22, &pB_l1ms22, 2, "Fr_gt_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c,&pA_l1ms23, &pB_l1ms23, 3, "Fr_gt_l1ms2_unit_test");
}

void Fr_gt_l1ns2_unit_test()
{
    //Fr_gt_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_gt(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_gt(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_gt(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c,&pA_l1ns20, &pB_l1ns20, 0, "Fr_gt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c,&pA_l1ns21, &pB_l1ns21, 1, "Fr_gt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c,&pA_l1ns22, &pB_l1ns22, 2, "Fr_gt_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c,&pA_l1ns23, &pB_l1ns23, 3, "Fr_gt_l1ns2_unit_test");
}

void Fr_gt_s1l2n_unit_test()
{
    //Fr_gt_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_gt_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_gt(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_gt(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_gt(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_gt(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c,&pA_s1l2n0, &pB_s1l2n0, 0, "Fr_gt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c,&pA_s1l2n1, &pB_s1l2n1, 1, "Fr_gt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c,&pA_s1l2n2, &pB_s1l2n2, 2, "Fr_gt_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c,&pA_s1l2n3, &pB_s1l2n3, 3, "Fr_gt_s1l2n_unit_test");
}

void Fr_band_s1s2_unit_test()
{
    //Fr_band_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1b0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x7fffffff,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_band(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_band(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_band(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c,&pA_s1s20, &pB_s1s20, 0, "Fr_band_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c,&pA_s1s21, &pB_s1s21, 1, "Fr_band_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c,&pA_s1s22, &pB_s1s22, 2, "Fr_band_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c,&pA_s1s23, &pB_s1s23, 3, "Fr_band_s1s2_unit_test");
}

void Fr_band_l1nl2n_unit_test()
{
    //Fr_band_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x0,0x80000000,{0x1b0e241a8000000,0x10183020205c1840,0x8c08021940808004,0x12003170084004}};
    //Fr_band_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x0,0x80000000,{0xbc1e0a6c0ffffffe,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0xf9bb18d1ece5fd6}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_band(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_band(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_band(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c,&pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_band_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c,&pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_band_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c,&pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_band_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c,&pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_band_l1nl2n_unit_test");
}

void Fr_band_l1ml2n_unit_test()
{
    //Fr_band_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_band_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x0,0x80000000,{0x11b0240128216102,0x3ac283181105841,0x409020402210084,0x650801f4e4481}};
    //Fr_band_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x0,0x80000000,{0x6786558e824ee6b4,0x1f24f29e98a78409,0xf02a37d1d2c8fb00,0x1a7855215e6c4b0c}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_band(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_band(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_band(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_band_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_band_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_band_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_band_l1ml2n_unit_test");
}

void Fr_band_l1ml2m_unit_test()
{
    //Fr_band_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x0,0x80000000,{0x981300004920100c,0xce101c001c807,0x800409c00c301818,0x1c3f00100800018}};
    //Fr_band_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x0,0x80000000,{0x49424100927735a,0x22ac641189204809,0x442c22442821002e,0x40a51c01a06d50b}};
    //Fr_band_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x0,0x80000000,{0x6786558e824ee6b4,0x1f24f29e98a78409,0xf02a37d1d2c8fb00,0x1a7855215e6c4b0c}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_band(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_band(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_band(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_band_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_band_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_band_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_band_l1ml2m_unit_test");
}

void Fr_band_l1nl2m_unit_test()
{
    //Fr_band_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x0,0x80000000,{0xa090300848000000,0x141874041c408808,0x4428224b4040042e,0x80227011000d004}};
    //Fr_band_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x0,0x80000000,{0x6786558e824ee6b4,0x1f24f29e98a78409,0xf02a37d1d2c8fb00,0x1a7855215e6c4b0c}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_band(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_band(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_band(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0, 0, "Fr_band_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1, 1, "Fr_band_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2, 2, "Fr_band_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3, 3, "Fr_band_l1nl2m_unit_test");
}

void Fr_band_s1l2m_unit_test()
{
    //Fr_band_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x0,0x80000000,{0xa1f0,0x0,0x0,0x0}};
    //Fr_band_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x0,0x80000000,{0xe6b4,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_band(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_band(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_band(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c,&pA_s1l2m0, &pB_s1l2m0, 0, "Fr_band_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c,&pA_s1l2m1, &pB_s1l2m1, 1, "Fr_band_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c,&pA_s1l2m2, &pB_s1l2m2, 2, "Fr_band_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c,&pA_s1l2m3, &pB_s1l2m3, 3, "Fr_band_s1l2m_unit_test");
}

void Fr_band_l1ms2_unit_test()
{
    //Fr_band_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x0,0x80000000,{0x2,0x0,0x0,0x0}};
    //Fr_band_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x0,0x80000000,{0x1318,0x0,0x0,0x0}};
    //Fr_band_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x0,0x80000000,{0xe6b4,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_band(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_band(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_band(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c,&pA_l1ms20, &pB_l1ms20, 0, "Fr_band_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c,&pA_l1ms21, &pB_l1ms21, 1, "Fr_band_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c,&pA_l1ms22, &pB_l1ms22, 2, "Fr_band_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c,&pA_l1ms23, &pB_l1ms23, 3, "Fr_band_l1ms2_unit_test");
}

void Fr_band_l1ns2_unit_test()
{
    //Fr_band_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x0,0x80000000,{0xffff,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_band(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_band(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_band(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c,&pA_l1ns20, &pB_l1ns20, 0, "Fr_band_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c,&pA_l1ns21, &pB_l1ns21, 1, "Fr_band_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c,&pA_l1ns22, &pB_l1ns22, 2, "Fr_band_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c,&pA_l1ns23, &pB_l1ns23, 3, "Fr_band_l1ns2_unit_test");
}

void Fr_band_s1l2n_unit_test()
{
    //Fr_band_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    //Fr_band_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x0,0x80000000,{0x21a0,0x0,0x0,0x0}};
    //Fr_band_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x0,0x80000000,{0xffff,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_band(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_band(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_band(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_band(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c,&pA_s1l2n0, &pB_s1l2n0, 0, "Fr_band_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c,&pA_s1l2n1, &pB_s1l2n1, 1, "Fr_band_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c,&pA_s1l2n2, &pB_s1l2n2, 2, "Fr_band_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c,&pA_s1l2n3, &pB_s1l2n3, 3, "Fr_band_s1l2n_unit_test");
}

void Fr_land_s1s2_unit_test()
{
    //Fr_land_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_land(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_land(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_land(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c,&pA_s1s20, &pB_s1s20, 0, "Fr_land_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c,&pA_s1s21, &pB_s1s21, 1, "Fr_land_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c,&pA_s1s22, &pB_s1s22, 2, "Fr_land_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c,&pA_s1s23, &pB_s1s23, 3, "Fr_land_s1s2_unit_test");
}

void Fr_land_l1nl2n_unit_test()
{
    //Fr_land_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_land(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_land(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_land(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c,&pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_land_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c,&pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_land_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c,&pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_land_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c,&pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_land_l1nl2n_unit_test");
}

void Fr_land_l1ml2n_unit_test()
{
    //Fr_land_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_land(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_land(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_land(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_land_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_land_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_land_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_land_l1ml2n_unit_test");
}

void Fr_land_l1ml2m_unit_test()
{
    //Fr_land_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_land(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_land(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_land(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_land_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_land_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_land_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_land_l1ml2m_unit_test");
}

void Fr_land_l1nl2m_unit_test()
{
    //Fr_land_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_land(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_land(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_land(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0, 0, "Fr_land_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1, 1, "Fr_land_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2, 2, "Fr_land_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3, 3, "Fr_land_l1nl2m_unit_test");
}

// 6
void Fr_land_s1l2m_unit_test()
{
    //Fr_land_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_land(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_land(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_land(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c,&pA_s1l2m0, &pB_s1l2m0, 0, "Fr_land_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c,&pA_s1l2m1, &pB_s1l2m1, 1, "Fr_land_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c,&pA_s1l2m2, &pB_s1l2m2, 2, "Fr_land_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c,&pA_s1l2m3, &pB_s1l2m3, 3, "Fr_land_s1l2m_unit_test");
}

void Fr_land_l1ms2_unit_test()
{
    //Fr_land_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x1,0x0,{0x0,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_land(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_land(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_land(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c,&pA_l1ms20, &pB_l1ms20, 0, "Fr_land_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c,&pA_l1ms21, &pB_l1ms21, 1, "Fr_land_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c,&pA_l1ms22, &pB_l1ms22, 2, "Fr_land_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c,&pA_l1ms23, &pB_l1ms23, 3, "Fr_land_l1ms2_unit_test");
}

void Fr_land_l1ns2_unit_test()
{
    //Fr_land_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_land(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_land(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_land(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c,&pA_l1ns20, &pB_l1ns20, 0, "Fr_land_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c,&pA_l1ns21, &pB_l1ns21, 1, "Fr_land_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c,&pA_l1ns22, &pB_l1ns22, 2, "Fr_land_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c,&pA_l1ns23, &pB_l1ns23, 3, "Fr_land_l1ns2_unit_test");
}

void Fr_land_s1l2n_unit_test()
{
    //Fr_land_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_land_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_land(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_land(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_land(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_land(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c,&pA_s1l2n0, &pB_s1l2n0, 0, "Fr_land_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c,&pA_s1l2n1, &pB_s1l2n1, 1, "Fr_land_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c,&pA_s1l2n2, &pB_s1l2n2, 2, "Fr_land_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c,&pA_s1l2n3, &pB_s1l2n3, 3, "Fr_land_s1l2n_unit_test");
}

void Fr_lor_s1s2_unit_test()
{
    //Fr_lor_s1s2_test 0:
    FrElement pA_s1s20= {0x1,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s20= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1s2_test 1:
    FrElement pA_s1s21= {0x0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s21= {0x2,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1s2_test 2:
    FrElement pA_s1s22= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1s2_test 3:
    FrElement pA_s1s23= {0x7fffffff,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1s23= {0x7fffffff,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1s23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_s1s20, &pB_s1s20);
    Fr_lor(&Result1_c, &pA_s1s21, &pB_s1s21);
    Fr_lor(&Result2_c, &pA_s1s22, &pB_s1s22);
    Fr_lor(&Result3_c, &pA_s1s23, &pB_s1s23);

    compare_Result(&pResult_s1s20, &Result0_c,&pA_s1s20, &pB_s1s20, 0, "Fr_lor_s1s2_unit_test");
    compare_Result(&pResult_s1s21, &Result1_c,&pA_s1s21, &pB_s1s21, 1, "Fr_lor_s1s2_unit_test");
    compare_Result(&pResult_s1s22, &Result2_c,&pA_s1s22, &pB_s1s22, 2, "Fr_lor_s1s2_unit_test");
    compare_Result(&pResult_s1s23, &Result3_c,&pA_s1s23, &pB_s1s23, 3, "Fr_lor_s1s2_unit_test");
}

void Fr_lor_l1nl2n_unit_test()
{
    //Fr_lor_l1nl2n_test 0:
    FrElement pA_l1nl2n0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2n_test 1:
    FrElement pA_l1nl2n1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2n_test 2:
    FrElement pA_l1nl2n2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2n_test 3:
    FrElement pA_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1nl2n0, &pB_l1nl2n0);
    Fr_lor(&Result1_c, &pA_l1nl2n1, &pB_l1nl2n1);
    Fr_lor(&Result2_c, &pA_l1nl2n2, &pB_l1nl2n2);
    Fr_lor(&Result3_c, &pA_l1nl2n3, &pB_l1nl2n3);

    compare_Result(&pResult_l1nl2n0, &Result0_c,&pA_l1nl2n0, &pB_l1nl2n0, 0, "Fr_lor_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n1, &Result1_c,&pA_l1nl2n1, &pB_l1nl2n1, 1, "Fr_lor_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n2, &Result2_c,&pA_l1nl2n2, &pB_l1nl2n2, 2, "Fr_lor_l1nl2n_unit_test");
    compare_Result(&pResult_l1nl2n3, &Result3_c,&pA_l1nl2n3, &pB_l1nl2n3, 3, "Fr_lor_l1nl2n_unit_test");
}

void Fr_lor_l1ml2n_unit_test()
{
    //Fr_lor_l1ml2n_test 0:
    FrElement pA_l1ml2n0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2n_test 1:
    FrElement pA_l1ml2n1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2n_test 2:
    FrElement pA_l1ml2n2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2n_test 3:
    FrElement pA_l1ml2n3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1ml2n0, &pB_l1ml2n0);
    Fr_lor(&Result1_c, &pA_l1ml2n1, &pB_l1ml2n1);
    Fr_lor(&Result2_c, &pA_l1ml2n2, &pB_l1ml2n2);
    Fr_lor(&Result3_c, &pA_l1ml2n3, &pB_l1ml2n3);

    compare_Result(&pResult_l1ml2n0, &Result0_c,&pA_l1ml2n0, &pB_l1ml2n0, 0, "Fr_lor_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n1, &Result1_c,&pA_l1ml2n1, &pB_l1ml2n1, 1, "Fr_lor_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n2, &Result2_c,&pA_l1ml2n2, &pB_l1ml2n2, 2, "Fr_lor_l1ml2n_unit_test");
    compare_Result(&pResult_l1ml2n3, &Result3_c,&pA_l1ml2n3, &pB_l1ml2n3, 3, "Fr_lor_l1ml2n_unit_test");
}

void Fr_lor_l1ml2m_unit_test()
{
    //Fr_lor_l1ml2m_test 0:
    FrElement pA_l1ml2m0= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ml2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2m_test 1:
    FrElement pA_l1ml2m1= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ml2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ml2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2m_test 2:
    FrElement pA_l1ml2m2= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ml2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ml2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ml2m_test 3:
    FrElement pA_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ml2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ml2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1ml2m0, &pB_l1ml2m0);
    Fr_lor(&Result1_c, &pA_l1ml2m1, &pB_l1ml2m1);
    Fr_lor(&Result2_c, &pA_l1ml2m2, &pB_l1ml2m2);
    Fr_lor(&Result3_c, &pA_l1ml2m3, &pB_l1ml2m3);

    compare_Result(&pResult_l1ml2m0, &Result0_c,&pA_l1ml2m0, &pB_l1ml2m0, 0, "Fr_lor_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m1, &Result1_c,&pA_l1ml2m1, &pB_l1ml2m1, 1, "Fr_lor_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m2, &Result2_c,&pA_l1ml2m2, &pB_l1ml2m2, 2, "Fr_lor_l1ml2m_unit_test");
    compare_Result(&pResult_l1ml2m3, &Result3_c,&pA_l1ml2m3, &pB_l1ml2m3, 3, "Fr_lor_l1ml2m_unit_test");
}

void Fr_lor_l1nl2m_unit_test()
{
    //Fr_lor_l1nl2m_test 0:
    FrElement pA_l1nl2m0= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1nl2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2m_test 1:
    FrElement pA_l1nl2m1= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1nl2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1nl2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2m_test 2:
    FrElement pA_l1nl2m2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1nl2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1nl2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1nl2m_test 3:
    FrElement pA_l1nl2m3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1nl2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1nl2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1nl2m0, &pB_l1nl2m0);
    Fr_lor(&Result1_c, &pA_l1nl2m1, &pB_l1nl2m1);
    Fr_lor(&Result2_c, &pA_l1nl2m2, &pB_l1nl2m2);
    Fr_lor(&Result3_c, &pA_l1nl2m3, &pB_l1nl2m3);

    compare_Result(&pResult_l1nl2m0, &Result0_c,&pA_l1nl2m0, &pB_l1nl2m0, 0, "Fr_lor_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m1, &Result1_c,&pA_l1nl2m1, &pB_l1nl2m1, 1, "Fr_lor_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m2, &Result2_c,&pA_l1nl2m2, &pB_l1nl2m2, 2, "Fr_lor_l1nl2m_unit_test");
    compare_Result(&pResult_l1nl2m3, &Result3_c,&pA_l1nl2m3, &pB_l1nl2m3, 3, "Fr_lor_l1nl2m_unit_test");
}

// 6
void Fr_lor_s1l2m_unit_test()
{
    //Fr_lor_s1l2m_test 0:
    FrElement pA_s1l2m0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2m0= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2m_test 1:
    FrElement pA_s1l2m1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2m1= {0x2,0xc0000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2m1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2m_test 2:
    FrElement pA_s1l2m2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2m2= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2m2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2m_test 3:
    FrElement pA_s1l2m3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2m3= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2m3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_s1l2m0, &pB_s1l2m0);
    Fr_lor(&Result1_c, &pA_s1l2m1, &pB_s1l2m1);
    Fr_lor(&Result2_c, &pA_s1l2m2, &pB_s1l2m2);
    Fr_lor(&Result3_c, &pA_s1l2m3, &pB_s1l2m3);

    compare_Result(&pResult_s1l2m0, &Result0_c,&pA_s1l2m0, &pB_s1l2m0, 0, "Fr_lor_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m1, &Result1_c,&pA_s1l2m1, &pB_s1l2m1, 1, "Fr_lor_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m2, &Result2_c,&pA_s1l2m2, &pB_s1l2m2, 2, "Fr_lor_s1l2m_unit_test");
    compare_Result(&pResult_s1l2m3, &Result3_c,&pA_s1l2m3, &pB_s1l2m3, 3, "Fr_lor_s1l2m_unit_test");
}

void Fr_lor_l1ms2_unit_test()
{
    //Fr_lor_l1ms2_test 0:
    FrElement pA_l1ms20= {0x1,0xc0000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ms20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ms2_test 1:
    FrElement pA_l1ms21= {0x0,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ms21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ms21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ms2_test 2:
    FrElement pA_l1ms22= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ms22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ms22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ms2_test 3:
    FrElement pA_l1ms23= {0xffff,0xc0000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ms23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ms23= {0x1,0x0,{0x0,0x0,0x0,0x0}};


    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1ms20, &pB_l1ms20);
    Fr_lor(&Result1_c, &pA_l1ms21, &pB_l1ms21);
    Fr_lor(&Result2_c, &pA_l1ms22, &pB_l1ms22);
    Fr_lor(&Result3_c, &pA_l1ms23, &pB_l1ms23);

    compare_Result(&pResult_l1ms20, &Result0_c,&pA_l1ms20, &pB_l1ms20, 0, "Fr_lor_l1ms2_unit_test");
    compare_Result(&pResult_l1ms21, &Result1_c,&pA_l1ms21, &pB_l1ms21, 1, "Fr_lor_l1ms2_unit_test");
    compare_Result(&pResult_l1ms22, &Result2_c,&pA_l1ms22, &pB_l1ms22, 2, "Fr_lor_l1ms2_unit_test");
    compare_Result(&pResult_l1ms23, &Result3_c,&pA_l1ms23, &pB_l1ms23, 3, "Fr_lor_l1ms2_unit_test");
}

void Fr_lor_l1ns2_unit_test()
{
    //Fr_lor_l1ns2_test 0:
    FrElement pA_l1ns20= {0x1,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pB_l1ns20= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns20= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ns2_test 1:
    FrElement pA_l1ns21= {0x0,0x80000000,{0x0,0x0,0x0,0x0}};
    FrElement pB_l1ns21= {0x2,0x0,{0x2,0x0,0x0,0x0}};
    FrElement pResult_l1ns21= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ns2_test 2:
    FrElement pA_l1ns22= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_l1ns22= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_l1ns22= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_l1ns2_test 3:
    FrElement pA_l1ns23= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_l1ns23= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_l1ns23= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_l1ns20, &pB_l1ns20);
    Fr_lor(&Result1_c, &pA_l1ns21, &pB_l1ns21);
    Fr_lor(&Result2_c, &pA_l1ns22, &pB_l1ns22);
    Fr_lor(&Result3_c, &pA_l1ns23, &pB_l1ns23);

    compare_Result(&pResult_l1ns20, &Result0_c,&pA_l1ns20, &pB_l1ns20, 0, "Fr_lor_l1ns2_unit_test");
    compare_Result(&pResult_l1ns21, &Result1_c,&pA_l1ns21, &pB_l1ns21, 1, "Fr_lor_l1ns2_unit_test");
    compare_Result(&pResult_l1ns22, &Result2_c,&pA_l1ns22, &pB_l1ns22, 2, "Fr_lor_l1ns2_unit_test");
    compare_Result(&pResult_l1ns23, &Result3_c,&pA_l1ns23, &pB_l1ns23, 3, "Fr_lor_l1ns2_unit_test");
}

void Fr_lor_s1l2n_unit_test()
{
    //Fr_lor_s1l2n_test 0:
    FrElement pA_s1l2n0= {0x1,0x0,{0x1,0x0,0x0,0x0}};
    FrElement pB_s1l2n0= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n0= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2n_test 1:
    FrElement pA_s1l2n1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pB_s1l2n1= {0x2,0x80000000,{0x2,0x0,0x0,0x0}};
    FrElement pResult_s1l2n1= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2n_test 2:
    FrElement pA_s1l2n2= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB_s1l2n2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult_s1l2n2= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_lor_s1l2n_test 3:
    FrElement pA_s1l2n3= {0xffff,0x0,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pB_s1l2n3= {0xffff,0x80000000,{0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff}};
    FrElement pResult_s1l2n3= {0x1,0x0,{0x0,0x0,0x0,0x0}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    Fr_lor(&Result0_c, &pA_s1l2n0, &pB_s1l2n0);
    Fr_lor(&Result1_c, &pA_s1l2n1, &pB_s1l2n1);
    Fr_lor(&Result2_c, &pA_s1l2n2, &pB_s1l2n2);
    Fr_lor(&Result3_c, &pA_s1l2n3, &pB_s1l2n3);

    compare_Result(&pResult_s1l2n0, &Result0_c,&pA_s1l2n0, &pB_s1l2n0, 0, "Fr_lor_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n1, &Result1_c,&pA_s1l2n1, &pB_s1l2n1, 1, "Fr_lor_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n2, &Result2_c,&pA_s1l2n2, &pB_s1l2n2, 2, "Fr_lor_s1l2n_unit_test");
    compare_Result(&pResult_s1l2n3, &Result3_c,&pA_s1l2n3, &pB_s1l2n3, 3, "Fr_lor_s1l2n_unit_test");
}

void Fr_shr_unit_test()
{
    //Fr_shr_test 0:
    FrElement pA0= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB0= {0x1bb8,0x0,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult0= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_shr_test 1:
    FrElement pA1= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB1= {0x1bb8,0x40000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult1= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_shr_test 2:
    FrElement pA2= {0xa1f0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB2= {0x1bb8,0x80000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult2= {0x0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_shr_test 3:
    FrElement pA3= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB3= {0x1bb8,0xc0000000,{0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5}};
    FrElement pResult3= {0x0,0x0,{0x0,0x0,0x0,0x0}};

    //Fr_shr_test 5:
    FrElement pA5= {0xa1f0,0x0,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB5= {0x1,0x0,{0x0,0x0,0x0,0x0}};
    FrElement pResult5= {0x50f8,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_shr_test 6:
    FrElement pA6= {0xa1f0,0x40000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB6= {-1,0x40000000,{0x0,0x0,0x0,0x0}};
    FrElement pResult6= {0x143e0,0x0,{0x0,0x0,0x0,0x0}};
    //Fr_shr_test 7:
    FrElement pA7= {0x0,0x80000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB7= {0x0,0x80000000,{0x1,0x0,0x0,0x0}};
    FrElement pResult7= {0x0,0x80000000,{0x50f87d64fc000000,0x4a0cfa121e6e5c24,0x6e14116da0605617,0xc19139cb84c680a}};
    //Fr_shr_test 8:
    FrElement pA8= {0xa1f0,0xc0000000,{0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014}};
    FrElement pB8= {-1,0xc0000000,{0x0,0x0,0x0,0x0}};
    FrElement pResult8= {0x0,0x80000000,{0x55b425913927735a,0xa3ac6d7389307a4d,0x543d3ec42a2529ae,0x256e51ca1fcef59b}};

    FrElement Result0_c = {0,0,{0,0,0,0}};
    FrElement Result1_c = {0,0,{0,0,0,0}};
    FrElement Result2_c= {0,0,{0,0,0,0}};
    FrElement Result3_c= {0,0,{0,0,0,0}};

    FrElement Result5_c = {0,0,{0,0,0,0}};
    FrElement Result6_c = {0,0,{0,0,0,0}};
    FrElement Result7_c= {0,0,{0,0,0,0}};
    FrElement Result8_c= {0,0,{0,0,0,0}};

    Fr_shr(&Result0_c, &pA0, &pB0);
    Fr_shr(&Result1_c, &pA1, &pB1);
    Fr_shr(&Result2_c, &pA2, &pB2);
    Fr_shr(&Result3_c, &pA3, &pB3);

    Fr_shr(&Result5_c, &pA5, &pB5);
    Fr_shr(&Result6_c, &pA6, &pB6);
    Fr_shr(&Result7_c, &pA7, &pB7);
    Fr_shr(&Result8_c, &pA8, &pB8);

    compare_Result(&pResult0, &Result0_c,&pA0, &pB0, 0, "Fr_shr_unit_test");
    compare_Result(&pResult1, &Result1_c,&pA1, &pB1, 1, "Fr_shr_unit_test");
    compare_Result(&pResult2, &Result2_c,&pA2, &pB2, 2, "Fr_shr_unit_test");
    compare_Result(&pResult3, &Result3_c,&pA3, &pB3, 3, "Fr_shr_unit_test");

    compare_Result(&pResult5, &Result5_c,&pA5, &pB5, 5, "Fr_shr_unit_test");
    compare_Result(&pResult6, &Result6_c,&pA6, &pB6, 6, "Fr_shr_unit_test");
    compare_Result(&pResult7, &Result7_c,&pA7, &pB7, 7, "Fr_shr_unit_test");
    compare_Result(&pResult8, &Result8_c,&pA8, &pB8, 8, "Fr_shr_unit_test");
}

void Fr_rawShr_test(FrRawElement r_expected, FrRawElement a, uint64_t b)
{
    FrRawElement r_computed = {0xbadbadbadbadbadb,0xadbadbadbadbadba,0xdbadbadbadbadbad,0xbadbadbadbadbadb};

    Fr_rawShr(r_computed, a, b);

    compare_Result(r_expected, r_computed, a, b, (int)b, __func__);
}

void Fr_rawShr_unit_test()
{
    FrRawElement rawA1     = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement rawA2     = {0xaaaaaaaaaaaaaaaa,0xaaaaaaaaaaaaaaaa,0xaaaaaaaaaaaaaaaa,0xaaaaaaaaaaaaaaaa};

    FrRawElement result1   = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x7fffffffffffffff};
    FrRawElement result2   = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x3fffffffffffffff};
    FrRawElement result3   = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x1fffffffffffffff};
    FrRawElement result4   = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x0fffffffffffffff};

    FrRawElement result7   = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x01ffffffffffffff};
    FrRawElement result8   = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x00ffffffffffffff};
    FrRawElement result9   = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x007fffffffffffff};

    FrRawElement result15  = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x0001ffffffffffff};
    FrRawElement result16  = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x0000ffffffffffff};
    FrRawElement result17  = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x00007fffffffffff};

    FrRawElement result30  = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x00000003ffffffff};
    FrRawElement result31  = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x00000001ffffffff};
    FrRawElement result32  = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x00000000ffffffff};
    FrRawElement result33  = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x000000007fffffff};
    FrRawElement result34  = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x000000003fffffff};

    FrRawElement result63  = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x0000000000000001};
    FrRawElement result64  = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x0000000000000000};
    FrRawElement result65  = {0xffffffffffffffff,0xffffffffffffffff,0x7fffffffffffffff,0x0000000000000000};

    FrRawElement result95  = {0xffffffffffffffff,0xffffffffffffffff,0x00000001ffffffff,0x0000000000000000};
    FrRawElement result96  = {0xffffffffffffffff,0xffffffffffffffff,0x00000000ffffffff,0x0000000000000000};
    FrRawElement result97  = {0xffffffffffffffff,0xffffffffffffffff,0x000000007fffffff,0x0000000000000000};

    FrRawElement result127 = {0xffffffffffffffff,0xffffffffffffffff,0x0000000000000001,0x0000000000000000};
    FrRawElement result128 = {0xffffffffffffffff,0xffffffffffffffff,0x0000000000000000,0x0000000000000000};
    FrRawElement result129 = {0xffffffffffffffff,0x7fffffffffffffff,0x0000000000000000,0x0000000000000000};

    FrRawElement result159 = {0x5555555555555555,0x0000000155555555,0x0000000000000000,0x0000000000000000};
    FrRawElement result160 = {0xaaaaaaaaaaaaaaaa,0x00000000aaaaaaaa,0x0000000000000000,0x0000000000000000};
    FrRawElement result161 = {0x5555555555555555,0x0000000055555555,0x0000000000000000,0x0000000000000000};

    FrRawElement result191 = {0x5555555555555555,0x0000000000000001,0x0000000000000000,0x0000000000000000};
    FrRawElement result192 = {0xaaaaaaaaaaaaaaaa,0x0000000000000000,0x0000000000000000,0x0000000000000000};
    FrRawElement result193 = {0x5555555555555555,0x0000000000000000,0x0000000000000000,0x0000000000000000};

    FrRawElement result223 = {0x0000000155555555,0x0000000000000000,0x0000000000000000,0x0000000000000000};
    FrRawElement result224 = {0x00000000aaaaaaaa,0x0000000000000000,0x0000000000000000,0x0000000000000000};
    FrRawElement result225 = {0x0000000055555555,0x0000000000000000,0x0000000000000000,0x0000000000000000};

    FrRawElement result250 = {0x000000000000003f,0x0000000000000000,0x0000000000000000,0x0000000000000000};
    FrRawElement result251 = {0x000000000000001f,0x0000000000000000,0x0000000000000000,0x0000000000000000};
    FrRawElement result252 = {0x000000000000000f,0x0000000000000000,0x0000000000000000,0x0000000000000000};
    FrRawElement result253 = {0x0000000000000007,0x0000000000000000,0x0000000000000000,0x0000000000000000};

    Fr_rawShr_test(result1, rawA1, 1);
    Fr_rawShr_test(result2, rawA1, 2);
    Fr_rawShr_test(result3, rawA1, 3);
    Fr_rawShr_test(result4, rawA1, 4);

    Fr_rawShr_test(result7, rawA1, 7);
    Fr_rawShr_test(result8, rawA1, 8);
    Fr_rawShr_test(result9, rawA1, 9);

    Fr_rawShr_test(result15, rawA1, 15);
    Fr_rawShr_test(result16, rawA1, 16);
    Fr_rawShr_test(result17, rawA1, 17);

    Fr_rawShr_test(result30, rawA1, 30);
    Fr_rawShr_test(result31, rawA1, 31);
    Fr_rawShr_test(result32, rawA1, 32);
    Fr_rawShr_test(result33, rawA1, 33);
    Fr_rawShr_test(result34, rawA1, 34);

    Fr_rawShr_test(result63, rawA1, 63);
    Fr_rawShr_test(result64, rawA1, 64);
    Fr_rawShr_test(result65, rawA1, 65);

    Fr_rawShr_test(result95, rawA1, 95);
    Fr_rawShr_test(result96, rawA1, 96);
    Fr_rawShr_test(result97, rawA1, 97);

    Fr_rawShr_test(result127, rawA1, 127);
    Fr_rawShr_test(result128, rawA1, 128);
    Fr_rawShr_test(result129, rawA1, 129);

    Fr_rawShr_test(result159, rawA2, 159);
    Fr_rawShr_test(result160, rawA2, 160);
    Fr_rawShr_test(result161, rawA2, 161);

    Fr_rawShr_test(result191, rawA2, 191);
    Fr_rawShr_test(result192, rawA2, 192);
    Fr_rawShr_test(result193, rawA2, 193);

    Fr_rawShr_test(result223, rawA2, 223);
    Fr_rawShr_test(result224, rawA2, 224);
    Fr_rawShr_test(result225, rawA2, 225);

    Fr_rawShr_test(result250, rawA1, 250);
    Fr_rawShr_test(result251, rawA1, 251);
    Fr_rawShr_test(result252, rawA1, 252);
    Fr_rawShr_test(result253, rawA1, 253);
}

void Fr_rawShl_test(FrRawElement r_expected, FrRawElement a, uint64_t b)
{
    FrRawElement r_computed = {0xbadbadbadbadbadb,0xadbadbadbadbadba,0xdbadbadbadbadbad,0xbadbadbadbadbadb};

    Fr_rawShl(r_computed, a, b);

    compare_Result(r_expected, r_computed, a, b, (int)b, __func__);
}

void Fr_rawShl_unit_test()
{
    FrRawElement rawA1     = {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
    FrRawElement rawA2     = {0xaaaaaaaaaaaaaaaa,0xaaaaaaaaaaaaaaaa,0xaaaaaaaaaaaaaaaa,0xaaaaaaaaaaaaaaaa};

    FrRawElement result1   = {0xbc1e0a6c0ffffffd,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result2   = {0xbc1e0a6c0ffffffb,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result3   = {0xbc1e0a6c0ffffff7,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result4   = {0xbc1e0a6c0fffffef,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};

    FrRawElement result7   = {0xbc1e0a6c0fffff7f,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result8   = {0xbc1e0a6c0ffffeff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result9   = {0xbc1e0a6c0ffffdff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};

    FrRawElement result15  = {0xbc1e0a6c0fff7fff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result16  = {0xbc1e0a6c0ffeffff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result17  = {0xbc1e0a6c0ffdffff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};

    FrRawElement result30  = {0xbc1e0a6bcfffffff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result31  = {0xbc1e0a6b8fffffff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result32  = {0xbc1e0a6b0fffffff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result33  = {0xbc1e0a6a0fffffff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result34  = {0xbc1e0a680fffffff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};

    FrRawElement result63  = {0x3c1e0a6c0fffffff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result64  = {0xbc1e0a6c0fffffff,0xd7cc17b786468f6d,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result65  = {0xbc1e0a6c0fffffff,0xd7cc17b786468f6c,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};

    FrRawElement result95  = {0xbc1e0a6c0fffffff,0xd7cc17b706468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result96  = {0xbc1e0a6c0fffffff,0xd7cc17b686468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result97  = {0xbc1e0a6c0fffffff,0xd7cc17b586468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};

    FrRawElement result127 = {0xbc1e0a6c0fffffff,0x57cc17b786468f6e,0x47afba497e7ea7a2,0x0f9bb18d1ece5fd6};
    FrRawElement result128 = {0xbc1e0a6c0fffffff,0xd7cc17b786468f6e,0x47afba497e7ea7a1,0x0f9bb18d1ece5fd6};
    FrRawElement result129 = {0xbc1e0a6c0fffffff,0xd7cc17b786468f6e,0x47afba497e7ea7a0,0x0f9bb18d1ece5fd6};

    FrRawElement result159 = {0x0000000000000000,0x0000000000000000,0x5555555500000000,0x1555555555555555};
    FrRawElement result160 = {0x0000000000000000,0x0000000000000000,0xaaaaaaaa00000000,0x2aaaaaaaaaaaaaaa};
    FrRawElement result161 = {0x0000000000000000,0x0000000000000000,0x5555555400000000,0x1555555555555555};

    FrRawElement result191 = {0x0000000000000000,0x0000000000000000,0x0000000000000000,0x1555555555555555};
    FrRawElement result192 = {0x0000000000000000,0x0000000000000000,0x0000000000000000,0x2aaaaaaaaaaaaaaa};
    FrRawElement result193 = {0x0000000000000000,0x0000000000000000,0x0000000000000000,0x1555555555555554};

    FrRawElement result223 = {0x0000000000000000,0x0000000000000000,0x0000000000000000,0x1555555500000000};
    FrRawElement result224 = {0x0000000000000000,0x0000000000000000,0x0000000000000000,0x2aaaaaaa00000000};
    FrRawElement result225 = {0x0000000000000000,0x0000000000000000,0x0000000000000000,0x1555555400000000};

    FrRawElement result250 = {0xbc1e0a6c0fffffff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x0b9bb18d1ece5fd6};
    FrRawElement result251 = {0xbc1e0a6c0fffffff,0xd7cc17b786468f6e,0x47afba497e7ea7a2,0x079bb18d1ece5fd6};
    FrRawElement result252 = {0x0000000000000000,0x0000000000000000,0x0000000000000000,0x3000000000000000};
    FrRawElement result253 = {0x0000000000000000,0x0000000000000000,0x0000000000000000,0x2000000000000000};

    Fr_rawShl_test(result1, rawA1, 1);
    Fr_rawShl_test(result2, rawA1, 2);
    Fr_rawShl_test(result3, rawA1, 3);
    Fr_rawShl_test(result4, rawA1, 4);

    Fr_rawShl_test(result7, rawA1, 7);
    Fr_rawShl_test(result8, rawA1, 8);
    Fr_rawShl_test(result9, rawA1, 9);

    Fr_rawShl_test(result15, rawA1, 15);
    Fr_rawShl_test(result16, rawA1, 16);
    Fr_rawShl_test(result17, rawA1, 17);

    Fr_rawShl_test(result30, rawA1, 30);
    Fr_rawShl_test(result31, rawA1, 31);
    Fr_rawShl_test(result32, rawA1, 32);
    Fr_rawShl_test(result33, rawA1, 33);
    Fr_rawShl_test(result34, rawA1, 34);

    Fr_rawShl_test(result63, rawA1, 63);
    Fr_rawShl_test(result64, rawA1, 64);
    Fr_rawShl_test(result65, rawA1, 65);

    Fr_rawShl_test(result95, rawA1, 95);
    Fr_rawShl_test(result96, rawA1, 96);
    Fr_rawShl_test(result97, rawA1, 97);

    Fr_rawShl_test(result127, rawA1, 127);
    Fr_rawShl_test(result128, rawA1, 128);
    Fr_rawShl_test(result129, rawA1, 129);

    Fr_rawShl_test(result159, rawA2, 159);
    Fr_rawShl_test(result160, rawA2, 160);
    Fr_rawShl_test(result161, rawA2, 161);

    Fr_rawShl_test(result191, rawA2, 191);
    Fr_rawShl_test(result192, rawA2, 192);
    Fr_rawShl_test(result193, rawA2, 193);

    Fr_rawShl_test(result223, rawA2, 223);
    Fr_rawShl_test(result224, rawA2, 224);
    Fr_rawShl_test(result225, rawA2, 225);

    Fr_rawShl_test(result250, rawA1, 250);
    Fr_rawShl_test(result251, rawA1, 251);
    Fr_rawShl_test(result252, rawA1, 252);
    Fr_rawShl_test(result253, rawA1, 253);
}

void print_results()
{
    std::cout << "Results: " << std::dec << tests_run << " tests were run, " << tests_failed << " failed." << std::endl;
}

int main()
{
    Fr_Rw_add_unit_test();
    Fr_Rw_sub_unit_test();
    Fr_Rw_copy_unit_test();
    Fr_Rw_Neg_unit_test();
    Fr_Rw_mul_unit_test();
    Fr_Rw_Msquare_unit_test();
    Fr_Rw_mul1_unit_test();
    Fr_Rw_ToMontgomery_unit_test();
    Fr_Rw_IsEq_unit_test();
    Fr_rawIsZero_unit_test();
    Fr_Rw_FromMontgomery_unit_test();
    Fr_toNormal_unit_test();
    Fr_copy_unit_test();
    Fr_copyn_unit_test();
    Fr_mul_s1s2_unit_test();
    Fr_mul_l1nl2n_unit_test();
    Fr_mul_l1ml2n_unit_test();
    Fr_mul_l1ml2m_unit_test();
    Fr_mul_l1nl2m_unit_test();
    Fr_mul_l1ns2n_unit_test();
    Fr_mul_s1nl2n_unit_test();
    Fr_mul_s1nl2m_unit_test();
    Fr_mul_l1ms2n_unit_test();
    Fr_mul_l1ns2m_unit_test();
    Fr_mul_l1ms2m_unit_test();
    Fr_mul_s1ml2m_unit_test();
    Fr_mul_s1ml2n_unit_test();
    Fr_sub_s1s2_unit_test();
    Fr_sub_l1nl2n_unit_test();
    Fr_sub_l1ml2n_unit_test();
    Fr_sub_l1ml2m_unit_test();
    Fr_sub_l1nl2m_unit_test();
    Fr_sub_s1nl2m_unit_test();
    Fr_sub_l1ms2n_unit_test();
    Fr_sub_l1ms2m_unit_test();
    Fr_sub_s1ml2m_unit_test();
    Fr_sub_l1ns2_unit_test();
    Fr_sub_s1l2n_unit_test();
    Fr_add_s1s2_unit_test();
    Fr_add_l1nl2n_unit_test();
    Fr_add_l1ml2n_unit_test();
    Fr_add_l1ml2m_unit_test();
    Fr_add_l1nl2m_unit_test();
    Fr_add_s1nl2m_unit_test();
    Fr_add_l1ms2n_unit_test();
    Fr_add_l1ms2m_unit_test();
    Fr_add_s1ml2m_unit_test();
    Fr_add_l1ns2_unit_test();
    Fr_add_s1l2n_unit_test();
    Fr_geq_s1s2_unit_test();
    Fr_geq_l1nl2n_unit_test();
    Fr_geq_l1ml2n_unit_test();
    Fr_geq_l1ml2m_unit_test();
    Fr_geq_l1nl2m_unit_test();
    Fr_geq_s1l2m_unit_test();
    Fr_geq_l1ms2_unit_test();
    Fr_geq_l1ns2_unit_test();
    Fr_geq_s1l2n_unit_test();
    Fr_eq_s1s2_unit_test();
    Fr_eq_l1nl2n_unit_test();
    Fr_eq_l1ml2n_unit_test();
    Fr_eq_l1ml2m_unit_test();
    Fr_eq_l1nl2m_unit_test();
    Fr_eq_s1l2m_unit_test();
    Fr_eq_l1ms2_unit_test();
    Fr_eq_l1ns2_unit_test();
    Fr_eq_s1l2n_unit_test();
    Fr_neq_s1s2_unit_test();
    Fr_neq_l1nl2n_unit_test();
    Fr_neq_l1ml2n_unit_test();
    Fr_neq_l1ml2m_unit_test();
    Fr_neq_l1nl2m_unit_test();
    Fr_neq_s1l2m_unit_test();
    Fr_neq_l1ms2_unit_test();
    Fr_neq_l1ns2_unit_test();
    Fr_neq_s1l2n_unit_test();
    Fr_gt_s1s2_unit_test();
    Fr_gt_l1nl2n_unit_test();
    Fr_gt_l1ml2n_unit_test();
    Fr_gt_l1ml2m_unit_test();
    Fr_gt_l1nl2m_unit_test();
    Fr_gt_s1l2m_unit_test();
    Fr_gt_l1ms2_unit_test();
    Fr_gt_l1ns2_unit_test();
    Fr_gt_s1l2n_unit_test();
    Fr_band_s1s2_unit_test();
    Fr_band_l1nl2n_unit_test();
    Fr_band_l1ml2n_unit_test();
    Fr_band_l1ml2m_unit_test();
    Fr_band_l1nl2m_unit_test();
    Fr_band_s1l2m_unit_test();
    Fr_band_l1ms2_unit_test();
    Fr_band_l1ns2_unit_test();
    Fr_band_s1l2n_unit_test();
    Fr_land_s1s2_unit_test();
    Fr_land_l1nl2n_unit_test();
    Fr_land_l1ml2n_unit_test();
    Fr_land_l1ml2m_unit_test();
    Fr_land_l1nl2m_unit_test();
    Fr_land_s1l2m_unit_test();
    Fr_land_l1ms2_unit_test();
    Fr_land_l1ns2_unit_test();
    Fr_land_s1l2n_unit_test();
    Fr_lor_s1s2_unit_test();
    Fr_lor_l1nl2n_unit_test();
    Fr_lor_l1ml2n_unit_test();
    Fr_lor_l1ml2m_unit_test();
    Fr_lor_l1nl2m_unit_test();
    Fr_lor_s1l2m_unit_test();
    Fr_lor_l1ms2_unit_test();
    Fr_lor_l1ns2_unit_test();
    Fr_lor_s1l2n_unit_test();
    Fr_lt_s1s2_unit_test();
    Fr_lt_l1nl2n_unit_test();
    Fr_lt_l1ml2n_unit_test();
    Fr_lt_l1ml2m_unit_test();
    Fr_lt_l1nl2m_unit_test();
    Fr_lt_s1l2m_unit_test();
    Fr_lt_l1ms2_unit_test();
    Fr_lt_l1ns2_unit_test();
    Fr_lt_s1l2n_unit_test();
    Fr_toInt_unit_test();
    Fr_neg_unit_test();
    Fr_shr_unit_test();
    Fr_rawShr_unit_test();
    Fr_rawShl_unit_test();

    print_results();

    return tests_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
