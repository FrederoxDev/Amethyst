import Title from './components/Title';
import DividedSection from './components/DividedSection';
import MainPanel from './components/MainPanel'
import Dropdown from './components/Dropdown';
import { useState } from 'react';
import { SemVersion } from './types/SemVersion';
import { MinecraftVersion, VersionType } from './types/MinecraftVersion';
import { downloadVersion } from './downloader/VersionManager';
import CancellationToken from './downloader/CancellationToken';

export default function App() {
  const [ runtimeMod, setRuntimeMod ] = useState("None");
  const [ allRuntimeMods, setAllRuntimeMods ] = useState(["None", "AmethystRuntime@1.1.0"]);

  const [ gameVersion, setGameVersion ] = useState("1.20.51.1");
  const [ allSupportedVersions, setAllSupportedVersions ] = useState(["1.20.51.1"]);

  const [ isDownloading, setIsDownloading ] = useState(false)
  const [ currentTransferred, setCurrentTransferred ] = useState(0)
  const [ totalSize, setTotalSize ] = useState(0)
 
  const semVersion = new SemVersion(1, 20, 51, 1)
  const minecraftVersion = new MinecraftVersion(semVersion, "58c5f0cd-09d7-4e99-a6b6-c3829fd62ac9", VersionType.Release)

  const onClickButton = async () => {
    let cancellationToken = new CancellationToken();
    await downloadVersion(minecraftVersion, cancellationToken, setCurrentTransferred, setTotalSize, setIsDownloading)
  }

  const toMB = (bytes: number) => {
    let mb = bytes / (1024 * 1024)
    return `${mb.toFixed(1)}MB`
  }

  return (
    <div>
      <p>Is Downloading: {isDownloading ? "true" : "false"}</p>
      <p>{toMB(currentTransferred)} / {toMB(totalSize)}</p>
      <button onClick={onClickButton} disabled={isDownloading}>Download 1.20.51.1 Appx</button>
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
