import React, {createContext} from 'react';
import {BrowserRouter, Switch, Route, Redirect} from 'react-router-dom';
import {ConfigProvider} from 'antd';
// global引入的样式放这
import './global.css';
import './antd.global.css';
// 路由下的相关页面
import {Home} from './pages/home/home';
import {Test} from './pages/test/test';
// import {Provider} from "./reducers/provider"
import {Provider} from "./reducers/providerContext"
const App = () => {

  return (
    <Provider>
      <ConfigProvider>
        <BrowserRouter>
          <Switch>
            <Route exact path='/'>
              <Home/>
            </Route>
            <Route exact path='/test'>
              <Test/>
            </Route>
            <Redirect to='/'/>
          </Switch>
        </BrowserRouter>
      </ConfigProvider>
    </Provider>
  );
};

export default App;
