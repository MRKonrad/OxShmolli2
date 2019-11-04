/*!
 * \file OxFunctionsT1AdapterVnlCost_test.cpp
 * \author Konrad Werys
 * \date 2018/07/31
 */

#include "CmakeConfigForTomato.h"
#ifdef USE_VNL

#include "gtest/gtest.h"
#include "OxTestData.h"

#include <vnl/algo/vnl_amoeba.h>
#include "OxFunctionsT1ThreeParam.h"
#include "OxFunctionsT1AdapterVnlCost.h"

TEST(OxFunctionsT1AdapterVnlCost, f) {

    typedef double TYPE;

    char filePath [] = "testData/T1_blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();
    int nDims = 3;

    TYPE params[3] = {0, 0, 0};

    Ox::FunctionsT1ThreeParam<TYPE> functionsObject;
    functionsObject.setNSamples(nSamples);
    //functionsObject.setParameters(params);
    functionsObject.setInvTimes(testData.getInvTimesPtr());
    functionsObject.setSignal(testData.getSignalMagPtr());

    Ox::FunctionsT1AdapterVnlCost functionsAdaptedToVnl(nDims);
    functionsAdaptedToVnl.setFunctionsT1(&functionsObject);

    vnl_vector<TYPE> temp(params, 3);

    EXPECT_DOUBLE_EQ(
            functionsAdaptedToVnl.f(temp),
            functionsObject.calcCostValue(params)
    );
}

TEST(OxFunctionsT1AdapterVnlCost, gradf) {

    typedef double TYPE;

    char filePath [] = "testData/T1_blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();
    int nDims = 3;

    TYPE params[3] = {100, 200, 1200};

    Ox::FunctionsT1ThreeParam<TYPE> functionsObject;
    functionsObject.setNSamples(nSamples);
    //functionsObject.setParameters(params);
    functionsObject.setInvTimes(testData.getInvTimesPtr());
    functionsObject.setSignal(testData.getSignalMagPtr());

    Ox::FunctionsT1AdapterVnlCost functionsAdaptedToVnl(nDims);
    functionsAdaptedToVnl.setFunctionsT1(&functionsObject);

    // FunctionsT1ThreeParam results
    TYPE derivative1[] = {0, 0, 0};
    functionsObject.calcCostDerivative(params, derivative1);

    // FunctionsT1ThreeParam results
    vnl_vector<TYPE> derivative2(3);
    vnl_vector<TYPE> params2(params, 3);
    functionsAdaptedToVnl.gradf(params2, derivative2);

    EXPECT_DOUBLE_EQ(derivative1[0], derivative1[0]);
    EXPECT_DOUBLE_EQ(derivative1[1], derivative1[1]);
    EXPECT_DOUBLE_EQ(derivative1[2], derivative1[2]);
}

TEST(OxFunctionsT1AdapterVnlCost, fitting) {

    typedef double TYPE;

    char filePath [] = "testData/T1_blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();
    int nDims = 3;

    TYPE params[3] = {100, 200, 1200};

    Ox::FunctionsT1ThreeParam<TYPE> functionsObject;
    functionsObject.setNSamples(nSamples);
    //functionsObject.setParameters(params);
    functionsObject.setInvTimes(testData.getInvTimesPtr());
    functionsObject.setSignal(testData.getSignalPtr());

    Ox::FunctionsT1AdapterVnlCost functionsAdaptedToVnl(nDims);
    functionsAdaptedToVnl.setFunctionsT1(&functionsObject);

    vnl_vector<TYPE> paramsVnl(params, 3);
    vnl_amoeba vnlFitter(functionsAdaptedToVnl);
    vnlFitter.minimize(paramsVnl);

    EXPECT_NEAR(paramsVnl[0], testData.getResultsMolli()[0], 1e-2);
    EXPECT_NEAR(paramsVnl[1], testData.getResultsMolli()[1], 1e-2);
    EXPECT_NEAR(paramsVnl[2], testData.getResultsMolli()[2], 1e-2);
}
#endif