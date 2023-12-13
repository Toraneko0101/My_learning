/**
 * CとC++で使えるコード例
*/

struct Sample{
    unsigned char C;
    double height;
    double width;
};


#ifdef __cplusplus
//Cではメンバ関数は使えないので
class SampleCpp : public Sample{
public:
    double Area() const{
        return height * width;
    }
};

#endif
