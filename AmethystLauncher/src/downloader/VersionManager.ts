import { MinecraftVersion } from "../types/MinecraftVersion";
import CancellationToken from "./CancellationToken";
import { download } from "./MinecraftVersionDownloader";

export async function downloadVersion(
    version: MinecraftVersion, 
    cancellationToken: CancellationToken, 
    setCurrentTransferred: React.Dispatch<React.SetStateAction<number>>,
    setTotalSize: React.Dispatch<React.SetStateAction<number>>,
    setIsDownloading: React.Dispatch<React.SetStateAction<boolean>>
) {
    const downloadFolder = "C:/Users/blake/Desktop"
    const fileName = `Minecraft-${version.version.toString()}.appx`

    setIsDownloading(true)

    await download(version.uuid, "1", `${downloadFolder}/${fileName}`, cancellationToken, (transferred, totalSize) => {
        setCurrentTransferred(transferred);
        setTotalSize(totalSize);
    }, 
    (success) => {
        setIsDownloading(false);
        console.log("Finished, success: ", success)
    }
    )
}