#include <gtest/gtest.h>
#include "BigInt.cpp"

TEST(incrTest, increment)
{
	const std::vector<std::pair<BigInt, BigInt>> ExpectedList = {
		{ BigInt("0"), BigInt("1") },
	        { BigInt("-34464"), BigInt("-34463") },
       		{ BigInt("-10000"), BigInt("-9999") },
        	{ BigInt("99999"), BigInt("100000") }
	};
	for(auto [num, num_plus_one] : ExpectedList)
	{
	        EXPECT_EQ(++num, num_plus_one);
    	}
}
TEST(decrTest, decrement)
{
	const std::vector<std::pair<BigInt, BigInt>> ExpectedList = {
                { BigInt("0"), BigInt("-1") },
                { BigInt("100"), BigInt("99") },
                { BigInt("-99"), BigInt("-100") },
                { BigInt("288288282"), BigInt("288288281") }
        };
	for(auto [num, num_minus_one] : ExpectedList)
        {
                EXPECT_EQ(--num, num_minus_one);
        }
}

TEST(sumTest, adding)
{
        ASSERT_EQ(BigInt("-1") + BigInt("1"), BigInt("0"));
	ASSERT_EQ(BigInt("0") + BigInt("-50"), BigInt("-50"));
  	ASSERT_EQ(BigInt("-101") + BigInt("97"), BigInt("-4"));
   	ASSERT_EQ(BigInt("120") + BigInt("-115"), BigInt("5"));
      

}

TEST(substractTest, substraction)
{
	ASSERT_EQ(BigInt("0"), BigInt("100") - BigInt("100"));
        ASSERT_EQ(BigInt("100"), BigInt("97") - BigInt("-3"));
        ASSERT_EQ(BigInt("-111"), BigInt("-100") - BigInt("11"));
        ASSERT_EQ(BigInt("-8"), BigInt("-333") - BigInt("-325"));
}

TEST(mulTest, multiplication)
{
	ASSERT_EQ(BigInt("0") * BigInt("-23"), BigInt("0"));
	ASSERT_EQ(BigInt("-10") * BigInt("10"), BigInt("-100"));
	ASSERT_EQ(BigInt("-10") * BigInt("-10"), BigInt("100"));

}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
