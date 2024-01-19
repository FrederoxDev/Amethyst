export default function Header() {
    return (
        <>
            <div className="h-[42px] bg-[#E6E8EB] flex items-center justify-center">
                <p className="minecraft-ten">Amethyst Launcher</p>
            </div>

            {/* Shadow/Highlight */}
            <div className="bg-[#EBEDEF] h-[2px]"></div>
            <div className="bg-[#B1B2B5] h-[4px]"></div>
        </>
    )
}