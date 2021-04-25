import React, {useEffect} from 'react';
import {BrowserRouter, Switch, Route, Redirect} from 'react-router-dom';
import {ConfigProvider} from 'antd';
// reducer的react聚合模式
import {Provider as ReducerProvider} from './reducers/provider';
// 引入axios的react版本处理
import {AxiosProvider} from 'react-axios';
import axiosInstance from './services/axios.instance';
// global引入的样式放这
import './global.css';
import './antd.global.css';
// 路由下的相关页面
import {Home} from './pages/home/home.page';
import {DemoPage} from './pages/demo/demo.page';

const App = () => {
  useEffect(() => {
    console.log('项目初始化完了\n');
    console.log('请开始接下来的表演\n');
  }, []);
  return (
    <ReducerProvider>
      <AxiosProvider instance={axiosInstance}>
        <ConfigProvider>
          <BrowserRouter>
            <Switch>
              <Route exact path='/'>
                <Home/>
              </Route>
              <Route exact path='/demo'>
                <DemoPage/>
              </Route>
              <Redirect to='/'/>
            </Switch>
          </BrowserRouter>
        </ConfigProvider>
      </AxiosProvider>
    </ReducerProvider>
  );
};

export default App;
