#include <fstream>
#include <iterator>
#include <streambuf>
#include <string>
#include <tvm/runtime/module.h>
#include <tvm/runtime/packed_func.h>
#include <tvm/runtime/registry.h>

/*!
 * \brief Get the TVM device id corresponding to device string.
 * \param device the target device in string format.
 * \return dl_device corresponding to the device string.
 */
int GetTVMDevice(std::string device)
{
    if (!device.compare("cpu"))
    {
        return static_cast<int>(kDLCPU);
    }
    else if (!device.compare("llvm"))
    {
        return static_cast<int>(kDLCPU);
    }
    else if (!device.compare("cuda"))
    {
        return static_cast<int>(kDLCUDA);
    }
    else if (!device.compare("opencl"))
    {
        return static_cast<int>(kDLOpenCL);
    }
    else if (!device.compare("vulkan"))
    {
        return static_cast<int>(kDLVulkan);
    }
    else if (!device.compare("metal"))
    {
        return static_cast<int>(kDLMetal);
    }
    else if (!device.compare("vpi"))
    {
        return static_cast<int>(kDLVPI);
    }
    else if (!device.compare("rocm"))
    {
        return static_cast<int>(kDLROCM);
    }
    else if (!device.compare("oneapi"))
    {
        return static_cast<int>(kDLOneAPI);
    }
    else
    {
        LOG(FATAL) << "TVMRunner : Unsupported device :" << device;
    }
}

std::string ReadJsonModel(std::string model_json_path)
{
    // Read model json file
    std::ifstream json_reader(model_json_path.c_str());
    CHECK(!json_reader.fail()) << "Failed to open json file:" << model_json_path.c_str();
    std::string json_str((std::istreambuf_iterator<char>(json_reader)),
                         std::istreambuf_iterator<char>());
    json_reader.close();
    return json_str;
}

std::string ReadParamsModel(std::string model_params_path)
{
    // Read params binary file
    std::ifstream params_reader(model_params_path.c_str(), std::ios::binary);
    CHECK(!params_reader.fail()) << "Failed to open json file:"
                                 << model_params_path.c_str();
    const std::string params_str((std::istreambuf_iterator<char>(params_reader)),
                                 std::istreambuf_iterator<char>());
    params_reader.close();
    return params_str;
}