/*
 * created by Li Shao 11/15/2016
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "com/catheter_commands.h"
#include "com/pc_utils.h"

/**
 * \brief test
 */

TEST(pc_utils, testCurrentGen){

	std::vector<CatheterChannelCmdSet> commandVect;
	int status_readingFile = loadPlayFile("data/test_case.play", commandVect);
	
	std::vector<double> timeSlice;
	std::vector<std::vector<double>> currentPool;
	std::vector<double> currentGenerated;

	int status_groupData = currentGen(commandVect, timeSlice, currentPool, 3,1);
 
	std::vector<double> expectedCurrent0 ={0,0,-0};
	std::vector<double> expectedCurrent1 ={0,0,100};
	std::vector<double> expectedCurrent2 ={10.691,-42.022,131.89}; 
	std::vector<double> expectedCurrent3 ={11.714,-41.149,131.58}; 
	std::vector<double> expectedCurrent4 ={0,0,-0};

    //testing the given time ticker at t = 2000ms, 4000ms, 5003ms, 5012ms
	std::vector<double> actualCurrent0 = publishCurrent(2000,timeSlice, currentPool);
	std::vector<double> actualCurrent1 = publishCurrent(4000,timeSlice, currentPool);
	std::vector<double> actualCurrent2 = publishCurrent(5003,timeSlice, currentPool);
	std::vector<double> actualCurrent3 = publishCurrent(5012,timeSlice, currentPool);
	std::vector<double> actualCurrent4 = publishCurrent(9005,timeSlice, currentPool);

    ASSERT_TRUE(expectedCurrent0 == actualCurrent0);
	ASSERT_TRUE(expectedCurrent1 == actualCurrent1);
	ASSERT_TRUE(expectedCurrent2 == actualCurrent2);
	ASSERT_TRUE(expectedCurrent3 == actualCurrent3);
	ASSERT_TRUE(expectedCurrent4 == actualCurrent4);
}


 int main(int argc, char** argv){
 	testing::InitGoogleTest(&argc,argv);
 	return RUN_ALL_TESTS();
 }
