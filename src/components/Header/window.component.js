import React from 'react';
import {Col, Row} from 'antd';
import {MIcon} from '../MIcon/micon.component';
import {styles} from './header.style.js';
import {SendMessageToWindow} from '../../window/event.window';

export const WindowComponent = ({}) => {


  return (<>
    <Row gutter={[0, 0]} style={styles.header_window}>
      <Col style={styles.header_window_icon_wrapper} onClick={() => SendMessageToWindow('MIN_WINDOW')}>
        <MIcon icon="MIN_WINDOW" style={styles.header_window_icon}/>
      </Col>
      <Col style={styles.header_window_icon_wrapper} onClick={() => SendMessageToWindow('MAX_WINDOW')}>
        <MIcon icon="MAX_WINDOW" style={styles.header_window_icon}/>
      </Col>
      <Col style={styles.header_window_icon_wrapper} onClick={() => SendMessageToWindow('CLOSE_WINDOW')}>
        <MIcon icon="CLOSE_WINDOW" style={styles.header_window_icon}/>
      </Col>
    </Row>
  </>);
};
