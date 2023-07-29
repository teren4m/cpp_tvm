#pragma once

#include <tvm/runtime/module.h>
#include <tvm/runtime/packed_func.h>
#include <tvm/runtime/registry.h>

#include <string>

#include "tvm/runtime/c_runtime_api.h"

/*!
 * \brief various meta information related to the compiled TVM model.
 */
typedef struct _TVMMetaInfo
{
    int n_inputs;
    int n_outputs;
    std::map<std::string, std::pair<std::vector<int>, std::string>> input_info;
    std::map<std::string, std::pair<std::vector<int>, std::string>> output_info;
} TVMMetaInfo;

class TVMRunner
{
public:
    /*! \brief Constructor */
    TVMRunner(std::string path, std::string device);

    /*! \brief Initiates graph runtime and with the compiled model */
    int Load(void);

    /*! \brief Executes one inference cycle */
    int Run(void);

    /*! \brief To set the input from binary data */
    int SetInput(std::string, char *);

    /*! \brief Get the model output in binary format */
    int GetOutput(std::string, char *);

private:
    /*! \brief Module handle for the shared object */
    tvm::runtime::Module mod_handle;
    /*! \brief Graph runtime module handle */
    tvm::runtime::Module graph_handle;
    /*! \brief The local model path from where we load the model */
    std::string model_path;
    /*! \brief The target device */
    std::string device;
    // /*! \brief Holds meta information queried from graph runtime */
    // TVMMetaInfo mInfo;
    /*! \brief Mark if the run method was called */
    bool r_run_was_called;
};