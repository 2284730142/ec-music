import React from 'react';
import {Button} from 'antd';
import {useHistory} from 'react-router';

export const Home = ({}) => {

  const history = useHistory();

  const goToDemo = () => {
    history.push('/demo');
  };

  return (
    <Button onClick={() => goToDemo()}>
      demo
    </Button>
  );
};
