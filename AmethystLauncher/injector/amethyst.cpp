#include <node.h>
using namespace v8;

void GetModsList(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    Local<Array> array = Array::New(isolate, 2);
    array->Set(isolate->GetCurrentContext(), 0, String::NewFromUtf8(isolate, "Minimap@1.4.0").ToLocalChecked());
    array->Set(isolate->GetCurrentContext(), 1, String::NewFromUtf8(isolate, "ItemInformation@1.2.0").ToLocalChecked());

    args.GetReturnValue().Set(array);
}

void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "GetModsList", GetModsList);
}

NODE_MODULE_INIT(/* exports, module, context */) {
    Initialize(exports);
}