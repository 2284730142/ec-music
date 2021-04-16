import React, {createContext} from 'react';
// 小型聚合Store（Context方案替代）
import {useGlobalState} from './global.reducer';

export const AppContext = createContext(null);

export const Provider = ({children}) => {
  return (
    <Context.Provider value={{
      useGlobalState: useGlobalState()
    }}>
      {children}
    </Context.Provider>
  );
};
