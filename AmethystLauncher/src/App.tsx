import Title from './components/Title';
import DividedSection from './components/DividedSection';
import MainPanel from './components/MainPanel'
import Dropdown from './components/Dropdown';
import { useState } from 'react';
import { SemVersion } from './types/SemVersion';
import { MinecraftVersion, VersionType } from './types/MinecraftVersion';

export default function App() {
  const [ runtimeMod, setRuntimeMod ] = useState("None");
  const [ allRuntimeMods, setAllRuntimeMods ] = useState(["None", "AmethystRuntime@1.1.0"]);

  const [ gameVersion, setGameVersion ] = useState("1.20.51.1");
  const [ allSupportedVersions, setAllSupportedVersions ] = useState(["1.20.51.1"]);

  const semVersion = new SemVersion(1, 20, 51, 1)
  const minecraftVersion = new MinecraftVersion(semVersion, "58c5f0cd-09d7-4e99-a6b6-c3829fd62ac9", VersionType.Release)

  return (
    <div className='select-none'>
      <Title />
      <MainPanel>
        <p>{runtimeMod}</p>
        <p>{gameVersion}</p>

        <DividedSection>
          {/* Runtime Mod Selector */}
          <Dropdown 
            id="runtime-mod" 
            options={allRuntimeMods}
            labelText='Runtime Mod'
            value={runtimeMod}
            setValue={setRuntimeMod}
          />

          {/* Version Selector */}
          <Dropdown 
            id="game-version" 
            options={allSupportedVersions}
            labelText='Game Version'
            value={gameVersion}
            setValue={setGameVersion}
          />  
        </DividedSection>
      </MainPanel>
    </div>
  )
}
