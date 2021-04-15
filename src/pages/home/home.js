import React, { useContext, useEffect } from 'react';
import { Spin } from 'antd';
import { ipcRenderer } from 'electron';
import { GlobalContext } from '../../context/global';

export const Home = ({}) => {

  const { setExct, setInit, init } = useContext(GlobalContext);

  useEffect(() => {
    if (init) {
      setTimeout(() => {
        setInit(false);
        setExct('qrcode');
      }, 1000);
    }
  }, []);

  return init ? (<div style={{
    margin: '20px 0',
    marginBottom: '20px',
    padding: '30px 50px',
    textAlign: 'center',
    borderRadius: '4px'
  }}>
    <div>
      <Spin size='large' />
    </div>
    初始化中...
  </div>) : null;
};
