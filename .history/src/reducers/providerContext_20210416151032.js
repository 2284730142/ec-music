import React, {createContext, useContext} from 'react';
// 小型聚合Store（Context方案替代）
import {useGlobalState} from './global.reducer';

const AppContext = createContext(null);

const Provider = ({children}) => {
  return (
    <AppContext.Provider value={{
      useGlobalState: useGlobalState()
    }}>
      {children}
    </AppContext.Provider>
  );
};
const useApp = () => useContext(AppContext)
export default {
  Provider,
  useApp
}
