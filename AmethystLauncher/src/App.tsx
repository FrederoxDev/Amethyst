import Title from './components/Title';
import DividedSection from './components/DividedSection';
import MainPanel from './components/MainPanel'
import Dropdown from './components/Dropdown';
import { useState } from 'react';
import { SemVersion } from './types/SemVersion';
import { MinecraftVersion, VersionType } from './types/MinecraftVersion';
import { downloadVersion, extractVersion, getCurrentlyInstalledPackageID, registerVersion, unregisterExisting } from './VersionManager';


export default function App() {
  const [ runtimeMod, setRuntimeMod ] = useState("None");
  const [ allRuntimeMods, setAllRuntimeMods ] = useState(["None", "AmethystRuntime@1.1.0"]);

  const [ gameVersion, setGameVersion ] = useState("1.20.51.1");
  const [ allSupportedVersions, setAllSupportedVersions ] = useState(["1.20.51.1"]);

  const [ status, setStatus ] = useState("")
  const [ actionLock, setActionLock ] = useState(false)
 
  const semVersion = new SemVersion(1, 20, 51, 1)
  const minecraftVersion = new MinecraftVersion(semVersion, "58c5f0cd-09d7-4e99-a6b6-c3829fd62ac9", VersionType.Release)

  const downloadButton = async () => {
    await downloadVersion(minecraftVersion, setStatus, setActionLock);
  }

  const extractButton = async () => {
    await extractVersion(minecraftVersion, setStatus, setActionLock);
  }

  const registerButton = async () => {
    unregisterExisting();
    registerVersion(minecraftVersion)
  }

  const installGame = async () => {
    await downloadVersion(minecraftVersion, setStatus, setActionLock);
    await extractVersion(minecraftVersion, setStatus, setActionLock);
    unregisterExisting();
    registerVersion(minecraftVersion)
  }

  return (
    <div>
      <p>Is Locked {actionLock ? "true" : "false"}</p>
      <p>{status ?? " "}</p>
      <hr />
      <button onClick={installGame} disabled={actionLock} 
        className={`${actionLock ? 'cursor-wait' : 'cursor-pointer'}`}>
          Install Minecraft
      </button>

      <hr />
      <h1>Individual Actions</h1>

      <button onClick={downloadButton} disabled={actionLock} 
        className={`${actionLock ? 'cursor-wait' : 'cursor-pointer'}`}>
          Download 1.20.51.1 Appx
      </button>
      <hr />
      <button onClick={extractButton} disabled={actionLock} 
        className={`${actionLock ? 'cursor-wait' : 'cursor-pointer'}`}>
          Extract
      </button>
      <hr />
      <button onClick={registerButton} disabled={actionLock} 
        className={`${actionLock ? 'cursor-wait' : 'cursor-pointer'}`}>
          Register
      </button>
    </div>
  )

  // return (
  //   <div className='select-none'>
  //     <Title />
  //     <MainPanel>
  //       <p>{runtimeMod}</p>
  //       <p>{gameVersion}</p>

  //       <DividedSection>
  //         {/* Runtime Mod Selector */}
  //         <Dropdown 
  //           id="runtime-mod" 
  //           options={allRuntimeMods}
  //           labelText='Runtime Mod'
  //           value={runtimeMod}
  //           setValue={setRuntimeMod}
  //         />

  //         {/* Version Selector */}
  //         <Dropdown 
  //           id="game-version" 
  //           options={allSupportedVersions}
  //           labelText='Game Version'
  //           value={gameVersion}
  //           setValue={setGameVersion}
  //         />  
  //       </DividedSection>
  //     </MainPanel>
  //   </div>
  // )
}
