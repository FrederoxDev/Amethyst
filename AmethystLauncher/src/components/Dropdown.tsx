type DropdownProps = {
    id: string;
    labelText: string;
    options: string[];
    value: string;
    setValue: React.Dispatch<React.SetStateAction<string>>
}

export default function Dropdown({ id, labelText, options, value, setValue }: DropdownProps) {
    const handleSelectChange = (event: React.ChangeEvent<HTMLSelectElement>) => {
        const selectedValue = event.target.value;
        setValue(selectedValue);
    };

    return <div className="h-full">
        <label htmlFor={id} className="minecraft-seven text-white text-[14px]">{labelText}</label>
        <select name={id} id={id} onChange={handleSelectChange} value={value}
            className="box-border border-[2px] border-[#1E1E1F] bg-[#313233] padding-[4px] w-full 
            text-white rounded-none minecraft-seven text-[13px] block p-[4px]"
        >
            {options.map((option, index) => 
                <option value={option} key={index} className="text-white">
                    {option}
                </option>
            )}
        </select>
    </div>
}