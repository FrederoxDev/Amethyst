import DividedSection from "./DividedSection";

type ModSectionProps = {
    actionLock: boolean
}

export default function ModSection({ actionLock }: ModSectionProps) {
    return (
        <DividedSection className={`flex absolute left-0 right-0 ${actionLock ? "bottom-[96px]" : "bottom-[72px]" } 
            top-[235px] justify-around transition-all duration-300 ease-in-out`
        }>
            <div className="w-[45%] mb-[20px]">
                <p className="minecraft-seven text-white">Active Mods</p>
                <div className="box-border border-[2px] border-[#1E1E1F] bg-[#313233] min-h-[95%]">mod</div>
            </div>
            <div className="w-[45%] mb-[20px]">
                <p className="minecraft-seven text-white">Active Mods</p>
                <div className="box-border border-[2px] border-[#1E1E1F] bg-[#313233] min-h-[95%]">mod</div>
            </div>
        </DividedSection>
    );
}