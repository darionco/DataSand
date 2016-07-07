#include "DataSand.h"
#include "core/printToConsole.h"
#include "core/DSTaskScheduler.h"

DataSandInstance::DataSandInstance(PP_Instance instance) : pp::Instance(instance) {
    setGlobalInstance(this);
}

DataSandInstance::~DataSandInstance() { }

void DataSandInstance::HandleMessage(const pp::Var &var_message) {
    if (!var_message.is_string()) {
        return;
    }

    std::string message = var_message.AsString();
    if (message == "Hello") {
        printToConsole("Holy chow!");
    }
}

void DataSandInstance::printToConsole(std::string message) {
    PostMessage(pp::Var(message));
}

DataSandModule::DataSandModule() : pp::Module() { }

DataSandModule::~DataSandModule() { }

pp::Instance *DataSandModule::CreateInstance(PP_Instance instance) {
    return new DataSandInstance(instance);
}

namespace pp {
/// Factory function called by the browser when the module is first loaded.
/// The browser keeps a singleton of this module.  It calls the
/// CreateInstance() method on the object you return to make instances.  There
/// is one instance per <embed> tag on the page.  This is the main binding
/// point for your NaCl module with the browser.
    Module *CreateModule() {
        return new DataSandModule();
    }
}  // namespace pp
