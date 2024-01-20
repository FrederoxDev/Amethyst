import DividedSection from "./DividedSection";
import MinecraftButton from "./MinecraftButton";

interface ButtonSectionProps {
    launchGame: () => void,
    actionLock: boolean,
    loadingPercent: number,
    status: string
}

export default function ButtonSection({ launchGame, actionLock, loadingPercent, status }: ButtonSectionProps) {
    return (
        <div className="absolute bottom-0 w-full">
            <div className={`bg-[#313233] ${actionLock ? "block" : "hidden"} h-[25px]`}>
                <div className={`bg-[#3C8527] absolute min-h-[25px]`} style={{width: `${loadingPercent * 100}%`}}></div>
                <p className='minecraft-seven absolute z-30 text-white overflow-hidden text-ellipsis whitespace-nowrap max-w-full px-2'>{status}</p>
            </div>
            <DividedSection>
                <div className="flex justify-around">
                    <div className="w-[45%]">
                        <MinecraftButton text='Launch Game' onClick={launchGame} key='launch-game' disabled={actionLock} />
                    </div>
                    <div className="w-[45%]">
                        <MinecraftButton text='Open Mods Folder' onClick={() => {}} key='open-mods-folder'/>
                    </div>
                </div>
            </DividedSection>
        </div>
    )
}