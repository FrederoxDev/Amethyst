import { MinecraftVersion } from "./types/MinecraftVersion";
import { download } from "./downloader/MinecraftVersionDownloader";
import { Extractor } from "./installer/Extractor";
const regedit = window.require('regedit-rs') as typeof import('regedit-rs');
const child = window.require('child_process') as typeof import('child_process')
// const { remote } = require('electron');

const toMB = (bytes: number) => {
    let mb = bytes / (1024 * 1024)
    return `${mb.toFixed(1)}MB`
}

function getAmethystFolder() {
    //@ts-ignore
    return window.env["Amethyst"]
}

export async function downloadVersion(
    version: MinecraftVersion, 
    setStatus: React.Dispatch<React.SetStateAction<string>>,
    setLock: React.Dispatch<React.SetStateAction<boolean>>
) {
    const downloadFolder = getAmethystFolder() + "/versions";
    const fileName = `Minecraft-${version.version.toString()}.appx`

    setLock(true);

    await download(version.uuid, "1", `${downloadFolder}/${fileName}`, (transferred, totalSize) => {
        setStatus(`Downloading: ${toMB(transferred)} / ${toMB(totalSize)}`)
    }, 
    (success) => {
        setLock(false);
        setStatus("");
        console.log("Finished, success: ", success)
    }
    )
}

export async function extractVersion(
    version: MinecraftVersion, 
    setStatus: React.Dispatch<React.SetStateAction<string>>,
    setLock: React.Dispatch<React.SetStateAction<boolean>>
) {
    const downloadFolder = getAmethystFolder() + "/versions";
    const fileName = `Minecraft-${version.version.toString()}`
    const exludes = ["AppxMetadata/CodeIntegrity.cat", "AppxMetadata", "AppxBlockMap.xml", "AppxSignature.p7x", "[Content_Types].xml"];

    setLock(true);

    await Extractor.extractFile(`${downloadFolder}/${fileName}.appx`, `${downloadFolder}/${fileName}/`, exludes, 
    (fileIndex, totalFiles, fileName) => {
        setStatus(`Unzipping: ${fileName}`)
    }, 
    (success) => {
        console.log("Finished extracting!")
        setLock(false)
        setStatus("")
    });
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

export function unregisterExisting() {
    const packageId = getCurrentlyInstalledPackageID();
    console.log("Currently installed packageId", packageId)
    if (packageId === undefined) return;

    const unregisterCmd = `powershell -ExecutionPolicy Bypass -Command "& { Remove-AppxPackage -Package "${packageId}" }"`;
    child.spawn(unregisterCmd, { shell: true })
}

export function registerVersion(version: MinecraftVersion) {
    const currentPackageId = getCurrentlyInstalledPackageID();
    if (currentPackageId != undefined) {
        throw new Error("There is still a version installed!");
    }

    const downloadFolder = getAmethystFolder() + "/versions";
    const fileName = `Minecraft-${version.version.toString()}`

    const registerCmd = `powershell -ExecutionPolicy Bypass -Command "& { Add-AppxPackage -Path "${downloadFolder}/${fileName}/AppxManifest.xml" -Register }"`;
    child.spawn(registerCmd, { shell: true })
}