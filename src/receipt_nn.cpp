#include <receipt_nn.hpp>
#include <tvm_runner.hpp>
#include <string>

ReceiptDetect::ReceiptDetect()
{
    std::string model_path = "model";
    std::string device = "llvm";
    tvmRunner = new TVMRunner(model_path, device);
    tvmRunner->Load();
    // Query Model meta Information
    TVMMetaInfo mInfo = tvmRunner->GetMetaInfo();
    tvmRunner->PrintMetaInfo();
}

bool ReceiptDetect::detect_receipt(char *dataMat)
{
    union
    {
        float f;
        char b[4];
    } u;
    char output_buffer[4];
    tvmRunner->SetInput("input_1", dataMat);
    tvmRunner->Run();
    tvmRunner->GetOutput("tvmgen_default_fused_nn_contrib_dense_pack_add_sigmoid", u.b);
    LOG(INFO) << u.f;
    return u.f > 0.5;
}