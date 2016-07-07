#include "DataSand.h"
#include "core/printToConsole.h"
#include "core/DSDataFormater.h"

#include <GLES2/gl2.h>
#include "ppapi/lib/gl/gles2/gl2ext_ppapi.h"

DataSandInstance::DataSandInstance(PP_Instance instance) : pp::Instance(instance) {
    setGlobalInstance(this);
}

DataSandInstance::~DataSandInstance() {
    delete m_taskScheduler;
}

void DataSandInstance::HandleMessage(const pp::Var &var_message) {
    if (!var_message.is_string()) {
        return;
    }
    std::string message = var_message.AsString();
    // assume its csv file for now when size > 100
    if (message.size() > 100) {
        auto dataFormatter = m_taskScheduler->m_dataFormatter;
        dataFormatter->loadCsvFile(message);
    }
}

void DataSandInstance::DidChangeView(const pp::View &view) {
    if (m_context.is_null()) {
        if (!glInitializePPAPI(pp::Module::Get()->get_browser_interface())) {
            printToConsole("Unable to initialize GL PPAPI!");
            return;
        }

        int32_t width = view.GetRect().width() * view.GetDeviceScale();
        int32_t height = view.GetRect().height() * view.GetDeviceScale();

        if (width == 0 || height == 0) {
            printToConsole("View size cannot be zero in any axis.");
            return;
        }

        printToConsole("Width: " + std::to_string(width));
        printToConsole("Height: " +std::to_string(height));

        const int32_t attrib_list[] = {
                PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 8,
                PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 24,
                PP_GRAPHICS3DATTRIB_WIDTH, width,
                PP_GRAPHICS3DATTRIB_HEIGHT, height,
                PP_GRAPHICS3DATTRIB_NONE
        };

        m_context = pp::Graphics3D(this, attrib_list);
        if (!BindGraphics(m_context)) {
            printToConsole("Unable to bind 3d context!");
            m_context = pp::Graphics3D();
            glSetCurrentContextPPAPI(0);
            return;
        }

        glSetCurrentContextPPAPI(m_context.pp_resource());

        if (!m_taskScheduler) {
            m_taskScheduler = new DSTaskScheduler();
        }
    }
}

void DataSandInstance::printToConsole(std::string message) {
    PostMessage(pp::Var(message));
}

DataSandModule::DataSandModule() : pp::Module() { }

DataSandModule::~DataSandModule() {}

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
