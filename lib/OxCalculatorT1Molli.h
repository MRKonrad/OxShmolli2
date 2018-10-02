/*!
 * \file OxCalculatorT1Molli.h
 * \author Konrad Werys
 * \date 2018/08/01
 */

#ifndef Tomato_OXCALCULATORT1MOLLI_H
#define Tomato_OXCALCULATORT1MOLLI_H

#include "OxCalculatorT1.h"

namespace Ox {

    /**
     * \class CalculatorT1Molli
     * \brief
     * \details
     * @tparam MeasureType
     */
    template< typename MeasureType >
    class CalculatorT1Molli : public CalculatorT1<MeasureType> {
    public:

        /**
         * calling calculateMolli(int nSamples, const MeasureType* invTimes, MeasureType* signal, MeasureType* signs)
         * @return success/failure
         */
        virtual int calculate(){
            this->_Results = CalculatorT1Results<MeasureType>();

            // calculate if higher than the cutoff
            if (KWUtil::calcMeanArray(this->getNSamples(), this->getSigMag()) < this->getMeanCutOff()) {
                return 0; // EXIT_SUCCESS
            }

            // get ready, continue if prepareToCalculate EXIT_SUCCESS
            if (this->prepareToCalculate() == 1) {
                return 1; // EXIT_FAILURE
            }

            this->_Results = calculateMolli( this->getNSamples(),
                                             this->getInvTimes(),
                                             this->getSignal(),
                                             this->getSigns());

            return 0; // EXIT_SUCCESS
        }

        /**
         * The most important function of this class
         * It has all the input parametrs so that I can call it from the shmolli class
         * @param nSamples
         * @param invTimes
         * @param signal
         * @param signs
         * @return success/failure
         */
        virtual CalculatorT1Results<MeasureType> calculateMolli(int nSamples, const MeasureType* invTimes, MeasureType* signal, MeasureType* signs){

            // some initialisation
            CalculatorT1Results<MeasureType> resultsStruc;

            MeasureType lastValue = 1e32;
            MeasureType lastValueTemp = 1e32;
            MeasureType tempParameters[3];
            MeasureType tempResults[3];

            // configure Functions object and fitter object
            this->getFunctionsT1()->setNSamples(nSamples);
            this->getFunctionsT1()->setSignal(signal);
            this->getFunctionsT1()->setInvTimes(invTimes);
            this->getFunctionsT1()->setParameters(tempParameters);
            this->getFunctionsT1()->copyToParameters(this->_StartPoint); // start from the starting point

            this->getFitter()->setFunctionsT1(this->getFunctionsT1());

            // fit
            this->getFitter()->performFitting();

            // save the tempResults at the best tempResults
            KWUtil::copyArrayToArray(3, tempResults, this->getFunctionsT1()->getParameters());
            lastValue = this->getFunctionsT1()->calcCostValue();

            // look for better solutions than the above one
            for (int iSwap = 0; iSwap < nSamples; iSwap++) {

                // continue only if TI in reasonable range
                if (invTimes[iSwap] > this->MaxTIForSignInvert) continue;

                // continue if sign was already calculated before
                if (signs[iSwap] != 0) continue;

                // in each iteration change the sign of one of the signal elements
                signal[iSwap] = -fabs(signal[iSwap]);

                // start from the starting point
                this->getFunctionsT1()->copyToParameters(this->_StartPoint);

                // fit
                this->getFitter()->performFitting();
                lastValueTemp = this->getFunctionsT1()->calcCostValue();

                // are these the best tempResults?
                if (lastValueTemp < lastValue) {
                    // save the tempResults at the best tempResults
                    KWUtil::copyArrayToArray(3, tempResults, this->getFunctionsT1()->getParameters());
                    lastValue = lastValueTemp;
                }
            }

            if (lastValue != 1e32 && tempResults[0] != 0) {
                resultsStruc.T1     = tempResults[2] * (tempResults[1] / tempResults[0] - 1.);
                resultsStruc.R2     = calculateR2AbsFromModel(invTimes, signal, tempResults);
                resultsStruc.A      = tempResults[0];
                resultsStruc.B      = tempResults[1];
                resultsStruc.T1star = tempResults[2];
                resultsStruc.ChiSqrt = KWUtil::getChiSqrt(lastValue, nSamples);
                resultsStruc.SNR =  (resultsStruc.B - resultsStruc.A) / (resultsStruc.ChiSqrt + 0.001);
                resultsStruc.LastValue = lastValue;
                //vecType residuals(nSamples); //TODO
                //this->m_Minimizer->GetFunctor()->calcLSResiduals(residuals); //TODO
                //vnl_matrix<MeasureType> invCovarianceMatrix = this->CalculateInvCovarianceMatrix(invTimes, residuals, curPos); //TODO
                //vnl_matrix<MeasureType> covarianceMatrix(3,3,0); //TODO
                //if (vnl_determinant(invCovarianceMatrix) > 1e-12){ //TODO
                //    covarianceMatrix = vnl_matrix_inverse<MeasureType> (invCovarianceMatrix); //TODO
                //}

                //tempResults.SD_A = covarianceMatrix(1,1); //TODO
                //tempResults.SD_B = covarianceMatrix(2,2); //TODO
                //tempResults.SD_T1 = covarianceMatrix(0,0); //TODO

                //std::cout << tempResults.SD_A << " " << tempResults.SD_B << " " << tempResults.SD_T1 << " " << std::endl;
            }

            return resultsStruc;
        }

