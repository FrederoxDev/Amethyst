import { MinecraftVersion } from "./types/MinecraftVersion";
import { download } from "./downloader/MinecraftVersionDownloader";
import { Extractor } from "./installer/Extractor";
const regedit = window.require('regedit-rs') as typeof import('regedit-rs');
const child = window.require('child_process') as typeof import('child_process')
const fs = window.require('fs') as typeof import('fs');
const path = window.require("path") as typeof import('path')

const toMB = (bytes: number) => {
    let mb = bytes / (1024 * 1024)
    return `${mb.toFixed(1)}MB`
}

export function getAmethystFolder() {
    //@ts-ignore
    return window.env["AppData"] + "\\Amethyst"
}

export function getMinecraftFolder() {
    //@ts-ignore
    return window.env["LocalAppData"] + "\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe"
}

async function sleep(ms: number) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

export async function downloadVersion(
    version: MinecraftVersion, 
    setStatus: React.Dispatch<React.SetStateAction<string>>,
    setLoadingPercent: React.Dispatch<React.SetStateAction<number>>
) {
    const downloadFolder = getAmethystFolder() + "/versions";
    if (!fs.existsSync(downloadFolder)) {
        fs.mkdirSync(downloadFolder, { recursive: true })
    }

    const fileName = `Minecraft-${version.version.toString()}.appx`

    await download(version.uuid, "1", `${downloadFolder}/${fileName}`, (transferred, totalSize) => {
        setStatus(`Downloading: ${toMB(transferred)} / ${toMB(totalSize)}`)
        setLoadingPercent(transferred / totalSize)
    }, 
    (success) => {
        setStatus("");
        console.log("Finished, success: ", success)
    }
    )
}

export async function extractVersion(
    version: MinecraftVersion, 
    setStatus: React.Dispatch<React.SetStateAction<string>>,
    setLoadingPercent: React.Dispatch<React.SetStateAction<number>>
) {
    const downloadFolder = getAmethystFolder() + "/versions";
    const fileName = `Minecraft-${version.version.toString()}`
    const exludes = ["AppxMetadata/CodeIntegrity.cat", "AppxMetadata", "AppxBlockMap.xml", "AppxSignature.p7x", "[Content_Types].xml"];

    await Extractor.extractFile(`${downloadFolder}/${fileName}.appx`, `${downloadFolder}/${fileName}/`, exludes, 
    (fileIndex, totalFiles, fileName) => {
        setLoadingPercent(fileIndex / totalFiles);
        setStatus(`Unzipping: ${fileName}`)
    }, 
    (success) => {
        if (!success) {
            alert("There was an issue extracting the game!");
            return;
        }

        console.log("Finished extracting!")
        setStatus("")
    });

    //@ts-ignore
    const proxyDllPath = window.native.path.join(window.native.__dirname, "proxy", "dxgi.dll");
    const targetDllPath = `${downloadFolder}/${fileName}/dxgi.dll`;

    fs.copyFileSync(proxyDllPath, targetDllPath);
}

export function getCurrentlyInstalledPackageID() {
    const regKey = 'HKCU\\SOFTWARE\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\CurrentVersion\\AppModel\\Repository\\Packages';
    const listed = regedit.listSync(regKey);
    if (!listed[regKey].exists) return undefined;

    const minecraftKey = listed[regKey].keys.find(key => key.startsWith('Microsoft.MinecraftUWP_'));
    if (minecraftKey === undefined) return undefined;

    const minecraftValues = regedit.listSync(`${regKey}\\${minecraftKey}`)[`${regKey}\\${minecraftKey}`];
    if (!minecraftValues.exists) return undefined;

    const packageId = minecraftValues.values['PackageID'].value as string;
    return packageId;
}

export async function unregisterExisting() {
    const packageId = getCurrentlyInstalledPackageID();
    console.log("Currently installed packageId", packageId)
    if (packageId === undefined) return;

    const unregisterCmd = `powershell -ExecutionPolicy Bypass -Command "& { Remove-AppxPackage -Package "${packageId}" }"`;
    child.spawn(unregisterCmd, { shell: true })
    await sleep(6000);
}

export async function registerVersion(version: MinecraftVersion) {
    const currentPackageId = getCurrentlyInstalledPackageID();
    if (currentPackageId !== undefined) {
        throw new Error("There is still a version installed!");
    }

    const downloadFolder = getAmethystFolder() + "/versions";
    const fileName = `Minecraft-${version.version.toString()}`

    const registerCmd = `powershell -ExecutionPolicy Bypass -Command "& { Add-AppxPackage -Path "${downloadFolder}/${fileName}/AppxManifest.xml" -Register }"`;
    child.spawn(registerCmd, { shell: true })
    await sleep(6000);
}

export function isRegisteredVersionOurs(version: MinecraftVersion) {
    const regKey = 'HKCU\\SOFTWARE\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\CurrentVersion\\AppModel\\Repository\\Packages';
    const listed = regedit.listSync(regKey);
    if (!listed[regKey].exists) return false;

    const minecraftKey = listed[regKey].keys.find(key => key.startsWith('Microsoft.MinecraftUWP_'));
    if (minecraftKey === undefined) return false;

    const minecraftValues = regedit.listSync(`${regKey}\\${minecraftKey}`)[`${regKey}\\${minecraftKey}`];
    if (!minecraftValues.exists) return false;

    const packageRootFolder = minecraftValues.values['PackageRootFolder'].value as string;
    const downloadFolder = getAmethystFolder() + "\\versions";
    const fileName = `Minecraft-${version.version.toString()}`

    return packageRootFolder === `${downloadFolder}\\${fileName}`
}

export function isVersionDownloaded(version: MinecraftVersion) {
    const downloadFolder = getAmethystFolder() + "\\versions";
    const fileName = `Minecraft-${version.version.toString()}`
    const folder = `${downloadFolder}\\${fileName}\\`
    return fs.existsSync(folder)
}

export function cacheMinecraftData() {
    //@ts-ignore
    const minecraftDataFolder = window.env["LocalAppData"] + "\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe";
    const tempDataFolder = getAmethystFolder() + "\\DataRestorePoint\\";

    // There is no data so do nothing
    if (!fs.existsSync(minecraftDataFolder)) return;
    
    // Remove any existing stuff so if installing multiple times, they wont merge
    if (fs.existsSync(tempDataFolder)) {
        fs.rmdirSync(tempDataFolder, { recursive: true });
    }

    // Store contents of minecraft data in a temp folder
    fs.cpSync(minecraftDataFolder, tempDataFolder, {recursive: true})
}

export function restoreMinecraftData() {
    //@ts-ignore
    const minecraftDataFolder = window.env["LocalAppData"] + "\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe";
    const tempDataFolder = getAmethystFolder() + "\\DataRestorePoint\\";

    // Check there was actually something to restore from
    if (!fs.existsSync(tempDataFolder)) return;

    if (fs.existsSync(minecraftDataFolder)) {
        fs.rmdirSync(minecraftDataFolder, { recursive: true });
    }

    fs.cpSync(tempDataFolder, minecraftDataFolder, {recursive: true})
}