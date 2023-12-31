#pragma once

#include <string>
#include <tvm/runtime/module.h>

int GetTVMDevice(std::string device);

std::string ReadJsonModel(std::string model_json_path);

std::string ReadParamsModel(std::string model_params_path);

size_t GetMemSize(tvm::runtime::NDArray &narr);

void PrintNDArrayShape(tvm::runtime::NDArray& narr);