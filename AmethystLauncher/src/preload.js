const amethyst = require('../build/Release/amethyst');
const { shell } = require("electron")
const path = require('path'); 
const fs = require("fs")
const { exec } = require('child_process');

// Find mods folder + create if doesn't exist
const amethystFolder = path.resolve(process.env.LOCALAPPDATA, "Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/AC/Amethyst/");
const modsFolder = path.resolve(amethystFolder, "mods/");
const configPath = path.resolve(amethystFolder, "launcher_config.json")

let loadedConfig = { "runtime": "", "mods": [], "developer_mode": false, "keep_open": true };

let normalMods = [];
let runtimeMods = [];

// Local State
let selectedRuntimeIndex = 0;
let keepOpen = false;
let devMode = false;
let modsToLoad = []

/**
 * Syncronises the UI with the loaded data
 */
function updateUI() {
    // Runtime mod selector
    const runtimeSelector = document.getElementById("runtime-mod-select")
    runtimeSelector.value = selectedRuntimeIndex;

    // Checkbox settings
    document.getElementById("keep-open-checkbox").checked = keepOpen;
    document.getElementById("dev-mode-checkbox").checked = devMode;

    const loadedModDiv = document.getElementById("loaded-mods");
    const unloadedModDiv = document.getElementById("unloaded-mods");

    loadedModDiv.innerHTML = ""
    unloadedModDiv.innerHTML = ""

    const unloadCallback = (name) => {
        modsToLoad = modsToLoad.filter(mod => mod != name);
        saveConfig();
        updateUI();
    }

    const loadCallback = (name) => {
        modsToLoad.push(name)
        saveConfig();
        updateUI();
    }

    // Regular mod selector
    normalMods.forEach(modName => {
        const isLoaded = modsToLoad.includes(modName);
        const form = isLoaded ? loadedModDiv : unloadedModDiv;

        const div = document.createElement("div");
        const button = document.createElement("button");
        button.innerText = isLoaded ? "-" : "+";
        button.onclick = isLoaded ? () => unloadCallback(modName) : () => loadCallback(modName);

        const text = document.createElement("p");
        text.innerText = modName;

        div.append(button);
        div.append(text);
        form.append(div);
    })
}

/**
 * Saves the launcher_config.json 
 */
function saveConfig() {
    // Index 0 is None option for runtime
    loadedConfig["runtime"] = selectedRuntimeIndex == 0 ? "" : runtimeMods[selectedRuntimeIndex];
    loadedConfig["keep_open"] = keepOpen;
    loadedConfig["developer_mode"] = devMode;
    loadedConfig["mods"] = modsToLoad;
    
    if (!fs.existsSync(modsFolder)) fs.mkdirSync(modsFolder, { recursive: true });
    fs.writeFileSync(configPath, JSON.stringify(loadedConfig, undefined, 4));
}

/**
 * Reads the launcher_config.json, falls back to a default config
 */
function tryReadConfig() {
    try {
        let data = fs.readFileSync(configPath, "utf-8");
        loadedConfig = JSON.parse(data);
    }
    catch (e) {
        console.log("Failed parsing launcher_config.json, falling back to default config!");
        saveConfig();
        return;
    }

    // Load runtime option
    const runtimeName = loadedConfig["runtime"] ?? "";

    // Make sure the field is blank and the mod still exists
    if (!runtimeMods.includes(runtimeName)) {
        console.log("Defaulting runtime mod to None")
        selectedRuntimeIndex = 0;
    }
    else {
        selectedRuntimeIndex = runtimeMods.indexOf(runtimeName);
    }

    // Checkbox settings
    keepOpen = loadedConfig["keep_open"] ?? true;
    devMode = loadedConfig["developer_mode"] ?? false;

    // Ensure the regular mods still exist
    const _modsToLoad = loadedConfig["mods"] ?? [];
    _modsToLoad.forEach(modName => {
        if (!normalMods.includes(modName)) return;
        modsToLoad.push(modName);
    })

    saveConfig();
}

/**
 * Loads all the folders in the mod folder
 */
function loadModlist() {
    // Ensure mods dir exists
    if (!fs.existsSync(modsFolder)) fs.mkdirSync(modsFolder, { recursive: true });

    const allMods = fs.readdirSync(modsFolder, { withFileTypes: true })
        .filter(f => f.isDirectory())
        .map(dir => dir.name);

    runtimeMods = allMods.filter(name => name.includes("Runtime"));
    normalMods = allMods.filter(name => !name.includes("Runtime"));

    runtimeMods = ["None", ...runtimeMods]

    // Add options to the runtime mod selector
    const runtimeSelector = document.getElementById("runtime-mod-select");

    runtimeMods.forEach((modName, i) => {
        let option = document.createElement("option");
        option.value = i;
        option.innerText = modName;
        runtimeSelector.append(option);
    })
}

function addSecurityGroup() {
    let command = `icacls "${amethystFolder}" /grant "*S-1-15-2-1:(OI)(CI)F"`;

    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.log(`addSecurityGroup Error: ${error.message}`);
            alert(`addSecurityGroup Error: ${error.message}`)
            return;
        }
        if (stderr) {
            console.log(`addSecurityGroup Stderr: ${stderr}`);
            alert(`addSecurityGroup Stderr: ${stderr}`);
            return;
        }
    });
}

window.addEventListener('DOMContentLoaded', () => {
    addSecurityGroup();
    loadModlist();
    tryReadConfig();
    updateUI();

    document.getElementById("launch-button").addEventListener("click", () => {
        if (loadedConfig["runtime"] == "") {
            alert("No runtime mod!");
            return;
        }

        const versionedName = loadedConfig["runtime"];
        const modName = versionedName.split("@")[0];
        const dllPath = path.resolve(modsFolder, `${versionedName}/${modName}.dll`);

        amethyst.LaunchGame(dllPath);
    })

    document.getElementById("open-folder-button").addEventListener("click", () => {
        shell.showItemInFolder(modsFolder)
    })

    const runtimeSelector = document.getElementById("runtime-mod-select");
    runtimeSelector.addEventListener("change", () => {
        selectedRuntimeIndex = runtimeSelector.value;
        saveConfig();
    })

    const settingsForm = document.getElementById("settings");
    const keepOpenCheckbox = document.getElementById("keep-open-checkbox");
    const devModeCheckbox = document.getElementById("dev-mode-checkbox");

    settingsForm.addEventListener("change", () => {
        keepOpen = keepOpenCheckbox.checked;
        devMode = devModeCheckbox.checked;
        saveConfig();
    })
});