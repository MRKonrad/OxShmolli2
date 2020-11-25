/*!
 * \file OxModelT1AdapterVnlLeastSquares_test.cpp
 * \author Konrad Werys
 * \date 2018/07/31
 */

#include "CmakeConfigForTomato.h"
#ifdef USE_VNL

#include "gtest/gtest.h"
#include "OxTestData.h"

#include <vnl/algo/vnl_levenberg_marquardt.h>
#include "OxModelT1ThreeParam.h"
#include "OxModelT1AdapterVnlLeastSquares.h"


TEST(OxModelT1AdapterVnlLeastSquares, f) {

    typedef double TYPE;

    char filePath [] = "testData/T1_blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();
    int nDims = 3;

    TYPE params[3] = {0, 0, 0};

    Ox::ModelT1ThreeParam<TYPE> model;
    model.setNSamples(nSamples);
    //model.setParameters(params);
    model.setInvTimes(testData.getInvTimesPtr());
    model.setSignal(testData.getSignalMagPtr());

    Ox::ModelT1AdapterVnlLeastSquares functionsAdaptedToVnl(nDims, nSamples, vnl_least_squares_function::use_gradient);
    // Ox::ModelT1AdapterVnlLeastSquares functionsAdaptedToVnl(nSamples, vnl_least_squares_function::no_gradient);
    functionsAdaptedToVnl.setModel(&model);

    vnl_vector<TYPE> paramsVnl(params, 3);
    vnl_vector<TYPE> residualsVnl(nSamples, 0);

    functionsAdaptedToVnl.f(paramsVnl, residualsVnl);

    for (int i = 0; i < nSamples; i++){
        EXPECT_DOUBLE_EQ(residualsVnl[i], -testData.getSignalMag()[i]);
    }
}

TEST(OxModelT1AdapterVnlLeastSquares, gradf) {

    typedef double TYPE;

    char filePath [] = "testData/T1_blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();
    int nDims = 3;

    TYPE params[3] = {0, 0, 1200};

    Ox::ModelT1ThreeParam<TYPE> model;
    model.setNSamples(nSamples);
    //model.setParameters(params);
    model.setInvTimes(testData.getInvTimesPtr());
    model.setSignal(testData.getSignalMagPtr());

    Ox::ModelT1AdapterVnlLeastSquares functionsAdaptedToVnl(nDims, nSamples, vnl_least_squares_function::use_gradient);
    // Ox::ModelT1AdapterVnlLeastSquares functionsAdaptedToVnl(nSamples, vnl_least_squares_function::no_gradient);
    functionsAdaptedToVnl.setModel(&model);

    vnl_vector<TYPE> paramsVnl(params, 3);
    vnl_matrix<TYPE> jacobianVnl(nSamples, 3);

    functionsAdaptedToVnl.gradf(paramsVnl, jacobianVnl);

    TYPE correct[7*3] = {
            1, -0.920044,   0,
            1, -0.860708,   0,
            1, -0.805198,   0,
            1, -0.239508,   0,
            1, -0.0619868,  0,
            1, -0.0167532,  0,
            1, -0.00461166, 0,
    };

    for (int iSample = 0; iSample < nSamples; iSample++) {
        for (int iDim = 0; iDim < 3; iDim++) {
            EXPECT_NEAR(jacobianVnl.data_block()[iSample*3+iDim], correct[iSample*3+iDim], 1e-3);
        }
    }
}

TEST(OxModelT1AdapterVnlLeastSquares, fitting) {

    typedef double TYPE;

    char filePath [] = "testData/T1_blood.yaml";
    Ox::TestData<TYPE> testData(filePath);
    int nSamples = testData.getNSamples();
    int nDims = 3;

    TYPE params[3] = {0, 0, 1200};

    Ox::ModelT1ThreeParam<TYPE> model;
    model.setNSamples(nSamples);
    //model.setParameters(params);
    model.setInvTimes(testData.getInvTimesPtr());
    model.setSignal(testData.getSignalPtr());

    Ox::ModelT1AdapterVnlLeastSquares functionsAdaptedToVnl(nDims, nSamples, vnl_least_squares_function::use_gradient);
    // Ox::ModelT1AdapterVnlLeastSquares functionsAdaptedToVnl(nSamples, vnl_least_squares_function::no_gradient);
    functionsAdaptedToVnl.setModel(&model);

    vnl_vector<TYPE> paramsVnl(params, 3);
    vnl_levenberg_marquardt vnlFitter(functionsAdaptedToVnl);
    vnlFitter.minimize(paramsVnl);

    EXPECT_NEAR(paramsVnl[0], testData.getResultsMolli()[0], 1e-2);
    EXPECT_NEAR(paramsVnl[1], testData.getResultsMolli()[1], 1e-2);
    EXPECT_NEAR(paramsVnl[2], testData.getResultsMolli()[2], 1e-2);
}
#endif //USE_VNL