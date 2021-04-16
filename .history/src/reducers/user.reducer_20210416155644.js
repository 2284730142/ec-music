import {useReducer} from 'react';
import { ACTIONS } from './action'

export const userState = () => {

  const ACTION = {
    userInfo: 'Collapse',
  };

  const action = (state, {type, payload}) => {
    switch (type) {
      case ACTION.COLLAPSE:
        return {...state, ...payload};
      default:
        throw new Error();
    }
  };

  const [state, dispatch] = useReducer(action, {
    collapse: true
  });

  return {state, dispatch, ACTION};
};
