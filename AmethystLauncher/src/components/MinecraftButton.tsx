type MinecraftButtonProps = {
    text: string,
    disabled?: boolean
    onClick?: () => void
}

export default function MinecraftButton({text, onClick, disabled = false}: MinecraftButtonProps) {
    return (
        <div className={`h-[52px]`} onClick={() => {
            if (disabled) return;
            onClick?.();
        }}>
            <div className="border-[2px] border-[#1E1E1F] h-[48px] cursor-pointer active:translate-y-[4px] active:h-[44px] group">
                <div className="bg-[#3C8527] border-[2px] border-[#4F913C] h-[40px] box-border group-hover:bg-[#2A641C] flex items-center justify-center">
                    <p className="minecraft-seven text-[16px] text-white">{ text }</p>
                </div>
                <div className="bg-[#1D4D13] h-[4px] box-border minecraft-button-shadow group-active:h-[0px]"></div>
            </div>
        </div>
    )
}