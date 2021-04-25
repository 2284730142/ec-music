import React from 'react';
import {Col, Row} from 'antd';
import {useHistory} from 'react-router';
import {styles} from './home.style.js';
import {WindowComponent} from '../../components/Header/window.component';

export const Home = ({}) => {

  const history = useHistory();

  const goToDemo = () => {
    history.push('/demo');
  };

  return (<>
    <Row gutter={[0, 0]} style={styles.home_header} justify="space-between">
      {/* 左边 */}
      <Col></Col>
      {/* 右上角 */}
      <Col>
        <WindowComponent/>
      </Col>
    </Row>
  </>);
};
