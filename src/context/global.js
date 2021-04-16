import React from 'react';

export const GlobalContext = React.createContext({
  addressSDK: '',
  sessionSDK: '',
  loginSDK: ({ openid, openkey, mode }) => {
  },
  mainSDKEvent: (type, message) => {
  },
  setExct: () => {
  },
  init: false,
  setInit: () => {
  }
});
