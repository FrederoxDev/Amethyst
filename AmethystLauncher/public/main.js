const { app, BrowserWindow } = require('electron')
const path = require('path');

function createWindow () {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true,
      preload: path.join(__dirname, 'preload.js'),
      sandbox: false,
      webSecurity: false,
      contextIsolation: false
    }
  })

  win.loadURL('http://localhost:3000');
}

app.whenReady().then(createWindow)

app.on('window-all-closed', () => {
    app.quit()
})

app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
        createWindow()
    }
})