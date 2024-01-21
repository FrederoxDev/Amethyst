const { contextBridge } = require("electron")
const path = require("path")

const native = {
    path: path,
    __dirname: __dirname
}

if (process.contextIsolated) {
    contextBridge.exposeInMainWorld("require", require);
    contextBridge.exposeInMainWorld("env", process.env)
    contextBridge.exposeInMainWorld("native", native)
}
else {
    window.require = require;
    window.env = process.env;
    window.native = native;
}