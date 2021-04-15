import React, { useContext, useEffect, useState } from 'react';
import QRCode from 'qrcode.react';
import { styles } from './qrcode.css';
import { Spin } from 'antd';
import { GlobalContext } from '../../context/global';
import { QRCodeContext } from '../../context/qrcode';

export const QRCodePage = ({}) => {

  const { addressSDK, sessionSDK, loginSDK, mainSDKEvent } = useContext(GlobalContext);

  const [qrcode, setQRCode] = useState('');

  // 初始化
  useEffect(() => {
    // 测试环境数据
    loginSDK({
      openid: '619338623194',
      openkey: '3cb607aeb352971b8da0eada786a2b0c',
      mode: 0
    });
    mainSDKEvent('createDesktopsession', 'create');
  }, []);

  useEffect(() => {
    console.log(addressSDK, sessionSDK);
    if (addressSDK && sessionSDK) {
      setQRCode(JSON.stringify({
        address: addressSDK,
        session: sessionSDK
      }));
    }
  }, [addressSDK, sessionSDK]);

  return (
    <QRCodeContext.Provider value={{}}>
      <div style={styles.container}>
        <div style={styles.qrcodeWrapper}>
          <div style={styles.qrcode}>
            <Spin spinning={!qrcode}>
              <QRCode value={qrcode || ''} size={256} />
            </Spin>
          </div>
          <div style={styles.info}>
            使用软件的扫描二维码远程登录
          </div>
        </div>
      </div>
    </QRCodeContext.Provider>
  );
};
