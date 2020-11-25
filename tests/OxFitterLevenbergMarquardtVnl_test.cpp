/*!
 * \file OxFitterLevenbergMarquardtVnl_test.cpp
 * \author Konrad Werys
 * \date 2018/07/31
 */

#include "CmakeConfigForTomato.h"
#ifdef USE_VNL

#include "gtest/gtest.h"
#include "OxTestData.h"

#include "OxModelT1ThreeParam.h"
#include "OxFitterLevenbergMarquardtVnl.h"

TEST(OxFitterLevenbergMarquardtVnl, performFitting) {

    typedef double TYPE;

    char filePath [] = "testData/T1_blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();

    double params[3] = {100, 200, 1200};

    Ox::ModelT1ThreeParam<TYPE> model;
    model.setNSamples(nSamples);
    model.setInvTimes(testData.getInvTimesPtr());
    model.setSignal(testData.getSignalPtr());

    Ox::FitterLevenbergMarquardtVnl<TYPE> fitter;
    fitter.setModel(&model);
    fitter.setParameters(params);

    fitter.setVerbose(false);
    fitter.setTrace(false);

    fitter.performFitting();

    EXPECT_NEAR(params[0], testData.getResultsMolli()[0], 1e-2);
    EXPECT_NEAR(params[1], testData.getResultsMolli()[1], 1e-2);
    EXPECT_NEAR(params[2], testData.getResultsMolli()[2], 1e-2);

}

TEST(OxFitterLevenbergMarquardtVnl, copyConstructor) {

    typedef double TYPE;

    char filePath [] = "testData/T1_blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();

    double params[3] = {100, 200, 1200};

    Ox::ModelT1ThreeParam<TYPE> model;
    model.setNSamples(nSamples);
    model.setInvTimes(testData.getInvTimesPtr());
    model.setSignal(testData.getSignalPtr());

    Ox::FitterLevenbergMarquardtVnl<TYPE> fitter;
    fitter.setModel(&model);
    fitter.setMaxFunctionEvals(123);
    fitter.setParameters(params);

    // copy constructor
    Ox::FitterLevenbergMarquardtVnl<TYPE> fitterCopy = fitter;

    // MaxFunctionEvals should be the same
    EXPECT_EQ( fitterCopy.getMaxFunctionEvals(), fitter.getMaxFunctionEvals());

    // Model was not declared for the copy, so it should be empty
    EXPECT_FALSE( fitterCopy.getModel());
    EXPECT_NE( fitterCopy.getModel(), fitter.getModel());

    // new FunctionsAdaptedToVnl should NOT be copied in the constructor
    EXPECT_FALSE( fitterCopy.getModelAdaptedToVnl());
}
#endif //USE_VNL
