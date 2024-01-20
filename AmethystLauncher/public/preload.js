const { contextBridge } = require("electron")

if (process.contextIsolated) {
    contextBridge.exposeInMainWorld("require", require);
    contextBridge.exposeInMainWorld("env", process.env)
}
else {
    window.require = require;
    window.env = process.env;
}