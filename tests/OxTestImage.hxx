/*!
 * \file OxTestImage.hxx
 * \author Konrad Werys
 * \date 2018/08/07
 */

#ifndef OXShmolli2_OXTESTImage_HXX
#define OXShmolli2_OXTESTImage_HXX


namespace Ox {

    template< typename MeasureType >
    TestImage<MeasureType>
    ::TestImage(int nRows, int nCols, std::vector <std::string> filesPaths) {
        _nCols = nCols;
        _nRows = nRows;
        int nTissues = filesPaths.size();
        std::vector< TestData <MeasureType> > TestDataVector; // vector with TestData objects

        // I do want to have less 'tissues' (TestData objects) than Rowumns, just for the sake of simplicity
        if (nTissues > _nCols){
            throw std::runtime_error("Give me more nCols or less tissues");
        }

        // populate TestDataVector
        for (int i = 0; i < nTissues; ++i){
            TestDataVector.push_back(TestData<MeasureType>((char*)filesPaths.at(i).c_str()));
        }

        // check if invTimes are equal
        for (int i = 1; i < nTissues; ++i){
            if(!(TestDataVector.at(i).getInvTimes() == TestDataVector.at(i-1).getInvTimes())){
                throw std::runtime_error("InvTimes are different");
            }
        }
        _invTimes = TestDataVector.at(0).getInvTimes();
        _nSamples = _invTimes.size();

        // allocate memory
        _imageMag = new MeasureType[_nCols*_nRows*_nSamples];
        _imagePha = new MeasureType[_nCols*_nRows*_nSamples];
        _imageResultsMolli = new MeasureType[_nRows*_nCols*3];
        _imageResultsShmolli = new MeasureType[_nRows*_nCols*3];

        // how to divide the memory?
        std::vector<int> ranges = KWUtil::bounds<int>(nTissues, _nCols);

//        std::cout << std::endl;
//        std::cout << std::endl;
//        for (int i = 0; i < ranges.size(); ++i ){
//            std::cout << ranges[i] << std::endl;
//        }

        // fill memory
        for (int iSample = 0; iSample < _nSamples; ++iSample){
            //for (int iCol = 0; iCol < _nCols; ++iCol) {
            for (int iRow = 0; iRow < _nRows; ++iRow) {
                for (int iTissue = 0; iTissue < ranges.size()-1; ++iTissue) {
                    //for (int iRow = ranges[iTissue]; iRow < ranges[iTissue+1]; ++iRow) {
                    for (int iCol = ranges[iTissue]; iCol < ranges[iTissue+1]; ++iCol) {
                        //int index = iSample * (nRows * nCols) + iCol * nRows + iRow;
                        int index = iSample * (nRows * nCols) + iRow * nCols + iCol;
                        _imageMag[index] = TestDataVector.at(iTissue).getSignalMagPtr()[iSample];
                        _imagePha[index] = TestDataVector.at(iTissue).getSignalPhaPtr()[iSample];
                    }
                }
            }
        }
        for (int iDim = 0; iDim < 3; ++iDim){
            //for (int iCol = 0; iCol < _nCols; ++iCol) {
            for (int iRow = 0; iRow < _nRows; ++iRow) {
                for (int iTissue = 0; iTissue < ranges.size()-1; ++iTissue) {
                    //for (int iRow = ranges[iTissue]; iRow < ranges[iTissue+1]; ++iRow) {
                    for (int iCol = ranges[iTissue]; iCol < ranges[iTissue+1]; ++iCol) {
                        //int index = iDim * (nRows * nCols) + iCol * nRows + iRow;
                        int index = iDim * (nRows * nCols) + iRow * nCols + iCol;
                        _imageResultsMolli[index] = TestDataVector.at(iTissue).getResultsMolliPtr()[iDim];
                        _imageResultsShmolli[index] = TestDataVector.at(iTissue).getResultsShmolliPtr()[iDim];
                    }
                }
            }
        }

    }

    template< typename MeasureType >
    TestImage<MeasureType>
    ::~TestImage(){
        delete [] _imageMag;
        delete [] _imagePha;
        delete [] _imageResultsMolli;
        delete [] _imageResultsShmolli;

    }
    template< typename MeasureType >
    std::vector<MeasureType>
    TestImage<MeasureType>
    ::getInvTimes() const {
        return _invTimes;
    }

    template< typename MeasureType >
    MeasureType *
    TestImage<MeasureType>
    ::getInvTimesPtr()  {
        return &_invTimes.at(0);
    }


    template< typename MeasureType >
    MeasureType *
    TestImage<MeasureType>
    ::getImageMagPtr() const {
        return _imageMag;
    }

    template< typename MeasureType >
    MeasureType *
    TestImage<MeasureType>
    ::getImagePhaPtr() const {
        return _imagePha;
    }

    template< typename MeasureType >
    MeasureType *
    TestImage<MeasureType>
    ::getImageResultsMolliPtr() const {
        return _imageResultsMolli;
    }

    template< typename MeasureType >
    MeasureType *
    TestImage<MeasureType>
    ::getImageResultsShmolliPtr() const {
        return _imageResultsShmolli;
    }

} // namespace Ox



#endif //OXShmolli2_OXTESTImage_HXX
