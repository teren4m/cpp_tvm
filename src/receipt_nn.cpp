#include <receipt_nn.hpp>
#include <tvm_runner.hpp>
#include <string>


ReceiptDetect::ReceiptDetect()
{
    std::string model_path = "model";
    std::string device = "llvm";
    tvmRunner = new TVMRunner(model_path, device);
    tvmRunner->Load();
}

bool ReceiptDetect::detect_receipt()
{   
    return false;
}