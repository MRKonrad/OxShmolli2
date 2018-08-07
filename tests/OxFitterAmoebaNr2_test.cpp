/*!
 * \file NumericalRecipes_test.cpp
 * \author Konrad Werys
 * \date 2018/08/03
 */

#include "CmakeConfigForOxShmolli2.h"
#ifdef USE_NR2

#include "gtest/gtest.h"
#include "OxTestData.h"

#include "OxFitterAmoebaNr2.h"
#include "OxFunctionsT1Basic.h"

TEST(OxFitterAmoebaNr2, performFitting) {

    typedef float TYPE;

    char filePath [] = "testData/blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();

    TYPE params[3] = {100, 200, 1200};

    Ox::FunctionsT1Basic<TYPE> functionsObject;
    functionsObject.setNSamples(nSamples);
    functionsObject.setInvTimes(testData.getInvTimesPtr());
    functionsObject.setSignal(testData.getSignalPtr());

    Ox::FitterAmoebaNr2<TYPE> fitterAmoebaNr2;
    fitterAmoebaNr2.setFunctionsT1(&functionsObject);
    functionsObject.setParameters(params);

    fitterAmoebaNr2.setVerbose(false);
    fitterAmoebaNr2.setTrace(false);

    fitterAmoebaNr2.performFitting();

    EXPECT_NEAR(params[0], testData.getResultsMolli()[0], 1e-0);
    EXPECT_NEAR(params[1], testData.getResultsMolli()[1], 1e-0);
    EXPECT_NEAR(params[2], testData.getResultsMolli()[2], 1e-0); // TODO: investigate why discrapancy is so big (0.13) compared with other fitting methods
}

#endif // USE_NR2

