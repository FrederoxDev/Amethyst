import DividedSection from "./DividedSection";

export default function ModSection() {
    return (
        <DividedSection className="flex absolute left-0 right-0 bottom-[72px] top-[235px] justify-around">
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