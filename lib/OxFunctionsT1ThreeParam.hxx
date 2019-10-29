/*!
 * \file OxFunctionsT1ThreeParams.hxx
 * \author Konrad Werys
 * \date 2018/07/29
 */

#ifndef Tomato_OXFUNCTIONST1ThreeParams_HXX
#define Tomato_OXFUNCTIONST1ThreeParams_HXX

namespace Ox {


    template< typename MeasureType >
    MeasureType
    FunctionsT1ThreeParam<MeasureType>
    ::calcModelValue(const MeasureType* parameters, MeasureType time){
        MeasureType A = parameters[0];
        MeasureType B = parameters[1];
        MeasureType T1star = parameters[2];

        if (fabs(T1star) < std::numeric_limits<MeasureType>::min())
            return A;

        return A - B * exp( -time / T1star );
    }

    template< typename MeasureType >
    void
    FunctionsT1ThreeParam<MeasureType>
    ::calcLSResiduals(const MeasureType* parameters, MeasureType* residuals){

        unsigned int nSamples = this->_nSamples;

        for (unsigned int i = 0; i < nSamples; i++) {
            MeasureType invTime = this->_InvTimes[i];
            MeasureType measured = this->_Signal[i];
            MeasureType calculated = 0;

            calculated = calcModelValue(parameters, invTime);

            residuals[i] = calculated - measured;
        }
    }

    template< typename MeasureType >
    void
    FunctionsT1ThreeParam<MeasureType>
    ::calcLSJacobian(const MeasureType* parameters, MeasureType* jacobian){
        int nSamples = this->_nSamples;

        //MeasureType A = parameters[0];
        MeasureType B = parameters[1];
        MeasureType T1star = parameters[2];
        MeasureType invTime, myexp;

        for (int i = 0; i < nSamples; i++) {
            invTime = this->_InvTimes[i];
            myexp = exp(-invTime/T1star);

            // calculated in matlab (syms A B T1 t), f=A-B*exp(-t./T1); diff(f,A), diff(f,B), diff(f,T1)
            jacobian[i*3+0] = 1.0;
            jacobian[i*3+1] = -myexp;
            jacobian[i*3+2] = -B * invTime * myexp / (T1star * T1star);
        }
    }

    template< typename MeasureType >
    MeasureType
    FunctionsT1ThreeParam<MeasureType>
    ::calcCostValue(const MeasureType* parameters){
        //std::cout << "calcCostValue" << std::endl;

        int nSamples = this->_nSamples;

        calcLSResiduals(parameters, this->_Residuals);
        MeasureType result = 0;

        for (int i = 0; i < nSamples; ++i) {
            result = result + this->_Residuals[i] * this->_Residuals[i];
        }

        return result;
    }

    template< typename MeasureType >
    void
    FunctionsT1ThreeParam<MeasureType>
    ::calcCostDerivative(const MeasureType* parameters, MeasureType* derivative){
        //std::cout << "calcCostDerivative" << std::endl;

        int nSamples = this->_nSamples;

        derivative[0] = 0;
        derivative[1] = 0;
        derivative[2] = 0;

        MeasureType measured, invTime, myexp;

        MeasureType A = parameters[0];
        MeasureType B = parameters[1];
        MeasureType T1star = parameters[2];

        // calculated in matlab (syms A B T1 t y), f=(A-B*exp(-t./T1)-y).^2; diff(f,A), diff(f,B), diff(f,T1)
        for (int i = 0; i < nSamples; ++i){
            measured = this->getSignal()[i];
            invTime = this->getInvTimes()[i];
            myexp = exp(-invTime/T1star);

            derivative[0] = derivative[0] + A*2 - measured*2 - myexp*B*2;;
            derivative[1] = derivative[1] + myexp*2*(measured - A + myexp*B);
            derivative[2] = derivative[2] + (invTime*myexp*B*2*(measured - A + myexp*B))/(T1star*T1star);
        }
    }

} //namespace Ox


#endif //Tomato_OXFUNCTIONST1ThreeParams_HXX
