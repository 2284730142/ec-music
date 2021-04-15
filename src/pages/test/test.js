import React, {useContext} from 'react';
import {Button} from 'antd';
import {useHistory} from 'react-router';
import {AppContext} from '../../app';

export const Test = ({}) => {
  const history = useHistory();
  const {useGlobalState: {state}} = useContext(AppContext);
  console.log(state);
  return (
    <div>
      <Button onClick={() => {
        history.goBack();
      }}>返回</Button>
    </div>
  );
};
