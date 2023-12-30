#include <node.h>
#include <Windows.h>
#include "Loader.h"
#include <iostream>
using namespace v8;

void LaunchGame(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if (args.Length() != 1) return; 
    if (!args[0]->IsString()) return;

    String::Utf8Value dllPath(isolate, args[0]);
    std::string strPath = *dllPath;

    std::cout << strPath << std::endl;

    HANDLE handle = getMinecraftWindowHandle();
    InjectDLL(handle, strPath);
}

void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "LaunchGame", LaunchGame);
}

NODE_MODULE_INIT(/* exports, module, context */) {
    Initialize(exports);
}