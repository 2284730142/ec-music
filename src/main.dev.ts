/* eslint global-require: off, no-console: off */

/**
 * This module executes inside of electron's main process. You can start
 * electron renderer process from here and communicate with the other processes
 * through IPC.
 *
 * When running `yarn build` or `yarn build:main`, this file is compiled to
 * `./src/main.prod.js` using webpack. This gives us some performance wins.
 * 备注：此处的console只能写英文，中文是乱码！！！
 */
import 'core-js/stable';
import 'regenerator-runtime/runtime';
import path from 'path';
import {app, BrowserWindow, ipcMain, IpcMainEvent} from 'electron';
import {autoUpdater} from 'electron-updater';
import log from 'electron-log';
import {ReceiveMessageFromRender, RenderMessageArgsType} from './window/event.window';
import {exec} from 'child_process';

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
    width: 960, height: 520,
    minWidth: 960, minHeight: 520,
    icon: getAssetPath('icon.png'),
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      devTools: true, // 正式的包不会有
    },
    fullscreen: false, // 默认全屏
    show: false, // 启动时白屏优化点
    frame: false, // 无边窗口化，美化窗体
  });
  // 加载主窗体
  mainWindow.loadURL(`file://${__dirname}/index.html`);
  // 开发调试栏
  // mainWindow.webContents.openDevTools();
  // 添加事件监听处理, 渲染进程加载结束
  mainWindow.webContents.on('did-finish-load', () => {
    if (!mainWindow) {
      throw new Error('"mainWindow" is not defined');
    }
    mainWindow.show();
  });
  // 关闭程序
  mainWindow.on('closed', () => {
    mainWindow = null;
  });
  // 添加主进程渲染进程的通信机制
  ipcMain.on('render-message', (event: IpcMainEvent, args: RenderMessageArgsType) => {
    ReceiveMessageFromRender(mainWindow, event, args);
  });
  // 移除菜单栏
  mainWindow.setMenu(null);
  // 创建本地node服务（整合express）pkg打包 todo 改成cluster模式的service pm2
  console.log(getAssetPath('run.vbs'));
  exec(`cscript ${getAssetPath('run.vbs')}`, (err, stdout) => {
    if (err) {
      console.log(`err: ${err}`);
      return;
    }
    console.log(`stdout: ${stdout}`);
  });
};

/**
 * Add event listeners...
 */

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.whenReady().then(createWindow).catch(console.log);

app.on('activate', () => {
  if (mainWindow === null) {
    (async () => {
      await createWindow();
    })();
  }
});
