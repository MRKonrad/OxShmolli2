/*!
 * \file OxFitterLevenbergMarquardtLmfit_test.cpp
 * \author Konrad Werys
 * \date 2019/08/14
 */

#include "CmakeConfigForTomato.h"
#ifdef USE_LMFIT

#include "gtest/gtest.h"
#include "OxTestData.h"

#include "OxFunctionsT1ThreeParam.h"
#include "OxFitterLevenbergMarquardtLmfit.h"

#ifdef USE_PRIVATE_NR2
#include "OxFunctionsT1Shmolli.h"
#endif // USE_PRIVATE_NR2

TEST(OxFitterLevenbergMarquardtLmfit, performFitting) {

    typedef double TYPE;

    char filePath [] = "testData/blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();

    TYPE params[3] = {100, 200, 1200};

    Ox::FunctionsT1ThreeParam<TYPE> functionsObject;
    functionsObject.setNSamples(nSamples);
    functionsObject.setInvTimes(testData.getInvTimesPtr());
    functionsObject.setSignal(testData.getSignalPtr());

    Ox::FitterLevenbergMarquardtLmfit<TYPE> fitter;
    fitter.setFunctionsT1(&functionsObject);
    fitter.setParameters(params);

    fitter.setVerbose(false);
    fitter.setTrace(false);

    fitter.performFitting();

    EXPECT_NEAR(params[0], testData.getResultsMolli()[0], 1e-2);
    EXPECT_NEAR(params[1], testData.getResultsMolli()[1], 1e-2);
    EXPECT_NEAR(params[2], testData.getResultsMolli()[2], 1e-2);
}

#ifdef USE_PRIVATE_NR2

TEST(OxFitterLevenbergMarquardtLmfit, performFitting_shmolli) {

    typedef double TYPE;

    char filePath [] = "testData/blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();

    TYPE params[3] = {100, 200, 1200};

    Ox::FunctionsT1Shmolli<TYPE> functionsObject;
    functionsObject.setNSamples(nSamples);
    functionsObject.setInvTimes(testData.getInvTimesPtr());
    functionsObject.setSignal(testData.getSignalPtr());

    Ox::FitterLevenbergMarquardtLmfit<TYPE> fitter;
    fitter.setFunctionsT1(&functionsObject);
    fitter.setParameters(params);

    fitter.setVerbose(false);
    fitter.setTrace(false);

    fitter.performFitting();

    EXPECT_NEAR(params[0], testData.getResultsMolli()[0], 1e-2);
    EXPECT_NEAR(params[1], testData.getResultsMolli()[1], 1e-2);
    EXPECT_NEAR(params[2], testData.getResultsMolli()[2], 1e-2);
}

#endif // USE_PRIVATE_NR2

TEST(OxFitterLevenbergMarquardtLmfit, copyConstructor) {

    typedef double TYPE;

    char filePath [] = "testData/blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();

    TYPE params[3] = {100, 200, 1200};

    Ox::FunctionsT1ThreeParam<TYPE> functionsObject;
    functionsObject.setNSamples(nSamples);
    functionsObject.setInvTimes(testData.getInvTimesPtr());
    functionsObject.setSignal(testData.getSignalPtr());


    Ox::FitterLevenbergMarquardtLmfit<TYPE> fitter;
    fitter.setFunctionsT1(&functionsObject);
    fitter.setParameters(params);
    fitter.setMaxFunctionEvals(123);
    fitter.setFTolerance(321);

    // copy constructor
    Ox::FitterLevenbergMarquardtLmfit<TYPE> fitterCopy = fitter;

    // MaxFunctionEvals should be the same
    EXPECT_EQ( fitterCopy.getMaxFunctionEvals(), fitter.getMaxFunctionEvals());
    EXPECT_EQ( fitterCopy.getFTolerance(), fitter.getFTolerance());

    // FunctionsT1 was not declared for the copy, so it should be empty
    EXPECT_FALSE( fitterCopy.getFunctionsT1());
    EXPECT_NE( fitterCopy.getFunctionsT1(), fitter.getFunctionsT1());

}

#ifndef _WIN32

TEST(OxFitterLevenbergMarquardtLmfit, disp) {

    typedef double TYPE;

    char filePath [] = "testData/blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();

    TYPE params[3] = {100, 200, 1200};

    Ox::FunctionsT1ThreeParam<TYPE> functionsObject;
    functionsObject.setNSamples(nSamples);
    functionsObject.setInvTimes(testData.getInvTimesPtr());
    functionsObject.setSignal(testData.getSignalPtr());

    Ox::FitterLevenbergMarquardtLmfit<TYPE> fitter;
    fitter.setFunctionsT1(&functionsObject);
    fitter.setParameters(params);

    testing::internal::CaptureStdout();
    fitter.disp();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.size(), 0);
}

#endif // _WIN32

#endif // USE_LMFIT