        MeasureType calculateR2AbsFromModel(const MeasureType* invTimes, const MeasureType* signal, const MeasureType* parameters) {

            int nSamples = this->getNSamples();
            MeasureType *absFitted  = new MeasureType[nSamples];
            MeasureType *absYsignal = new MeasureType[nSamples];

            MeasureType A = parameters[0];
            MeasureType B = parameters[1];
            MeasureType T1star = parameters[2];

            for (int i = 0; i < nSamples; i++){
                MeasureType fitted;
                fitted = A - B * exp(-invTimes[i] / T1star);
                absFitted[i] = fabs(fitted);
                absYsignal[i] = fabs(signal[i]);
            }

            double result = KWUtil::calcR2cor(nSamples, absFitted, absYsignal);

            delete[] absFitted;
            delete[] absYsignal;
            return result;
        }

//        MeasureType* calculateInvCovarianceMatrix(const MeasureType* invTimes, const MeasureType* residuals, const MeasureType* parameters) {
//
//            matrixType invCovarianceMatrix(3,3, 0); // indexing by column,row
//            //invCovarianceMatrix.fill_diagonal(1);
//
//            MeasureType A = parameters[0];
//            MeasureType B = parameters[1];
//            MeasureType T1star = parameters[2];
//            MeasureType T1 = (B/A-1)*T1star;
//
//            MeasureType dydA = 0;
//            MeasureType dydB = 0;
//            MeasureType dydT1 = 0;
//
//            for (unsigned int i = 0; i < invTimes.size(); ++i){
//                MeasureType invTime = invTimes[i];
//                MeasureType myexp = exp ( -invTime * ( B/A - 1) / T1);
//                dydA  = 1 - B * myexp * invTime * B / ( T1 * A * A);
//                dydB  = -myexp + B * myexp * invTime / ( T1 * A );
//                dydT1 = -B * myexp * invTime * (B/A-1) / ( T1 * T1);
//
//                invCovarianceMatrix( 0, 0 ) += dydT1 * dydT1;
//                invCovarianceMatrix( 0, 1 ) += dydA  * dydT1;
//                invCovarianceMatrix( 0, 2 ) += dydB  * dydT1;
//                invCovarianceMatrix( 1, 0 ) += dydT1 * dydA;
//                invCovarianceMatrix( 1, 1 ) += dydA  * dydA;
//                invCovarianceMatrix( 1, 2 ) += dydB  * dydA;
//                invCovarianceMatrix( 2, 0 ) += dydT1 * dydB;
//                invCovarianceMatrix( 2, 1 ) += dydA  * dydB;
//                invCovarianceMatrix( 2, 2 ) += dydB  * dydB;
//            }
//
//            MeasureType SD = KWUtil::calcStandardDeviationArray(residuals.size(), residuals.data_block());
//            invCovarianceMatrix = invCovarianceMatrix/(SD*SD);
//
//            return invCovarianceMatrix;
//        }

        /**
         * constructor
         */
        CalculatorT1Molli() : CalculatorT1<MeasureType>(){
            MaxTIForSignInvert = this->MAX_T1_TRESHOLD * 0.67;
        }

        /**
         * cloning
         * @return
         */
        virtual CalculatorT1<MeasureType> *newByCloning() { return new CalculatorT1Molli<MeasureType>(*this); }



    protected:
        double MaxTIForSignInvert;
    };

} //namespace Ox
#endif //Tomato_OXCALCULATORT1MOLLI_H
