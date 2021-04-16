import React, {createContext, useContext} from 'react';
// 小型聚合Store（Context方案替代）
import {useGlobalState} from './global.reducer';

export const AppContext = createContext(null);

export const Provider = ({children}) => {
  return (
    <AppContext.Provider value={{
      useGlobalState: useGlobalState()
    }}>
      {children}
    </AppContext.Provider>
  );
};
export const useApp = () => useContext(AppContext)
