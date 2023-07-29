#pragma once
#include <tvm_runner.hpp>

class ReceiptDetect
{
public:
    ReceiptDetect();
    bool detect_receipt(char* dataMat);

private:
    TVMRunner *tvmRunner;
};