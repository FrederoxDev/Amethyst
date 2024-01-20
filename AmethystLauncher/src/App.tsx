import Title from './components/Title';
import DividedSection from './components/DividedSection';
import MainPanel from './components/MainPanel'
import Dropdown from './components/Dropdown';
import { useState } from 'react';
import { SemVersion } from './types/SemVersion';
import { MinecraftVersion, VersionType } from './types/MinecraftVersion';
import { cacheMinecraftData, downloadVersion, extractVersion, getCurrentlyInstalledPackageID, isRegisteredVersionOurs, isVersionDownloaded, registerVersion, restoreMinecraftData, unregisterExisting } from './VersionManager';
const child = window.require('child_process') as typeof import('child_process')

export default function App() {
  const [ runtimeMod, setRuntimeMod ] = useState("None");
  const [ allRuntimeMods, setAllRuntimeMods ] = useState(["None", "AmethystRuntime@1.1.0"]);

  const [ status, setStatus ] = useState("")
  const [ actionLock, setActionLock ] = useState(false)
 
  const semVersion = new SemVersion(1, 20, 51, 1)
  const minecraftVersion = new MinecraftVersion(semVersion, "58c5f0cd-09d7-4e99-a6b6-c3829fd62ac9", VersionType.Release)

  const installGame = async () => {
    setActionLock(true);

    // Only install the game once
    if (!isVersionDownloaded(minecraftVersion)) {
      await downloadVersion(minecraftVersion, setStatus);
      await extractVersion(minecraftVersion, setStatus);
    }

    // Only register the game if needed
    if (!isRegisteredVersionOurs(minecraftVersion)) {
      setStatus("Copying existing minecraft data")
      cacheMinecraftData();

      setStatus("Unregistering existing version");
      await unregisterExisting();

      setStatus("Registering downloaded version");
      await registerVersion(minecraftVersion)

      setStatus("Restoring existing minecraft data")
      restoreMinecraftData();
    } 
  
    setStatus("")
    setActionLock(false);

    const startGameCmd = `start minecraft:`;
    child.spawn(startGameCmd, { shell: true })
  }

  return (
    <div>
      <p>Is Registered Version the one selected? {isRegisteredVersionOurs(minecraftVersion) ? "true" : "false"}</p>
      <p>Is version downloaded? {isVersionDownloaded(minecraftVersion) ? "true" : "false"}</p>
      <p>Is Locked {actionLock ? "true" : "false"}</p>
      <p>{status ?? " "}</p>
      <hr />
      <button onClick={installGame} disabled={actionLock} 
        className={`${actionLock ? 'cursor-wait' : 'cursor-pointer'}`}>
          Launch Game
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
