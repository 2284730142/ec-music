import React, { useEffect, useState } from 'react';
import slsdk from './sunloginsdk.node';
import { Route, Switch } from './pages/route';
import { ConfigProvider, message } from 'antd';
import './global.css';
import './antd.global.css';
import { GlobalContext } from './context/global';
import { ipcRenderer } from 'electron';

// 向日葵sdk的一些变量
const slClientInvalid = '0';
const slSessionInvalid = -1;
let slclient = slClientInvalid;
let desktopsession = slSessionInvalid;
let initslsdk = false;

const App = () => {

  const [init_slsdk, setInit_slsdk] = useState(true);
  const [address, setAddress] = useState('');
  const [session, setSession] = useState('');

  // 登录操作
  const loginSLS = ({ openid, openkey, mode }) => {
    if (slclient !== slClientInvalid) {
      if (mode === 0) {
        slsdk.clientLoginWithOpenID(slclient, openid, openkey, '', false);
      } else {
        slsdk.clientLoginWithLicense(slclient, openid, openkey);
      }
    }
  };

  // 向日葵事件
  const mainSLSEvent = (type, message) => {
    switch (type) {
      case 'createDesktopsession':
        message === 'create' ? createDesktopsession() : destroyDesktopsession();
        break;
    }
  };

  // 被控端事件回调
  const slclientCallback = (client, event) => {
    if (client === slclient) {
      if (event === 0) {
        console.log('连接服务器成功!!!');
      } else if (event === 1) {
        console.log('与服务器断开连接!!!');
      } else if (event === 2) {
        console.log('登陆服务器成功!!!');
        const address = slsdk.getClientAddress(slclient);
        console.log('address', address);
        setAddress(address);
      } else if (event === 3) {
        console.log('登陆服务器失败!!!');
      } else if (event === 4) {
        console.log('通道数已用完!!!');
      } else if (event === 5) {
        console.log('服务器检查通道数失败');
      }
    }
  };

  // 远程连接会话回调
  const slclientDesktopSessionCallback = (session, event) => {
    if (session === desktopsession) {
      if (event === 1) {
        console.log('桌面会话已连接!!!');
        slsdk.clientStartChat(slclient, desktopsession, false);
        ipcRenderer.send('loadWindow', 'page1');
      } else if (event === 2)
        console.log('桌面会话已断开!!!');
    }
  };

  // 创建会话
  const createDesktopsession = () => {
    if (slclient !== slClientInvalid) {
      if (desktopsession !== slSessionInvalid) {
        slsdk.destroyClientSession(slclient, desktopsession);
        desktopsession = slSessionInvalid;
      }
      desktopsession = slsdk.createClientSession(slclient, 0);
      console.log('桌面会话', desktopsession);
      if (desktopsession !== slSessionInvalid) {
        if (slsdk.setClientSessionOpt(slclient, desktopsession, 2, slclientDesktopSessionCallback, 0)) {
          console.log('创建远程会话成功!!!');
          const session = slsdk.getClientSessionName(slclient, desktopsession);
          console.log('session', session);
          setSession(session);
          // 监听当前会话是否已经连接还是未连接
        } else {
          console.log('设置远程会话回调失败!!!');
        }
      } else {
        console.log('创建远程会话失败!!!');
      }
    } else {
      console.log('无效的被控端实例!!!');
    }
  };

  // 销毁会话
  const destroyDesktopsession = () => {
    if (slclient !== slClientInvalid) {
      if (desktopsession !== slSessionInvalid) {
        slsdk.destroyClientSession(slclient, desktopsession);
        desktopsession = slSessionInvalid;
        console.log('销毁远程会话成功!!!');
        setSession('');
      }
    } else {
      console.log('无效的被控端实例!!!');
    }
  };

  // 初始化操作
  useEffect(() => {
    // 初始化向日葵SDK环境
    if (slsdk && slsdk.initialize()) {
      slclient = slsdk.createClient();
      if (slclient !== slClientInvalid) {
        slsdk.setClientCallback(slclient, slclientCallback);
        slsdk.openClientLog(slclient, './log');
        initslsdk = true;
      }
    }
    if (initslsdk) {
      console.log('初始化sdk成功！');
      setInit_slsdk(false);
    }
  }, []);

  const [init, setInit] = useState(true);
  const [exct, setExct] = useState('home');

  useEffect(() => {
    // 绑定主线程事件
    // 加载页面事件
    ipcRenderer.send('loadPage');
    ipcRenderer.on('loadPage-reply', (_event, args) => {
      setExct(args);
    });
  }, []);

  return (
    <GlobalContext.Provider value={{
      sessionSDK: session,
      addressSDK: address,
      loginSDK: loginSLS,
      mainSDKEvent: mainSLSEvent,
      setExct: setExct,
      init: init,
      setInit: setInit
    }}>
      <ConfigProvider>
        {
          init_slsdk ? (
            <div>正在初始化中</div>
          ) : (
            <Switch exct={exct}>
              <Route page='home' key='home' />
              <Route page='qrcode' key='qrcode' />
            </Switch>
          )
        }
      </ConfigProvider>
    </GlobalContext.Provider>
  );
};

export default App;
