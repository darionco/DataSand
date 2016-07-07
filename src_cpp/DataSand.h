//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DATASAND_H
#define DATASAND_DATASAND_H

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/graphics_3d.h"

#include "core/DSTaskScheduler.h"

class DataSandInstance : public pp::Instance {

    DSTaskScheduler *m_taskScheduler;
    pp::Graphics3D m_context;

public:
    /// The constructor creates the plugin-side instance.
    /// @param[in] instance the handle to the browser-side plugin instance.
    explicit DataSandInstance(PP_Instance instance);

    virtual ~DataSandInstance();

    virtual void HandleMessage(const pp::Var &var_message);
    virtual void DidChangeView(const pp::View& view);

    void printToConsole(std::string message);
};

/// The Module class.  The browser calls the CreateInstance() method to create
/// an instance of your NaCl module on the web page.  The browser creates a new
/// instance for each <embed> tag with type="application/x-pnacl".
class DataSandModule : public pp::Module {
public:
    DataSandModule();

    virtual ~DataSandModule();

    /// Create and return a HelloTutorialInstance object.
    /// @param[in] instance The browser-side instance.
    /// @return the plugin-side instance.
    virtual pp::Instance *CreateInstance(PP_Instance instance);
};

#endif //DATASAND_DATASAND_H
