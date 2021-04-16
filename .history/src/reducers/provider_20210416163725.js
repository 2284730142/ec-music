import React, {createContext, useContext} from 'react';
// 小型聚合Store（Context方案替代）
import {useGlobalState} from './global.reducer';
import {userState} from './user.reducer';
import { ACTION } from './action'

export const AppContext = createContext(null);

export const Provider = ({children}) => {
  return (
    <AppContext.Provider value={{
      useGlobalState: useGlobalState(),
      userInfo: userState(),
      ACTION: ACTION
    }}>
      {children}
    </AppContext.Provider>
  );
};
export const useApp = () => useContext(AppContext)