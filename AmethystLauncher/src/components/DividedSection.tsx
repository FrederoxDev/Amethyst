import { ReactNode } from "react"

type DividedSectionProps = {
    children: ReactNode;
    className?: string;
};

export default function DividedSection({ children, className }: DividedSectionProps) {
    return (
        <div className={`border-y-[2px] border-solid border-t-[#5A5B5C] border-b-[#000] p-[8px] bg-[#48494A] ${className}`}>
            {children}
        </div>
    );
}