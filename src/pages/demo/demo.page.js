import React, {useContext, useEffect, useState} from 'react';
import {Button, Col, Row, Spin} from 'antd';
import {AppContext} from '../../reducers/provider';
import {withAxios} from 'react-axios';
import {useHistory} from 'react-router';
import {getSomething} from '../../services/api/base.api';

const Other = () => {
  const {useGlobalState: {state}} = useContext(AppContext);
  useEffect(() => {
    console.log(state);
  }, [state]);
  return (<div>{state.collapse ? '真的' : '假的'}</div>);
};

// 接口调用方式withAxios，接收参数axios
export const DemoPage = withAxios((props) => {

  const {axios} = props;

  const history = useHistory();
  const {useGlobalState: {state, dispatch}, ACTION} = useContext(AppContext);

  const [loading, setLoading] = useState(false);
  const [data, setData] = useState();

  console.log(ACTION);
  // console.log(axios);
  console.log('props', props);
  // console.log('isLoading', axios.isLoading);

  return (
    <div>
      <Row>
        <Col span={24}>
          <Button onClick={() => history.goBack()}>返回主页</Button>
        </Col>
        <Col span={24}>
          <Row>
            <Col span={12}>
              <Button
                onClick={() => dispatch({
                  type: ACTION.COLLAPSE,
                  payload: {
                    collapse: !state.collapse
                  }
                })}>
                状态转换
              </Button>
            </Col>
            <Col>
              <Other/>
            </Col>
          </Row>
        </Col>
        <Col span={24}>
          <Row>
            <Col span={12}>
              <Button
                onClick={async () => {
                  setLoading(true);
                  const result = await axios(getSomething());
                  console.log('测试接口的结果：', result);
                  setData(result);
                  setLoading(false);
                }}>
                接口测试
              </Button>
            </Col>
            <Col span={6}>
              <Spin spinning={loading}/>
            </Col>
            <Col span={6}>
              data:{JSON.stringify(data ? data : '')}
            </Col>
          </Row>
        </Col>
      </Row>
    </div>
  );
});
