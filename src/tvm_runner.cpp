#include <tvm_runner.hpp>
#include <tvm_utils.hpp>
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

int TVMRunner::SetInput(std::string input_id, char *raw_input)
{
    tvm::runtime::NDArray in_arr = graph_handle.GetFunction("get_input")(input_id);
    auto ssize = GetMemSize(in_arr);
    in_arr.CopyFromBytes(raw_input, ssize);
    return 0;
}

/*!
 * \brief Get output of the model as a binary buffer.
 * \param output_id output node name to read the data.
 * \param raw_output the buffer to copy the data to.
 * \param 0 on success else error code.
 */
int TVMRunner::GetOutput(std::string output_id, char* raw_output) {
  tvm::runtime::NDArray out_arr = graph_handle.GetFunction("get_output")(output_id);
  auto ssize = GetMemSize(out_arr);
  out_arr.CopyToBytes(raw_output, ssize);
  return 0;
}

/*!
 * \brief Call one cycle of execution for the model.
 * \param 0 on success else error code.
 */
int TVMRunner::Run(void)
{
    // LOG(INFO) << "TVMRunner::Run";
    // r_run_was_called = true;
    graph_handle.GetFunction("run")();
    return 0;
}