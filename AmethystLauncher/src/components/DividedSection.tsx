import { ReactNode } from "react"

type DividedSectionProps = {
    children: ReactNode
}

export default function DividedSection({children}: DividedSectionProps) {
    return (
        <div className="border-y-[2px] border-solid border-t-[#5A5B5C] border-b-[#000] p-[8px]">
            { children }
        </div>
    )
}