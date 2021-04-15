import { BrowserView } from 'electron';

export const createView = (mainWindow, ipaddress = 'https://www.baidu.com/') => {
  const view = new BrowserView();
  mainWindow.setBrowserView(view);
  const [width, height] = mainWindow.getContentSize();
  view.setBounds({
    x: 0,
    y: 0,
    width: width,
    height: height
  });
  view.setAutoResize({ width: true, height: true });
  view.webContents.loadURL(ipaddress);
  // 开发调试栏
  // view.webContents.openDevTools();
  return view;
};
