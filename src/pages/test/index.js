import React, { forwardRef, useImperativeHandle, useState } from 'react';
import QRCode from 'qrcode.react';

export const Test = forwardRef(({ loginSDK, mainSDKEvent }, ref) => {

  const [form1, setForm1] = useState({
    openid: '619338623194',
    openkey: '3cb607aeb352971b8da0eada786a2b0c',
    mode: 0
  });
  const [form2, setForm2] = useState({
    address: '',
    session: '',
    sessiontype: 'createDesktopsession'
  });

  const handleChangeForm1 = (key, value) => {
    setForm1({
      ...form1,
      [key]: value
    });
  };

  const handleChangeForm2 = (key, value) => {
    setForm2({
      ...form2,
      [key]: value
    });
  };

  const createSession = (param) => {
    mainSDKEvent(form2.sessiontype, param);
  };

  const destroySession = (param) => {
    mainSDKEvent(form2.sessiontype, param);
  };

  useImperativeHandle(ref, () => ({
    handleChangeForm1,
    handleChangeForm2
  }));

  return (
    <div>
      <h4>登录demo</h4>
      <div>
        请输入要登录的OpenID信息或独立部署服务器的登陆密钥并选择登陆方式 <br />
        开发账号：
        <input style={{ width: '500px' }} value={form1.openid}
               onChange={(e) => handleChangeForm1('openid', e.target.value)} />
        <br />
        开发密码：
        <input style={{ width: '500px' }} value={form1.openkey}
               onChange={(e) => handleChangeForm1('openkey', e.target.value)} />
        <br />
        登陆方式：
        <label>
          <input
            name='logintype' type='radio'
            checked={form1.mode === 0}
            onChange={() => handleChangeForm1('mode', 0)} />
          OpenID
        </label>
        <label>
          <input
            name='logintype' type='radio'
            checked={form1.mode === 1}
            onChange={() => handleChangeForm1('mode', 1)} />
          独立服务器
        </label>
        <br />
        <button onClick={() => loginSDK({ ...form1 })}>登陆</button>
        <br /><br />
        连接地址：
        <input style={{ width: '500px' }} value={form2.address} readOnly />
        <br />
        连接会话：
        <input style={{ width: '500px' }} value={form2.session} readOnly />
        <br />
        会话类型:
        <label>
          <input
            name='sessiontype' type='radio'
            checked={form2.sessiontype === 'createDesktopsession'}
            onChange={() => handleChangeForm2('sessiontype', 'createDesktopsession')} />
          远程桌面
        </label>
        <br />
        <button onClick={() => createSession('create')}>创建会话</button>
        <button onClick={() => destroySession('delete')}>销毁会话</button>
      </div>
      <div>
        <h4>生成二维码</h4>
        <div>
          <QRCode
            size={256}
            value={JSON.stringify({ address: form2.address, session: form2.session })} />
        </div>
      </div>
    </div>
  );
});
