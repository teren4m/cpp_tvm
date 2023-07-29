#include <tvm_runner.hpp>
#include <tvm.utils.hpp>
#include <tvm/runtime/module.h>

TVMRunner::TVMRunner(std::string path, std::string device)
    : model_path(path), device(device), r_run_was_called(false)
{
    LOG(INFO) << "TVMRunner Constructor:" << model_path << " Devices:" << device;
}

int TVMRunner::Load()
{
    LOG(INFO) << "Load";
    mod_handle = tvm::runtime::Module::LoadFromFile((model_path + "/mod.so").c_str(), "so");
    std::string model_json_path = model_path + "/mod.json";
    std::string mod_json = ReadJsonModel(model_json_path);

    // Get ref to graph exeutor
    auto f_handle = tvm::runtime::Registry::Get("tvm.graph_executor.create");
    graph_handle = (*f_handle)(mod_json, mod_handle, GetTVMDevice(device), 0);

    std::string model_params_path = model_path + "/mod.params";
    std::string params_str = ReadParamsModel(model_params_path);
    
    TVMByteArray params_arr;
    params_arr.data = params_str.c_str();
    params_arr.size = params_str.length();

    // Load parameters
    graph_handle.GetFunction("load_params")(params_arr);

    return 0;
}