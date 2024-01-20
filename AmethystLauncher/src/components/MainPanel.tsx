import { ReactNode } from "react"

type MainPanelProps = {
    children: ReactNode
}

export default function MainPanel({children}: MainPanelProps) {
    return (
        <div className="h-screen">
            <div className="h-[2px] bg-[#333334]"></div>
            <div className="bg-[#48494A] h-[100%]">
                { children }
            </div>
        </div>
    )
}