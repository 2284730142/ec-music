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
        break;
      case "MAX_WINDOW":
        break;
      case "MIN_WINDOW":
        break;
      default:
        throw new Error();
    }
  }
}

export const SendMessageToWindow = (method: RenderMessageMethod, args?: any) => {
  ipcRenderer.send('render-message', {method, args});
}
