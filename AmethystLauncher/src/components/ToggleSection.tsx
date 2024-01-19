import DividedSection from "./DividedSection"
import MinecraftToggle from "./MinecraftToggle"

type ToggleSectionProps = {
    text: string,
    subtext: string,
    isCheckedByDefault: boolean
}

export default function ToggleSection({ text, subtext, isCheckedByDefault }: ToggleSectionProps) {
    return (
        <DividedSection>
            <div className="flex items-center justify-center">
                <div>
                    <p className="minecraft-seven text-white text-[14px]">{text}</p>
                    <p className="minecraft-seven text-[#BCBEC0] text-[12px]">{subtext}</p>
                </div>
                <div className="ml-auto">
                    <MinecraftToggle id={text} isCheckedByDefault={isCheckedByDefault} />
                </div>
            </div>
        </DividedSection>
    )
}