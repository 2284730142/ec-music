import React  from 'react';
import { Home } from './home/home';
import { Error } from './error/error';
import { QRCodePage } from './qrcode/qrcode';

export const Switch = ({ exct, children }) => {
  // todo 404界面处理
  let result = <Error />;
  if (Array.isArray(children)) {
    result = children.map(child => child.props.page === exct ? (<React.Fragment children={child} />) : null).filter(t => t);
  } else {
    if (children.props.page === exct) result = <React.Fragment children={children} />;
  }
  if (Array.isArray(result) && result.length === 0) result = <Error />;
  return result;
};

export const Route = ({ page }) => {
  if (page === 'home') {
    return <Home />;
  }
  if (page === 'qrcode') {
    return <QRCodePage />;
  }
};
