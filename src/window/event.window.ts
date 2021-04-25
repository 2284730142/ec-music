import {BrowserWindow, IpcMainEvent, ipcRenderer} from "electron";

export declare type RenderMessageMethod = 'CLOSE_WINDOW' | 'MAX_WINDOW' | 'MIN_WINDOW';

export interface RenderMessageArgsType {
  method: RenderMessageMethod;
  data?: any;
}

export const ReceiveMessageFromRender = (window: BrowserWindow | null, _event: IpcMainEvent, data: RenderMessageArgsType) => {
  // 处理...
  console.log(data);
  if (window) {
    switch (data.method) {
      case "CLOSE_WINDOW":
        console.log('is on close window');
        window.close();
        break;
      // todo 做一个还原状态的window操作
      case "MAX_WINDOW":
        console.log('is on max window');
        window.maximize();
        break;
      case "MIN_WINDOW":
        console.log('is on min window');
        window.minimize();
        break;
      default:
        throw new Error();
    }
  }
}

export const SendMessageToWindow = (method: RenderMessageMethod, args?: any) => {
  ipcRenderer.send('render-message', {method, args});
}
