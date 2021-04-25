import React from 'react';
import Icon from '@ant-design/icons';
import {CloseSVG} from './svg/close.svg';
import {MaxWindowSVG} from './svg/max-window.svg';
import {MinWindowSVG} from './svg/min-window.svg';

export const MIcon = ({icon, ...reset}) => {

  let component = null;

  switch (icon) {
    case 'CLOSE_WINDOW':
      component = CloseSVG;
      break;
    case 'MAX_WINDOW':
      component = MaxWindowSVG;
      break;
    case 'MIN_WINDOW':
      component = MinWindowSVG;
      break;
    default:
      throw new Error('没有这个图标啊！');
  }

  return component ? (<>
    <Icon component={component} {...reset}/>
  </>) : null;
};
