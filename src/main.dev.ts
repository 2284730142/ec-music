/* eslint global-require: off, no-console: off */

/**
 * This module executes inside of electron's main process. You can start
 * electron renderer process from here and communicate with the other processes
 * through IPC.
 *
 * When running `yarn build` or `yarn build:main`, this file is compiled to
 * `./src/main.prod.js` using webpack. This gives us some performance wins.
 */
import 'core-js/stable';
import 'regenerator-runtime/runtime';
import path from 'path';
import { app, BrowserWindow } from 'electron';
import { autoUpdater } from 'electron-updater';
import log from 'electron-log';
import MenuBuilder from './menu';

const RESOURCES_PATH = app.isPackaged ? path.join(process.resourcesPath, 'assets') : path.join(__dirname, '../assets');

const getAssetPath = (...paths: string[]): string => {
  return path.join(RESOURCES_PATH, ...paths);
};

export default class AppUpdater {
  constructor() {
    log.transports.file.level = 'info';
    autoUpdater.logger = log;
    autoUpdater.checkForUpdatesAndNotify();
  }
}

// 主窗体
let mainWindow: BrowserWindow | null = null;

if (process.env.NODE_ENV === 'production') {
  const sourceMapSupport = require('source-map-support');
  sourceMapSupport.install();
}

if (process.env.NODE_ENV === 'development' || process.env.DEBUG_PROD === 'true') {
  require('electron-debug')();
}

const installExtensions = async () => {
  const installer = require('electron-devtools-installer');
  const forceDownload = !!process.env.UPGRADE_EXTENSIONS;
  const extensions = ['REACT_DEVELOPER_TOOLS'];

  return installer.default(extensions.map((name) => installer[name]), forceDownload).catch(console.log);
};
// 创建窗体
const createWindow = async () => {
  if (process.env.NODE_ENV === 'development' || process.env.DEBUG_PROD === 'true') {
    await installExtensions();
  }
  // 获取桌面动态窗体大小
  // const { width, height } = screen.getPrimaryDisplay().workAreaSize;
  mainWindow = new BrowserWindow({
    width: 300, height: 400,
    icon: getAssetPath('icon.png'),
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      devTools: false,
    },
    fullscreen: false, // 默认全屏
    show: false // 启动时白屏优化点
  });
  // 加载主窗体
  mainWindow.loadURL(`file://${__dirname}/index.html`);
  // 开发调试栏
  // mainWindow.webContents.openDevTools();
  mainWindow.webContents.on('did-finish-load', () => {
    if (!mainWindow) {
      throw new Error('"mainWindow" is not defined');
    }
    // 窗体最大化
    // mainWindow.maximize();
    mainWindow.show();
    // 开启焦点
    // mainWindow.focus();
  });
  // 关闭程序
  mainWindow.on('closed', () => {
    // 回收BrowserWindow对象
    mainWindow = null;
  });
  // 视窗大小改变
  // mainWindow.on('resize', () => {
  //   mainWindow && mainWindow.reload();
  // });
  // 移除菜单栏
  // mainWindow.setMenu(null);
  // 菜单栏
  const menuBuilder = new MenuBuilder(mainWindow);
  menuBuilder.buildMenu();
  // Open urls in the user's browser
  // mainWindow.webContents.on('new-window', (event, url) => {
  //   event.preventDefault();
  //   shell.openExternal(url);
  // });
  // Remove this if your app does not use auto updates
  // eslint-disable-next-line
  // new AppUpdater();
};

/**
 * Add event listeners...
 */

app.on('window-all-closed', () => {
  // Respect the OSX convention of having the application in memory even
  // after all windows have been closed
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.whenReady().then(createWindow).catch(console.log);

app.on('activate', () => {
  // On macOS it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  if (mainWindow === null) {
    (async () => {
      await createWindow();
    })();
  }
});
