import {
  Menu,
  shell,
  BrowserWindow,
  IpcMainEvent,
  ipcMain,
  BrowserView,
  screen
} from 'electron';
import { createView } from './window/window';

declare type AcceleratorNameType = {
  fullScreen: string;
  closeApp: string;
  reloadView: string;
  reloadWindow: string;
  prevWindow: string;
  nextWindow: string;
  devTool: string;
}

declare type PageUrlType = {
  page1: string;
  page2: string;
}

declare type PageUrlNameType = 'page1' | 'page2';

const acceleratorName: AcceleratorNameType = {
  fullScreen: 'F11',
  closeApp: 'Ctrl+Q',
  reloadView: 'Ctrl+R',
  reloadWindow: 'Ctrl+F5',
  prevWindow: 'Alt+Left',
  nextWindow: 'Alt+Right',
  devTool: 'Alt+Ctrl+I'
};

const pageUrl: PageUrlType = {
  page1: 'https://www.gankao.com/go2class',
  page2: 'https://www.baidu.com/'
};

export default class MenuBuilder {

  mainWindow: BrowserWindow;
  loadPageEvent: IpcMainEvent | undefined;
  changeStateEvent: IpcMainEvent | undefined;
  viewWindow: BrowserView | undefined | null;

  constructor(mainWindow: BrowserWindow) {
    this.mainWindow = mainWindow;
  }

  // 移除BrowserView
  removeViewWindow(): void {
    if (this.viewWindow) {
      this.mainWindow.removeBrowserView(this.viewWindow);
      this.viewWindow = null;
    }
  }

  maxWindow(): void {
    const { width, height } = screen.getPrimaryDisplay().workAreaSize;
    this.mainWindow.setBounds({
      width,
      height,
      x: 0,
      y: 0
    });
  }

  buildMenu(): Menu {
    if (process.env.NODE_ENV === 'development' || process.env.DEBUG_PROD === 'true') {
      this.setupDevelopmentEnvironment();
    }
    // 加载页面事件
    ipcMain.on('loadPage', (event: IpcMainEvent) => {
      if (this.mainWindow) {
        this.loadPageEvent = event;
      }
    });
    // 加载窗口相关事件
    ipcMain.on('loadWindow', (_event: IpcMainEvent, page: PageUrlNameType) => {
      if (this.mainWindow) {
        this.removeViewWindow();
        this.viewWindow = createView(this.mainWindow, pageUrl[page]);
        this.maxWindow();
        if (this.loadPageEvent){
          this.loadPageEvent.reply('loadPage-reply', 'home');
        }
      }
    });
    const template = this.buildDefaultTemplate();
    const menu = Menu.buildFromTemplate(template);
    Menu.setApplicationMenu(menu);
    return menu;
  }

  // 开发环境设置
  setupDevelopmentEnvironment(): void {
    this.mainWindow.webContents.on('context-menu', (_, props) => {
      const { x, y } = props;
      Menu.buildFromTemplate([
        {
          label: 'Inspect element',
          click: () => {
            this.mainWindow.webContents.inspectElement(x, y);
          }
        }
      ]).popup({ window: this.mainWindow });
    });
  }

  // win 用菜单
  buildDefaultTemplate() {
    const templateDefault = [
      {
        label: '&开始',
        submenu: [
          // {
          //   label: '主页',
          //   click: () => {
          //     if (this.loadPageEvent) {
          //       this.loadPageEvent.reply('loadPage-reply', 'home');
          //     }
          //     this.removeViewWindow();
          //   }
          // },
          {
            label: '创建远控',
            click: () => {
              if (this.loadPageEvent) {
                this.loadPageEvent.reply('loadPage-reply', 'qrcode');
              }
              this.removeViewWindow();
            }
          },
          {
            label: '&关闭应用',
            accelerator: acceleratorName.closeApp,
            click: () => {
              this.mainWindow.close();
            }
          }
        ]
      },
      {
        label: '&应用',
        submenu: [
          {
            label: '应用1',
            click: () => {
              this.removeViewWindow();
              if (this.mainWindow) {
                this.viewWindow = createView(this.mainWindow, pageUrl['page1']);
                this.maxWindow();
              }
            }
          },
          {
            label: '百度',
            click: () => {
              this.removeViewWindow();
              if (this.mainWindow) {
                this.viewWindow = createView(this.mainWindow);
                this.maxWindow();
              }
            }
          }
        ]
      },
      {
        label: '&应用操作',
        submenu: [
          {
            label: '&前进',
            accelerator: acceleratorName.nextWindow,
            click: () => {
              if (this.viewWindow) {
                this.viewWindow.webContents.goForward();
              }
            }
          },
          {
            label: '&后退',
            accelerator: acceleratorName.prevWindow,
            click: () => {
              if (this.viewWindow) {
                this.viewWindow.webContents.goBack();
              }
            }
          },
          {
            label: '&刷新',
            accelerator: acceleratorName.reloadWindow,
            click: () => {
              if (this.viewWindow) {
                this.viewWindow.webContents.reload();
              }
            }
          }
        ]
      },
      {
        label: '&视图',
        submenu: process.env.NODE_ENV === 'development' || process.env.DEBUG_PROD === 'true' ? [
            {
              label: '&重新加载',
              accelerator: acceleratorName.reloadView,
              click: () => {
                this.mainWindow.webContents.reload();
              }
            },
            {
              label: '&全屏',
              accelerator: acceleratorName.fullScreen,
              click: () => {
                this.mainWindow.setFullScreen(!this.mainWindow.isFullScreen());
              }
            },
            {
              label: '&开发工具',
              accelerator: acceleratorName.devTool,
              click: () => {
                this.mainWindow.webContents.toggleDevTools();
              }
            }
          ]
          :
          [
            {
              label: '&全屏',
              accelerator: acceleratorName.fullScreen,
              click: () => {
                this.mainWindow.setFullScreen(!this.mainWindow.isFullScreen());
              }
            }
          ]
      },
      {
        label: '帮助',
        submenu: [
          {
            label: '关于',
            click() {
              shell.openExternal('https://www.baidu.com');
            }
          },
          {
            label: '文档',
            click() {
              shell.openExternal('https://www.baidu.com');
            }
          },
          {
            label: '联系我们',
            click() {
              shell.openExternal('https://www.baidu.com');
            }
          }
        ]
      }
    ];

    return templateDefault;
  }
}
