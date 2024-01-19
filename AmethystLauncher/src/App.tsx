import Title from './components/Title';
import DividedSection from './components/DividedSection';
import MainPanel from './components/MainPanel'
import MinecraftButton from './components/MinecraftButton';
import ToggleSection from './components/ToggleSection';
import Dropdown from './components/Dropdown';
import ButtonSection from './components/ButtonSection';

export default function App() {
  return (
    <div className='select-none'>
      <Title />
      <MainPanel>

        <DividedSection>
          <Dropdown 
            id="runtime-mod" 
            options={["None", "AmethystRuntime@1.1.0"]}
            labelText='Runtime Mod'
          />
        </DividedSection>

        <ToggleSection 
          text='Keep Launcher Open'
          subtext='Prevents the launcher from closing after launching the game.'
          isCheckedByDefault={false}
        />

        <ToggleSection 
            text='Developer Mode'
            subtext='Enables hot-reloading and prompting to attach a debugger.'
            isCheckedByDefault={true}
        />

        <DividedSection>
          <ButtonSection />
        </DividedSection>
        
      </MainPanel>
    </div>
  )
}
