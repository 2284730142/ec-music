import React, {useContext, useEffect} from 'react';
import {Button} from 'antd';
import {useHistory} from 'react-router';
import {AppContext, useApp} from '../../reducers/provider';

const Other = () => {
  const { useGlobalState: {state} } = useApp()
  useEffect(() => {
    console.log(state);
  }, [state]);
  console.log(useApp(), "useApp")
  return (<div>{state.collapse ? '真的' : '假的'}</div>);
};

export const Home = ({}) => {

  const history = useHistory();
  const {useGlobalState: {state, dispatch, ACTION}} = useContext(AppContext);

  return (
    <div>
      {/* <Button onClick={() => {
        history.push('/test');
      }}>跳转</Button>
      <Button onClick={() => {
        dispatch({
          type: ACTION.COLLAPSE,
          payload: {
            collapse: !state.collapse
          }
        });
      }}>状态转换</Button>
      <Other/> */}
    </div>
  );
};
