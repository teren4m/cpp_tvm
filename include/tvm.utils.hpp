#pragma once

#include <string>
#include <tvm/runtime/module.h>

int GetTVMDevice(std::string device);

std::string ReadJsonModel(std::string model_json_path);

std::string ReadParamsModel(std::string model_params_path);