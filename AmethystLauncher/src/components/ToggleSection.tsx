import DividedSection from "./DividedSection"
import MinecraftToggle from "./MinecraftToggle"

type ToggleSectionProps = {
    text: string,
    subtext: string,
    isChecked: boolean,
    setIsChecked: React.Dispatch<React.SetStateAction<boolean>>,
}

export default function ToggleSection({ text, subtext, isChecked, setIsChecked }: ToggleSectionProps) {
    return (
        <DividedSection>
            <div className="flex items-center justify-center">
                <div>
                    <p className="minecraft-seven text-white text-[14px]">{text}</p>
                    <p className="minecraft-seven text-[#BCBEC0] text-[12px]">{subtext}</p>
                </div>
                <div className="ml-auto">
                    <MinecraftToggle id={text} isChecked={isChecked} setIsChecked={setIsChecked} />
                </div>
            </div>
        </DividedSection>
    )
}