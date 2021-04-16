import React, {createContext} from 'react';
// 小型聚合Store（Context方案替代）
import {useGlobalState} from './global.reducer';
import {userState} from './user.reducer';
import {ACTION} from './action';

export const AppContext = createContext(null);

export const Provider = ({children}) => {
  return (
    <AppContext.Provider value={{
      ACTION: ACTION,
      useGlobalState: useGlobalState(),
      userInfo: userState(),
    }}>
      {children}
    </AppContext.Provider>
  );
};
