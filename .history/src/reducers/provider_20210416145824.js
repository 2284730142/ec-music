import React, {createContext} from 'react';
// 小型聚合Store（Context方案替代）
import {useGlobalState} from './global.reducer';
import Context from ""

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
