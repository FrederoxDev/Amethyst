import { getAmethystFolder, getMinecraftFolder } from "../VersionManager";
import DividedSection from "./DividedSection";
import MinecraftButton from "./MinecraftButton";
const child = window.require('child_process') as typeof import('child_process')
const fs = window.require('fs') as typeof import('fs');

interface ButtonSectionProps {
    launchGame: () => void,
    actionLock: boolean,
    loadingPercent: number,
    status: string
}

export default function ButtonSection({ launchGame, actionLock, loadingPercent, status }: ButtonSectionProps) {
    const openModsFolder = () => {
        // Don't reveal in explorer unless there is an existing minecraft folder
        if (!fs.existsSync(getMinecraftFolder())) {
            alert("Minecraft is not currently installed");
            return;
        }

        const folder = getMinecraftFolder() + "\\AC\\Amethyst\\mods\\";

        if (!fs.existsSync(folder)) fs.mkdirSync(folder, { recursive: true });

        const startGameCmd = `explorer "${folder}"`;
        child.spawn(startGameCmd, { shell: true })
    }

    return (
        <div className="absolute bottom-0 w-full">
            <div className={`bg-[#313233] ${actionLock ? "h-[25px]" : "h-[0px]"} transition-all duration-300 ease-in-out`}>
                <div className={`bg-[#3C8527] absolute min-h-[25px]`} style={{width: `${loadingPercent * 100}%`}}></div>
                <p className='minecraft-seven absolute z-30 text-white overflow-hidden text-ellipsis whitespace-nowrap max-w-full px-2'>{status}</p>
            </div>
            <DividedSection>
                <div className="flex justify-around">
                    <div className="w-[45%]">
                        <MinecraftButton text='Launch Game' onClick={launchGame} key='launch-game' disabled={actionLock} />
                    </div>
                    <div className="w-[45%]">
                        <MinecraftButton text='Open Mods Folder' onClick={openModsFolder} key='open-mods-folder'/>
                    </div>
                </div>
            </DividedSection>
        </div>
    )
}