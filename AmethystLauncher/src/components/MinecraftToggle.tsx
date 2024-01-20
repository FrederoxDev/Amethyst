type MinecraftToggleProps = {
    isChecked: boolean,
    setIsChecked: React.Dispatch<React.SetStateAction<boolean>>,
    id: string
}

export default function MinecraftToggle({ isChecked, setIsChecked, id }: MinecraftToggleProps) {
    const handleCheckboxChange = () => {
        setIsChecked(!isChecked);
    }

    return (
        <label htmlFor={id} className="flex select-none cursor-pointer w-fit group">
            {/* Hidden input checkbox */}
            <input id={id} type="checkbox" className="hidden" onChange={handleCheckboxChange} checked={isChecked} />

            {/* Grey/Green sides */}
            <div className="w-[60px] h-[28px] box-border border-[2px] border-[#1E1E1F] flex">
                <div className="w-[30px] h-[24px] box-border border-[2px] border-r-0 border-[#639D52] bg-[#3C8527] flex items-center justify-center">
                    <p className="minecraft-seven text-[#242425]">|</p>
                </div>
                <div className="w-[30px] h-[24px] box-border border-[2px] border-l-0 border-[#A3A4A6] bg-[#8C8D90] flex items-center justify-center">
                    <p className="minecraft-seven text-[#242425]">O</p>
                </div>
            </div>

            {/* Toggle */}
            <div
                className={`w-[32px] h-[30px] box-border absolute bg-[#D0D1D4] border-[2px] border-[#1E1E1F] translate-y-[-2px] z-10 ${
                    isChecked ? 'translate-x-[28px] toggle-transform' : 'toggle-transform'
                }`}
            >
                <div className="w-[28px] h-[24px] border-[2px] border-[#ECEDEE] group-hover:bg-[#B1B2B5]"></div>
                <div className="h-[3px] bg-[#58585A]"></div>
            </div>
        </label>
    )
}