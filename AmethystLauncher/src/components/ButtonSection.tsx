import Dropdown from "./Dropdown";
import MinecraftButton from "./MinecraftButton";

export default function ButtonSection() {
    return <div className="flex justify-around">
        {/* <div className="w-[30%]">
            <Dropdown 
                id="version"
                labelText="Minecraft Version"
                options={["1.20.51.1"]}
            />
        </div> */}
        <div className="w-[30%]">
            <MinecraftButton text='Launch Game' />
        </div>
        <div className="w-[30%]">
            <MinecraftButton text='Open Mods Folder' />
        </div>
    </div>
}